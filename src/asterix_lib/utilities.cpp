#include "hdr/asterix_lib/utilities.h"
#include "math.h"

namespace Utilities {


QVector<unsigned char> DataTools::GetFixedLengthDataItem(QByteArray &message, int length, int &offset) {

    int i = 0;
    QVector<unsigned char> dataItem(length);

    if (message.length() - offset >= length) {

        while (i < length) {
            dataItem[i] = message.at(i+offset);
            i++;
        }
        offset += i;
        return dataItem;
    }

    else {
        throw -1;
    }
}

QVector<unsigned char> DataTools::GetVariableLengthDataItem(QByteArray &message, int &offset) {
    int i = 0;
    QVector<unsigned char> dataItem;

    dataItem.append(message.at(offset));

    while ((dataItem.at(i) & 0x01) == 1) {
        dataItem.append(message.at(offset+i+1));
        i++;
    }
    offset += i + 1;
    return dataItem;
}

QVector<unsigned char> DataTools::GetRepetitiveDataItem(QByteArray &message, int factor, int &offset) {

    QVector<unsigned char> dataItem;
    short repFactor = (short) message.at(offset);
    dataItem.append(message.at(offset));

    int i = 0;

    if (factor * repFactor <= message.length() - offset) {

        while (i < (repFactor * factor)) {
            dataItem.append(message.at(offset+i+1));
            i++;
        }
        offset += (i+1);
        return dataItem;
    }

    else {
        throw -1;
    }
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
    return result.replace(" ","");
}

double DataTools::DecodeSpecialTwosComplement(QVector<unsigned char> bytes, double resolution, unsigned char  mask, int signIndicator) {

    bool negative = false;
    if ((unsigned char)bytes.at(0) >= signIndicator) {
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

    int extraDigits = log2(signIndicator);

    int totalDigits = (bytes.length()-1) * 8 + extraDigits;

    if (negative) {
        bytesValue = bytesValue - pow(2, totalDigits);
    }

    return bytesValue * resolution;

}

double RadarTools::PI = 3.14159265359;
double RadarTools::DEG2RAD = PI/180.0;
double RadarTools::A = 6378137.0;
double RadarTools::E2 = 0.00669437999013;
double RadarTools::ALMOST_ZERO = 1e-10;
double RadarTools::REQUIRED_PRECISION = 1e-8;
double RadarTools::RAD2DEG = 180.0/PI;

CoordinatesXYZ RadarTools::ChangeRadarCartesianToGeocentric(WGS84Coordinates radarCoords, CoordinatesXYZ radarCartesian) {

    double lat = radarCoords.GetLatitude() * DEG2RAD;
    double lon = radarCoords.GetLongitude() * DEG2RAD;
    double height = radarCoords.GetHeight();

    double xl = radarCartesian.GetX();
    double yl = radarCartesian.GetY();
    double zl = radarCartesian.GetZ();

    double nu = (RadarTools::A) / (sqrt(1 - E2 * pow(sin(lat),2)));

    double t1 = (nu + height) * cos(lat) * cos(lon);
    double t2 = (nu + height) * cos(lat) * sin(lon);
    double t3 = (nu * (1 - E2) + height) * sin(lat);


    double xg = (-sin(lon))*xl + (-sin(lat)*cos(lon))*yl + (cos(lat)*cos(lon))*zl + t1;
    double yg = (cos(lon)*xl) + (-sin(lat)*sin(lon))*yl + (cos(lat)*sin(lon))*zl + t2;
    double zg = (cos(lat)*yl) + (sin(lat))*zl + t3;

    return CoordinatesXYZ(xg,yg,zg);
    int c = 1;
}

WGS84Coordinates RadarTools::ChangeGeocentricToGeodesic(CoordinatesXYZ objectGeocenctric) {
    double x = objectGeocenctric.GetX();
    double y = objectGeocenctric.GetY();
    double z = objectGeocenctric.GetZ();
    WGS84Coordinates result = WGS84Coordinates();

    double lat, lon, height;



    double b = 6356752.3142;

    if ((abs(x) < ALMOST_ZERO) && (abs(y) < ALMOST_ZERO))
    {
        if (abs(z) < ALMOST_ZERO)
        {
            // the point is at the center of earth :)
            result.SetLatitude(PI / 2.0);
        }
        else
        {
            result.SetLatitude((PI / 2.0) * ((z / abs(z)) + 0.5));
        }
        result.SetLongitude(0);
        result.SetHeight(abs(z) - b);
        return result;
    }

    double d_xy = sqrt(x * x + y * y);
                // from formula 20
                lat = atan((z / d_xy) /
                    (1 - (A * E2) / sqrt(d_xy * d_xy + z * z)));
                // from formula 24
                double nu = A / sqrt(1 - E2 * pow(sin(lat), 2.0));
                // from formula 20
                height = (d_xy / cos(lat)) - nu;

                // iteration from formula 20b
                double Lat_over;
                if (lat >= 0) {
                    Lat_over = -0.1;
                }
                else {
                    Lat_over = 0.1;
                }

                int loop_count = 0;
                while ((abs(lat - Lat_over) > REQUIRED_PRECISION) && (loop_count < 50)) {
                    loop_count++;
                    Lat_over = lat;
                    lat = atan((z * (1 + height / nu)) / (d_xy * ((1 - E2) + (height / nu))));
                    nu = A / sqrt(1 - E2 * pow(sin(lat), 2.0));
                    height = d_xy / cos(lat) - nu;
                }
                lon = atan2(y, x);
                // if (loop_count == 50) { // exception }

                result.SetLatitude(lat*RAD2DEG);
                result.SetLongitude(lon*RAD2DEG);
                result.SetHeight(height);
                return result;
}



}




