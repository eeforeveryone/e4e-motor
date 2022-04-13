#include <project.h>
#include <ModbusData.h>
#include <Modbus.h>

//#include <cydevice_trm.h>
//#include <CyLib.h>

/***************************************************************************************************** 
        these global variables must be in an external file(s)  ( ProjectData.c ) 
 *****************************************************************************************************/		
//#define SlaveAddress 1 //Change this to whatever you want	
#define CHECK_BIT(var,pos) !!((var)&(1 << (pos)))
extern unsigned char  inputCoils[];  	// где-то есть inputCoils  с данными    ( DataAndFunc.h )
extern unsigned int  holdingReg[];  	// где-то есть holdingReg  с данными    ( DataAndFunc.h )
extern unsigned int    inputReg[];  	// где-то есть   inputReg  с данными    ( DataAndFunc.h )
extern unsigned char      coils[];  	// где-то есть      coils  с данными    ( DataAndFunc.h )
extern unsigned char   received[];		// где-то есть  буфер  приема    		( DataAndFunc.h )
extern unsigned char   response[]; 		// где-то есть  буфер  передачи   		( DataAndFunc.h )
extern volatile uint8 messageLength ;	// счетчик длины сообщений		( DataAndFunc.h )
/*****************************************************************************************************/

unsigned int     DataBuff[128];  		// массив подготовки данных для отправки 


//
//typedef enum  /************  MODBUS	ERRORs  **********************************************/
//{   NO_ERROR    = 0x00,
//    NO_Address  = 0x01,
//    NO_Resoonse = 0x02,
//	NO_Device   = 0x03,
//	CRC_ERROR   = 0x04
//} ErrorsCode;//.............................. 
 

typedef enum  /************  MODBUS	ERRORs  **********************************************/
{   NO_ERROR             = 0x00,
    ILLEGAL_FUNCTION     = 0x01,	// Принятый код функции не поддерживается 
    ILLEGAL_DATA_ADDRESS = 0x02,	// Адрес данных указанный в запросе не доступен 
	ILLEGAL_DATA_VALUE   = 0x03, 	// Величина в поле данных запроса недопустима
	SLAVE_DEVICE_FAILURE = 0x04		// Невосстанавливаемая ошибка во время выполнения запроса
						 //0x05 — устройство  обрабатывает запрос,(предохраняет  от генерации ошибки тайм-аута).
						 //0x06 —  устройство занято  повторить сообщение позже  
						 //0x07 —  устройство не может выполнить программную функцию, заданную в запросе использующего функции с номерами 13 или 14. Ведущее устройство должно запросить диагностическую информацию или информацию об ошибках от ведомого.
						 //0x08 — Ведомое устройство при чтении расширенной памяти обнаружило ошибку паритета. Ведущее устройство может повторить запрос, но обычно в таких случаях требуется ремонт.


} ErrorsCode;//.............................. 




/***************************************************************************************
*               Optimized CRC-16 calculation.
*      Polynomial: x^16 + x^15 + x^2 + 1 (0xA001)
*   Initial value: 0xffff
*    http://www.nongnu.org/avr-libc/user-manual/group__util__crc.html
****************************************************************************************/
unsigned int generateCRC(unsigned char messageLength)
{
unsigned int crc     = 0xFFFF;
int i,j = 0;

  for(i=0;i<messageLength-2;i++){
    crc ^= response[i];
    for(j=8; j!=0; j--)
	{
      if((crc & 0x0001))  { crc >>= 1;  crc ^= 0xA001; }
      else                { crc >>= 1;                 }
    }
  }
crc = (crc<<8)|((crc&0xFF00) >>8);	// перестановка байт
return crc;
}//..........................



/*********************************************************************************************  
						checkCRC   
**********************************************************************************************/
unsigned char checkCRC(void)			// перед ответом сначала  checkCRC потом  generateCRC
{
  unsigned int crc = 0xFFFF;
  unsigned int crcHigh, crcLow =0;
  int i,j = 0;

    for(i=0;i<messageLength-2;i++)		// для всех байт сообщения кроме CRC подсчитаем CRC
	{
      crc ^= received[i];
      for(j=8; j!=0; j--)
	{
        if((crc & 0x0001))  { crc = (crc >> 1)^0xA001; }
        else	            { crc >>= 1;               }
      }
    }
  //bytes are wrong way round so doing a swap here..
  crcHigh = (crc & 0x00FF);				 
  crcLow = (crc & 0xFF00) >>8;
  if((crcHigh == received[i])&&(crcLow == received[i+1]))  	{ return 1;  }	// Сравним с CRC сообщения
  else														{ return 0;  }
}//..........................



/****************************************************************************************
*  подпрограмма  чтения значения выходных / внутренних Coils 
*****************************************************************************************/
 /*            
Коды функций:  01 -для  coils  и 01 для inputcoils
received[2] -  Адрес начального Coil(Hi)    
received[3] -  Адрес начального Coil(Lo)
received[4] -  Количество Coils(Hi)        
received[5] -  Количество Coils(Lo)
********************************************************************************/

void readCoil(void)
{
/******************************************************************************/
/* Reads a coil and then responds                                             */
/******************************************************************************/
  unsigned int rc_Address  = 0;		// адрес первого регистра
  unsigned int rc_numCoils = 0;		// число регистров
  unsigned int crc = 0;

  unsigned char howManyBytes = 0;
  unsigned char lsb,i,j,l = 0;
  unsigned char  k = 3;				//start at response[3]
	
  rc_Address =  (received[2]<<8)|received[3]; 	// Combine address bytes	  Адрес начального регистра(HiLo) 
  rc_numCoils = (received[4]<<8)|received[5];	//Combine number of coils bytes    Количество  байт

  response[0] = SlaveAddress;		// установить адрес устройства в ответе
  response[1] = 0x01;				// код команды (01)

  howManyBytes = rc_numCoils/8 + rc_numCoils%8;		// сколько целых байт нужно для всех coils
  response[2] = howManyBytes ;

  l = rc_Address;									// начнем с этого адреса

 for(i=howManyBytes; i!=0; i--){	//упаковка в байты
	 response[k] = 0;							// чистим байт ответа
	 for(j=0;j<8;j++)// для каждого бита
		{
         lsb = (coils[l]!=0);					// устанавливаем текущий бит
		 response[k] = (lsb << j)|response[k];	// response[k] ^= (lsb << j); 
		 l++;									// следующий  coil
        }
	 k++; // следующий байт
  }
crc = generateCRC(k+2);		// вычисляем  CRC
response[k] = crc >> 8;		// старший байт CRC 
response[k+1] = crc;		// младший байт CRC 

TX_EN_Write(1); //Assert TX Enable - Speak to Bus
for(i=0;i!=k+2;i++){  UART_UartPutChar(response[i]);  }	// отправляем сообщение
}

void readInputCoil(void)
{
/******************************************************************************/
/* Reads a coil and then responds                                             */
/******************************************************************************/
  unsigned int rc_Address  = 0;		// адрес первого регистра
  unsigned int rc_numCoils = 0;		// число регистров
  unsigned int crc = 0;

  unsigned char howManyBytes = 0;
  unsigned char lsb,i,j,l = 0;
  unsigned char  k = 3;				//start at response[3]
	
  rc_Address =  (received[2]<<8)|received[3]; 	// Combine address bytes	  Адрес начального регистра(HiLo) 
  rc_numCoils = (received[4]<<8)|received[5];	//Combine number of coils bytes    Количество  байт

  response[0] = SlaveAddress;		// установить адрес устройства в ответе
  response[1] = 0x02;				// код команды (01)

  howManyBytes = rc_numCoils/8 + rc_numCoils%8;		// сколько целых байт нужно для всех coils
  response[2] = howManyBytes ;

  l = rc_Address;									// начнем с этого адреса

 for(i=howManyBytes; i!=0; i--){	//упаковка в байты
	 response[k] = 0;							// чистим байт ответа
	 for(j=0;j<8;j++)// для каждого бита
		{
         lsb = (inputCoils[l]!=0);					// устанавливаем текущий бит
		 response[k] = (lsb << j)|response[k];	// response[k] ^= (lsb << j); 
		 l++;									// следующий  coil
        }
	 k++; // следующий байт
  }
crc = generateCRC(k+2);		// вычисляем    CRC
response[k] = crc >> 8;		// старший байт CRC 
response[k+1] = crc;		// младший байт CRC 
TX_EN_Write(1); //Assert TX Enable - Speak to Bus
for(i=0;i!=k+2;i++){  UART_UartPutChar(response[i]);  }	// отправляем сообщение
}



unsigned int checAddr( unsigned char  comm, unsigned int*  DeviceReg,  unsigned int  numRegs )    
{	
 unsigned int i=0;
 if( *DeviceReg > 1000) return ILLEGAL_DATA_ADDRESS; 		// пример ограничения по допустимому адресу
 if(    numRegs > 127 ) return ILLEGAL_DATA_ADDRESS;    	// ограничение длины запрашиваемых данных
 	if(   comm ==0x03) 
		{	// для команды    void readReg(void);	
			// здесь в буфер отправки складываются запрошеные данные
			for(i=0;i< 128;  i++)    {DataBuff[i] = holdingReg[*DeviceReg+i];}	// добавить свой вариант.....
		}
 	else
		{// для команды    void readInputReg(void);
		 for(i=0;i< 128;  i++)    {DataBuff[i] = inputReg[*DeviceReg+i];}	// // добавить свой вариант..... 
        }	
return NO_ERROR;
}//..................


/****************************************************************************************
*  подпрограмма  чтения значения выходных / внутренних регистров.
*****************************************************************************************/
 /*            
Коды функций:  03 -для  holdingReg  и 04 для inputReg
received[2] -  Адрес начального регистра(Hi)    
received[3] -  Адрес начального регистра(Lo)
received[4] -  Количество регистров(Hi)        
received[5] -  Количество регистров (Lo)
********************************************************************************/
void getRegisters(unsigned char comm){
  int err =NO_ERROR;			// флаг ошибок
  unsigned int rr_Address = 0;	// адрес первого регистра 
  unsigned int rr_numRegs = 0;	// число регистров
  unsigned char  j = 3;			// response[3] - байт(Hi) первого  выводимого регистра
  unsigned int crc = 0;
  unsigned int   i = 0;
 
  rr_Address = (received[2]<<8)| received[3]; 	// Адрес начального регистра устройства (HiLo) 
  rr_numRegs =  (received[4]<<8)|received[5]; 	// Количество регистров 

  err = checAddr(comm,&rr_Address,rr_numRegs );	// проверяем наличие регистров и количество 

// --------собираем ответ------------
  response[0] = SlaveAddress;					// установить адрес устройства в ответе
  response[1] = comm;							// код команды (03 или 04)
  response[2] = rr_numRegs*2; 					// 2 bytes per reg  - байт данных в ответе  

 

if (err == NO_ERROR)	// регистры существуют и скопированы в буфер ответа - готовим ответ
	{  
	  for(i=0;i< rr_numRegs;  i++){	// заполняем ответ скопироваными в буфер значениями регистров
      response[j] = DataBuff[i] >> 8;	j++;			// старший байт (начинаем с J =3 )
      response[j] = DataBuff[i];     	j++;}			// младший байт
 	}//...
else         //--------------- ошибка адреса или количества регистров   ------------------------------------
	{
		response[1] = response[1] | 0x80;				// признак ошибки
		response[2] = ILLEGAL_DATA_ADDRESS; 			// код ошибки
		j = 3;											// количество байт в ответе бкез CRC
	}// конец обработки ------------------
	
//  --------------  Расчет  CRC  ------------ 
  crc = generateCRC(j+2);								// calculate CRC
  response[j] = crc >> 8;  j++;							// CRC upper byte
  response[j] = crc;       j++;						    // CRC lower byte
 


  response[j] = 0x00;      j+=1;//add null terminator

TX_EN_Write(1); //Assert TX Enable - Speak to Bus
    UART_UartPutString(response);
// for(i=0;i<j;i++) {UART_UartPutChar(response[i]);}	// Send the packet

}//..........................



/****************************************************************************************
*  подпрограмма  записи значения во  внутренний регистр.
*****************************************************************************************/
 /*            
Код функции:  06 
received[2] -  Адрес начального регистра(Hi)    
received[3] -  Адрес начального регистра(Lo)
received[4] -  Данные для даписи в регистр(Hi)        
received[5] -  Данные для даписи в регистр(Lo)
****************************************************************************************/
void writeReg(void)
{
  unsigned int wr_Address = 0;
  unsigned int crc, i,j = 0;
  //unsigned int errW   = 0;
	
 wr_Address = (received[2]<<8)|received[3]; 				// Адрес записываемого регистра(HiLo) 
 
  // готовим ответ
  response[0] = SlaveAddress;
  response[1] = 0x06;
  response[2] = received[2]; 								//useful to store  2 bytes per reg
  response[3] = received[3];

//TO DO CHECK VALUE IS ACTUALLY WRITTEN//
if (wr_Address<127) 	//если нет ошибок
	{
	 holdingReg[wr_Address] = (received[4]<<8)|received[5];	// меняем значение регистра на новое
	 response[4] =  holdingReg[wr_Address]>>8;				// передаем его 
	 response[5] =  holdingReg[wr_Address]&0xFF;			// в данные ответа 
	 j = 6;													// число байт в ответе (без CRC) 
 	}	
else 
	{
	 response[1] = 0x06|0x80;
	 response[2] = ILLEGAL_DATA_ADDRESS; 
	 j =3; 													// число байт в ответе (без CRC) 
 	}	
 //   ---------ваычисляем CRC-------------------
  crc = generateCRC(j+2);								
  response[j] = crc >> 8; j++;
  response[j] = crc; j+=1;

TX_EN_Write(1); //Assert TX Enable - Speak to Bus
  for(i=0;i<j;i++)  {UART_UartPutChar(response[i]); }// отправляем ответ
}//.............................



/****************************************************************************************
*  подпрограмма  записи значения во  внутренниe регистрs.
*****************************************************************************************/
 /*            
received[1] -  Код функции:   0x10
received[2] -  Адрес начального регистра(Hi)    
received[3] -  Адрес начального регистра(Lo)
received[4] -  количество регистров(Hi)        
received[5] -  количество регистров(Lo)
received[6] -  количество байт(Lo)
****************************************************************************************/
void writeMultipleRegs(void)
{
//возвращает адрес SL, функцию, адрес первого регистра и количество записанных регистров.
  unsigned int wmr_Address  = 0;
  unsigned int wmr_numBytes = 0;
  unsigned int valToWrite   = 0;	// новое значение регистра
  unsigned int crc,i = 0;
  unsigned char j = 0;

  wmr_Address = (received[2]<<8)|received[3]; // Combine address bytes	  Адрес начального регистра(HiLo) ;

  wmr_numBytes = received[6]/2;  				// число обновляемых регистров 

  response[0] = SlaveAddress;
  response[1] = 0x10;
  response[2] = received[2];   	// адрес первого регистра байт (Hi)
  response[3] = received[3];   	// адрес первого регистра  (Lo)
  response[4] = received[4];	// число регистров байт(Hi)
  response[5] = received[5];	// число регистров (Lo)

//TO DO CHECK VALUE IS ACTUALLY WRITTEN//
if (wmr_Address<127) 	//если нет ошибок
	{
  	  for(i=0;i<wmr_numBytes;i++)  {			// обновляем регистры
    	valToWrite = received[j]<<8; j++;
    	valToWrite |= received[j];	j++;
    	holdingReg[wmr_Address + i] = valToWrite; 
		j = 6;}            // количество байт в ответе бкез CRC
	}
else 
	{
	  response[1] = 0x10|0x80;					// признак ошибки
	  response[2] = ILLEGAL_DATA_ADDRESS; 		// код ошибки
	  j =3; 	       // количество байт в ответе бкез CRC	
 	}

 //   ---------ваычисляем CRC-------------------
  crc = generateCRC(j+2);	 
  response[j] = crc >> 8;  j++;
  response[j] = crc;       j+=1;

TX_EN_Write(1); //Assert TX Enable - Speak to Bus
for(i=0;i<j;i++){ UART_UartPutChar(response[i]); }	// отправим сообщение
}//.....................



/******************************************************************************/
/* Writes to a coil and then responds                                         */
/******************************************************************************/
void writeCoil(void)
{
  unsigned int wc_Address = 0;
  unsigned int wc_valToWrite = 0;
  unsigned int crc, i = 0;

  wc_Address =(received[2]<<8)| received[3]; 	// Адрес начального регистра(HiLo) 
  wc_valToWrite = (received[4]<<8)|received[5]; // данные для записи

  if(wc_valToWrite){coils[wc_Address] = 0xFF; }	// новое значение регистра
  else             {coils[wc_Address] = 0x00; }

  response[0] = SlaveAddress;
  response[1] = 0x05;
  response[3] =  received[3]; //2 bytes per reg
  response[2] =  received[4];

//TO DO CHECK VALUE IS ACTUALLY WRITTEN//
  response[4] = received[4];
  response[5] = received[5];

  crc = generateCRC(8);
  response[6] = crc >> 8;
  response[7] = crc;

TX_EN_Write(1); //Assert TX Enable - Speak to Bus
  for(i=0;i<8;i++){ UART_UartPutChar(response[i]); }
}


/******************************************************************************/
/* Write a Multiple coils and then responds                                             */
/******************************************************************************/
void writeMultipleCoils(void)	 
{
  unsigned int  wmc_Address = 0;
  unsigned int  wmc_numCoils = 0;
  unsigned char valToWrite;
  unsigned char q = 7; 				//count through vals to write	  адрес первого значения
	
  unsigned int  crc = 0;
  unsigned char howManyBytes = 0;	// целое число байт
  unsigned char remainder = 0;		// остаток 
  unsigned char i,j,l = 0;

  wmc_Address  = (received[2]<<8)|received[3]; 	// Адрес начального регистра(HiLo) 
  wmc_numCoils = (received[4]<<8)|received[5]; 	// количество jданных для записи

  response[0] = SlaveAddress;
  response[1] = 0x0F;							// The Function Code 

  howManyBytes = wmc_numCoils/8;
  remainder = wmc_numCoils % 8;

  if(remainder){    howManyBytes += 1;  }		// добавим байт для оставшихся данных
  response[2] = received[2];					// Data Address of the first coil
  response[3] = received[3];
  response[4] = received[4];					// The number of coils to written
  response[5] = received[5];
  l = wmc_Address;								// начнем с указанного coil 

  for(i=howManyBytes; i!=0; i--){
    valToWrite = received[q];	// q = 7 начало данных
    q++;
    if(i>0){	// для целого байта пишем все биты
      		for(j=0;j!=8;j++){
				if(CHECK_BIT(valToWrite, j)) { coils[l] = 0x01; }
				else						 { coils[l] = 0x00; }//need to sort out remainder stuff
			      l++;}
    }
    else{	// для дробной части запишем только укказаные в remainder
      	for(j=0;j!=remainder;j++){
      		if(CHECK_BIT(valToWrite, j)){  coils[l] = 0x01; }
      		else                        {  coils[l] = 0x00; }
      		l++; }
    }
  }
  crc = generateCRC(8);
  response[6] = crc >> 8;
  response[7] = crc;

TX_EN_Write(1); //Assert TX Enable - Speak to Bus
  for(i=0;i<8;i++){ UART_UartPutChar(response[i]); } // Slave Address,  0F,  Data Address of the first coil, num coils to written, CRC
}



/******************************************************************************************************************
 										обработчик сообщений
*******************************************************************************************************************/
void processMessage(void)	  
{  
	//unsigned char ERR; 
  	unsigned int crc;  //
	if(received[0] == SlaveAddress)
  {   
  // if(!checkCRC())  {return;}  //TODO: Fix and Enable!	//  проверка - CRC при ошибке - выход без ответа мастеру
 
 	 switch (received[1])
  	 {
	  case 0x01: { readCoil() 				;	break;};	// чтение статуса Coils (дискретных выходных битов). 
	  case 0x02: { readInputCoil()  		;	break;};	// чтение статуса дискретных входов
	  case 0x03: { getRegisters( 0x03)     ;	break;};	// *чтение значения выходных/внутренних регистров.    пример  [01][03][00][01][00][02][95][CB]
	  case 0x04: { getRegisters( 0x04)  	;	break;};	// *чтение значения входных регистров
	  case 0x05: { writeCoil() 				;	break;};	// запись выходного/внутреннего бита (Coil). 
	  case 0x06: { writeReg()       		;	break;};	// *запись внутреннего регистра. 
	  case 0x0F: { writeMultipleCoils() 	;	break;};	// запись нескольких выходных/внутренних битов (Coils). 
	  case 0x10: { writeMultipleRegs()  	;	break;};	// запись нескольких внутренних регистров. 

      default: {
				response[0] = SlaveAddress;					// адрес
		 		response[1] = received[1]| 0x80;			// накладываем маску ошибки
				response[2] = ILLEGAL_FUNCTION ;  			// ILLEGAL_FUNCTION Принятый код функции не поддерживается на подчиненном. 
				crc = generateCRC(5);						
				response[3] = crc >> 8;
  				response[4] = crc;
                
                TX_EN_Write(1); //Assert TX Enable - Speak to Bus
                for(int i=0;i<5;i++){ UART_UartPutChar(response[i]); } // сообщаем о не поддерживаемой функции
	           };
	
     };	

  }

 if(received[0] == 0)   { /*   вставить обработчик широковещательных сообщений   */ };

//modbusMessage = 0;
}//...................................



/* [] END OF FILE */


