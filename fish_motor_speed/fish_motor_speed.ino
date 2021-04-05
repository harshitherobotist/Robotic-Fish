#include<RF24.h>
#include<Servo.h>
#include<SPI.h>
#include<nRF24L01.h>
const byte address[6]="00010";
Servo s1;
RF24 radio(7,8);
void setup() {
  // put your setup code here, to run once:
radio.begin();
Serial.begin(9600);

radio.openReadingPipe(0, address);
radio.setPALevel(RF24_PA_MIN);
radio.startListening();
s1.attach(3);
}

void loop() {
  // put your main code here, to run repeatedly:
if(radio.available())
{
  int servo1="";

radio.read(&servo1,sizeof(servo1));
  
  Serial.println(servo1);
  for(int i=0;i<180;i=i+10){
    s1.write(i);
    delay(servo1);
  }
  for(int i=180;i>0;i=i-10){
    s1.write(i);
    delay(servo1);
  }
}
}
