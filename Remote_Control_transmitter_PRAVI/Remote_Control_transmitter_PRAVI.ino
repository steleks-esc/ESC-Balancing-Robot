#include <SPI.h>  //the communication interface with the modem
#include "RF24.h" //the library which helps us to control the radio modem

//define the data pins
int joyX = A1;
int joyY = A0;

int data[2] = {0, 0};
int byte2send;
RF24 radio(7,8); //10 and 9 are a digital pin numbers to which signals CE and CSN are connected
                                      
//const uint64_t pipe = 0xE8E8F0F0E1LL; //the address of the modem, that will receive data from Arduino
const byte address[6] = "00001";

void setup(void){
  Serial.begin(9600);
  radio.begin();                      //it activates the modem
  radio.openWritingPipe(address);        //sets the address of the receiver to which the program will send data
}

void loop(){
  //Send signal data
  data[0] = analogRead(joyX);
  data[1] = analogRead(joyY);
   byte2send = B00000000;

   if (data[0] > 550){byte2send |= B00000100;} //naprijed
   if (data[0] < 400){byte2send |= B00001000;} //nazad

   //data Y
   if (data[1] > 550 ){byte2send |= B00000001;} //desno
   if (data[1] < 400 ){byte2send |= B00000010;} //lijevo

  //  data[0] = byte2send;

   radio.write(&byte2send, sizeof(byte2send));
  //  Serial.println(*data);
  
}
