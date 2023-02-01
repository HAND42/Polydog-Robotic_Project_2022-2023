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

#include <Arduino.h>
#include "Accelerometer.h"
#include <Wire.h>

Accelerometer::Accelerometer() {
}

void Accelerometer::start(){

    Wire.begin(); // Initiate the Wire library
    // Set ADXL345 in measuring mode
    Wire.beginTransmission(ADXL345); // Start communicating with the device
    Wire.write(0x2D); // Access/ talk to POWER_CTL Register - 0x2D
    // Enable measurement
    Wire.write(8); // Bit D3 High for measuring enable (8dec -> 0000 1000 binary)
    Wire.endTransmission();
    delay(10);

    //Off-set Calibration
    //X-axis
    Wire.beginTransmission(ADXL345);
    Wire.write(0x1E);
    Wire.write(1);
    Wire.endTransmission();
    delay(10);
    //Y-axis
    Wire.beginTransmission(ADXL345);
    Wire.write(0x1F);
    Wire.write(-2);
    Wire.endTransmission();
    delay(10);

    //Z-axis
    Wire.beginTransmission(ADXL345);
    Wire.write(0x20);
    Wire.write(-9);
    Wire.endTransmission();
    delay(10);
}

void Accelerometer::display_rolls_pitch(){

    // === Read acceleromter data === //
  Wire.beginTransmission(ADXL345);
  Wire.write(0x32); // Start with register 0x32 (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  X_out = ( Wire.read() | Wire.read() << 8); // X-axis value
  X_out = X_out / 256; //For a range of +-2g, we need to divide the raw values by 256, according to the datasheet
  Y_out = ( Wire.read() | Wire.read() << 8); // Y-axis value
  Y_out = Y_out / 256;
  Z_out = ( Wire.read() | Wire.read() << 8); // Z-axis value
  Z_out = Z_out / 256;

  // Calculate Roll and Pitch (rotation around X-axis, rotation around Y-axis)
  roll = atan(Y_out / sqrt(pow(X_out, 2) + pow(Z_out, 2))) * 180 / PI;
  pitch = atan(-1 * X_out / sqrt(pow(Y_out, 2) + pow(Z_out, 2))) * 180 / PI;

  // Low-pass filter
  rollF = 0.94 * rollF + 0.06 * roll;
  pitchF = 0.94 * pitchF + 0.06 * pitch;

  Serial.print(rollF); //Penché en avant en arrière
  Serial.print("/");
  Serial.println(pitchF); //Penché d'un côté ou de l'autre

}

 