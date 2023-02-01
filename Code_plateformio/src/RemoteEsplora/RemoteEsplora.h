// Copyright (c) 2022-2022. BAZI Younes
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

/**
 * @file RemoteEsplora.h
 *
 * @brief 
 *
 * @author BAZI Younes
 * <p>
 * Contact:
 *
 */

#ifndef REMOTEESPLORA_H
#define REMOTEESPLORA_H

#include <Arduino.h>
#include "RemoteEsplora/RemoteEsplora.h"
#include <Esplora.h>
#include <SoftwareSerial.h>
#include "PolyDog/PolyDog.h"



class RemoteEsplora
{
private:
int AccX;
int AccY;
int JoyX;
int JoyY;
int Switch1;
int Switch2;
int Switch3;
int Switch4;
int Joybutton;
SoftwareSerial Serial3;
int serialFlags;
public:

    RemoteEsplora();
    RemoteEsplora(int rxPin, int txPin);
    void begin(long speed);
    void RemoteInstruction(PolyDog dog);
};

#endif