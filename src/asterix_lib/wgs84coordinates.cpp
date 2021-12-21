#include "hdr/wgs84coordinates.h"
#include "math.h"

WGS84Coordinates::WGS84Coordinates() {
    this->height = nan("");
    this->latitude = nan("");
    this->longitude = nan("");
}

WGS84Coordinates::WGS84Coordinates(double latitude,double longitude, double height)
{
    this->height = height;
    this->latitude = latitude;
    this->longitude = longitude;
}

WGS84Coordinates::WGS84Coordinates(double latitude,double longitude)
{
    this->height = 0;
    this->latitude = latitude;
    this->longitude = longitude;
}

double WGS84Coordinates::GetLatitude() {
    return this->latitude;
}

double WGS84Coordinates::GetLongitude() {
    return this->longitude;
}

double WGS84Coordinates::GetHeight() {
    return this->height;
}

void WGS84Coordinates::SetLatitude(double lat) {
    this->latitude = lat;

}

void WGS84Coordinates::SetLongitude(double lon) {
    this->longitude = lon;
}

void WGS84Coordinates::SetHeight(double height) {
    this->height = height;
}

QString WGS84Coordinates::ToString() {
    return "Latitude: " + QString::number(this->latitude) + "º, Longitude: "  + QString::number(this->longitude) + "º, Height: " + QString::number(this->height) + " m";
}


