#include "hdr/asterix_lib/utilities.h"
#include "math.h"

namespace Utilities {


QVector<unsigned char> DataTools::GetFixedLengthDataItem(QByteArray &message, int length, int &offset) {    //Function for getting a fixed length data item

    int i = 0;
    QVector<unsigned char> dataItem(length);

    if (message.length() - offset >= length) {                  //Check that there are enough bytes for getting this data item

        while (i < length) {
            dataItem[i] = message.at(i+offset);                 //Get bytes until we get the desired length
            i++;
        }
        offset += i;
        return dataItem;                                    //Return the vector of bytes
    }

    else {
        throw -1;                               //Throw an exception if required length is greater than available bytes
    }
}

QVector<unsigned char> DataTools::GetVariableLengthDataItem(QByteArray &message, int &offset) {     //Function to get a variable length data item using the LSB extension
    int i = 0;
    QVector<unsigned char> dataItem;

    dataItem.append(message.at(offset));

    while ((dataItem.at(i) & 0x01) == 1) {                          //If last bit is 1, FX is true, so we have to get next byte
        dataItem.append(message.at(offset+i+1));
        i++;
    }
    offset += i + 1;
    return dataItem;
}

QVector<unsigned char> DataTools::GetRepetitiveDataItem(QByteArray &message, int factor, int &offset) {     //Function to get a repetitive data item

    QVector<unsigned char> dataItem;
    short repFactor = (short) message.at(offset);
    dataItem.append(message.at(offset));

    int i = 0;

    if (factor * repFactor <= message.length() - offset) {                  //Check that there are enough bytes for returning the array

        while (i < (repFactor * factor)) {
            dataItem.append(message.at(offset+i+1));                        //We get X items of the data item of Y length
            i++;
        }
        offset += (i+1);
        return dataItem;
    }

    else {
        throw -1;                   //If not enough bytes, throw an exception
    }
}

double DataTools::DecodeUnsignedBytesToDouble(QVector<unsigned char> bytes, double resolution) {        //Function to get decimal value of an array of bytes

    double bytesValue = 0;
    double multiplier = 1;                                          //Multiplying factor for each byte.
    for (int c = bytes.length() - 1; c >= 0; c--)                   //Start by the last byte of the array (holds the LSB)
    {
        bytesValue += ((unsigned char)bytes.at(c) * multiplier);        //Add the value of the chart times the multiplier
        multiplier = multiplier * pow(2,8);                             //Multiply the factor by 2^8, as the next byte starts at bit 9 of the data item
    }
    return bytesValue * resolution;                                     //Multiply the value with the resolution of the data item
}

double DataTools::DecodeTwosComplementToDouble(QVector<unsigned char> bytes, double resolution) {           //Function to get decimal value of an array of bytes encoded in twos complement

    unsigned char mask = 0x7F;                  //Mask to remove the sign bit
    bool negative = false;
    if ((unsigned char)bytes.at(0) > 127) {     //If the value of the first byte (MSB) is greater than 127, MSB is true so value is negative
        negative = true;
    }
    unsigned char noSign = (unsigned char)(bytes.at(0) & mask);     //Get a byte removing the sign byte
    double bytesValue = 0;
    double multiplier = 1;

    for (int c = bytes.length() - 1; c >= 0; c--)
    {
        if (c == 0)
        {
            bytesValue += noSign * multiplier;                          //Decode the value as normal
            break;
        }
        bytesValue += ((unsigned char)bytes.at(c) * multiplier);
        multiplier = multiplier * pow(2, 8);
    }
    if (negative) {
        bytesValue = bytesValue - pow(2, (bytes.length() * 8) - 1);     //If the value is negative, we use the formula to get the twos complement of that number (Cn2 - 2^n = -N)
    }

    return bytesValue * resolution;
}

QString DataTools::GetAircraftIDFromBytes(QVector<unsigned char> bytes) {           //Function that translates from bytes to callsign using ICAO encoding

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

double DataTools::DecodeSpecialTwosComplement(QVector<unsigned char> bytes, double resolution, unsigned char  mask, int signIndicator) {        //Function to decode twos complement when sign byte is not in MSB

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

CoordinatesXYZ RadarTools::ChangeRadarCartesianToGeocentric(WGS84Coordinates radarCoords, CoordinatesXYZ radarCartesian) {  //Function to change from radar 2D Cartesian to Geocentric

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

WGS84Coordinates RadarTools::ChangeGeocentricToGeodesic(CoordinatesXYZ objectGeocenctric) {             //Change from Geocentric to Geodesic
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
    lat = atan((z / d_xy) /
               (1 - (A * E2) / sqrt(d_xy * d_xy + z * z)));
    double nu = A / sqrt(1 - E2 * pow(sin(lat), 2.0));
    height = (d_xy / cos(lat)) - nu;

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

    result.SetLatitude(lat*RAD2DEG);
    result.SetLongitude(lon*RAD2DEG);
    result.SetHeight(height);
    return result;
}

}




