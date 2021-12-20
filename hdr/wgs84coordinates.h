#ifndef WGS84COORDINATES_H
#define WGS84COORDINATES_H

#include "QString"


class WGS84Coordinates
{
public:
    WGS84Coordinates();
    WGS84Coordinates(double latitude,double longitude, double height);
    WGS84Coordinates(double latitude,double longitude);

    double GetLatitude();
    double GetLongitude();
    double GetHeight();

    void SetLatitude(double lat);
    void SetLongitude(double lon);
    void SetHeight(double height);

    QString ToString();

private:
    double latitude;
    double longitude;
    double height;
};

#endif // WGS84COORDINATES_H
