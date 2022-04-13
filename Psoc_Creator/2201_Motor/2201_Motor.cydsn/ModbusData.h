/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/


#ifndef _MODBUSDATA_H
    #define _MODBUSDATA_H 1 //only include this once
    
    #define MODBUS_RX_BUFFER_LEN 20
    #define MODBUS_TX_BUFFER_LEN 20

#include <project.h>
#include "cytypes.h"


/***************************************************************************  	
Все необходимые переменных обьявлены в этом файле в качестве  extern 
и находятся в файле  ProjectData.c 	
использовать #include <ProjectData.h> для подключения
****************************************************************************/	

//extern  int				 *tick_CM0_ENABLE; 			// указатель на регистр включения   SysTick Timer	
	
extern unsigned char 	SlaveAddress;				// Change this to whatever you want	
//extern uint32 Baudrate;								// Скорость обмена по UART
	
extern unsigned char 	received[MODBUS_RX_BUFFER_LEN];				// буфер приема 
extern unsigned char 	response[MODBUS_TX_BUFFER_LEN]; 				// буфер передачи
extern unsigned char     inputCoils[];  	        // где-то есть inputCoils  
extern unsigned  int      holdingReg[];  	        // где-то есть holdingReg  
extern unsigned int        inputReg[];  	        // где-то есть   inputReg 
extern unsigned char          coils[];  	        // где-то есть      coils  
extern volatile uint8 	modbusMessage;				// флаг готовности сообщения. Устанавливается в interupt.c  используется в main.c 
extern volatile uint8   messageLength;				// длина сообщения (мастеру очищать принудительно)
extern volatile int8  	messageLengthNotChanged;	// счетчик тишины на  линии	



#endif

/* [] END OF FILE */
