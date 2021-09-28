#include "hdr/asterix_lib/utilities.h"
#include "math.h"

namespace Utilities {


QVector<char> DataTools::GetFixedLengthDataItem(QVector<char> &message, int length) {

    int i = 0;
    QVector<char> dataItem(length);

    while (i < length) {
        dataItem[i] = message.at(0);
        message.remove(0);
        i++;
    }
    return dataItem;
}

QVector<char> DataTools::GetVariableLengthDataItem(QVector<char> &message) {
    int i = 0;
    QVector<char> dataItem;

    dataItem.append(message.at(0));
    message.remove(0);

    while ((dataItem.at(i) & 0x01) == 1) {
        dataItem.append(message.at(0));
        message.remove(0);
        i++;
    }
    return dataItem;
}

double DataTools::DecodeUnsignedBytesToDouble(QVector<char> bytes, double resolution) {

    double bytesValue = 0;
    double multiplier = 1;
    for (int c = bytes.length() - 1; c >= 0; c--)
    {
        bytesValue += ((unsigned char)bytes.at(c) * multiplier);
        multiplier = multiplier * pow(2,8);
    }
    return bytesValue * resolution;
}
}
