#include "hdr/asterix_lib/coordinatesxyz.h"

CoordinatesXYZ::CoordinatesXYZ()
{
}


CoordinatesXYZ::CoordinatesXYZ(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

double CoordinatesXYZ::GetX() {
    return this->x;
}

double CoordinatesXYZ::GetY() {
    return this->y;
}

double CoordinatesXYZ::GetZ() {
    return this->z;
}

void CoordinatesXYZ::SetX(double x) {
    this->x = x;

}

void CoordinatesXYZ::SetY(double y) {
    this->y = y;

}

void CoordinatesXYZ::SetZ(double z) {
    this->z = z;

}

QString CoordinatesXYZ::ToString() {
    return "X: " + QString::number(this->x) + " m, Y: "  + QString::number(this->y) + " m, Z: " + QString::number(this->z) + " m";
}



