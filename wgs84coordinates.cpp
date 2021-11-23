#include "wgs84coordinates.h"

WGS84Coordinates::WGS84Coordinates(double latitude,double longitude, double altitude)
{
    this->altitude = altitude;
    this->latitude = latitude;
    this->longitude = longitude;
}
