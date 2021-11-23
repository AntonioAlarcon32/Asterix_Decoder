#ifndef WGS84COORDINATES_H
#define WGS84COORDINATES_H


class WGS84Coordinates
{
public:
    WGS84Coordinates(double latitude,double longitude, double altitude);
    double latitude;
    double longitude;
    double altitude;
};

#endif // WGS84COORDINATES_H
