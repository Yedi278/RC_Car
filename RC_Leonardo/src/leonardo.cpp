#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <string.h>

#define MSG_LENGHT 4

SoftwareSerial bt(10,9);

char sendbuffer[5] = "NULL";
char b ;
String btBuffer = "";
String SendBuffer = "NULL";

void sendMessage() {

  if(SendBuffer != "NULL"){
    
    SendBuffer.toCharArray(sendbuffer,MSG_LENGHT+1);
    Wire.write(sendbuffer);
  
  }else{

    Wire.write("INIT");

  }
}


void setup() {

  bt.begin(10000);
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(sendMessage); // register event

}

void loop() {
  
  b = bt.read();

  while(b != -1){

    btBuffer.concat(b);
    b = bt.read();

  }
  if(btBuffer.length() == MSG_LENGHT){

    SendBuffer = btBuffer;
    btBuffer = "";
  }
  
  
}