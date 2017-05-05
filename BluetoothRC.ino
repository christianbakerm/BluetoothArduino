#include <SoftwareSerial.h>

/*
Project: accelerometer controlled rc car
Date: Oct 13, 2015
Author: Christian Baker
Description: Firmware used on arduino controlled RC car. Uses data from any devices
accelerometer to control the movement of the car
*/
 #include <AFMotor.h>
 #define START_CMD '>'
 #define DEBUG 1 
String inText;
float value0, value1, value2;
int forspeed = 255;
SoftwareSerial mySerial(2, NULL);
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

 void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("Starting accelerometer..");
  motor1.setSpeed(250);
  motor2.setSpeed(250);
  motor3.setSpeed(250);
  motor4.setSpeed(250);
  
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
 }
 void loop() {
   mySerial.flush();
   unsigned long logCount = 0L;
   
   char val= ' '; //Read the serial
   
    if (mySerial.available() > 0) {
      while (mySerial.available() > 0) {
        value0 = mySerial.parseFloat();
        value1 = mySerial.parseFloat();
        value2 = mySerial.parseFloat();
        
        if (DEBUG) {
          Serial.print("Val0: ");
          Serial.println(value0);
        
          Serial.print("Val1: ");
          Serial.println(value1);
        
          Serial.print("Val2: ");
          Serial.println(value2);
        }
        
        // Stop motors if device is held in neutral position
        if (value0 > 9 && value0 < 10 && value2 > 0 && value2 < 1 ) {
          motor1.run(RELEASE);
          motor2.run(RELEASE);
          motor3.run(RELEASE);
          motor4.run(RELEASE);
          
        } else if (value0 < 9 && value2 > 1 && value1 > -3 && value1 < 3) {
          // Move Forward if device is tilted forward
          forspeed = value2;
          forspeed = map(forspeed, 1, 9, 100, 255);
          motor1.setSpeed(forspeed);
          motor2.setSpeed(forspeed);
          motor3.setSpeed(forspeed);
          motor4.setSpeed(forspeed);
      
          motor1.run(FORWARD);
          motor2.run(FORWARD);
          motor3.run(FORWARD);
          motor4.run(BACKWARD);
          
           } else if (value1 < -3) {
          // Turn Left if device is tilted left
          motor1.setSpeed(255);
          motor2.setSpeed(255);
          motor3.setSpeed(255);
          motor4.setSpeed(255);
      
          motor1.run(BACKWARD);
          motor2.run(FORWARD);
          motor3.run(FORWARD);
          motor4.run(FORWARD);
          
          } else if (value1 > 3) {
          // Turn Right if device is tilted right
          motor1.setSpeed(255);
          motor2.setSpeed(255);
          motor3.setSpeed(255);
          motor4.setSpeed(255);
      
          motor1.run(FORWARD);
          motor2.run(BACKWARD);
          motor3.run(BACKWARD);
          motor4.run(BACKWARD);
          
        } else if (value0 < 9 && value2 < 0 && value1 > -3 && value1 < 3) {
          // Move backward if device is tilted back
          forspeed = value2;
          forspeed = map(forspeed, -9, -1, 255, 100);
          motor1.setSpeed(forspeed);
          motor2.setSpeed(forspeed);
          motor3.setSpeed(forspeed);
          motor4.setSpeed(forspeed);
      
          motor1.run(BACKWARD);
          motor2.run(BACKWARD);
          motor3.run(BACKWARD);
          motor4.run(FORWARD);
        }
      }
    }
 }
