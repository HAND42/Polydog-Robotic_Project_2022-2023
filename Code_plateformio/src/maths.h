#include <Arduino.h>
#include <ArduinoSTL.h>

// define the lenght of the different part of the leg

float CE = 0;
float CD = 0;
float DE = 0;
float DA = 0;
float OA = 0;
float omega = acos((pow(DE, 2) + pow(CD, 2) - pow(CE, 2)) / (2 * CD * DE));

std::tuple<float, float> get_coordonate_E_simplified(float ha, float ka)
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

    return std::make_tuple(AG, EG); // retourner un tuple contenant les valeurs a, b, et c
}

std::tuple<float, float, float> get_coordonate_E(float ha, float ka, float sa)
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

    return std::make_tuple(x, y, z); // retourner un tuple contenant les valeurs a, b, et c
}