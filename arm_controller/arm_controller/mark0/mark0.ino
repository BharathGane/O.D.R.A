#include <Arduino.h>


void setup() //initializing serial communication baud rate
{
  Serial.begin(9600);
}
  
void homes()//returns to initial position
{
  Serial.println("#7 P1000 T500");
  delay(1000);
  Serial.println("#4 P1300 T500");
  delay(1000);
  Serial.println("#15 P2350 T500");
  delay(1000);
  Serial.println("#19 P1000 T500");
  delay(1000);
  Serial.println("#16 P500 T500");
  delay(1000); 
}

void foward()//moves the arm forward
{
  Serial.println("#20 P1200 T1000");//moves elbow servo to position 1200
  delay(1000);
  Serial.println("#19 P1300 T1000");//moves shoulder servo to position 1400
  delay(1000);
  Serial.println("#15 P1800 T1000");//moves wrist servo to position 1900
  delay(1000);
}

void back1()//moving the arm backwards 
{
  Serial.println("#19 P1000 T500"); //moves shoulder servo to position 1000
  delay(1000);
  Serial.println("#15 P2350 T500");
  delay(1000);
}

void back2()//moving the arm backwards 
{
  Serial.println("#15 P2330 T500");
  delay(500);
  Serial.println("#16 P1500 #19 P1000 #20 P1200 T1000");
  delay(500);
}

void lift()//lifts the robot arm
{
 Serial.println("#16 P2400 #19 P1300 #20 P1700 T1000");
  delay(1000);
}

void grip()//Gripping the object
{
  Serial.println("#7 P1550 T500");
  delay(1000); 
}

void drop()//Drops the object
{
  Serial.println("#15 P1900 T500");//moves wrist servo to position 1900
  delay(1000);
  Serial.println("#7 P1000 T1000");
  delay(500); 
}

void turnC()//turns the arm clockwise
{
  Serial.println("#16 P500 T1000");
  delay(1000);
}

void turnA()//turns the arm anticlockwise
{
  Serial.println("#16 P2400 T1000");
  delay(1000);
}
void halfturn()//turns the arm clockwise
{
  Serial.println("#16 P1500 T1000");
  delay(1000);
}


void loop()
{  
    //Pick the object and place it on platform
    homes();
    delay(1000);
    foward();
    delay(1000);
    grip();
    delay(1000);
    back1();
    delay(1000);
    halfturn();
    delay(500);
    lift();
    delay(2000);
    drop();
    delay(1000);
    back2();
    delay(500);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Include the Servo library 
#include <Servo.h> 
// Declare the Servo pin 
int servoPin = 3; 
// Create a servo object 
Servo Servo1; 
void setup() { 
   // We need to attach the servo to the used pin number 
   Servo1.attach(servoPin); 
}
void loop(){ 
   // Make servo go to 0 degrees 
   Servo1.write(0); 
   delay(1000); 
   // Make servo go to 90 degrees 
   Servo1.write(90); 
   delay(1000); 
   // Make servo go to 180 degrees 
   Servo1.write(180); 
   delay(1000); 
}

