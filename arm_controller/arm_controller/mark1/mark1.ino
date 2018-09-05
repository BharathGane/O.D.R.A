#include <Servo.h>

// Declare the Servo pin 
int servoPin1 = 3;
int servoPin2 = 5;
int servoPin3 = 6;
int servoPin4 = 9;
int servoPin5 = 10;

// Servo Initialize
Servo Servo1;
Servo Servo2;
Servo Servo3;
Servo Servo5;

// String Buffer
String inData;

// Default COnfiguration
void reset() {
  Servo1.write(65);
  Servo2.write(95);
  Servo3.write(60);
  delay(3000);
}

void servo_control_x(int _x){
  int x;
  x = map(_x,0,1000,65,115);

  reset();
  
  Servo1.write(65);
  delay(3000);

  Servo1.write(x);
  
  delay(10000);
  Servo5.write(0);
  delay(3000);
  Servo5.write(180);
  delay(3000);
  
  Servo1.write(180);
  
  delay(3000);
  Servo5.write(0);
  delay(3000);
  Servo5.write(180);
  delay(3000);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Waiting for coordinates...\n");
  
  Servo1.attach(servoPin1);
  Servo2.attach(servoPin2);
  Servo3.attach(servoPin3);
  Servo5.attach(servoPin5);
}

void loop(){
  Serial.flush();
  reset();
  while (Serial.available() > 0)
  {
      String indata;
      char recieved = Serial.read();
      inData += recieved; 

      // Process message when new line character is recieved
      if (recieved == '\n')
      {
          Serial.print("Arduino Received: ");
          Serial.print(inData);
          servo_control_x(inData.toInt());
          Serial.flush();
          inData = ""; // Clear recieved buffer
      }
  }
}
