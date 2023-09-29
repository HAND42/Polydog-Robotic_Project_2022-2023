// Copyright (c) 2022-2022. ANJOU Raphaël & DURAND Hugo
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <Arduino.h>
#include "PolyDog/PolyDog.h"
#include "CustomServo/CustomServo.h"
#include "Accelerometer/Accelerometer.h"
#include "RemoteEsplora/RemoteEsplora.h"
#include "Leg/Leg.h"
#include <SoftwareSerial.h>

#define rxPin 10
#define txPin 11
#define baudrate 38400

// Default value of the joystick buttons

int AccX = 136;
int AccY = 128;
int JoyX = 127;
int JoyY = 132;
int Switch1 = 1;
int Switch2 = 1;
int Switch3 = 1;
int Switch4 = 1;
int Joybutton = 1;

/* We instanciate the robot dog and the accelerometer inside the body
 *to mesure the pitch and the roll of the robot.
 */

PolyDog dog = PolyDog();
Accelerometer dof = Accelerometer();

SoftwareSerial Serial3 = SoftwareSerial(rxPin, txPin);
// RemoteEsplora remote = RemoteEsplora(rxPin,txPin);
bool orientation = false;

void setup()
{
    // Sets the data rate in bits per second (baud) for serial data transmission.

    Serial.begin(115200); // Scc32 default baud rate
    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for Native USB only
    }

    // remote.begin(baudrate);
    Serial3.begin(baudrate);
    // Serial3.println("Hello, world?");
    dof.start();

    // pinMode(rxPin, INPUT);
    // pinMode(txPin, OUTPUT);

    // dog.placing_legs();

    //dog.stand_up7(179.9474701877878, 50.983042177042776);
    //delay(2000);
     dog.stand_up5();
     //delay(2000);
    // dog.moving_shoulders();
}
void loop()
{
    // dog.stand_up4();
    // dog.avance();
    //  dog.move_leg2(0);
    //  dog.stand_up7();
    //  delay(1000);
    //  dog.move_leg2(1);
    //  delay(1000);
    //  dog.move_leg(2);
    //  delay(1000);
    //  dog.move_leg(3);
    //  delay(1000);

    // dog.move_2leg(2,0);
    // delay(1000);

    /*
     * When it receive 9 values from the bluetooth module it read them on the SoftwareSerial allocated in pin 10 and 11;
     * We print the values for debuging, and use them in order to move our robot.
     * */

    if (Serial3.available() >= 9)
    {
        AccX = Serial3.read(); // read the first value
        if (AccX != 1 | AccX != 0)
        {
            AccY = Serial3.read(); // read the second value

            JoyX = Serial3.read(); // read the third value

            JoyY = Serial3.read();

            Switch1 = Serial3.read();

            Switch2 = Serial3.read();

            Switch3 = Serial3.read();

            Switch4 = Serial3.read();

            Joybutton = Serial3.read();

            Serial.print("AccX= ");
            Serial.println(AccX);
            Serial.print("AccY= ");
            Serial.println(AccY);
            Serial.print("JoyX= ");
            Serial.println(JoyX);
            Serial.print("JoyY= ");
            Serial.println(JoyY);
            Serial.print("Switch1= ");
            Serial.println(Switch1);
            Serial.print("Switch2= ");
            Serial.println(Switch2);
            Serial.print("Switch3= ");
            Serial.println(Switch3);
            Serial.print("Switch4= ");
            Serial.println(Switch4);
            Serial.print("Joybutton= ");
            Serial.println(Joybutton);
            delay(10);

            if (JoyY <= 100)
            {
                dog.avance();
            }
            if (JoyY >= 150)
            {
                dog.avance();
            }
            if (Switch1 != 1)
            {
                orientation = 1 - orientation;
                dog.stand_up3();
            }
            if (Switch2 != 1)
            {
                dog.stand_up2();
                dog.move_leg2(0);
            }
            if (Switch3 != 1)
            {
                dog.stand_up();
                dog.move_leg2(3);
            }
            if (Switch4 != 1)
            {
                dog.stand_up3();
            }
        }
        else
        {
            AccX = 130;
            AccY = 130;
        }
    }

    if (orientation)
    {
        dog.orientation(AccX, AccY);
    }

    // Here is a problem from the remote, it can't handle when there are a lot of values coming in at the same time
    // and the button values are off.

    // AccX= 1
    // AccY= 1
    // JoyX= 139
    // JoyY= 127
    // Switch1= 126
    // Switch2= 132
    // Switch3= 1
    // Switch4= 1
    // Joybutton= 1

    // remote.RemoteInstruction(dog);

    // dof.display_rolls_pitch();
}
