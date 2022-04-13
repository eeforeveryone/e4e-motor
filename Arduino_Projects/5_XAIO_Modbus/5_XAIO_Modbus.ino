//https://github.com/emelianov/modbus-esp8266

/* ========================================
 *
 * Modbus Test Code
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

#define txEn 0
#define LED 9

//Magic Packet Definition:
uint8_t packet[9] = {0x01,0x03,0x00,0x00,0x00,0x01,0x84,0x0A, 0x00};  //REQUEST REG1 from SLAVE 1
uint8_t packetlength = 8;


#include <ModbusRTU.h>
ModbusRTU mb;


void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200); //this is for monitoring
  Serial1.begin(38400, SERIAL_8E1); //even parity, 38400 baud.
  mb.begin(&Serial1, txEn, true); //use txenable, positive logic
  mb.setBaudrate(38400);

  mb.master();

  pinMode(txEn, OUTPUT);
  digitalWrite(txEn, LOW);
  pinMode(LED,OUTPUT);
}


uint16_t holding[20]; //local copy of holding registers

uint32_t blinkmillis = 0;
uint32_t othermillis = 0;


uint16_t ADDR = 0;
uint16_t state = 99;

void loop() {
  // put your main code here, to run repeatedly:

  if(Serial1.available()){ //Loopback slave responses
    Serial.print(Serial1.read(), HEX);
    //Serial.write(Serial1.read());
    //digitalWrite(LED,HIGH);
  }



if(blinkmillis + 500 < millis()){
  blinkmillis = millis();

  digitalWrite(LED,!digitalRead(LED));
}


if(othermillis + 50 < millis()){ //Periodically send data Requests
  othermillis = millis();

  if(!mb.slave()){ //if the previous tranaction has finished
    switch(state){
        case 0:
          Serial.print("\n0: ");
          mb.writeHreg(1, 1, (uint16_t) 1500); //set P term for speed regulator, units is thousanths of "Pterm"
          state = 1;
          break;
        case 1:
          Serial.print("\n1: ");
          mb.writeHreg(1, 2, (uint16_t) 0); //set I term for speed regulator, units is thousanths of "Iterm"
          state = 2;
          break;
        case 2:
          Serial.print("\n2: ");
          mb.writeHreg(1, 3, (uint16_t) 1000); //set P term for position regulator, units is thousanths of "Pterm"
          state = 3;
          break;
        case 3:
          Serial.print("\n3: ");
          mb.writeHreg(1, 4, (uint16_t) 0); //set I term for position regulator, units is thousanths of "Iterm"
          state = 4;
          break;
        case 4:
          Serial.print("\n4: ");
          mb.writeHreg(1, 5, (uint16_t) 1800); //set Nudge, in Deg/10, I.E. 3600 = 1 rotation.
          state = 5;
          break;
        default:
          if(state != 99){
            //Serial.println("Init complete!");
            state = 100;
          }
          //donothing
          break;
      }
  }

    //Serial.print("Ping!");
}


  if(Serial.available()){ //from USB to HARDWARE
    while(Serial.available()){
      Serial.read();
    }
    Serial.println(" "); //newline to show response

    if(state > 99){//config is done!
      mb.writeHreg(1, 0, 1); //set "Go" bit, will tell motor to spin "REG5" degrees 
    }else{
      state = 0; //start init sequence
      Serial.println("ERROR! Init not complete!");
    }

  }

mb.task(); //must do periodially

}
