/* ▪  * Team Id:      PF#47
 ▪  * Author List:     Harshit Sharma, Aniket nayak, Rohan Shani,Lakshay goyal
 ▪  * Filename:       fish_reciever  
 ▪  * Theme:           PATROL FISH
 ▪  * Functions:       DataPackage,setup(),loop() \
 ▪  * Global Variables:  int i (for operating for loop)  
                         const byte address; */
#include<RF24.h>
#include<Servo.h>
#include<SPI.h>
#include<nRF24L01.h>
const byte address[6]="00010";
Servo s1,s2;
int i;
RF24 radio(7,8);

/* ▪  * Function Name: DataPackage() 
 ▪  * Input:     none
 ▪  * Output:    value of 2 bytes
 ▪  * Logic:     contains data in form of byte(joystick values) for radio communication
 ▪  * Example Call:   DataPackage() */ 
struct DataPackage{
 byte servo1;
 byte servo2;
};

DataPackage data;
 /* ▪  * Function Name: setup() 
 ▪  * Input:     none
 ▪  * Output:    none
 ▪  * Logic:     initiates serial communication and radio communication
                 and attaches servo motors
 ▪  * Example Call:   setup() */ 
void setup() {
  // put your setup code here, to run once:
radio.begin();
Serial.begin(9600);

radio.openReadingPipe(0, address);
radio.setPALevel(RF24_PA_MAX);
radio.startListening();
radio.setDataRate(RF24_250KBPS);
s1.attach(3);
s2.attach(5);
}
/* ▪  * Function Name: loop() 
 ▪  * Input:     none
 ▪  * Output:    none
 ▪  * Logic:     reads radio data and operates servo motors by giving angles
 ▪  * Example Call:   loop() */ 
void loop() {
  // put your main code here, to run repeatedly:
if(radio.available())
{
  radio.read(&data,sizeof(DataPackage));

    Serial.print("rotation=");
    Serial.print(data.servo1);
    Serial.print("speed=");
    Serial.println(data.servo2);
    s1.write(data.servo2);  // turning motor left or right based on desired signal
    for(i=0;i<180;i=i+20) //increasing or decresing speed of reciprocating motion of the back fin of the fish as desired while sweeping in one direction from 0 to 180 degree
        {
          s2.write(i);
          delay(data.servo1);  // as the delay value increses the fin speed decreses as it sweeps in one direction from 0 to 180 degree
        }
    for(i=180;i>0;i=i-20)  // doing same thing for other part of sweep
        { 
          s2.write(i);
          delay(data.servo1);
        }
}
}
