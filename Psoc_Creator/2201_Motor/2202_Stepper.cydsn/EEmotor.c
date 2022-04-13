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
#include "EEmotor.h"

/**************STRUCT DEFINITION*************************/

struct EEmotor_PIreg{
    float K_P;
    float K_I;
    float last_error;
    float last_Iterm;
    float last_control; 
    float INPUT_SCALAR;
    float OUTPUT_SCALAR;
};


#define SHAPER_OFF 0 //pass through values directly
struct EEmotor_Shaper{
    uint8_t mode;
};

struct EEmotor{
    
    long set_position; //Stores requested position, relative to home
    long shaper_out; //stores output of the shaper - used as input for position regulator
    long home; //stores "home" offset
    uint32_t encoder; //stores current encoder position, in pulses
    uint32_t oldMillis;
    float output; //stores current motor speed setpoint  //1000 = Full speed forward. -1000 = Full speed backward
    
    float speed;
    long position; //stores current position
    
    struct EEmotor_PIreg speedReg;
    struct EEmotor_PIreg PosReg;
    struct EEmotor_Shaper ShaperVars;
  
};



/**************CONSTRUCTORS AND DESTRUCTORS**************/
struct EEmotor* EEmotor__create(uint32_t encoderVal){ //constructor
    struct EEmotor* result = (struct EEmotor*) malloc(sizeof(struct EEmotor)); //alocate memory, typecast to EEmotor struct.
    EEmotor__init(result, encoderVal); //initialize variables
    return(result);
}
void EEmotor__init(struct EEmotor *self, uint32_t encoderVal){ //modifier (empty)
    self->encoder = encoderVal;
    self->shaper_out = encoderVal;
    self->home = encoderVal;
    self->set_position = encoderVal;
    self->oldMillis = 0;
    self->output = 0;
    self->speed = 0;
    self->position = 0;
    
    self->speedReg.K_I = 0.0002;
    self->speedReg.K_P = 1.0;
    self->speedReg.last_error = 0;
    self->speedReg.last_Iterm = 0;
    self->speedReg.last_control = 0;
    self->speedReg.INPUT_SCALAR = 1;
    self->speedReg.OUTPUT_SCALAR = 20000; // +/- 30000 for 1 rot/sec operation
    
    self->PosReg.K_I = 0.0001;
    self->PosReg.K_P = 1.0;
    self->PosReg.last_error = 0;
    self->PosReg.last_Iterm = 0;
    self->PosReg.last_control = 0;
    self->PosReg.INPUT_SCALAR = 1.0/1080.0; //Scale 1:1  (For our motor)
    self->PosReg.OUTPUT_SCALAR = 1; //Scale 1:1
    
    self->ShaperVars.mode = SHAPER_OFF;
    
}

void EEmotor__destroy(struct EEmotor *self){ //destructor
    if(self){
    free(self);
  }
}


/********************** MEMBER FUNCTIONS *******************/
long EEmotor__getSpeedOutput(struct EEmotor *self){
  return(self->output);   
}

void EEmotor__go(struct EEmotor *self, long NewPositionPulses){ //set the new position target
    self->set_position = NewPositionPulses + self->home; //include home offset
}

void EEmotor__nudge(struct EEmotor *self, long pulses_to_nudge){ //set the new position target
    self->set_position += pulses_to_nudge;
}

int EEmotor__run(struct EEmotor *self, uint32_t newmillis, uint32_t newencoder){
    if(self->oldMillis > newmillis){ //millisecond rollover event occured!
        self->oldMillis = newmillis;
        return(-1); //error
    }
    
    uint32_t elapsedMs = newmillis - self->oldMillis;
    float elapsedSec = (float)elapsedMs/1000.0;
    
    if( (newencoder > self->encoder) && ((newencoder - self->encoder) > EEMOTOR__ENCODER_ERR_THRESHOLD) ){ //encoder rollover event occured in positive direction!
        self->encoder = newencoder;
        self->set_position = newencoder; // TODO: Fix Rollover Handling - This is a hack!!!
        return(-2); //error  
    }else if( (newencoder < self->encoder) && ((self->encoder - newencoder) > EEMOTOR__ENCODER_ERR_THRESHOLD) ){ //encoder rollover event occured in negative direction!
        self->encoder = newencoder;
        self->set_position = newencoder; // TODO: Fix Rollover Handling - This is a hack!!!
        return(-2); //error
        
    }else{
        /*long deltaPosition = (newencoder - self->encoder);
        self->speed = (float)deltaPosition/elapsedSec;
        self->position += deltaPosition; //stores current position*/
        
        EEmotor__runShaper(self, elapsedSec);
    
        long positionError = self->shaper_out - (long)newencoder; //Don't handle rollover or anything... Something is broken
        self->output = EEmotor__runPI(&self->speedReg,elapsedSec,EEmotor__runPI(&self->PosReg, elapsedSec, ((float)positionError*self->PosReg.INPUT_SCALAR))); //run nested PI Regulator. Feed Position output into speed
        //self->output = EEmotor__runPI(&self->PosReg, elapsedSec, ((float)positionError*self->PosReg.INPUT_SCALAR)) * self->speedReg.OUTPUT_SCALAR; //Direct Position REgulator output -- TESTING ONLY TODO: Fix!
        
    }
    

    return(1);
}


int EEmotor__runShaper(struct EEmotor *self, float timestepSeconds){
    switch(self->ShaperVars.mode){
        case SHAPER_OFF:
            self->shaper_out = self->set_position; //Passthrough set position without shaping
            break;
        default:
            return(-1);
            break;
    }
    
    return(1); //success!
}

#define PI_MAXVAL 1.0
#define PI_MINVAL -1.0
float EEmotor__runPI(struct EEmotor_PIreg *self, float timestepSeconds, float error){ //returns control output: range 
    
    float thiserror = error;//*self->INPUT_SCALAR; //Scaling moved outside of this handler for effiiency - sometimes it is unused / unnecessary
    if(thiserror > PI_MAXVAL){
        thiserror = PI_MAXVAL;
        
    }else if(thiserror < PI_MINVAL){
        thiserror = PI_MINVAL;
    }
    
    float control_out = 0;
    
    //============= PI CONTROLLER ===================//                                      
    control_out = (thiserror * self->K_P); //Save P Term Output
    float thisIterm = ((((thiserror+self->last_error)/2.0 * self->K_I) * timestepSeconds) + self->last_Iterm); // I - Trapezoidal approx
    control_out = control_out + thisIterm; //Add I term portion to P term
    //============= PI CONTROLLER ===================//
    
    self->last_error = thiserror;
    
     if(control_out > PI_MAXVAL){ //Antiwindup - CTRL!
        control_out = PI_MAXVAL;
      }else if (control_out < PI_MINVAL){
        control_out = PI_MINVAL;
      }

      if(thisIterm > PI_MAXVAL){ //Antiwindup - I Term!
        thisIterm = PI_MAXVAL;
      }else if (thisIterm < PI_MINVAL){
        thisIterm = PI_MINVAL;
      }
    
    self->last_Iterm = thisIterm;
    self->last_control = control_out;
    return(control_out*self->OUTPUT_SCALAR);
}

/* [] END OF FILE */
