#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <stdio.h>
#include <printf.h>
#include <RF24_config.h>
#include <Servo.h>
using namespace std;

#define MessageID 45949




const int ServoPins[3] = {2,3,4};
//       Servos    1 2 3
const int ServoOffsets[3] = {0, 120, 240};

const uint8_t L_EN[3] = {30,32,34};
const uint8_t L_PWM[3] = {40,42,44};
const uint8_t R_EN[3] = {31,33,35};
const uint8_t R_PWM[3] = {41,43,45};
const uint8_t pushDistance = 512;
const float moduleDistance = 188.375;

int MotorSpeeds[3] = {0,0,0};
int ServoPositions[3] = {0, 0, 0};
Servo ServoObjects[3];


// Still need to do motor stuff


//Define structs
// This is how data is recieved from the controller
typedef struct{
  int16_t Identifier;
  float LeftJoyForce; // How far from center the joystick is
  float LeftJoyOrient; // The angle relative to the centre of the joystick
  float RightJoyForce;
  float RightJoyOrient;
}__attribute__((packed)) DataStruct;
DataStruct dataPackage;


typedef struct Point {
    float x, y;
};

// Define functions
Point lineIntersect(Point A, Point B, Point C, Point D);
void getModuleCrab(int (&Mos)[3], int (&Svp)[3]);
void getModuleSnake(int (&Mos)[3], int(&Svp)[3]);
float tangentAngleToXAxis(Point Centre, Point TanPoint);






// Define radio
RF24 radio(48,49); // CE, CSN
const byte address[5] = "0110";



void setup() {
  printf_begin();
  pinMode(48,  OUTPUT); 
  pinMode(49, OUTPUT);


  // attach servos to pins
  for (int i = 0; i < 3; i++){
    ServoObjects[i].attach(ServoPins[i]);
    pinMode(L_EN[i],  OUTPUT); 
    pinMode(R_EN[i],  OUTPUT); 
    pinMode(L_PWM[i],  OUTPUT); 
    pinMode(R_PWM[i],  OUTPUT);
  }

  // end pinmodes

  Serial.begin(9600); 
  if (!radio.begin()) { Serial.println(F("radio hardware not responding!"));}
  radio.openReadingPipe(0, address);
  radio.setPALevel(-18);
  radio.startListening();

  // Make an LED or something to check if Radio is transmitting
}






void loop() {
  while (!radio.available()); // If the radio drops out repeatedly i'll add the code for a restart then
  radio.read( &dataPackage, sizeof(DataStruct) );

  if (dataPackage.Identifier != MessageID){ // If unauthorized message
    return;
  };

  if (dataPackage.RightJoyForce == 0){ // if not turning, I want the simpler crab drive math to work
    getModuleCrab(MotorSpeeds, ServoPositions);
  } else {
    // I want it to reset until I get snake working
    // Once the complicated snake math is working, it goes here
    getModuleDefaults(MotorSpeeds, ServoPositions);
  }

  //I will need to figure out how to get the servo positioning to work
  for (int i = 0; i < 3; i++){
    
    int rotation = ServoPositions[i] - ServoOffsets[i];
    rotation = (rotation % 360);
    
    if (rotation < 180){
      analogWrite(L_PWM[i], 0);
      digitalWrite(L_EN[i], LOW);
      digitalWrite(R_EN[i], HIGH);
      analogWrite(R_PWM[i], MotorSpeeds[i]);
      ServoObjects[i].write(rotation);


    } else {
      analogWrite(R_PWM[i], 0);
      digitalWrite(R_EN[i], LOW);
      analogWrite(L_PWM[i], MotorSpeeds[i]);
      digitalWrite(L_EN[i], HIGH);
      ServoObjects[i].write(rotation - 180);
    }
  }
  
}








void getModuleCrab(int (&Mos)[3], int(&Svp)[3]) {
   // crab drive math; point and go
  for (int i = 0; i<3; i++){
    Mos[i] = round(dataPackage.LeftJoyForce); // still on the 512 scale NEED FIX
    Svp[i] = round(degrees(dataPackage.LeftJoyOrient));
  }
}


void getModuleSnake(int (&Mos)[3], int(&Svp)[3]){
   // Find rotation centre
    // Define vars
   int L_Orient = dataPackage.LeftJoyOrient;
   int R_Orient = dataPackage.RightJoyOrient + L_Orient; // rotate R_orient with L_orient
   int L_Force = dataPackage.LeftJoyForce;
   int R_Force = dataPackage.RightJoyForce;
   
   // Find the length of the vector
   int Vector_Hyp = L_Force - R_Force;
   
   Point Centre{0,0};
   // Find chord midpoint first
   // Don't even need to find chord first this vector is the midpoint
   float Vector_X = Vector_Hyp * cos(R_Orient);
   float Vector_Y = Vector_Hyp * sin(R_Orient);
   Point Midpoint{Vector_X, Vector_Y};
   // find any point on perpendicular bisector
   float Bisector_Slope = -(Midpoint.x - Centre.x)/(Midpoint.y-Centre.y);
   float Bisector_X = 513;
   float Bisector_Y_Intercept = Midpoint.y-(Midpoint.x * Bisector_Slope);
   float Bisector_Y = Bisector_Slope * Bisector_X + Bisector_Y_Intercept;
   Point ArbitraryBisectorSlope{Bisector_X, Bisector_Y};



   float Vector_X = Vector_Hyp * cos(L_Orient);
   float Vector_Y = Vector_Hyp * sin(L_Orient);
   Point AbitraryCenterLine{Vector_X,Vector_Y};

   // Rotation centre here
   Point Global_Rot_Center = lineIntersect(Centre, AbitraryCenterLine, Midpoint, ArbitraryBisectorSlope);
   
   // Now to find servo positions and motor speeds

   // Calculate motor speeds is after servo pos because we need the max
   float Radii[3] = {0,0,0};
   float Max_Rad = 0;
   for (int i = 0; i <3; i++){
      float Mdist = moduleDistance;
      // find the x/y of the motor
      int angle = radians(ServoOffsets[i]);
      float Vector_X = Mdist * cos(angle);
      float Vector_Y = Mdist * sin(angle);

      Point Module_Loc{Vector_X, Vector_Y};
      float Circle_rad = hypot(Module_Loc.x-Global_Rot_Center.x, Module_Loc.y-Global_Rot_Center.y);
      float angle = tangentAngleToXAxis(Global_Rot_Center,Module_Loc);

      Svp[i] = round(degrees(angle));
      Radii[i] = Circle_rad;
      if (Circle_rad > Max_Rad){
        Max_Rad = Circle_rad;
      }

    }

    for (int i=0; i< 3; i++){
      // Speed is on scale of 0 to 512
      float Speed_factor = Radii[i] / Max_Rad;
      Mos[i] = Speed_factor * pushDistance;

    }



}



void getModuleDefaults(int (&Mos)[3], int(&Svp)[3]) {
  // Resets motor speeds and all to defaults
  for (int i = 0; i<3; i++){
    Mos[i] = 0;
    Svp[i] = ServoOffsets[i];
  }
}

Point lineIntersect(Point A, Point B, Point C, Point D){
    float a1 = B.y - A.y;
    float b1 = A.x - B.x;
    float c1 = a1 * A.x + b1 * A.y;

    float a2 = D.y - C.y;
    float b2 = C.x - D.x;
    float c2 = a2 * C.x + b2 * C.y;

    float determinant = a1 * b2 - a2 * b1;

    if (determinant == 0) {
        return Point{0,0};
    } else {
        float x = (b2 * c1 - b1 * c2) / determinant;
        float y = (a1 * c2 - a2 * c1) / determinant;
        return Point{x, y};
    }
}


float tangentAngleToXAxis(Point Centre, Point TanPoint) {
    // Find slope of rad
    float radius_slope = (TanPoint.y - Centre.y) / (TanPoint.x - Centre.x);
    
    // Calculate the slope of the tangent line
    float m_tangent = -1 / radius_slope;  // Perpendicular slope
    
    //Calc tangent
    float angle_radians = atan(m_tangent);  // atan returns angle in radians
    
    return angle_radians; 
}