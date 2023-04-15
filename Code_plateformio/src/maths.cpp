#include "maths.hpp"
#include <math.h>
#include <Arduino.h>
#include <ArduinoSTL.h>

double CE = 170.5;
double CD = 47.273;
double DE = 124.7;
double DA = 130;
double OA = 46.5;
double omega = acos((DE * DE + CD * CD - CE * CE) / (2 * CD * DE)) * 180 / M_PI;

void get_coordonate_E_simplified(double ha, double ka, double &AG, double &EG)
{
    double beta = (90 - ha);
    double teta = ha + ka;
    double gamma = (90 + teta - omega);
    double alpha = (gamma + 90);
    double AE = sqrt(DE * DE + DA * DA - 2 * DA * DE * cos(alpha * M_PI / 180));
    double little_phi = acos((-DE * DE + DA * DA + AE * AE) / (2 * DA * AE)) * 180 / M_PI;
    EG = round(sin((beta - little_phi) * M_PI / 180) * AE);
    AG = round(cos((beta - little_phi) * M_PI / 180) * AE);
}

void get_coordonate_E(double ha, double ka, double sa, double &x, double &y, double &z)
{
    double AG, EG;
    get_coordonate_E_simplified(ha, ka, AG, EG);
    double beta = (M_PI / 2 - ha) * 180 / M_PI;
    double teta = (ha + ka) * 180 / M_PI;
    double gamma = (M_PI / 2 + teta - omega) * 180 / M_PI;
    double alpha = (gamma + M_PI / 2) * 180 / M_PI;
    double AE = sqrt(DE * DE + DA * DA - 2 * DA * DE * cos(alpha * M_PI / 180));
    double little_phi = acos((-DE * DE + DA * DA + AE * AE) / (2 * DA * AE)) * 180 / M_PI;

    EG = sin(beta - little_phi) * AE;
    AG = cos(beta - little_phi) * AE;

    x = OA * cos(sa);
    y = EG;
    z = OA * sin(sa) + AG;
}

void get_angle_simplified(double AG, double EG, double &ha, double &ka)
{
    double EA = sqrt(AG * AG + EG * EG);
    double epsilon = acos(AG / EA) * 180 / M_PI;
    double little_phi = acos((-DE * DE + DA * DA + EA * EA) / (2 * DA * EA)) * 180 / M_PI;
    ha = (90 - little_phi - epsilon);
    double alpha = acos((DE * DE + DA * DA - EA * EA) / (2 * DA * EA)) * 180 / M_PI;
    if (EA >= 181.42434761668073)
    {
        ka = (omega + alpha - 180 - ha);
    }
    else
    {
        ka = (omega - alpha - ha);
    }

    ha = round(ha);
    ka = round(ka);
}
