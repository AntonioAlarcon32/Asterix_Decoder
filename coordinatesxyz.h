#ifndef COORDINATESXYZ_H
#define COORDINATESXYZ_H

#include "QString"
#include "hdr/wgs84coordinates.h"
#include "math.h"


class CoordinatesXYZ
{
public:
    CoordinatesXYZ();
    CoordinatesXYZ(double x, double y, double z);
    double GetX();
    double GetY();
    double GetZ();
    void SetX(double x);
    void SetY(double y);
    void SetZ(double z);
    QString ToString();

private:
    double x,y,z;
};

#endif // COORDINATESXYZ_H
