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

double DataTools::DecodeTwosComplementToDouble(QVector<char> bytes, double resolution) {

    char mask = 0x7F;
    bool negative = false;
    if ((unsigned char)bytes.at(0) > 127) {
        negative = true;
    }
    unsigned char noSign = (unsigned char)(bytes.at(0) & mask);
    double bytesValue = 0;
    double multiplier = 1;

    for (int c = bytes.length() - 1; c >= 0; c--)
    {
        if (c == 0)
        {
            bytesValue += noSign * multiplier;
            break;
        }
        bytesValue += ((unsigned char)bytes.at(c) * multiplier);
        multiplier = multiplier * pow(2, 8);
    }
    if (negative) {
        bytesValue = bytesValue - pow(2, (bytes.length() * 8) - 1);
    }

    return bytesValue * resolution;
}
}
