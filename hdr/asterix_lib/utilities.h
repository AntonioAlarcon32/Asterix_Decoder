#ifndef UTILITIES_H
#define UTILITIES_H
#include "QVector"
#include "wgs84coordinates.h"
#include "coordinatesxyz.h"

namespace Utilities
{

    class DataTools {

    public:
        static QVector<unsigned char> GetFixedLengthDataItem(QByteArray &message, int length, int &offset);
        static QVector<unsigned char> GetVariableLengthDataItem(QByteArray &message,int &offset);
        static QVector<unsigned char> GetRepetitiveDataItem(QByteArray &message,int factor, int &offset);
        static double DecodeUnsignedBytesToDouble(QVector<unsigned char> bytes, double resolution);
        static double DecodeTwosComplementToDouble(QVector<unsigned char> bytes, double resolution);
        static double DecodeSpecialTwosComplement(QVector<unsigned char> bytes, double resolution, unsigned char  mask, int signIndicator);
        static QString GetAircraftIDFromBytes(QVector<unsigned char> bytes);
    };

    class RadarTools {
    private:
        static double E2;
        static double A;
        static double DEG2RAD;
        static double RAD2DEG;
        static double ALMOST_ZERO;
        static double REQUIRED_PRECISION;
    public:
        static CoordinatesXYZ ChangeRadarCartesianToGeocentric(WGS84Coordinates radarCoords, CoordinatesXYZ radarCartesian);
        static WGS84Coordinates ChangeGeocentricToGeodesic(CoordinatesXYZ objectGeocenctric);
        static double PI;

    };
};



#endif // UTILITIES_H
