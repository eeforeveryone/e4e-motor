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

#include <project.h>
#include "cytypes.h"
#include "ModbusData.h"


unsigned char 	SlaveAddress = 0x01;		// адрес устройства   Адрес ведомого устройства. 
    										// может иметь значения от 1 до 247. Адрес 0 используется для широковещательной передачи, 



volatile uint8  modbusMessage;				// флаг готовности сообщения. Устанавливается в interupt.c  используется в main.c  
volatile uint8  messageLength;				// длина сообщения (мастеру очищать принудительно)
volatile  int8  messageLengthNotChanged;	// счетчик тишины на  линии


unsigned char received[MODBUS_RX_BUFFER_LEN];				// буфер приема 
unsigned char response[MODBUS_TX_BUFFER_LEN]; 				// буфер передачи


unsigned char       coils[10]= {1,1,0,0,1,1,0,0,1};		// тестовые данные 
unsigned char  inputCoils[1]= {1};		// тестовые данные //Not used for motor controller
unsigned int  holdingReg[10]= {0x1001,0x1002,0x1003,0x1004,0x1005,0x1006,7,8,9,10}; 		//Used for Read/Write access with host
unsigned int    inputReg[10]= {0x3001,0x3002,0x3003,0x3004,0x3005,0x3006,0x3007,0x3008,0x3009,0x300A}; 		//Used for Reporting values back to host

/* [] END OF FILE */

/* [] END OF FILE */
