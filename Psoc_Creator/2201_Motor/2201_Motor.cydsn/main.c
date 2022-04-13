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

#include <project.h>
#include <stdlib.h>
#include "EEmodbus.h"
#include "EEmotor.h"

uint64_t SYSTCK_millis = 0;
uint16_t MOT1_NEXT_COMP = 000; //Range: 0-800 for 30kHz operation
uint16_t MOT2_NEXT_COMP = 000; //Range: 0-800 for 30kHz operation

uint8_t ModRX_INDEX = 0; //Global var - Index of RX


struct EEmodbus* Mod;


#define NESTED_ISR                          (1u)
#define DEFAULT_PRIORITY                    (3u)
#define HIGHER_PRIORITY                     (2u)


/* Interrupt prototypes */
CY_ISR_PROTO(SYSTCK_HANDLER);
CY_ISR_PROTO(MOT1_HANDLER);
CY_ISR_PROTO(MOT2_HANDLER);

uint64_t modbus_check_millis = 0;

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
    M1_PWM_WriteCompare(MOT1_NEXT_COMP);
    
     /* Clear pending Interrupt */
    M1_ISR_ClearPending();
    /* Clear pin Interrupt */
    M1_PWM_ClearInterrupt(M1_PWM_INTR_MASK_TC); //Clear TC Interrupt, not CC_MATCH "SYSTCK_TIMER_INTR_MASK_CC_MATCH" 
}

CY_ISR(MOT2_HANDLER){ //define the ISR for the MOT2 ISR
    //Adjust Period --TODO:Move Protections to another castle
    /*if(MOT2_NEXT_COMP > M2_PWM_ReadPeriod()){ //Clip Values that are too high!
        MOT2_NEXT_COMP = M2_PWM_ReadPeriod();
    }*/
    M2_PWM_WriteCompare(MOT2_NEXT_COMP);
    
     /* Clear pending Interrupt */
    M2_ISR_ClearPending();
    /* Clear pin Interrupt */
    M2_PWM_ClearInterrupt(M2_PWM_INTR_MASK_TC); //Clear TC Interrupt, not CC_MATCH "SYSTCK_TIMER_INTR_MASK_CC_MATCH" 
}


CY_ISR(UART_HANDLER){ //Define the ISR for the custom UART ISR Function.
    
    
    //// https://github.com/EmbeddedSam/Modbus-Slave-for-PSoC4
    
    uint32_t itrCause = UART_GetInterruptCause();
    
    if( (itrCause&UART_INTR_CAUSE_RX) >0){ //If this is an RX Interrupt
        uint32_t rx_cause = UART_GetRxInterruptSource();
        
        if( (rx_cause & UART_INTR_RX_NOT_EMPTY) > 0){ //If the RX FIFO is not empty... read in stuff!
            //Read in Data and DO SOMETHING!!!!
            
            EEmodbus__addByte(Mod, UART_UartGetByte()); //process next byte
        }
        
        UART_CLEAR_INTR_RX(UART_INTR_RX_NOT_EMPTY);
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






/*void UART_sendString( const char8 string[]){
    
    TX_EN_Write(1); //Assert TX Enable - Speak to Bus
    UART_UartPutString(string);
    
}

void UART_senduint32( uint32_t thisval){
    char thischar[15] = "              ";
    itoa(thisval,thischar,10); //convert to string
    UART_sendString(thischar); //print using helper function
}*/
    

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

#define MODBUS_DO_INTERVAL 1
#define LED_BLINK_INTERVAL 500
#define MOTOR_INTERVAL 5000
#define CONTROL_TIME 25


#define HOLD_STATE 0
#define HOLD_SPD_P 1
#define HOLD_SPD_I 2
#define HOLD_POS_P 3
#define HOLD_POS_I 4
#define HOLD_NUDGE 5
#define HOLD_ABSGO 6


//#define PPR 2160  //Number of pulses per rotation, Gear Ratio = 1:45, Encoder = 48PPR
#define PPR 540  //Number of pulses per rotation, Gear Ratio = 1:45, Encoder = 48PPR || For some reason the real value is adding an offset of 4x

int main()
{
    /* Start PWM Interrupts and Peripherals*/
    M1_ISR_StartEx(MOT1_HANDLER);
    M1_ISR_SetPriority(DEFAULT_PRIORITY);// Changes initial priority for the SYSTICK interrupt
    
    M2_ISR_StartEx(MOT2_HANDLER);
    M2_ISR_SetPriority(DEFAULT_PRIORITY);// Changes initial priority for the SYSTICK interrupt

    M1_PWM_Start();
    M2_PWM_Start();
    
    
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
    
    //uint32_t lastval = 0;
    
    
    struct EEmotor* MyMot = EEmotor__create(ENC_ReadCounter());
    Mod = EEmodbus__create(1); //set address to 1
    
    uint64_t modbus_millis = SYSTCK_millis;
    uint64_t main_millis = SYSTCK_millis;
    uint64_t mot_millis = SYSTCK_millis;
    uint64_t control_millis = SYSTCK_millis;

    for(;;){
        
        if(EEmodbus__getHoldingReg(Mod, HOLD_STATE) == 1){ //new command available
            EEmodbus__setHoldingReg(Mod, HOLD_STATE, 0);// reset flag
            
            EEmotor__setPIParams(MyMot, (float)EEmodbus__getHoldingReg(Mod, HOLD_SPD_I)/1000.0, (float)EEmodbus__getHoldingReg(Mod, HOLD_SPD_P)/1000.0, (float)EEmodbus__getHoldingReg(Mod, HOLD_POS_I)/1000.0 ,(float)EEmodbus__getHoldingReg(Mod, HOLD_POS_P)/1000.0);
            
            if(EEmodbus__getHoldingReg(Mod, HOLD_NUDGE) > 0){
                EEmotor__nudge(MyMot, (uint32_t)EEmodbus__getHoldingReg(Mod, HOLD_NUDGE)*PPR/3600);
            }
        }
        
        
        //if (modbus_millis + MODBUS_DO_INTERVAL < SYSTCK_millis){
            EEmodbus__do(Mod, SYSTCK_millis); //check for end of packet, CALL PERIODICALLY
        /*    modbus_millis = SYSTCK_millis;
        }*/
        
        
        if(main_millis + LED_BLINK_INTERVAL < SYSTCK_millis){
            main_millis = main_millis + LED_BLINK_INTERVAL;
            LED_ACT_Write(!LED_ACT_Read());
     
        }

        
        if(control_millis + CONTROL_TIME < SYSTCK_millis){
            control_millis = control_millis + CONTROL_TIME;
            EEmotor__run(MyMot, SYSTCK_millis, ENC_ReadCounter());
            
            if(EEmotor__getSpeedOutput(MyMot) >0){
                MOT2_NEXT_COMP = 0;
                MOT1_NEXT_COMP = abs(EEmotor__getSpeedOutput(MyMot));
            }else{      
                MOT2_NEXT_COMP = abs(EEmotor__getSpeedOutput(MyMot));
                MOT1_NEXT_COMP = 0;
            }
        }
        
        /*if(mot_millis + MOTOR_INTERVAL < SYSTCK_millis){
            mot_millis = mot_millis + MOTOR_INTERVAL;
            
            
            EEmotor__nudge(MyMot, PPR);

        }*/
    }
}

/* [] END OF FILE */