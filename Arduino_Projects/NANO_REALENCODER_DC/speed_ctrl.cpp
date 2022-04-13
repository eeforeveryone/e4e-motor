/* ========================================
 *
 * 
 * This CodeIS PROVIDED "AS IS" AND "WITH ALL FAULTS". EEForEveryone DISCLAIMS ALL OTHER WARRANTIES, EXPRESS OR IMPLIED, 
 * INCLUDING BUT NOT LIMITED TO, ANY IMPLIED WARRIENTIS OR MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. 
 * This code is provided for EDUCATIONAL PURPOSES ONLY.
 * EEforEveryone may make changes to specifications and implementation details at any time, without notice. 
 * EEforEveryone does not endorce the software described here as "Safe" or "Suitable" for any particular purpose or application. 
 * The design information on any Web Site or Materials is uncontrolled and subject to change without notice. 
 * Do not create or finalize a product with this information.
 *
 *
 *
 * ========================================
*/

// speed_ctrl.cpp - Controls a Motor Speed with encoder
#include "speed_ctrl.h"
#include <Encoder.h>

//#TODO: Handle Negative Encoder Values!!!
//#TODO: AutoTuning!!!

speed_ctrl::speed_ctrl(int pinA, int pinB, uint8_t PulsePerRotation, uint8_t GearRatio, int MotA, int MotB):myEnc(pinA,pinB),mymotor(MotA, MotB, true) { //constructor, pass in 2 pwm pins, plus 
  pin1 = pinA;
  pin2 = pinB;

  ENC_compensation_factor = PulsePerRotation*GearRatio; //Converts from encoder pulses to Rotations



  this_speed = 0;
  myEnc.write(0);
  old_rawposition = 0;
  ENC_position = 0;

  last_SPEED_millis = millis();
  last_CTRL_millis = millis();



  //==== Control Loop Parameters ==== 
  TARGET_SPEED = 0;
  _MAX_SPEED = 36000; //600RPM = 10RPS = 3600 Degree Per Second = 36000 Tenths of Degrees per Second
  K_P = 10.0;
  K_I = 15.0;
  last_error = 0;
  last_Iterm = 0;
  last_control = 0;

}

void speed_ctrl::SetSpeed(long NewSpeed){ //Target Speed, In tenths of Degrees per second.
  TARGET_SPEED = NewSpeed;
}

void speed_ctrl::SetPI(float newP, float newI){ //set P & I
  K_P = newP;
  K_I = newI;
}

uint32_t speed_ctrl::MeasureSpeed(){
  uint32_t elapsed_ms = millis() - last_SPEED_millis;
  last_SPEED_millis = millis();
  long thisPos = myEnc.read();
  long Distance_RawCounts = thisPos - old_rawposition;
  old_rawposition = thisPos;

  if(thisPos > RAW_ENC_OVERFLOW){ //Correct Overflow
    myEnc.write(thisPos-RAW_ENC_OVERFLOW);
    old_rawposition = thisPos-RAW_ENC_OVERFLOW;
    //Serial.println("Overflow");
    
  }else if(thisPos < RAW_ENC_OVERFLOW*-1){ //Correct Underflow
    myEnc.write(thisPos+RAW_ENC_OVERFLOW);
    old_rawposition = thisPos+RAW_ENC_OVERFLOW;
    //Serial.println("Underflow");
  }


  long ENC_pos_delta_tenths = Distance_RawCounts*3600L/ENC_compensation_factor; //Assuming there's no weird math glitches... this should provide the delta in tenths of degrees.
  
    ENC_position += ENC_pos_delta_tenths;
    this_speed = (ENC_pos_delta_tenths*1000L)/(long)elapsed_ms;

    /*Serial.print("\n Distance_RawCounts:");Serial.println(Distance_RawCounts);
    Serial.print("ENC_pos_delta_tenths:");Serial.println(ENC_pos_delta_tenths);
    Serial.print("ENC_position:");Serial.println(ENC_position);
    Serial.print("this_speed:");Serial.println(this_speed);*/
    

    return(elapsed_ms); // return elapsed ms since last call
}

long speed_ctrl::GetSpeed(){ //returns last measured speed, in 10ths of degrees per second.
    return this_speed;
}

long speed_ctrl::GetPos(){ //returns last position, in 10ths of degrees.
  return ENC_position;
}

void speed_ctrl::ResetPos(){
  ENC_position = 0L; //set encoder position to 0
  old_rawposition = 0L;
  myEnc.write(0); //Set encoder to 0
}

uint32_t speed_ctrl::TunePI(float pterm, float iterm, uint32_t periodMS){ //Attempt Unit Step Response with Provided I, and P. Returns Quality Factor. (Upper 16 = mag. overshoot; lower 16 = response time)

  //Serial.println(" speed_ctrl::TunePI Start!");
  float overshoot = 0;
  float last5err[5];
  uint16_t errIndex = 0;
  bool canbedone = false;
  bool isdone = false;

  float cache_I = K_I;
  float cache_p = K_P;

  bool capture_err = false;
  float maxError = 654321; //set to a garbage value - show if it never triggered
  uint32_t settling = 0;
  
  TARGET_SPEED = 0L;

  float DONE_THRESH = 20; //sum error is > 20/5 = (4 deg per s) (1% error)

  resetCompensator(); //turn off comp.
  delay(1000); //wait 1000ms for the motor to settle.
  K_I = iterm;
  K_P = pterm;
  TARGET_SPEED = 3600; //Set to 1 Rotation/s for tuning
  uint32_t oldmillis = millis();

  //Serial.println(" speed_ctrl::TunePI Enter While Loop...");

    uint32_t tune_fail_ms = millis() + (4000); //If it takes more than 4s to settle... flag as Fail!

    if(tune_fail_ms < millis()){ // rollover event!
      tune_fail_ms = 4000; //Allow fail to last a little longer... makes the math easy.
    }
    
  //DO THE TEST!!!
  while(isdone == false){
    uint32_t tthiss_ms = millis();
    
    if(tthiss_ms > (oldmillis + periodMS)){ //time to run the loop
      runPI();

      if(this_speed >= TARGET_SPEED){
        capture_err = true;
        maxError = 0;
      }
      
      float this_error = last_error* ((float)_MAX_SPEED/10); //Unscale Speed Error so it's in Deg/s
      if(this_error < 0){
        this_error = this_error * -1;
      } //Ensure this_error is always positive!
      
      if(capture_err){
        if(this_error > maxError){
          maxError = this_error;
        }
      }
      settling++; //incrememnt settling time counter! (1 count = 1 control loop time

        last5err[errIndex++] = this_error; //pass in error, then increment
      if(errIndex > 4){ //reset overflow
        errIndex = 0;
        canbedone = true;
      }
  
  
      if(canbedone){ //if we've filled the whole error buffer
        float ERR_SUM = 0;
        for(int i = 0; i<5; i++){
          ERR_SUM += last5err[i];
        }
        //Serial.print("Err: ");Serial.println(ERR_SUM);
        if(ERR_SUM < DONE_THRESH){
          isdone = true;
        }
      }

      
      oldmillis = oldmillis + periodMS; //increment Control Loop!
    }

    if(tthiss_ms > tune_fail_ms){ //check for timeout!
      isdone = true; //Abort test
      maxError = 654321;
    }

  }
  //END TEST
  
  resetCompensator(); //turn off comp.
  delay(250); //wait 250ms for the motor to settle.
  TARGET_SPEED = 0L;


  //GENERATE METRICS
  uint32_t output = 0;

  output = (settling & 0x0000FFFF); //Put Settling time in lower 16 bits
  if(maxError < 65535){
    output = output + ((uint32_t)maxError << 16); //Add MaxError
  }else{
    output = output + (65534 << 16); //Add clipped value-1
  }

  //RESET COMPENSATOR to original values
  TARGET_SPEED = 0;
  K_I = cache_I;
  K_P = cache_p;
  resetCompensator();
  return(output); 
}


void  speed_ctrl::resetCompensator(){
  last_error = 0;
  last_Iterm = 0;
  last_control = 0;
  mymotor.SetSpeed(0); //Turn off Motor!
}

void speed_ctrl::runPI(){
  //Serial.println(" speed_ctrl::TunePI Enter runPI...");
  float elapsed_Sec = (float)MeasureSpeed()/1000.0; //This should be a constant!!!
  //TODO: Error if timing is not constant enough!!

  float error = TARGET_SPEED - this_speed; //Negative number == too High!!
  float error_scaled = error / (float)_MAX_SPEED;

  float control_out = 0;
  
      //============= PI CONTROLLER ===================//
      //                   P                                          
        control_out = (error_scaled * K_P); //Save P Term Output
        float thisIterm = ((((error_scaled+last_error)/2 * K_I) * elapsed_Sec) + last_Iterm); // I - Trapezoidal approx
        control_out = control_out + thisIterm; //Add I term portion to P term
      //============= PI CONTROLLER ===================//

  if(control_out > 1.0){ //Antiwindup - CTRL!
    control_out = 1;
  }else if (control_out < -1.0){
    control_out = -1.0;
  }

  if(thisIterm > 1.0){ //Antiwindup - I Term!
    thisIterm = 1;
  }else if (thisIterm < -1.0){
    thisIterm = -1.0;
  }

  last_error = error_scaled;
  last_Iterm = thisIterm;
  last_control = control_out;


    /*Serial.print("\nIterm:");Serial.println(thisIterm);
    Serial.print("error_scaled:");Serial.println(error_scaled);
    Serial.print("control_out:");Serial.println(control_out);
    Serial.print("elapsed_Sec:");Serial.println(elapsed_Sec);*/

    mymotor.SetSpeed(last_control*255); //Set the Speed!
  
}


int speed_ctrl::Run(){
    runPI();

    return (1); //Return 1 if good, return -1 if timing error
}


// RAW_ENC_OVERFLOW
