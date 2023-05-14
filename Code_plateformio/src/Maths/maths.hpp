#ifndef MATHS_HPP
#define MATHS_HPP

struct Coord
{
    double x;
    double y;
    double z;
};

void get_coordonate_E_simplified(double ha, double ka, Coord &coord);
// void get_coordonate_E(double ha, double ka, double sa, double &x, double &y, double &z);
void get_angle_simplified(Coord &coord, double &hanche_angle, double &knew_angle);

#endif
