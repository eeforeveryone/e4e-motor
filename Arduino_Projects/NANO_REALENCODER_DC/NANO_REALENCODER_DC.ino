/* ========================================
 *
 * DC Motor Encoder
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

#include "position_ctrl.h" //include our speed control library


#define ENC_A 2
#define ENC_B 3
#define PPR 48 //Might be 12 or 48?
#define GEAR_RATIO 45 //45 Encoder Revolutions to 1 Output Revolution

#define MOTOR_A 5 //Use 980Hz PWM
#define MOTOR_B 6 //Use 980Hz PWM



position_ctrl MOT(MOTOR_A, MOTOR_B, ENC_B, ENC_A, PPR, GEAR_RATIO);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  Serial.println("Boot!\n");
  delay(500);


  //Tune Control Loop:
  //autotune(3.0, 0.25, 4, 7.0, 0.5, 4); //(P_init, P_increment, P_numSteps, I_init, I_increment, I_numSteps)
  //while(1); //WAIT FOREVER

  MOT.SpeedPI(3.25, 8.5); //set PI to best value from autotuning
  MOT.PositionPI(13.0, 0.0); //set PI to best value from autotuning
  MOT.SetMaxAccel(100); //set accel to 100 rot/s^2
  MOT.SetTgtSpeed(3600); //set target speed to 0.5rps (for wave shaping
  MOT.SetMaxSpeed(7200); //set max speed to 2RPS (4s period)


}

void loop() {
  uint32_t oldMillis = millis();
  uint32_t printMillis = millis();
  uint32_t stepMillis = millis;
  #define STEPINTERVAL 15000

  long thisPOS = 0;

  int counter = 0;
  delay(1000);

  Serial.println("In Main Loop!");

  long thisincrement = 2L;

  while(1){

    if(millis() > oldMillis+50){
      MOT.Run(); //run the control loops!
      oldMillis += 50;
    }


    if(millis() > printMillis+250){ //Export Speed every 250ms
      MOT.printReport();
      printMillis += 500;
    }

    if(millis() > stepMillis+STEPINTERVAL){ //Export Speed every 500ms
      thisPOS = thisPOS - 3600L*thisincrement; //add two rotation
      MOT.Go(thisPOS, POS_RAMPTYPE_TRAP); //go to the specified position, in deg/10 - Trapezoidal Ramp  POS_RAMPTYPE_TRAP

      if(thisincrement == 2L){
        thisincrement = -2L;
      }else{
        thisincrement = 2L;
      }
      
      stepMillis += STEPINTERVAL;
    }

   
    
    
  }

}

void autotune(float P_Start, float P_step, uint8_t P_numSteps, float I_Start, float I_step, uint8_t I_numSteps){

  float P_Stop = P_Start + (P_step * P_numSteps); //stop value for P 
  float I_Stop = I_Start + (I_step * I_numSteps); //stop value for I 

  float     top5_I[5]   = {0,0,0,0,0};
  float     top5_P[5]   = {0,0,0,0,0};
  uint16_t  top5_ST[5]  = {10000,10000,10000,10000,10000};
  uint16_t  top5_ER[5]  = {10000,10000,10000,10000,10000};
  uint8_t top5_index = 0;

  for(  float PP = P_Start; PP < P_Stop; PP = PP+P_step ){ //Loop around P Values
    for(float II = I_Start; II < I_Stop; II = II+I_step ){ //Loop I Values Inside P Values
      Serial.print("\nTuning Speed CTRL with P=");Serial.print(PP);Serial.print(" and I=");Serial.print(II);Serial.println("... ");
      uint32_t result = MOT.TunePI_speed(PP, II, 50); //Attempt Unit Step Response with Provided I, and P. Returns Quality Factor. (Upper 16 = mag. overshoot; lower 16 = response time)

      uint16_t maxError = (result >> 16); //upper 16 are max error
      uint16_t settlingTime = (result & 0x0000FFFF); //lower 16 are settling time (in CTRL cycles)

       Serial.print("Settling Time: "); Serial.println(settlingTime);
       Serial.print("MaxError: "); Serial.println(maxError);

        bool Saved = false;
       for(int i = 0; (i<5 && Saved == false); i++){ //check top5 previous results.
        if(settlingTime < top5_ST[i]){ //If settling time is less
          top5_ST[i] = settlingTime;
          top5_ER[i] = maxError;
          top5_I[i] = II;
          top5_P[i] = PP;
          Saved = true;
        }
       }
        
    }
  }

  //TODO: Collect Array of Best Values, report, set operating parameters appropriately.

  Serial.print("\n\nAdjust motor to desired position. you have 10 seconds.");
  delay(10000);

  Serial.print("===================================\n===SPEED TEST REPORT:\n===================================\n");
  for(int i = 0; i<5; i++){ 
    Serial.print("Top "); Serial.print(i); Serial.print(" Speed Controller Result\n");
    Serial.print("SETTLE: "); Serial.print(top5_ST[i]); Serial.print(" CTRL Cycles\n");
    Serial.print("ERROR : "); Serial.print(top5_ER[i]); Serial.print(" Deg. per Second\n");
    Serial.print("P Term: "); Serial.print(top5_P[i]); Serial.print(" unitless\n");
    Serial.print("I Term: "); Serial.print(top5_I[i]); Serial.print(" unitless\n\n");


    if(top5_P[i] > 0 || top5_I[i] > 0){
      MOT.SpeedPI(top5_P[i], top5_I[i]); //Set Speed Controller to new COMP VALUES
      //TODO: Tune Position Values
      autotune_position(9.0, 1.0, 7,  0.0, 1.0, 5); //Test Position PI Controller
    }
    
  }
  
}


void autotune_position(float P_Start, float P_step, uint8_t P_numSteps, float I_Start, float I_step, uint8_t I_numSteps){
  float P_Stop = P_Start + (P_step * P_numSteps); //stop value for P 
  float I_Stop = I_Start + (I_step * I_numSteps); //stop value for I 

  float     top5_I[5]   = {0,0,0,0,0};
  float     top5_P[5]   = {0,0,0,0,0};
  uint16_t  top5_ST[5]  = {10000,10000,10000,10000,10000};
  uint16_t  top5_ER[5]  = {10000,10000,10000,10000,10000};
  uint8_t top5_index = 0;

  for(  float PP = P_Start; PP < P_Stop; PP = PP+P_step ){ //Loop around P Values
    for(float II = I_Start; II < I_Stop; II = II+I_step ){ //Loop I Values Inside P Values
      Serial.print("Tuning Position CTRL with P=");Serial.print(PP);Serial.print(" and I=");Serial.print(II);Serial.println("... ");
      uint32_t result = MOT.TunePI_position(PP, II, 50); //Attempt Unit Step Response with Provided I, and P. Returns Quality Factor. (Upper 16 = mag. overshoot; lower 16 = response time)

      uint16_t maxError = (result >> 16); //upper 16 are max error
      uint16_t settlingTime = (result & 0x0000FFFF); //lower 16 are settling time (in CTRL cycles)

       /*Serial.print("Settling Time: "); Serial.println(settlingTime);
       Serial.print("MaxError: "); Serial.println(maxError);*/

        bool Saved = false;
       for(int i = 0; (i<5 && Saved == false); i++){ //check top5 previous results.
        if(settlingTime < top5_ST[i]){ //If settling time is less
          top5_ST[i] = settlingTime;
          top5_ER[i] = maxError;
          top5_I[i] = II;
          top5_P[i] = PP;
          Saved = true;
        }
       }
        
    }
  }

  //TODO: Collect Array of Best Values, report, set operating parameters appropriately.

  Serial.print("\n\nAdjust motor to desired position. you have 10 seconds.");
  delay(10000);

  Serial.print("===================================\n===POSITION TEST REPORT:\n===================================\n");
  for(int i = 0; i<5; i++){ 
    Serial.print("Top "); Serial.print(i); Serial.print(" Position Controller Result\n");
    Serial.print("SETTLE: "); Serial.print(top5_ST[i]); Serial.print(" CTRL Cycles\n");
    Serial.print("ERROR : "); Serial.print(top5_ER[i]); Serial.print(" Deg. per Second\n");
    Serial.print("P Term: "); Serial.print(top5_P[i]); Serial.print(" unitless\n");
    Serial.print("I Term: "); Serial.print(top5_I[i]); Serial.print(" unitless\n");
  }
}
