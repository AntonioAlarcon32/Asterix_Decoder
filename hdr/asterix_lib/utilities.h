#ifndef UTILITIES_H
#define UTILITIES_H
#include "QVector"

namespace Utilities
{

    class DataTools {

    public:
        static QVector<unsigned char> GetFixedLengthDataItem(QVector<unsigned char> &message, int length);
        static QVector<unsigned char> GetVariableLengthDataItem(QVector<unsigned char> &message);
        static QVector<unsigned char> GetRepetitiveDataItem(QVector<unsigned char> &message,int factor);
        static double DecodeUnsignedBytesToDouble(QVector<unsigned char> bytes, double resolution);
        static double DecodeTwosComplementToDouble(QVector<unsigned char> bytes, double resolution);
        static double DecodeSpecialTwosComplement(QVector<unsigned char> bytes, double resolution, unsigned char  mask, int signIndicator);
        static QString GetAircraftIDFromBytes(QVector<unsigned char> bytes);
    };
};

#endif // UTILITIES_H
