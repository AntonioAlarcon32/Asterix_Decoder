#ifndef UTILITIES_H
#define UTILITIES_H
#include "QVector"
#include "hdr/wgs84coordinates.h"
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
        static double PI;
        static double E2;
        static double A;
        static double DEG2RAD;
    public:
        static CoordinatesXYZ ChangeRadarCartesianToGeocentric(WGS84Coordinates radarCoords, CoordinatesXYZ radarCartesian);

    };
};



#endif // UTILITIES_H
