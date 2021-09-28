#ifndef UTILITIES_H
#define UTILITIES_H
#include "QVector"

namespace Utilities
{

    class DataTools {

    public:
        static QVector<char> GetFixedLengthDataItem(QVector<char> &message, int length);
        static QVector<char> GetVariableLengthDataItem(QVector<char> &message);
        static QVector<char> GetRepetitiveDataItem(QVector<char> message, int length);
        static double DecodeUnsignedBytesToDouble(QVector<char> bytes, double resolution);
    };

};

#endif // UTILITIES_H
