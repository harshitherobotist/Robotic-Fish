 /* ▪  * Team Id:      PF#47
 ▪  * Author List:     Harshit Sharma, Aniket nayak, Rohan Shani,Lakshay goyal
 ▪  * Filename:       fish_transmitter  
 ▪  * Theme:           PATROL FISH
 ▪  * Functions:       DataPackage,setup(),loop(),buzzer_initial() \
 ▪  * Global Variables:  int joy1_Xval, joy2_Yval, joy1_Yval, joy2_Xval,push_button;
                         const byte address;
                         char back_fin,front_fin;  */ 
#include<RF24.h>
#include<SPI.h>
#include<nRF24L01.h>
int joy1_Xval, joy2_Yval, joy1_Yval, joy2_Xval,push_button;//returns integer value
const byte address[6]="00010";
char back_fin,front_fin;
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
                 and reads joystick values
 ▪  * Example Call:   setup() */ 
void setup() {
  // put your setup code here, to run once:
//data=DataPackage; // creating a variable of the data structure above
Serial.begin(9600);  // setting baud rate = 9600 for communucation
pinMode(6,OUTPUT);  // buzzer connected at digital pin 2 of arduino
pinMode(5,INPUT_PULLUP);  // Push button for buzzer connected to digital pin 5 and pulled up 
radio.begin();  // begin radio transmission
radio.openWritingPipe(address);
radio.setPALevel(RF24_PA_MIN);
radio.setDataRate(RF24_250KBPS);
radio.stopListening();
pinMode(A0,INPUT); // Joystick 1 x val
pinMode(A1,INPUT); // Joystick 1 y val
pinMode(A5,INPUT); // Joystick 2 x val
pinMode(A6,INPUT); // Joystick 2 y val
buzzer_initial();  //buzzing buzzer for 3 seconds

}

/* ▪  * Function Name: loop() 
 ▪  * Input:     none
 ▪  * Output:    none
 ▪  * Logic:     reads analog values from joysticks continously
 ▪  * Example Call:   loop() */ 
void loop() {
  // put your main code here, to run repeatedly:
   joy1_Xval=analogRead(A5);
   joy1_Yval=analogRead(A1);
   joy2_Yval=analogRead(A0);
   joy2_Xval=analogRead(A6);
   push_button = digitalRead(5); //declarartion of push_button variable for getting push buttton value
   if(push_button == LOW) // if the buuton is pressed then buzzzer should beep
   {
    buzzer_initial();
   }
data.servo2= map(joy1_Xval,0,1023,180,0);  // mapping analog values to rotate the fish left or right
data.servo1= map(joy2_Yval,0,1023,20,5);  // mapping analog values so that to give reciprocating motion for back fin of motor
  radio.write(&data, sizeof(DataPackage)); //sending data for radio communication
  Serial.print("data of servo1 =  ");
  Serial.print(data.servo1);  //printing data of servo 1 on Serial monitor
  Serial.print("    ");
  Serial.print("data of servo2 =  ");  
  Serial.print(data.servo2);  //printing data of servo 2 on Serial monitor
  Serial.print("    ");
  Serial.print("push_button value =  ");
  Serial.println(push_button);  //printing data of push button value on serial monitor
  
  
}
/* ▪  * Function Name: buzzer_initial() 
 ▪  * Input:     none
 ▪  * Output:    none
 ▪  * Logic:     beeps the buzzer for 3 seconds
 ▪  * Example Call:   buzzer_initial() */ 
void buzzer_initial(){
analogWrite(6,100);
delay(3000);
analogWrite(6,255);
}
