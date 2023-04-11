#include <Arduino.h>
#include <ArduinoSTL.h>

// define the lenght of the different part of the leg

float CE = 170.5;
float CD = 47.273;
float DE = 124.7;
float DA = 130;
float OA = 46.5;
float omega = acos((pow(DE, 2) + pow(CD, 2) - pow(CE, 2)) / (2 * CD * DE));

float *get_coordonate_E_simplified(float ha, float ka)
{
    int AG = 0;
    float EG = 0;
    float beta = PI / 2 - ha;
    float teta = ha + ka;
    float gamma = (PI / 2 + teta - omega) * RAD_TO_DEG; // valid for both configuration of the leg
    float alpha = gamma + PI / 2;
    float AE = sqrt(pow(DE, 2) + pow(DA, 2) - 2 * DA * DE * cos(alpha));
    float little_phi = acos((-pow(DE, 2) + pow(DA, 2) + pow(AE, 2)) / (2 * DA * AE));

    EG = sin(beta - little_phi) * AE;
    AG = cos(beta - little_phi) * AE;

    static float coord[2] = {AG, EG}; // return an array of 2 floats
    return coord;
}

float *get_coordonate_E(float ha, float ka, float sa)
{
    float z, x, y;

    int AG = 0;
    float EG = 0;
    float beta = PI / 2 - ha;
    float teta = ha + ka;
    float gamma = (PI / 2 + teta - omega) * RAD_TO_DEG; // valid for both configuration of the leg
    float alpha = gamma + PI / 2;
    float AE = sqrt(pow(DE, 2) + pow(DA, 2) - 2 * DA * DE * cos(alpha));
    float little_phi = acos((-pow(DE, 2) + pow(DA, 2) + pow(AE, 2)) / (2 * DA * AE));

    EG = sin(beta - little_phi) * AE;
    AG = cos(beta - little_phi) * AE;

    x = OA * cos(sa);
    y = EG;
    z = OA * sin(sa) + AG;

    static float coord[3] = {x, y, z}; // return an array of 2 floats
    return coord;
}