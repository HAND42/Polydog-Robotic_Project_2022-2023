#include "maths.hpp"
#include <math.h>
#include <Arduino.h>
#include <ArduinoSTL.h>

double CH = 153.545;
double CD = 47.273;
double DH = 107.191;
double HE = 20;
double DA = 130;
double OA = 46.5;

double omega = acos((DH * DH + CD * CD - CH * CH) / (2 * CD * DH)) * 180 / PI;

void get_coordonate_E_simplified(double ha, double ka, Coord &coord)
{

    double beta = (90 - ha);
    double teta = ha + ka;
    double gamma = (90 + teta - omega);
    double alpha = (gamma + 90);
    double AH = sqrt(DH * DH + DA * DA - 2 * DA * DH * cos(alpha * PI / 180));
    double little_phi = acos((-DH * DH + DA * DA + AH * AH) / (2 * DA * AH)) * 180 / PI;
    coord.y = round(sin((beta - little_phi) * PI / 180) * AH);
    coord.z = round(cos((beta - little_phi) * PI / 180) * AH) + HE;
}

// void get_coordonate_E(double ha, double ka, double sa, double &x, double &y, double &z)
// {
//     double AG, EG;
//     get_coordonate_E_simplified(ha, ka, AG, EG);
//     double beta = (M_PI / 2 - ha) * 180 / M_PI;
//     double teta = (ha + ka) * 180 / M_PI;
//     double gamma = (M_PI / 2 + teta - omega) * 180 / M_PI;
//     double alpha = (gamma + M_PI / 2) * 180 / M_PI;
//     double AE = sqrt(DH * DH + DA * DA - 2 * DA * DH * cos(alpha * M_PI / 180));
//     double little_phi = acos((-DH * DH + DA * DA + AE * AE) / (2 * DA * AE)) * 180 / M_PI;

//     EG = sin(beta - little_phi) * AE;
//     AG = cos(beta - little_phi) * AE;

//     x = OA * cos(sa);
//     y = EG;
//     z = OA * sin(sa) + AG;
// }

void get_angle_simplified(Coord &coord, double &hanche_angle, double &knew_angle)
{
    // Position variable is define with position[0]=AG=height and position[1]=EG=distance_projeted
    double AG = abs(coord.z);
    double EG = abs(coord.y);

    Serial.println(AG);
    Serial.println(EG);

    // False_AG is the height but without taking into account the squash ball distance
    float false_AG = AG - HE;

    Serial.println("flaseAG " + String(false_AG));

    // Hypotenus from the hip tip to the center of the foot support
    float HA = sqrt((false_AG * false_AG) + (EG * EG));

    Serial.println("HA " + String(HA));

    double epsilon = acos(false_AG / HA) * 180 / PI;

    Serial.println("epsilon " + String(epsilon));

    double little_phi = acos((-DH * DH + DA * DA + HA * HA) / (2 * DA * HA)) * 180 / PI; // Why M_PI and not PI
    Serial.println("little_phi" + String(little_phi));

    if (coord.y >= 0)
    {
        hanche_angle = (90 - little_phi - epsilon);
    }
    else
    {
        hanche_angle = (90 - little_phi + epsilon);
    }

    double alpha = acos((DH * DH + DA * DA - HA * HA) / (2 * DA * HA)) * 180 / PI;

    Serial.println("alpha" + String(alpha));

    if (HA >= 181.42434761668073)
    {
        knew_angle = (omega + alpha - 180 - hanche_angle);
    }
    else
    {
        knew_angle = (omega - alpha - hanche_angle);
    }

    hanche_angle = round(hanche_angle);
    knew_angle = round(knew_angle);
}
