#include <Arduino.h>
#include <Wire.h>
#include <AFMotor.h>

#define MAXSPEED 255

char c;
AF_DCMotor motore(3);
String receivedBuffer = "NULL";

void setup() {

  motore.setSpeed(MAXSPEED);
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output

}

void loop() {
  
  Wire.requestFrom(8, 4);    // request 6 bytes from peripheral device #8

  while (Wire.available()) { // peripheral may send less than requested
    
    c = Wire.read(); // receive a byte as character
    
    receivedBuffer.concat(c);

  }
  Serial.println(receivedBuffer);
  receivedBuffer = "";
  delay(500);

}

void motorControl(){

  switch(receivedBuffer){

    default:
      motore.run(RELEASE);
      break;

    case "0011":
    


  }

}