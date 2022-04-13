/* ========================================
 *
 * EE for Everyone Modbus Library
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

#include <project.h> //Include pre-compiled source
#include "EEmodbus.h"

/**************STRUCT DEFINITION*************************/


#define EEMODBUS_PACKET_ADDR_OFFSET 0
#define EEMODBUS_PACKET_FUNCTIONCODE_OFFSET 1
#define EEMODBUS_PACKET_RWADDR_OFFSET 2
#define EEMODBUS_PACKET_RWNUM_OFFSET 4
#define EEMODBUS_PACKET_CRC_OFFSET 2
struct EEmodbus_packet{
    uint8_t complete;
    uint16_t length;
    uint8_t BUFFER[EEMODBUS__BUFF_LENGTH];
};

struct EEmodbus{
    
    uint32_t oldMillis;
    uint8_t state; //stores current packet parsing state
    uint8_t address; //Stores this node's address
    uint16_t holdingRegs[EEMODBUS__NUM_HOLDING_REGS];
    
    uint16_t RWaddress;
    uint16_t RWnum;
    
    uint8_t CRC_UPPER;
    uint8_t CRC_LOWER;
    
    struct EEmodbus_packet TxPacket; 
    struct EEmodbus_packet RxPacket;
    
    uint32_t rxmillis;
    uint16_t oldrxlength;
  
};



/**************CONSTRUCTORS AND DESTRUCTORS**************/
struct EEmodbus* EEmodbus__create(uint8_t ADDRESS){ //constructor
    struct EEmodbus* result = (struct EEmodbus*) malloc(sizeof(struct EEmodbus)); //alocate memory, typecast to EEmotor struct.
    EEmodbus__init(result, ADDRESS); //initialize variables
    return(result);
}
void EEmodbus__init(struct EEmodbus *self, uint8_t ADDRESS){ //modifier (empty)
    
    self->state = EEMODBUS__STATE_IDLE;
    self->oldMillis = 0;
    self->address = ADDRESS;
    
    for(int i=0; i< EEMODBUS__NUM_HOLDING_REGS; i++){ //set all holding registers to 0
        self->holdingRegs[i] = 0;
    }
    
    __EEmodbus_clear_packet(&self->TxPacket); //set up TxPacket vars
    __EEmodbus_clear_packet(&self->RxPacket); //set up RxPacket vars
    
    self-> rxmillis = 0;
    self->oldrxlength = 2;
    
    self->CRC_UPPER = 0;
    self->CRC_LOWER = 0;
    
    self->RWaddress = 0;
    self->RWnum = 0;
    
}

void EEmodbus__destroy(struct EEmodbus *self){ //destructor
    if(self){
    free(self);
  }
}



/********************** Helper FUNCTIONS *******************/
void __EEmodbus_clear_packet(struct EEmodbus_packet *self){
    
    self->complete = 0;
    self->length = 0;
    for(int i=0; i< EEMODBUS__BUFF_LENGTH; i++){ //set RXBUFFER
        self->BUFFER[i] = 0;
    }
    
}


void __EEmodbus_calc_crc16(struct EEmodbus *self, uint8_t* array, uint16_t numbytes){

    uint16_t crc = 0xFFFF;
    int i,j = 0;

    for(i=0;i<numbytes;i++)	// Calculate CRC
	{
      crc ^= array[i];
      for(j=8; j!=0; j--)
	{
        if((crc & 0x0001))  { crc = (crc >> 1)^0xA001; }
        else	            { crc >>= 1;               }
      }
    }
  //bytes are wrong way round so doing a swap here..
  self->CRC_UPPER = (crc & 0x00FF);				 
  self->CRC_LOWER = (crc & 0xFF00) >>8;
    
}

void __EEmodbus_create_Error_TxPacket(struct EEmodbus *self, uint8_t errorcode){
    self->TxPacket.BUFFER[0] = self->address;
    self->TxPacket.BUFFER[1] = self->RxPacket.BUFFER[1] | 0x80; // set error bit
    self->TxPacket.BUFFER[2] = errorcode; //set error code
    __EEmodbus_calc_crc16(self, self->TxPacket.BUFFER, 3); //calcuate CRC
    self->TxPacket.BUFFER[3] = self->CRC_UPPER;
    self->TxPacket.BUFFER[4] = self->CRC_LOWER;
    self->TxPacket.length = 5;
    self->TxPacket.complete = 1;
}


/********************** MEMBER FUNCTIONS *******************/
void EEmodbus__addByte(struct EEmodbus *self, uint8_t newData){
    switch(self->state){
        case EEMODBUS__STATE_IDLE:
            __EEmodbus_clear_packet(&self->RxPacket); //clear RXPacket for new nonsense
            self->state = EEMODBUS__STATE_BUILDPACKET; //transition to next state
            //break; //Break statement intentionally omitted: Flow through both states!!
        case EEMODBUS__STATE_BUILDPACKET: //building a packet
            self->RxPacket.BUFFER[self->RxPacket.length] = newData;
            self->RxPacket.length ++; //increment length
            break;
        default:
            //Throw away byte! //TODO: handle this gracefully
            break;
    }  
}

void EEmodbus__do(struct EEmodbus *self, uint32_t milliseconds){ //check for end of packet, CALL PERIODICALLY
    switch(self->state){
        case EEMODBUS__STATE_IDLE:
            self-> rxmillis = milliseconds; //Keep ms counter up to date
            break;
        
        case EEMODBUS__STATE_BUILDPACKET: //building a packet - look for timeout or end of packet
            
            if(milliseconds > self->rxmillis + EEMODBUS__RX_EOP_TIMEOUT){ //Assume end of packet reached when no more serial data is recieved
                self->state = EEMODBUS__STATE_CHECKADDRESS;
            }
            
            if( (milliseconds < self->rxmillis) || (self->oldrxlength != self->RxPacket.length) ){ //ms counter overflow or rx packet length changed
                self-> rxmillis = milliseconds; //Keep ms counter up to date
                self->oldrxlength = self->RxPacket.length; //update rx counter
            }
            
            break;
            
        case EEMODBUS__STATE_CHECKADDRESS:
            
            if(self->RxPacket.BUFFER[EEMODBUS_PACKET_ADDR_OFFSET] == self->address){ //if the address is a match!
                self->state = EEMODBUS__STATE_CHECKCRC; //verify CRC
            }else{
                self->state = EEMODBUS__STATE_IDLE; //Ignore packet, go to idle state
            }

            break;
            
        case EEMODBUS__STATE_CHECKCRC:
            
            
            __EEmodbus_calc_crc16(self, self->RxPacket.BUFFER, self->RxPacket.length - EEMODBUS_PACKET_CRC_OFFSET); //calculate CRC Locally, the last two bytes are crc, exclude!
            
            if((self->RxPacket.BUFFER[self->RxPacket.length-2] == self->CRC_UPPER) && (self->RxPacket.BUFFER[self->RxPacket.length-1] == self->CRC_LOWER)){ //CRC MATCH!
                self->state = EEMODBUS__STATE_PROCESSCODE; //verify CRC
                
            }else{ //Return Exception code
                __EEmodbus_create_Error_TxPacket(self, EEMODBUS__CRC_ERROR);
                self->state = EEMODBUS__STATE_IDLE; //Ignore packet, go to idle state
            }
            
            break;
            
        case EEMODBUS__STATE_PROCESSCODE:
            
            
            if(self->RxPacket.BUFFER[EEMODBUS_PACKET_FUNCTIONCODE_OFFSET] == 0x03){ //function code 3 Read one or multiple holding registers
                
                
                self->RWaddress = (self->RxPacket.BUFFER[EEMODBUS_PACKET_RWADDR_OFFSET]<<8) | self->RxPacket.BUFFER[EEMODBUS_PACKET_RWADDR_OFFSET+1];   //starting register number
                self->RWnum = (self->RxPacket.BUFFER[EEMODBUS_PACKET_RWNUM_OFFSET]<<8) | self->RxPacket.BUFFER[EEMODBUS_PACKET_RWNUM_OFFSET+1];         //number of registers to read
                
                if( self->RWaddress + self->RWnum > EEMODBUS__NUM_HOLDING_REGS){ //if we have exceeded the number of registers available; Return Error!
                    __EEmodbus_create_Error_TxPacket(self, EEMODBUS__ILLEGAL_DATA_ADDRESS); //return appropriate error
                    
                }else{ //Return Data
                    
                    self->TxPacket.BUFFER[0] = self->address;					                            //Address
                    self->TxPacket.BUFFER[1] = self->RxPacket.BUFFER[EEMODBUS_PACKET_FUNCTIONCODE_OFFSET];	//function code
                    self->TxPacket.BUFFER[2] = 2*self->RWnum; 					                            //number of data bytes, 2 per register
                    self->TxPacket.length = 3;        //this is the current number of bytes
                    
                    //LOAD DATA BYTES!!!
                        for(int i = self->RWaddress; i < (self->RWaddress + self->RWnum); i++){
                            self->TxPacket.BUFFER[self->TxPacket.length] = (self->holdingRegs[i]>>8); //upper byte
                            self->TxPacket.length++;
                            self->TxPacket.BUFFER[self->TxPacket.length] = (self->holdingRegs[i] & 0x00FF); //lower byte
                            self->TxPacket.length++;
                        }
                    //END LOAD DATA BYTES
                    
                    __EEmodbus_calc_crc16(self, self->TxPacket.BUFFER, 5); //calcuate CRC
                    self->TxPacket.BUFFER[self->TxPacket.length] = self->CRC_UPPER;
                    self->TxPacket.length++;
                    self->TxPacket.BUFFER[self->TxPacket.length] = self->CRC_LOWER;
                    self->TxPacket.length++;
                    self->TxPacket.complete = 1;
                }

                   
            }else if(self->RxPacket.BUFFER[EEMODBUS_PACKET_FUNCTIONCODE_OFFSET] == 0x06){ //function code 3 Write one holding register
                
                self->RWaddress = (self->RxPacket.BUFFER[EEMODBUS_PACKET_RWADDR_OFFSET]<<8) | self->RxPacket.BUFFER[EEMODBUS_PACKET_RWADDR_OFFSET+1];   //starting register number
                self->RWnum = 1;//(self->RxPacket.BUFFER[EEMODBUS_PACKET_RWNUM_OFFSET]<<8) | self->RxPacket.BUFFER[EEMODBUS_PACKET_RWNUM_OFFSET+1];         //number of registers to read
                
                if( self->RWaddress + self->RWnum > EEMODBUS__NUM_HOLDING_REGS){ //if we have exceeded the number of registers available; Return Error!
                    __EEmodbus_create_Error_TxPacket(self, EEMODBUS__ILLEGAL_DATA_ADDRESS); //return appropriate error
                    
                }else{ //Return Data
                
                    self->TxPacket.BUFFER[0] = self->address;					                            //Address
                    self->TxPacket.BUFFER[1] = self->RxPacket.BUFFER[EEMODBUS_PACKET_FUNCTIONCODE_OFFSET];	//function code
                    self->TxPacket.BUFFER[2] = self->RxPacket.BUFFER[2];	//requested address
                    self->TxPacket.BUFFER[3] = self->RxPacket.BUFFER[3];	//requested address
                    self->TxPacket.length = 4;        //this is the current number of bytes
                    
                    //Store Data!
                        self->holdingRegs[self->RWaddress] = (self->RxPacket.BUFFER[4]<<8) | self->RxPacket.BUFFER[5];	//store data
    	                self->TxPacket.BUFFER[4] = self->holdingRegs[self->RWaddress]>>8;				//return upper data
    	                self->TxPacket.BUFFER[5] = self->holdingRegs[self->RWaddress]&0x00FF;			//return lower data
                    //END Store Data
                    self->TxPacket.length = 6;        //this is the current number of bytes
                        
                    __EEmodbus_calc_crc16(self, self->TxPacket.BUFFER, 5); //calcuate CRC
                    self->TxPacket.BUFFER[self->TxPacket.length] = self->CRC_UPPER;
                    self->TxPacket.length++;
                    self->TxPacket.BUFFER[self->TxPacket.length] = self->CRC_LOWER;
                    self->TxPacket.length++;
                    self->TxPacket.complete = 1;
                }
                
                
            }else{ //send error packet
                __EEmodbus_create_Error_TxPacket(self, EEMODBUS__ILLEGAL_FUNCTION);
            }
            
            self->state = EEMODBUS__STATE_IDLE; //Processing Complete, go to idle state
            break;
            
        default: //error
            break;
    }
    
    
    if(self->TxPacket.complete == 1){ //a response is ready to send //TODO: Make more portable!!!
        
        TX_EN_Write(1); //Assert TX Enable - Speak to Bus
        for(int i=0; i<self->TxPacket.length; i++){ //send all bytes
            UART_UartPutChar(self->TxPacket.BUFFER[i]); 
        }
        //Tx enable is de-asserted in the ISR
        __EEmodbus_clear_packet(&self->TxPacket); //set up TxPacket vars
    }
        
}

uint16_t EEmodbus__getHoldingReg(struct EEmodbus *self, uint16_t holdRegID){
    if(holdRegID < EEMODBUS__NUM_HOLDING_REGS){
        return(self->holdingRegs[holdRegID]);
    }else{
        return(0xFFFF);
    }
}

void EEmodbus__setHoldingReg(struct EEmodbus *self, uint16_t holdRegID, uint16_t value){
    if(holdRegID < EEMODBUS__NUM_HOLDING_REGS){
        self->holdingRegs[holdRegID] = value;
    }
}



/* [] END OF FILE */
