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

//#TODO: Handle Position Rollover Better!
//#TODO: Wave Shaping and better tuning of control loops

#include "position_ctrl.h"
#include "math.h"


position_ctrl::position_ctrl(int motA, int motB, int encA, int encB, uint8_t PulsePerRotation, uint8_t GearRatio):mySpeedCtrl(encA, encB, PulsePerRotation, GearRatio, motA,motB) { //constructor, pass in 2 pwm pins, plus 
  TARGET_position = 0;
  trap_vTarget = 3600; //set to 1 rot/second
  maxSpeed = 7200; //set to 2 rot/second
  maxAccel = 3600; //set to 1 rot/second^2
  moving = false;


    //==== Control Loop Parameters ==== 
  _POS_SCALLER = 3600; //All coefficients Scaled to ERR1 = 1 Rotation
  K_P = 12.0;
  K_I = 1;
  last_error = 0;
  last_Iterm = 0;
  last_control = 0;
  last_CTRL_millis = 0;


  //==== Wave Shaping Parameters ====

  trap_sign = 1;
  trap_decel_thresh = 0; //Threshold to start deceleration
  POS_ThisMoveType = 0; //set to no ramp by default
  trap_move_length = 0;
  trap_distance_increment_last = 0; //value to add to speed every control cycle - NEED TO SCALE BY CONTROL TIME!
  trap_vmin = 0; //when this speed is reached, Switch to PI!
  trap_vmax = 0;
  trap_accel = 0;
  trap_decel_thresh = 0; //When this position is reached, start decel!
  trap_start_position = 0;
  trap_finalPosition = 0;
  trap_state = 0; //start at state 0, accel
}

void position_ctrl::SetMaxSpeed(uint16_t NewSpeed){
  maxSpeed = NewSpeed;
}
void position_ctrl::SetMaxAccel(uint16_t NewAccel){
  maxAccel = NewAccel;
}
bool position_ctrl::Done(){
  return moving;
}

void position_ctrl::printReport(){ //prints control stuff
  
  Serial.print(TARGET_position);Serial.print(","); //Variable 1: This Position Target
  Serial.print(trap_finalPosition);Serial.print(","); //Variable 2: Target Position
  Serial.print(trap_state);Serial.print(","); //Variable 3: Trap State
  Serial.print(mySpeedCtrl.GetPos());Serial.print(","); //Variable 4: Real Position
  Serial.println(last_control* maxSpeed); //Final Variable, Requested Speed
}

void position_ctrl::SetTgtSpeed(uint16_t NewSpeed){ //Target Speed for waveshaping, In tenths of Degrees per second.
  trap_vTarget = NewSpeed; //set to new speed
}

void position_ctrl::SpeedPI(float newP, float newI){ //set P & I used for speed
  mySpeedCtrl.SetPI(newP, newI); //set P & I
}
void position_ctrl::PositionPI(float newP, float newI){ //set P & I used for position 
  K_P = newP;
  K_I = newI;
}

void position_ctrl::Go(long NewPosition, uint8_t ramptype){
  
  switch(ramptype){
    case POS_RAMPTYPE_NONE:
      TARGET_position = NewPosition;
      POS_ThisMoveType = POS_RAMPTYPE_NONE; //simple PI by default
    break;

    
    case POS_RAMPTYPE_TRAP:
      trap_finalPosition = NewPosition; //store new target position
      TARGET_position = mySpeedCtrl.GetPos(); //Don't move right away...
      trap_start_position = TARGET_position; //Store starting position
      trap_move_length = NewPosition - mySpeedCtrl.GetPos(); //positive = forward motion (tenths of deg/s
      if(trap_move_length > 0L){
        trap_sign = 1L;
      }else{
        trap_sign = -1L;
      }
      trap_vmax = trap_vTarget * trap_sign; //maximum speed
      trap_vmin = trap_vmax / 5.0; //Make Final Speed 20% of travel speed (% full speed)
      trap_accel = maxAccel * trap_sign; //Acceleration
      trap_distance_increment_last = 0; //Last Position
      
      long trap_decel_distance = sq(trap_vTarget-abs(trap_vmin))/(25*maxAccel+1); //Distance covered during triangular nonsense (deltaSpeed^2/(2*acceleration)) assume we reach maxspeed //TODO: This is probably where weird math errors will occur. Big numbers!!!

      if(trap_decel_distance > abs(trap_move_length)/2){ //Clip absurd values of distance
        trap_decel_distance = abs(trap_move_length)/2; 
      }
      
      trap_decel_thresh = trap_finalPosition - (trap_decel_distance*trap_sign); //used for decel decision
      
      trap_state = 0; //start at state 0, accel
      POS_ThisMoveType = POS_RAMPTYPE_TRAP; //Don't use Simple PI!


      /*Serial.print("\ntrap_vmax : ");Serial.println(trap_vmax);
      Serial.print("trap_decel_distance : ");Serial.println(trap_decel_distance);
      Serial.print("decel_thresh : ");Serial.println(trap_decel_thresh);
      Serial.print("TARGET_position : ");Serial.println(trap_finalPosition);
      Serial.print("trap_distance_increment_last : ");Serial.println(trap_distance_increment_last);
      Serial.print("trap_accel : ");Serial.println(trap_accel);
      Serial.print("trap_state : ");Serial.println(trap_state);*/

      
    break;
    
    case POS_RAMPTYPE_S:

    break;
    default:
      //TODO: Something!!
    break;
    
  }
  //Serial.println("Got new Position!");
}



void  position_ctrl::resetCompensator(){
  last_error = 0;
  last_Iterm = 0;
  last_control = 0;
  mySpeedCtrl.SetSpeed(0); //Turn off Motor!
}

int position_ctrl::Run(){

    float elapsed_Sec = (float)(millis() - last_CTRL_millis)/1000.0;
    last_CTRL_millis = millis();

    float error = mySpeedCtrl.GetPos() - TARGET_position;; //Negative number == too High!!
    if(error > (float)_POS_SCALLER){ //Clip Error that is too big!
      error = (float)_POS_SCALLER;
    }else if(error < ((float)_POS_SCALLER * -1)){
      error = ((float)_POS_SCALLER * -1);
    }
    
    float error_scaled = (error *-1) / (float)_POS_SCALLER; //scale error from range 0 -> 1
  
    float control_out = 0;

    /*Serial.print("POS_ThisMoveType : ");Serial.println(POS_ThisMoveType);
    Serial.print("trap_state : ");Serial.println(trap_state);*/

    switch (POS_ThisMoveType) { //DO: Wave-Shaping of different types        
      case POS_RAMPTYPE_TRAP:
        if(trap_state == 0){ //Acceleration
          
          TARGET_position = TARGET_position + trap_distance_increment_last; //adjust position target
          trap_distance_increment_last = trap_distance_increment_last + (trap_accel*elapsed_Sec); //Add progressively more distance to the target
          
          if((trap_sign > 0L && trap_distance_increment_last > (trap_vmax*elapsed_Sec))||(trap_sign < 0L && trap_distance_increment_last < (trap_vmax*elapsed_Sec))){ // If we have achieved the target speed
            //Serial.println("Const Speed State!");
            trap_state = 1; //Go to Constant Speed state
          }else if((trap_sign > 0L && TARGET_position > trap_start_position+trap_move_length/2)||(trap_sign < 0L && TARGET_position < trap_start_position+trap_move_length/2)){ //Half the move distance has been travelled
            //Serial.println("Decel State!");
            trap_state = 2; //Go to Decel state
          }
          
        }else if(trap_state == 1){ //Constant Speed
          TARGET_position = TARGET_position + trap_distance_increment_last; //adjust position target (constant speed
          
          if((trap_sign > 0L &&  TARGET_position > trap_decel_thresh)||(trap_sign < 0L &&  TARGET_position < trap_decel_thresh)){
            trap_state = 2; //Go to Decel State
          }
          
        }else if(trap_state == 2){ //Decel
          TARGET_position = TARGET_position + trap_distance_increment_last; //adjust position target

          if((trap_sign > 0L && trap_distance_increment_last > (trap_vmin*elapsed_Sec))||(trap_sign < 0L && trap_distance_increment_last < (trap_vmin*elapsed_Sec))){ //Don't go below minimum speed
            trap_distance_increment_last = trap_distance_increment_last - (trap_accel*elapsed_Sec); //Add progressively more distance to the target
          }
          
          if((trap_sign > 0L && TARGET_position > trap_finalPosition-10)||(trap_sign < 0L && TARGET_position < trap_finalPosition+10)){
            trap_state = 3; //Hand over to PI - wave shaping complete!
          }
          
        }else{ //Simple Closed Loop Control, Target Reached!
          TARGET_position = trap_finalPosition; //Set to final position
          POS_ThisMoveType = POS_RAMPTYPE_NONE;
        }
        
        break;


      default:
        //TODO: Something!?!?
        break;
    }


    //============= PI CONTROLLER ===================//                                        
    control_out = (error_scaled * K_P); //Save P Term Output
    float thisIterm = ((((error_scaled+last_error)/2 * K_I) * elapsed_Sec) + last_Iterm); // I - Trapezoidal approx
    control_out = control_out + thisIterm; //Add I term portion to P term
    //============= PI CONTROLLER ===================//

   //================= ANTI-WINDUP & CACHE OLD VALUES! ==============//  
  
    if(thisIterm > 1.0){ //Antiwindup - I Term!
      thisIterm = 1;
    }else if (thisIterm < -1.0){
      thisIterm = -1.0;
    }
    last_Iterm = thisIterm;


  if(control_out > 1.0){ //Clip CTRL out!
    control_out = 1;
  }else if (control_out < -1.0){
    control_out = -1.0;
  }
        
  last_error = error_scaled;
  last_control = control_out;
  mySpeedCtrl.SetSpeed(control_out * maxSpeed);

  if (control_out != 0){
    moving == true;
  }else{
    moving == false;
  }
  
  return (mySpeedCtrl.Run()); //Pass through SpeedCtrl Pass/Fail Code
}


//========================================================================================//
//========================================================================================//
//============== AUTOTUNING ALGORITHM ====================================================//
//========================================================================================//
//========================================================================================//

uint32_t position_ctrl::TunePI_speed(float pterm, float iterm, uint32_t periodMS){ //Attempt Unit Step Response with Provided I, and P. Returns Quality Factor. (Upper 16 = mag. overshoot; lower 16 = response time)
  uint32_t result = mySpeedCtrl.TunePI(pterm, iterm, periodMS);
  mySpeedCtrl.ResetPos(); //return positions to zero.
  return(result);
}

uint32_t position_ctrl::TunePI_position(float pterm, float iterm, uint32_t periodMS){ //Attempt Unit Step Response with Provided I, and P. Returns Quality Factor. (Upper 16 = mag. overshoot; lower 16 = response time)
    //Serial.println(" position_ctrl::TunePI Start!");
  float overshoot = 0;
  float last5err[5];
  uint16_t errIndex = 0;
  bool canbedone = false;
  bool isdone = false;

  float cache_I = K_I;
  float cache_p = K_P;
  uint16_t cache_maxSpeed = maxSpeed;

  bool capture_err = false;
  float maxError = 654321; //set to a garbage value - show if it never triggered
  uint32_t settling = 0;

  float DONE_THRESH = 20; //sum error is > 20/5 = (4 deg) (1% error)
  maxSpeed = 3600; //Set max speed to 1 rot/s
  resetCompensator(); //turn off position controller.
  mySpeedCtrl.resetCompensator(); //turn off speed controller
  delay(1000); //wait 1000ms for the motor to settle.
  K_I = iterm;
  K_P = pterm;

    /*Serial.print("ThisPos: ");Serial.println(mySpeedCtrl.GetPos());
    Serial.print("Target : ");Serial.println(TARGET_position);*/
  
  TARGET_position = mySpeedCtrl.GetPos() + 3600L; //Set to 1 Rotation for tuning
  uint32_t oldmillis = millis();
  
    /*Serial.print("ThisPos: ");Serial.println(mySpeedCtrl.GetPos());
    Serial.print("Target : ");Serial.println(TARGET_position);*/

  //Serial.println(" speed_ctrl::TunePI Enter While Loop...");

    uint32_t tune_fail_ms = millis() + (10000); //If it takes more than 10s to settle... flag as Fail!

    if(tune_fail_ms < millis()){ // rollover event!
      tune_fail_ms = 10000; //Allow fail to last a little longer... makes the math easy.
    }
    
  //DO THE TEST!!!
  while(isdone == false){
    uint32_t tthiss_ms = millis();
    
    if(tthiss_ms > (oldmillis + periodMS)){ //time to run the loop
      Run();
      
      /*Serial.print("ThisPos: ");Serial.println(mySpeedCtrl.GetPos());
      Serial.print("Target : ");Serial.println(TARGET_position);*/
      
      float this_error = last_error* ((float)_POS_SCALLER/10.0); //Unscale position Error so it's in Degrees
      if(this_error < 0){
        this_error = this_error * -1;
      } //Ensure this_error is always positive!
      
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
          maxError = ERR_SUM/5; //report final error
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
  
  resetCompensator(); //turn off position controller.
  mySpeedCtrl.resetCompensator(); //turn off speed controller
  delay(250); //wait 250ms for the motor to settle.


  //GENERATE METRICS
  uint32_t output = 0;

  output = (settling & 0x0000FFFF); //Put Settling time in lower 16 bits
  if(maxError < 65535){
    output = output + ((uint32_t)maxError << 16); //Add MaxError
  }else{
    output = output + (65534 << 16); //Add clipped value-1
  }

  //RESET COMPENSATOR to original values
  K_I = cache_I;
  K_P = cache_p;
  maxSpeed = cache_maxSpeed;
  resetCompensator();
  return(output); 
}

  
