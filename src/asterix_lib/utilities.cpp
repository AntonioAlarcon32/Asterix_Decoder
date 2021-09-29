#include "hdr/asterix_lib/utilities.h"
#include "math.h"

namespace Utilities {


QVector<unsigned char> DataTools::GetFixedLengthDataItem(QVector<unsigned char> &message, int length) {

    int i = 0;
    QVector<unsigned char> dataItem(length);

    while (i < length) {
        dataItem[i] = message.at(0);
        message.remove(0);
        i++;
    }
    return dataItem;
}

QVector<unsigned char> DataTools::GetVariableLengthDataItem(QVector<unsigned char> &message) {
    int i = 0;
    QVector<unsigned char> dataItem;

    dataItem.append(message.at(0));
    message.remove(0);

    while ((dataItem.at(i) & 0x01) == 1) {
        dataItem.append(message.at(0));
        message.remove(0);
        i++;
    }
    return dataItem;
}

QVector<unsigned char> DataTools::GetRepetitiveDataItem(QVector<unsigned char> &message, int factor) {

    QVector<unsigned char> dataItem;
    short repFactor = (short) message.at(0);
    dataItem.append(message.at(0));
    message.remove(0);

    int i = 0;

    while (i < (repFactor * factor)) {
        dataItem.append(message.at(0));
        message.remove(0);
        i++;
    }
    return dataItem;
}

double DataTools::DecodeUnsignedBytesToDouble(QVector<unsigned char> bytes, double resolution) {

    double bytesValue = 0;
    double multiplier = 1;
    for (int c = bytes.length() - 1; c >= 0; c--)
    {
        bytesValue += ((unsigned char)bytes.at(c) * multiplier);
        multiplier = multiplier * pow(2,8);
    }
    return bytesValue * resolution;
}

double DataTools::DecodeTwosComplementToDouble(QVector<unsigned char> bytes, double resolution) {

    unsigned char mask = 0x7F;
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

QString DataTools::GetAircraftIDFromBytes(QVector<unsigned char> bytes) {

    QString result = "";

    for (unsigned char byte : bytes) {
        switch (byte) {
        case 0:
            result.append(" ");
            break;
        case 1:
            result.append("A");
            break;
        case 2:
            result.append("B");
            break;
        case 3:
            result.append("C");
            break;
        case 4:
            result.append("D");
            break;
        case 5:
            result.append("E");
            break;
        case 6:
            result.append("F");
            break;
        case 7:
            result.append("G");
            break;
        case 8:
            result.append("H");
            break;
        case 9:
            result.append("I");
            break;
        case 10:
            result.append("J");
            break;
        case 11:
            result.append("K");
            break;
        case 12:
            result.append("L");
            break;
        case 13:
            result.append("M");
            break;
        case 14:
            result.append("N");
            break;
        case 15:
            result.append("O");
            break;
        case 16:
            result.append("P");
            break;
        case 17:
            result.append("Q");
            break;
        case 18:
            result.append("R");
            break;
        case 19:
            result.append("S");
            break;
        case 20:
            result.append("T");
            break;
        case 21:
            result.append("U");
            break;
        case 22:
            result.append("V");
            break;
        case 23:
            result.append("W");
            break;
        case 24:
            result.append("X");
            break;
        case 25:
            result.append("Y");
            break;
        case 26:
            result.append("Z");
            break;
        case 32:
            result.append(" ");
            break;
        case 48:
            result.append("0");
            break;
        case 49:
            result.append("1");
            break;
        case 50:
            result.append("2");
            break;
        case 51:
            result.append("3");
            break;
        case 52:
            result.append("4");
            break;
        case 53:
            result.append("5");
            break;
        case 54:
            result.append("6");
            break;
        case 55:
            result.append("7");
            break;
        case 56:
            result.append("8");
            break;
        case 57:
            result.append("9");
            break;
        }
    }
    return result;
}

}
