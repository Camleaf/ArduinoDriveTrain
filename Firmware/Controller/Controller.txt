#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <stdio.h>
#include <printf.h>
#include <RF24_config.h>
#include <BTS7960.h>
using namespace std;

#define LeftJoyX A0
#define LeftJoyY A1
#define RightJoyX A2
#define RightJoyY A3
#define MessageID 45949
#define ControlDeadZone 10

typedef struct{
  int16_t Identifier;
  float LeftJoyForce; // How far from center the joystick is
  float LeftJoyOrient; // The angle relative to the centre of the joystick
  float RightJoyForce;
  float RightJoyOrient;
}__attribute__((packed)) DataStruct;

DataStruct dataPackage;

RF24 radio(49,48); // CE, CSN CHANGE THESE PINS
// SPI PINS
// SCK: 52
// MO: 51
// MI: 50

//Vars

//Inputs
int leftX = 512;
int leftY = 512;
int rightX = 512;
int rightY = 512;
int VX = 0;
int VY = 0;
int OX = 512;
int OY = 512;
float force = 0;
//End vars


const byte address[5] = "0110";

void setup() {
  // pinmodes
  printf_begin();
  pinMode(48,  OUTPUT); 
  pinMode(49, OUTPUT);
  // end pinmodes

  Serial.begin(9600); 
  if (!radio.begin()) { Serial.println(F("radio hardware not responding!"));}
  radio.openReadingPipe(0, address);
  radio.setPALevel(-18);
  radio.stopListening();

  // Make an LED or something to check if Radio is transmitting
  dataPackage.Identifier = MessageID;
}



void loop() {
  leftX = analogRead(LeftJoyX);
  leftY = analogRead(LeftJoyY);
  rightX = analogRead(RightJoyX);
  rightY = analogRead(RightJoyY);
  // put your main code here, to run repeatedly:
  
  //left side
  VX = leftX - OX;
  VY = leftY - OY;
  force = sqrt(pow(VX, 2) + pow(VY, 2));
  if (force < ControlDeadZone){
    dataPackage.RightJoyForce = 0;
    dataPackage.LeftJoyOrient = 0;
  } else {
    dataPackage.LeftJoyForce = sqrt(force);
    dataPackage.LeftJoyOrient = atan2(VX,VY);
  }
  

  VX = rightX - OX;
  VY = rightY - OY;
  force = sqrt(pow(VX, 2) + pow(VY, 2));
  if (force < ControlDeadZone){
    dataPackage.RightJoyForce = 0;
    dataPackage.RightJoyOrient = 0;
  } else {
    dataPackage.RightJoyForce = sqrt(force);
    dataPackage.RightJoyOrient = atan2(VX,VY);
  }


  radio.write(&dataPackage, sizeof(DataStruct));
  delay(10);


}

// for the cars code, I want the turning to set a point outside the car to turn around. The turning itself will be a constant value, however it will have a perception of distance by the force vector and the turn force
// I can finish this while parts arrive
