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

// position_ctrl.h - Controls a Motor position

#include "Arduino.h"
#include "speed_ctrl.h" //include speed controller


// ensure this library description is only included once
#ifndef SRC_POS_CTRL_H
#define SRC_POS_CTRL_H

class position_ctrl   
{
public:
    position_ctrl(int motA, int motB, int encA, int encB, uint8_t PulsePerRotation, uint8_t GearRatio);
    void SetMaxSpeed(uint16_t NewSpeed); //Max Speed, In tenths of Degrees per second.
    void SetMaxAccel(uint16_t newAccel); //Max Acceleration, in tenths of Degrees per second^2
    void SetTgtSpeed(uint16_t NewSpeed); //Target Speed for waveshaping, In tenths of Degrees per second.
    void SpeedPI(float newP, float newI); //set P & I used for speed
    void PositionPI(float newP, float newI); //set P & I used for position 
    
    void SetHome(); //Set Current position to home (0 rotations, relative)

    void Go(long NewPosition, uint8_t ramptype); //go to the specified position
    bool Done(); //Returns 1 when motion is done

    int Run(); //Runs the control loop for position regulation. Returns 1 if OK, -1 if CTRL Time is not happy
    void resetCompensator();

    void printReport(); //prints control stuff

    uint32_t TunePI_speed(float pterm, float iterm, uint32_t periodMS); //Attempt Unit Step Response with Provided I, and P. Returns Quality Factor. (Upper 16 = mag. overshoot; lower 16 = response time)
    uint32_t TunePI_position(float pterm, float iterm, uint32_t periodMS); //Attempt Unit Step Response with Provided I, and P. Returns Quality Factor. (Upper 16 = mag. overshoot; lower 16 = response time)
 
private:
  speed_ctrl mySpeedCtrl;

  
  uint16_t maxSpeed;
  uint16_t maxAccel;
  long TARGET_position; 

  bool moving;

  uint32_t last_CTRL_millis;


    //==== Control Loop Parameters ==== 
  float _POS_SCALLER;
  float K_P;
  float K_I;
  float last_error;
  float last_Iterm;
  float last_control;


  //==== Wave Shaping Parameters ====
  #define POS_RAMPTYPE_NONE 0 //set to 0
  #define POS_RAMPTYPE_TRAP 1 //set to 1
  #define POS_RAMPTYPE_S 2 //set to 2

  uint8_t POS_ThisMoveType;

  long trap_vTarget; //target speed

  long trap_sign; //holds + or - for the speed
  long trap_decel_thresh; //When this position is reached, start decel!
  long trap_move_length;
  long trap_start_position;
  long trap_finalPosition; //holds final value of trapezoidal ramp
  float trap_distance_increment_last; //value to add to distance every second - NEED TO SCALE BY CONTROL TIME!
  long trap_vmin; //when this speed is reached, Switch to PI!
  long trap_vmax;
  long trap_accel;
  uint8_t trap_state; //start at state 0, accel


  
 
};
#endif
