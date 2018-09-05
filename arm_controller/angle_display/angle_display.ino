#include <Wire.h>

int angle = 0;

byte seven_seg_digits[10][7] = { { 1,1,1,1,1,1,0 },  // = 0
                                 { 0,1,1,0,0,0,0 },  // = 1
                                 { 1,1,0,1,1,0,1 },  // = 2
                                 { 1,1,1,1,0,0,1 },  // = 3
                                 { 0,1,1,0,0,1,1 },  // = 4
                                 { 1,0,1,1,0,1,1 },  // = 5
                                 { 1,0,1,1,1,1,1 },  // = 6
                                 { 1,1,1,0,0,0,0 },  // = 7
                                 { 1,1,1,1,1,1,1 },  // = 8
                                 { 1,1,1,0,0,1,1 }   // = 9
                                 };

void sevenSegWrite(byte digit) {
  byte pin = 2;
  for (byte segCount = 0; segCount < 7; ++segCount) {
    digitalWrite(pin, !seven_seg_digits[digit][segCount]);
    ++pin;
  }
}

void receiveEvent(int bytes) {
  angle = Wire.read();    // read one character from the I2C
}

void setup() {
  Wire.begin(9);
  Wire.onReceive(receiveEvent);          
  pinMode(2, OUTPUT);   
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  int units = angle%10;
  int tens = (angle / 10) % 10;
  int hundreds = angle/100;

  digitalWrite(13, HIGH);
  digitalWrite(12,LOW);
  digitalWrite(11,LOW);
  sevenSegWrite(units);
  delay(10);
  
  digitalWrite(12,HIGH);
  digitalWrite(13,LOW);
  digitalWrite(11,LOW);
  sevenSegWrite(tens);
  delay(10);
  
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);
  digitalWrite(11,HIGH);
  sevenSegWrite(hundreds);
  delay(10);
   
}
