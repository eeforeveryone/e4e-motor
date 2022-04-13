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

#include <project.h>
#include <stdlib.h>
#include "EEmotor.h"

uint64_t SYSTCK_millis = 0;
uint16_t MOT1_NEXT_PERIOD = 30000; //30000 = 1 Rotation per second in quarter step mode


#define NESTED_ISR                          (1u)
#define DEFAULT_PRIORITY                    (3u)
#define HIGHER_PRIORITY                     (2u)


/* Interrupt prototypes */
CY_ISR_PROTO(SYSTCK_HANDLER);
CY_ISR_PROTO(MOT1_HANDLER);
CY_ISR_PROTO(UART_HANDLER);




CY_ISR(SYSTCK_HANDLER){ //define the ISR for the SYSTCK ISR
    SYSTCK_millis ++;
    
    
     /* Clear pending Interrupt */
    SYSTCK_ISR_ClearPending();
    /* Clear pin Interrupt */
    SYSTCK_TIMER_ClearInterrupt(SYSTCK_TIMER_INTR_MASK_TC); //Clear TC Interrupt, not CC_MATCH "SYSTCK_TIMER_INTR_MASK_CC_MATCH" 
}

CY_ISR(MOT1_HANDLER){ //define the ISR for the MOT1 ISR
    //Adjust Period --TODO:Move Protections to another castle
    /*if(MOT1_NEXT_COMP > M1_PWM_ReadPeriod()){ //Clip Values that are too high!
        MOT1_NEXT_COMP = M1_PWM_ReadPeriod();
    }*/
    M1_PWM_WritePeriod(MOT1_NEXT_PERIOD); //set period value
    M1_PWM_WriteCompare((MOT1_NEXT_PERIOD>>1)); //Divide by 2 to set pwm duty cycle to 50%
    
     /* Clear pending Interrupt */
    M1_ISR_ClearPending();
    /* Clear pin Interrupt */
    M1_PWM_ClearInterrupt(M1_PWM_INTR_MASK_TC); //Clear TC Interrupt, not CC_MATCH "SYSTCK_TIMER_INTR_MASK_CC_MATCH" 
}


CY_ISR(UART_HANDLER){ //Define the ISR for the custom UART ISR Function.
    
    
    //// https://github.com/EmbeddedSam/Modbus-Slave-for-PSoC4
    
    uint32_t itrCause = UART_GetInterruptCause();
    
    if( (itrCause&UART_INTR_CAUSE_RX) >0){ //If this is an RX Interrupt
        uint32_t rx_cause = UART_GetRxInterruptSource();
        
        if( (rx_cause & UART_INTR_RX_NOT_EMPTY) > 0){ //If the TX FIFO is empty... turn off TX_ENABLE
            //Read in Data and DO SOMETHING!!!!
            
            TX_EN_Write(1); //Assert TX Enable - Speak to Bus
            UART_UartPutChar(UART_UartGetChar());
        }
        
        UART_CLEAR_INTR_RX(rx_cause);
    }
    
    
    if( (itrCause&UART_INTR_CAUSE_TX) >0){ //If this is an TX Interrupt
        
        uint32_t tx_cause = UART_GetTxInterruptSource();
        
        if( (tx_cause & UART_INTR_TX_UART_DONE) > 0){ //TX Transfer Complete... turn off TX_ENABLE
            TX_EN_Write(0); //De-Assert TX Enable - Listen
        }
        
        /*if( (tx_cause & UART_INTR_TX_EMPTY) == 0){ //If TX Buffer has content - Grab TX_ENABLE
            TX_EN_Write(1); //Assert TX Enable - Talk
        }*/ //TODO: Not working! Fix!
        
        UART_CLEAR_INTR_TX(tx_cause);
    }
        
    
    
    
}






void UART_sendString( const char8 string[]){
    
    TX_EN_Write(1); //Assert TX Enable - Speak to Bus
    UART_UartPutString(string);
    
}

void UART_senduint32( uint32_t thisval){
    char thischar[15] = "              ";
    itoa(thisval,thischar,10); //convert to string
    UART_sendString(thischar); //print using helper function
}
    

/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  Main function.
*
* Parameters:  
*  None
*
* Return: 
*  None
*
*******************************************************************************/

#define LED_BLINK_INTERVAL 500
#define MOTOR_INTERVAL 5000
#define CONTROL_TIME 20

//#define PPR 2160  //Number of pulses per rotation, Gear Ratio = 1:45, Encoder = 48PPR
#define PPR 540  //Number of pulses per rotation, Gear Ratio = 1:45, Encoder = 48PPR || For some reason the real value is adding an offset of 4x

uint32_t vert_encoder = 0;

int main()
{
    /* Start PWM Interrupts and Peripherals*/
    M1_ISR_StartEx(MOT1_HANDLER);
    M1_ISR_SetPriority(DEFAULT_PRIORITY);// Changes initial priority for the SYSTICK interrupt
    

    M1_PWM_Start();
    
    
    /* Start Encoder */
    ENC_Start();
    
    /*Start UART Peripheral*/
    UART_Start();

    UART_SetCustomInterruptHandler(UART_HANDLER);
    
    
    
    /* Sets up the SYSTICK interrupt and enables it */
    SYSTCK_ISR_StartEx(SYSTCK_HANDLER);
    SYSTCK_ISR_SetPriority(DEFAULT_PRIORITY);// Changes initial priority for the SYSTICK interrupt
    
    SYSTCK_TIMER_Start(); //Start the SYSTICK Timer! - This Generates SYSTICK ISR EVENTS
    
    CyGlobalIntEnable; //global interrupts enable
    
    uint32_t lastval = 0;
    
    uint64_t main_millis = SYSTCK_millis;
    uint64_t mot_millis = SYSTCK_millis;
    uint64_t control_millis = SYSTCK_millis;
    
    struct EEmotor* MyMot = EEmotor__create(vert_encoder); //ENC_ReadCounter()
    
    
    //TEMP TODO: Move This into proper code!
    //Enable Motor Driver - 1/4 step
    MODE0_Write(1); //[0,0] = Full;     [1,0] = Half A
    MODE1_Write(1); //[1,0] = Half B;   [1,1] = Quarter
    N_MOTrst_Write(1); //Take out of reset
    ENABLE_Write(1); //Enable Motor Driver
    
    
    CW_CCW_Write(0); //Clockwise
    //800 pps = 1 rotation per second
    //PWM_Clock = 24MHz, 800pps Period = 30000
    

    for(;;){
        
        
        if(main_millis + LED_BLINK_INTERVAL < SYSTCK_millis){
            main_millis = main_millis + LED_BLINK_INTERVAL;
            LED_ACT_Write(!LED_ACT_Read());
        }
        
        if(control_millis + CONTROL_TIME < SYSTCK_millis){
            control_millis = control_millis + CONTROL_TIME;
            EEmotor__run(MyMot, SYSTCK_millis, vert_encoder); //ENC_ReadCounter()
            
            //TODO - allow motor to STOP while holding position
            //TODO - fix Control pins to sync. with Period changes.
            //TODO - Allow for variable max speed - magic numbers in multiple places!!!
            if(EEmotor__getSpeedOutput(MyMot) >50){
                ENABLE_Write(1); //Enable Motor Driver
                CW_CCW_Write(0); //clockwise
                MOT1_NEXT_PERIOD = 30000 - abs(EEmotor__getSpeedOutput(MyMot));
                
                vert_encoder = vert_encoder + PPR*(30000.0/(float)MOT1_NEXT_PERIOD) * ((float)CONTROL_TIME/1000.0); // Increment Virtual Encoder - use real period value
                
            }else if (EEmotor__getSpeedOutput(MyMot) < -50){
                ENABLE_Write(1); //Enable Motor Driver
                CW_CCW_Write(1); //counter-clockwise
                MOT1_NEXT_PERIOD = 30000 - abs(EEmotor__getSpeedOutput(MyMot));
                
                vert_encoder = vert_encoder - PPR*(30000.0/(float)MOT1_NEXT_PERIOD) * ((float)CONTROL_TIME/1000.0); // Increment Virtual Encoder - use real period value
                
            }else{ //target reached!
                ENABLE_Write(0); //Disable Motor Driver
            }
            
            
            
        }
        
        if(mot_millis + MOTOR_INTERVAL < SYSTCK_millis){
            mot_millis = mot_millis + MOTOR_INTERVAL;
            
            
            EEmotor__nudge(MyMot, PPR);
            
            /*mot_millis = mot_millis + MOTOR_INTERVAL;
            
            CW_CCW_Write(!CW_CCW_Read()); //Invert Direction!
            
            UART_sendString("Set Motor to: "); //send null terminated string
            UART_senduint32(MOT1_NEXT_PERIOD); // send value
            UART_sendString(" of 800\n\r"); //send null terminated string
            UART_sendString("Encoder Position: "); //send null terminated string
            UART_senduint32(ENC_ReadCounter()); // send value
            UART_sendString(" \n\n\r"); //send null terminated string*/


        }
            
            
        
        uint32_t thisval = ENC_ReadCounter();
        
        if(thisval > lastval+50){
            lastval = thisval;
            
            
            LED_ACT_Write(1);
            CyDelay(100);
            LED_ACT_Write(0);
            //CyDelay(100);
        }
        
        if(thisval < lastval-50){
            lastval = thisval;
            
            
            LED_ACT_Write(1);
            CyDelay(50);
            LED_ACT_Write(0);
            CyDelay(50);
            LED_ACT_Write(1);
            CyDelay(50);
            LED_ACT_Write(0);
            
        }
    
    }
}

/* [] END OF FILE */