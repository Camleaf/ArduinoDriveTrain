#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>
#include <RF24_config.h>

#define LeftJoyX A0
#define LeftYoyY A1
#define RightJoyX A2
#define RightJoyY A3


#define ControlDeadZone 10

typedef struct{
  int16_t LeftJoyForce; // How far from center the joystick is
  float32_t LeftJoyOrient; // The angle relative to the centre of the joystick
  int16_t RightJoyForce;
  float32_t RightJoyOrient;
}__attribute__((packed)) DataStruct;

DataStruct dataPackage;

RF24 radio(49,48); // CE, CSN CHANGE THESE PINS
// SPI PINS
// SCK: 52
// MO: 51
// MI: 50

//Vars

//Inputs
int leftX = 512
int leftY = 512
int rightX = 512
int rightY = 512

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
  radio.startListening();

  // Make an LED or something to check if Radio is transmitting

}
void loop() {
  leftX = analogRead(LeftJoyX);
  leftY = analogRead(LeftJoyY);
  rightX = analogRead(RightJoyX);
  rightY = analogRead(RightJoyY);
  // put your main code here, to run repeatedly:


}

// for the cars code, I want the turning to set a point outside the car to turn around. The turning itself will be a constant value, however it will have a perception of distance by the force vector and the turn force
// I can finish this while parts arrive



























