// Copyright (c) 2022-2022. BAZI YOUNES
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
#include <SoftwareSerial.h>
#include "RemoteEsplora/RemoteEsplora.h"
#include "RemoteEsplora/RemoteEsplora.h"
#include <Esplora.h>

/*
*This class is not working for now. We still work on it.
*
*/


RemoteEsplora::RemoteEsplora(int rxPin, int txPin) : Serial3(rxPin, txPin){

}


void RemoteEsplora::begin(long speed) {
    Serial3.begin(speed);
    delay(100);
}

void RemoteEsplora::RemoteInstruction(PolyDog dog){ 
    
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
    delay(100);

    if (Switch4 != 0){
        dog.stand_up2();
    }

    // AccX= 28
    // AccY= 28
    // JoyX= 224
    // JoyY= 28
    // Switch1= 0
    // Switch2= 252
    // Switch3= 28
    // Switch4= 0


}
}
