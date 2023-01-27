#include <SPI.h>
#include <Servo.h>
#include "Wire.h"
int requested_state;   
// orientation/motion vars

float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

float pitch;
float roll;
float rollFiltered;

#define PI 3.1415926535897932384626433832795


Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

Servo servo5;
Servo servo6;
Servo servo7;
Servo servo8;

Servo servo9;
Servo servo10;
Servo servo11;
Servo servo12;



int AccX;
int AccY;
int AccZ;
int JoyX;
int JoyY;
int Switch1;
int Switch2;
int Switch3;
int Switch4;
int JoyButton;

int x;
int y;
int z;

int yaw;
int r;
int p;


// timers

unsigned long currentMillis;
unsigned long previousMillis;
unsigned long previousWalkMillis;
unsigned long previousSafetyMillis;

//multipier values for compliance

float multiplierKneesRight = 2;
float multiplierShouldersRight = 2;
float multiplierHipsRight = 0;

float multiplierKneesLeft = 2;
float multiplierShouldersLeft = 2;
float multiplierHipsLeft = 0;

// filters

int filterKneesRight = 30;
int filterShouldersRight = 25;
int filterHipsRight = 30;

int filterKneesLeft = 30;
int filterShouldersLeft = 25;
int filterHipsLeft = 30;

// global joint threshold value for hall effects
int threshholdGlobal =  5;

// values to write out to servos

float servo1Pos;    // initial value
float servo2Pos;
float servo3Pos;
float servo4Pos;
float servo5Pos;
float servo6Pos;
float servo7Pos;
float servo8Pos;
float servo9Pos;
float servo10Pos;
float servo11Pos;
float servo12Pos;

float servo1PosTrack;   // ongoing tracking value
float servo2PosTrack;
float servo3PosTrack;
float servo4PosTrack;
float servo5PosTrack;
float servo6PosTrack;
float servo7PosTrack;
float servo8PosTrack;
float servo9PosTrack;
float servo10PosTrack;
float servo11PosTrack;
float servo12PosTrack;

float servo1PosFiltered;  // filtered values
float servo2PosFiltered;
float servo3PosFiltered;
float servo4PosFiltered;
float servo5PosFiltered;
float servo6PosFiltered;
float servo7PosFiltered;
float servo8PosFiltered;
float servo9PosFiltered;
float servo10PosFiltered;
float servo11PosFiltered;
float servo12PosFiltered;

// servo offsets for default position - knees at 45', hips at 0', shoulders at 45'

int servo1Offset = 1680;
int servo2Offset = 1380;
int servo3Offset = 1350;
int servo4Offset = 1550;

int servo5Offset = 1430;
int servo6Offset = 1570;
int servo7Offset = 1550;
int servo8Offset = 1520;

int servo9Offset = 1400;
int servo10Offset = 1700;
int servo11Offset = 1650;
int servo12Offset = 1750;

void setup() {

  // Bluetooth stuff
  Serial.begin(38400);
  delay(500);
  Serial.println("Bonjour -Pret pour les commandes AT");
  Serial3.begin(38400); 


  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  pinMode(A8, INPUT);

  pinMode(A9, INPUT);
  pinMode(A14, INPUT);
  pinMode(A15, INPUT);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  
  pinMode(A3, INPUT);
  pinMode(A12, INPUT);
  pinMode(A13, INPUT);

  // write default positions with delays
  
  servo1.attach(24);      // hips
  servo2.attach(25);
  servo3.attach(5);
  servo4.attach(2);

  servo1.writeMicroseconds(servo1Offset);     // back left hip          |   higher value moves up/outwards
  servo2.writeMicroseconds(servo2Offset);     // back right hip         |   lower value moves up/outwards
  servo3.writeMicroseconds(servo3Offset);     // front left hip         |   lower value moves up/outwards
  servo4.writeMicroseconds(servo4Offset);     // front right hip        |   higher value moves up/outwards

  delay(1000);

  servo5.attach(9);       // shoulders
  servo6.attach(29);  
  servo7.attach(6);  
  servo8.attach(1);

  servo5.writeMicroseconds(servo5Offset);     // back left shoulder     |   higher value moves leg inwards
  servo6.writeMicroseconds(servo6Offset);     // back right shoulder    |   lower value moves leg inwards
  servo7.writeMicroseconds(servo7Offset);     // front left shoulder    |   higher value moves leg inwards
  servo8.writeMicroseconds(servo8Offset);     // front right shoulder   |   lower value moves leg inwards

  delay(1000);

  servo9.attach(8);       // knees
  servo10.attach(30);
  servo11.attach(7);
  servo12.attach(0);

  servo9.writeMicroseconds(servo9Offset);     // back left knee         |   higher value bends knee inwards
  servo10.writeMicroseconds(servo10Offset);    // back right knee        |   lower value bends knee inwards
  servo11.writeMicroseconds(servo11Offset);    // front left knee        |   lower value bends knee inwards
  servo12.writeMicroseconds(servo12Offset);    // front right knee       |   higher value bence knee inwards


}

void loop() {

  currentMillis = millis();
  if (currentMillis - previousMillis >= 10) {  // start timed event
          
        previousMillis = currentMillis;

        // receive Bluetooth data
        
        if (Serial3.available()>= 9) {
          AccX = Serial3.read(); // read the first value
          AccY = Serial3.read(); // read the second value
          JoyX = Serial3.read();// read the third value
          JoyY = Serial3.read();
          Switch1 = Serial3.read();
          Switch2 = Serial3.read();
          Switch3 = Serial3.read();
          Switch4 = Serial3.read();
          Joybutton = Serial3.read();
          previousSafetyMillis = currentMillis;
        }

        // check if remote has become disconnected

        if (currentMillis - previousSafetyMillis > 500) {         
            Serial.println("*no remote data* ");
            Switch1 = 1;
            Switch2 = 1;
            Switch3 = 1;
            Switch4 = 1;
            JoyButton = 1;
            JoyX = 126;
            JoyY= 133;
            AccX= 131;
            AccY= 131;
            
            
            
            
        } 

        
        
      
        
       
        

        roll = (ypr[1] * 180/M_PI) - 1.5;
        pitch = (ypr[2] * 180/M_PI) + 0.7;





        // convert sticks to measurements in mm or degrees

        z = map(JoyY, 0,254,80,274);    // overall height of the robot
        z = constrain(z,130,216);

        x = map(JoyX, 0,254,-60,60);
        x = constrain(x,-60,60);

        if (Switch3=0){
          y=60;
        }
        if (Switch1=0){
          y=-60;
        }
        
        
        // print control data for debug
                

        Serial.print(" z: ");
        Serial.print(z);        
        Serial.print(" x: ");
        Serial.print(x);
        Serial.print(" y: ");
        Serial.print(y);
 
        // send data to kinematic model function, compliance engine, and eventually write out to servos
        
        kinematics (1,x,y,z);   // front left leg
        kinematics (2,x,y,z);   // front right leg
        kinematics (3,x,y,z);   // back left leg
        kinematics (4,x,y,z);   // back right leg

  }   // end of timed loop

} //  end of main loop
