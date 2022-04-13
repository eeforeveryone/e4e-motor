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

// speed_ctrl.h - Controls a Motor Speed with encoder

#include "Arduino.h"
#include <Encoder.h>
#include "motor.h" //include motor


// ensure this library description is only included once
#ifndef SRC_SPEED_CTRL_H
#define SRC_SPEED_CTRL_H
//#define ENCODER_USE_INTERRUPTS 1 //may not be needed


#define RAW_ENC_OVERFLOW 20000

class speed_ctrl   
{
public:
    speed_ctrl(int pinA, int pinB, uint8_t PulsePerRotation, uint8_t GearRatio, int MotA, int MotB);
    void SetSpeed(long NewSpeed); //Target Speed, In tenths of Degrees per second.
    void SetPI(float newP, float newI); //set P & I
    
    long GetSpeed(); //returns last measured speed, in 10ths of degrees per second.
    long GetPos(); //returns last position, in 10ths of degrees.
    void ResetPos(); //Sets Position to 0


    int Run(); //Runs the control loop for speed regulation. Returns 1 if OK, -1 if CTRL Time is not happy
    void resetCompensator();
    uint32_t TunePI(float pterm, float iterm, uint32_t periodMS); //Attempt Unit Step Response with Provided I, and P. Returns Quality Factor. (Upper 16 = mag. overshoot; lower 16 = response time)
 
private:
  uint32_t MeasureSpeed();

  int pin1;
  int pin2;

  long this_speed;

  float ENC_compensation_factor;
  long old_rawposition;

  long ENC_position; 
  

  uint32_t last_SPEED_millis;
  uint32_t last_CTRL_millis;

  void runPI();


  
  //==== Control Loop Parameters ==== 
  long TARGET_SPEED;
  long _MAX_SPEED;
  float K_P;
  float K_I;
  float last_error;
  float last_Iterm;
  float last_control;
  
  

  Encoder myEnc;
  motor mymotor;
 
};
#endif
