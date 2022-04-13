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


#include <project.h> //Include pre-compiled source
#include <stdlib.h>

// ensure this library description is only included once
#ifndef SRC_EEMOTOR_H
#define SRC_EEMOTOR_H 1
    
    
#define EEMOTOR__ENCODER_ERR_THRESHOLD 0x0FFF

struct EEmotor;
    
struct EEmotor_PIreg;
struct EEmotor_Shaper;


/**************CONSTRUCTORS AND DESTRUCTORS**************/
struct EEmotor* EEmotor__create(uint32_t encoderVal); //constructor
void EEmotor__init(struct EEmotor *self, uint32_t encoderVal); //modifier (empty)
void EEmotor__destroy(struct EEmotor *self); //destructor

/**************MEMBER FUNCTIONS**************************/

int EEmotor__run(struct EEmotor *self, uint32_t newmillis, uint32_t newencoder);
int EEmotor__runShaper(struct EEmotor *self, float timestepSeconds);
float EEmotor__runPI(struct EEmotor_PIreg *self, float timestepSeconds, float error); //returns control output: range 


void EEmotor__go(struct EEmotor *self, long NewPositionPulses); //set the new position, relative to home
void EEmotor__nudge(struct EEmotor *self, long pulses_to_nudge); //set the new position, relative to home

long EEmotor__getSpeedOutput(struct EEmotor *self);

#endif


/* [] END OF FILE */
