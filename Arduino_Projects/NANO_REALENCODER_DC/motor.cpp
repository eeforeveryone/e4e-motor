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

//Motor.CPP - Implements methods for Motor Control
#include "motor.h"

motor::motor(int pinA, int pinB, bool ACTIVESTATE){ //constructor, pass in 2 pwm pins, plus 
  pin1 = pinA;
  pin2 = pinB;
  onState = ACTIVESTATE;

  digitalWrite(pin1, !onState); //make sure pins are off before driving
  digitalWrite(pin2, !onState);
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);

  lastspeed = 0;
}

void motor::SetSpeed(int NewSpeed){

  if(NewSpeed > 255){
    NewSpeed = 255;
  }else if(NewSpeed < -255){
    NewSpeed = -255;
  }
  lastspeed = NewSpeed;


  uint8_t thisspeed = 0;

  if(NewSpeed<0){
    thisspeed = NewSpeed * -1; //invert negative value
  }else{
    thisspeed = NewSpeed;
  }

  //COMPENSATE FOR NEGATIVE LOGIC
  if(onState == 0){ //Active LOW PWM
    thisspeed = 255-thisspeed; //Invert PWM command appropriately
  }
  
  if(NewSpeed<0){
    digitalWrite(pin1, !onState);
    analogWrite(pin2, thisspeed);
    
  }else{
    digitalWrite(pin2, !onState);
    analogWrite(pin1, thisspeed);
  }
  
}

int motor::GetSpeed()
{
    return lastspeed;
}
