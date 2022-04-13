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

// Motor.h - Controls a Motor Speed with 2 PWM outputs

#include "Arduino.h"


// ensure this library description is only included once
#ifndef SRC_MOTOR_H
#define SRC_MOTOR_H

class motor   
{
public:
    motor(int pinA, int pinB, bool ACTIVESTATE);
    void SetSpeed(int NewSpeed); //Value from -255 to 255
    int GetSpeed(); //returns last speed setting
 
private:
  int pin1;
  int pin2;
  bool onState;

  int lastspeed;
  
 
};
#endif
