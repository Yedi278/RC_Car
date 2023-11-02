#include <Arduino.h>
#include <Wire.h>
#include <AFMotor.h>

#define MAXSPEED 255

char c;
AF_DCMotor motore(3);
AF_DCMotor sterzo(1);

String receivedBuffer = "NULL";
char charBuff[5];

void motorControl();


void setup() {

  motore.setSpeed(MAXSPEED);
  sterzo.setSpeed(MAXSPEED);

  Wire.begin();        // join i2c bus (address optional for master)
  // Serial.begin(9600);  // start serial for output

}

void loop() {
  
  Wire.requestFrom(8, 4);    // request 4 bytes from peripheral device #8

  while (Wire.available()) { // peripheral may send less than requested
    
    c = Wire.read();         // receive a byte as character
    
    receivedBuffer.concat(c);

  }

  motorControl();
  receivedBuffer = "";
  delay(5);
}

void motorControl(){

  if      (receivedBuffer == "0011"){

    motore.run(FORWARD);

  }else if(receivedBuffer == "0012"){

    motore.run(BACKWARD);

  }else if(receivedBuffer == "0013"){

    motore.run(RELEASE);

  }else if(receivedBuffer == "0021"){

    sterzo.run(FORWARD);

  }else if(receivedBuffer == "0022"){

    sterzo.run(BACKWARD);

  }else if(receivedBuffer == "0023"){

    sterzo.run(RELEASE);

  }
}