/* ========================================
 *
 * 
 * This Code IS PROVIDED "AS IS" AND "WITH ALL FAULTS". EEForEveryone DISCLAIMS ALL OTHER WARRANTIES, EXPRESS OR IMPLIED, 
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

/*
 * 
 *  NOTE: Library Uses FreqCount Library, which counts on pin 5 & LOCKS OUT that timer/counter. Therefore, pins 3,9,10, and 11 cannot be used for PWM
 * Pin6 Can be used for PWM- at 980Hz.
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */

 #include <FreqCount.h>


  #define PWM_PIN 6
  #define PULSES_PER_REV 10

  uint32_t thismillis = millis(); //stores current ms value in main loop

  #define LOG_PRINT_INTERVAL 500 //Interval for Logging, ms
  uint32_t LOG_millis = 0;

  
  #define CTRL_TIME 100 //CTRL loop period, in ms
  uint32_t CTRL_millis = 0;

  unsigned long last_RPS;
  uint8_t PWM_set = 0;

  float CONT_TIMESTEP_S = (float)CTRL_TIME/1000.0;
  #define K_I 0.75
  #define K_P 1.0
  float last_error    = 0;
  float last_Iterm    = 0;
  float last_control  = 0;

  #define CLIP_PROTECTION_UINT32 2000000000 //max is 2147483647
  uint32_t ABS_DISTANCE_ROLLOVER_COUNT = 0; //Holds multiples of CLIP_PROTECTION_UINT32
  uint32_t ABS_DISTANCE = 0; //distance travelled, in 10ths of degrees.

void setup() {
  Serial.begin(115200);
  FreqCount.begin(CTRL_TIME); //Provide a count measurement every 1000 ms.

  pinMode(PWM_PIN, OUTPUT);
  analogWrite(PWM_PIN, PWM_set);

}

void loop() {

  bool SpeedPingPong = true;
  bool RunMotor = false;


  uint32_t DISTANCE_TARGET = 0; //how many deg/10 we want to travel
  int CTRL_SETPOINT_RPS = 11; //Set Target to 10 RPS (500 RPM)
  int MAX_RPS = 40; //Set Maximum Achievable RPS (2400RPM)
  
  

  while(1){
    thismillis = millis();
    if (FreqCount.available()) { //if a sample is ready
      unsigned long thiscount = FreqCount.read();
      ABS_DISTANCE = ABS_DISTANCE + (thiscount*(3600/PULSES_PER_REV)); //Add the absolute distance, in tenths of degrees
      if(ABS_DISTANCE>CLIP_PROTECTION_UINT32){ //overflow protection
        ABS_DISTANCE = ABS_DISTANCE-CLIP_PROTECTION_UINT32;
        ABS_DISTANCE_ROLLOVER_COUNT = ABS_DISTANCE_ROLLOVER_COUNT+1;
      }

      
      last_RPS = (thiscount  *(1000/CTRL_TIME))/PULSES_PER_REV; //Divide by number of windows per revolution, compensate for Sample times different than once per second
      
    }


    if(thismillis > (LOG_millis+(LOG_PRINT_INTERVAL-1))){ //RUN LOG over Serial!
      Serial.print(DISTANCE_TARGET);
      Serial.print(" ");
      Serial.println(ABS_DISTANCE);
      //Serial.print(" ");
    

      //#define DETAILED_REPORT 1

      #ifdef DETAILED_REPORT
        Serial.println("=====================");
        Serial.print("Distance Setpoint: "); Serial.print(DISTANCE_TARGET); Serial.println(" DEG/10");
        Serial.print("Distance Travelled: "); Serial.print(ABS_DISTANCE); Serial.println(" DEG/10");
        Serial.print("Speed (RPS): "); Serial.println(last_RPS); //print the revs per second.
        Serial.print("Last Setpoint: "); Serial.println(last_Iterm); //print the pulses this second.
        Serial.print("PWM Set: "); Serial.println(PWM_set); //print the pulses this second.
        Serial.print("Last Error: "); Serial.println(last_error); //print the pulses this second.
        Serial.print("Last I Term: "); Serial.println(last_Iterm); //print the pulses this second.
        Serial.print("\nCTRL Timestep: "); Serial.println(CONT_TIMESTEP_S); //print the pulses this second.
        Serial.print("Distance Rollover Count: "); Serial.println(ABS_DISTANCE_ROLLOVER_COUNT);
        
      #endif
      
      LOG_millis = thismillis;
    }else if(LOG_millis > thismillis){ //handle overflow
      LOG_millis = thismillis;
    }


    if(Serial.available()){
      if( SpeedPingPong){
        SpeedPingPong = false;
        CTRL_SETPOINT_RPS = 2;
      }else{
        SpeedPingPong = true;
        CTRL_SETPOINT_RPS = 12;
      }
      
      while(Serial.available()){
        DISTANCE_TARGET = DISTANCE_TARGET + (3600*4); //Add four revolution to the distance target!
        Serial.read();
      }
    }



//SIMPLE SPEED REGULATION!!
    if((DISTANCE_TARGET > ABS_DISTANCE)  && RunMotor == false){ //if the motor needs to move, and we're off!
      ControlLoop_Reset(); //Reset Control Loop!
      RunMotor = true;
    }
    else if((DISTANCE_TARGET <= ABS_DISTANCE) && RunMotor == true){ //If we've reached the setpoint!
      ControlLoop_Reset(); //Reset Control Loop & Turn off Motor!
      RunMotor = false;
    }
      
    


   if( RunMotor){
    
      if(thismillis > (CTRL_millis+(CTRL_TIME-1))){ //RUN CONTROL LOOP!
    

        PWM_set = ControlLoop( CTRL_SETPOINT_RPS,  last_RPS, MAX_RPS)*255; //CTRL is scaled to 1, multiply by 255 for PWM!
        analogWrite(PWM_PIN, PWM_set); //update PWM pin


        if(thismillis > (CTRL_millis+(CTRL_TIME*2))){ //If the CTRL_LOOP Is RUNNING BEHIND!!!
          Serial.println("\n\n========================WARN========================");
          Serial.println("==         CTRL LOOP IS FALLING BEHIND!         ==");
          Serial.println("== REDUCE MATH BURDEN OR USE MORE POWERFUL MCU! ==");
          Serial.println("========================WARN========================\n");
        }
        
        CTRL_millis = CTRL_millis+CTRL_TIME; // Avoid Accumulating time Error
      }else if(thismillis < CTRL_millis){ //handle overflow
        CTRL_millis = thismillis;
      }
    }
  }

}


void ControlLoop_Reset(){
  last_error    = 0;
  last_Iterm    = 0;
  last_control  = 0;
  PWM_set = 0;
  CTRL_millis = thismillis;
  analogWrite(PWM_PIN, PWM_set); //update PWM pin
}

float ControlLoop(float setpoint, float measurement, float MAX_MEASUREMENT){

  float error = setpoint - measurement; //Negative number == too High!!
  float error_scaled = error / MAX_MEASUREMENT;

  float control_out = 0;
  
  //    //============= P CONTROLLER ===================//
  //      control_out = error_scaled * K_P;
  //    //============= P CONTROLLER ===================//
  //
  //
      //============= PI CONTROLLER ===================//
      //                   P                                          
        control_out = (error_scaled * K_P); //Save P Term Output
        float thisIterm = ((((error_scaled+last_error)/2 * K_I) * CONT_TIMESTEP_S) + last_Iterm); // I - Trapezoidal approx
        control_out = control_out + thisIterm; //Add I term portion to P term
      //============= PI CONTROLLER ===================//
  //
//          //============= HYSTERETIC CONTROLLER ===================//
//        if(error > 20 ){
//          error = 20;
//        }else if(error < -20 ){
//          error = -20;
//        }
//  
//        if(error > 0.5 ){ //error is big enough to do something!
//          control_out = last_control + 0.01;
//        }else if(error < -0.5 ) {
//          control_out = last_control - 0.01;
//        }else{
//          control_out = last_control;
//        }
//      //============= HYSTERETIC CONTROLLER ===================//
  
  
  
  //TEST
  //    control_out = 1; //set to max!


 //================= ANTI-WINDUP & CACHE OLD VALUES! ==============//  
  if(control_out > 1.0){ //Antiwindup - CTRL!
    control_out = 1;
  }else if (control_out < 0.0){
    control_out = 0;
  }

  if(thisIterm > 1.0){ //Antiwindup - I Term!
    thisIterm = 1;
  }else if (thisIterm < -1.0){
    thisIterm = -1.0;
  }

  last_error = error_scaled;
  last_Iterm = thisIterm;
  last_control = control_out;

  return(control_out);
}
