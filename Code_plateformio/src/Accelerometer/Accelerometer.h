// Copyright (c) 2022-2022. BAZI Younes & DURAND Hugo
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
 * @file Accelerometer.h
 *
 * @brief Accelerometer object allows us to manage the 10 DOF V2.0 module
 *
 * @authors BAZI Younes & DURAND Hugo
 *
 */

#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <Arduino.h>


class Accelerometer
{
    public:
        Accelerometer();
        void start();
        String display_rolls_pitch();
        
        
    private:
        int ADXL345 = 0x53; // The ADXL345 sensor I2C address
        float X_out, Y_out, Z_out;  // Outputs
        float roll,pitch,rollF,pitchF=0;
        

};


#endif
