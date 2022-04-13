/* ========================================
 *
 * EE for Everyone Modbus Library
 * 
 * 
 * This Library IS PROVIDED "AS IS" AND "WITH ALL FAULTS". EEForEveryone DISCLAIMS ALL OTHER WARRANTIES, EXPRESS OR IMPLIED, 
 * INCLUDING BUT NOT LIMITED TO, ANY IMPLIED WARRIENTIS OR MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. 
 * This code is provided for EDUCATIONAL PURPOSES ONLY.
 * EEforEveryone may make changes to specifications and implementation details at any time, without notice. 
 * EEforEveryone does not endorce the software described here as "Safe" or "Suitable" for any particular purpose or application. 
 * The design information on any Web Site or Materials is uncontrolled and subject to change without notice. 
 * Do not create or finalize a product with this information.
 *

 *
 * ========================================
*/


#include <project.h> //Include pre-compiled source
#include <stdlib.h>

// ensure this library description is only included once
#ifndef SRC_EEMODBUS_H
#define SRC_EEMODBUS_H 1
    
    
#define EEMODBUS__BUFF_LENGTH 30
#define EEMODBUS__NUM_HOLDING_REGS 10
#define EEMODBUS__DEFAULT_ADDR 1
    
    
#define EEMODBUS__RX_EOP_TIMEOUT 5
    
#define EEMODBUS__STATE_IDLE 0
#define EEMODBUS__STATE_BUILDPACKET 1
#define EEMODBUS__STATE_CHECKADDRESS 2
#define EEMODBUS__STATE_CHECKCRC 3
#define EEMODBUS__STATE_PROCESSCODE 4
    
    
    
#define EEMODBUS__CRC_ERROR             0x04            // CRC Failure
#define EEMODBUS__ILLEGAL_FUNCTION      0x01	// Function code not supported
#define EEMODBUS__ILLEGAL_DATA_ADDRESS  0x02	// Data Address out of bounds
#define EEMODBUS__ILLEGAL_DATA_VALUE    0x03 	// Data Value is invalid

struct EEmodbus;
    
struct EEmodbus_packet;


/**************CONSTRUCTORS AND DESTRUCTORS**************/
struct EEmodbus* EEmodbus__create(uint8_t ADDRESS); //constructor
void EEmodbus__init(struct EEmodbus *self, uint8_t ADDRESS); //modifier (empty)
void EEmodbus__destroy(struct EEmodbus *self); //destructor

/**************MEMBER FUNCTIONS**************************/

void EEmodbus__addByte(struct EEmodbus *self, uint8_t newData);
void EEmodbus__do(struct EEmodbus *self, uint32_t milliseconds); //check for end of packet, CALL PERIODICALLY
uint16_t EEmodbus__getHoldingReg(struct EEmodbus *self, uint16_t holdRegID);
void EEmodbus__setHoldingReg(struct EEmodbus *self, uint16_t holdRegID, uint16_t value);




        //*************** INTERNAL FUNCTIONS ********************//
        void __EEmodbus_calc_crc16(struct EEmodbus *self, uint8_t* array, uint16_t numbytes);
        void __EEmodbus_clear_packet(struct EEmodbus_packet *self);
        void __EEmodbus_create_Error_TxPacket(struct EEmodbus *self, uint8_t errorcode); 

#endif

/* [] END OF FILE */
