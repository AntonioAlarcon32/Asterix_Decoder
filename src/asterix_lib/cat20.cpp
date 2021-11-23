#include "hdr/asterix_lib/cat20.h"

Cat20::Cat20()
{
    this->category = 20;
    this->length = 0;

    this->systemAreaCode = 0;
    this->systemIdentificationCode = 0;

    this->trSsr = "N/A";
    this->trMs = "N/A";
    this->trHf = "N/A";
    this->trVdl4 = "N/A";
    this->trUat = "N/A";
    this->trDme = "N/A";
    this->trOt = "N/A";
    this->trRab = "N/A";
    this->trSpi = "N/A";
    this->trChn = "N/A";
    this->trGbs = "N/A";
    this->trCrt = "N/A";
    this->trSim = "N/A";
    this->trTst = "N/A";
    this->trCf = "N/A";

    this->timeOfDay = QTime();

    this->wgs84latitude = nan("");
    this->wgs84longitude = nan("");

    this->cartesianX = nan("");
    this->cartesianY = nan("");

    this->trackNumber = -1;

    this->tsCnf = "N/A";
    this->tsTre = "N/A";
    this->tsCst = "N/A";
    this->tsCdm = "N/A";
    this->tsMah = "N/A";
    this->tsSth = "N/A";
    this->tsGho = "N/A";

    this->M3AValidated = "N/A";
    this->M3AGarbled = "N/A";
    this->M3ADerivation = "N/A";
    this->M3ACode = "N/A";

    this->cartesianVx = nan("");
    this->cartesianVy = nan("");

    this->flValidated = "N/A";
    this->flGarbled = "N/A";
    this->flFlightLevel = nan("");

    this->ModeCCode = "N/A"; //REVISA ;

    this->targetAddress = "N/A";

    this->targetIdentification = "N/A";

    this->measuredHeight = nan("");

    this->geometricHeight = nan("");

    this->cartesianAx = nan("");
    this->cartesianAy = nan("");

    this->VehicleFleetIdentification = "N/A";

    this->ppmTrb = "N/A";
    this->ppmMsg = "N/A";

    this->paDopX = nanf("");
    this->paDopY = nanf("");
    this->paDopXY = nanf("");

    this->paSigmaX = nanf("");
    this->paSigmaY = nanf("");
    this->paSigmaXY = nanf("");

    this->paSigmaGh = nanf("");

    this->contributingDevices = "N/A"; //REVISA ;

    this->modeSMBData = QVector<QByteArray>();
    this->modeSStoreAddress = QVector<unsigned char>();

    this->cacfsCom = "N/A";
    this->cacfsStat = "N/A";
    this->cacfsMssc = "N/A";
    this->cacfsArc = "N/A";
    this->cacfsAic = "N/A";
    this->cacfsB1A = "N/A";
    this->cacfsB1B = "N/A";

    this->acasReport = "N/A"; //REVISA = "N/A";

    this->M1Validated = "N/A";
    this->M1Garbled = "N/A";
    this->M1Derivation = "N/A";
    this->M1Code = "N/A";

    this->M2Validated = "N/A";
    this->M2Garbled = "N/A";
    this->M2Derivation = "N/A";
    this->M2Code = "N/A";

}


QString Cat20::GetTypeOfMessage() {
    return "N/A";
}

QTime Cat20::GetTimeOfReception() {
    return this->timeOfDay;
}

QString Cat20::GetSACSIC() {
    return QString::number(systemAreaCode) + "/" + QString::number(systemIdentificationCode);
}

WGS84Coordinates Cat20::GetPosition() {
    return WGS84Coordinates(0,0,0);
}
QString Cat20::GetIdentifier() {
    return "N/A";
}



void Cat20::FullDecode() {
    if (this->fspec.length() > 0) {

        if ((this->fspec.at(0) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeDataSourceIdentifier(dataItem);
        }
        if ((this->fspec.at(0) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetVariableLengthDataItem(this->data);
            this->DecodeTargetReportDescriptor(dataItem);
        }
        if ((this->fspec.at(0) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,3);
            this->DecodeTimeOfDay(dataItem);
        }
        if ((this->fspec.at(0) & 0x10) == 0x10) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,8);
            this->DecodePositionInWGS84Coordinates(dataItem);
        }
        if ((this->fspec.at(0) & 0x08) == 0x08) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,6);
            this->DecodePositionInCartesianCoordinates(dataItem);
        }
        if ((this->fspec.at(0) & 0x04) == 0x04) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeTrackNumber(dataItem);
        }
        if ((this->fspec.at(0) & 0x02) == 0x02) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetVariableLengthDataItem(this->data);
            this->DecodeTrackStatus(dataItem);
        }
    }
    if (this->fspec.length() > 1) {

        if ((this->fspec.at(1) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeMode3ACodeInOctalRepresentation(dataItem);
        }
        if ((this->fspec.at(1) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,4);
            this->DecodeCalculatedTrackVelocityInCartesianCoordinates(dataItem);
        }
        if ((this->fspec.at(1) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeFlightLevelInBinaryRepresentation(dataItem);
        }
        if ((this->fspec.at(1) & 0x10) == 0x10) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,4);
            this->DecodeModeCCode(dataItem);
        }
        if ((this->fspec.at(1) & 0x08) == 0x08) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,3);
            this->DecodeTargetAddress(dataItem);
        }
        if ((this->fspec.at(1) & 0x04) == 0x04) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,7);
            this->DecodeTargetIdentification(dataItem);
        }
        if ((this->fspec.at(1) & 0x02) == 0x02) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeMeasuredHeight(dataItem);
        }
    }
    if (this->fspec.length() > 2) {

        if ((this->fspec.at(2) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetRepetitiveDataItem(this->data,2);
            this->DecodeGeometricHeight(dataItem);
        }
        if ((this->fspec.at(2) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeCalculatedAcceleration(dataItem);
        }
        if ((this->fspec.at(2) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
            this->DecodeVehicleFleetIdentification(dataItem);
        }
        if ((this->fspec.at(2) & 0x10) == 0x10) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
            this->DecodePreProgrammedMessage(dataItem);
        }
        if ((this->fspec.at(2) & 0x08) == 0x08) {
            QVector<unsigned char> dataItem = this->GetPositionAccuracyDataItem();
            this->DecodePositionAccuracy(dataItem);
        }
        if ((this->fspec.at(2) & 0x04) == 0x04) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetRepetitiveDataItem(this->data,1);
            this->DecodeContributingDevices(dataItem);
        }
        if ((this->fspec.at(2) & 0x02) == 0x02) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetRepetitiveDataItem(this->data,8);
            this->DecodeBDSRegisterData(dataItem);
        }
    }
    if (this->fspec.length() > 3) {

        if ((this->fspec.at(3) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeCommsACASCapabilityAndFlightStatus(dataItem);
        }
        if ((this->fspec.at(3) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetRepetitiveDataItem(this->data,7);
            this->DecodeACASResolutionAdvisoryReport(dataItem);
        }
        if ((this->fspec.at(3) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetVariableLengthDataItem(this->data);
            this->DecodeWarningErrorConditions(dataItem);
        }
        if ((this->fspec.at(3) & 0x10) == 0x10) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
            this->DecodeMode1CodeInOctalRepresentation(dataItem);
        }
        if ((this->fspec.at(3) & 0x08) == 0x08) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeMode2CodeInOctalRepresentation(dataItem);
        }
        if ((this->fspec.at(3) & 0x04) == 0x04) {
            //this->DecodeSpecialPurposeField(dataItem);
        }
        if ((this->fspec.at(3) & 0x02) == 0x02) {
            //Reserved Expansion Field
        }
    }
}


void Cat20::DecodeDataSourceIdentifier(QVector<unsigned char> &dataItem) {
    this->systemAreaCode = (short)dataItem.at(0);
    this->systemIdentificationCode = (short)dataItem.at(1);
}

void Cat20::DecodeTargetReportDescriptor(QVector<unsigned char> &dataItem) {
    unsigned char ssrMask = 128;
    unsigned char msMask = 64;
    unsigned char hfMask = 32;
    unsigned char vdl4Mask = 16;
    unsigned char uatMask = 8;
    unsigned char dmeMask = 4;
    unsigned char otMask = 2;

    unsigned char ssr = (dataItem.at(0) & ssrMask) >> 7;
    unsigned char ms = (dataItem.at(0) & msMask) >> 6;
    unsigned char hf = (dataItem.at(0) & hfMask) >> 5;
    unsigned char vdl4 = (dataItem.at(0) & vdl4Mask) >> 4;
    unsigned char uat = (dataItem.at(0) & uatMask) >> 3;
    unsigned char dme = (dataItem.at(0) & dmeMask) >> 2;
    unsigned char ot = (dataItem.at(0) & otMask) >> 1;

    switch (ssr) {
    case 0:
        this->trSsr = "No Non-Mode S 1090MHz multilat.";
        break;
    case 1:
        this->trSsr = "Non-Mode S 1090MHz multilateration";
        break;
    }

    switch (ms) {
    case 0:
        this->trMs = "No Mode-S 1090 MHz multilateration";
        break;
    case 1:
        this->trMs = "Mode-S 1090 MHz multilateration";
        break;
    }

    switch (hf) {
    case 0:
        this->trHf = "No HF multilateration";
        break;
    case 1:
        this->trHf = "HF multilateration";
        break;
    }

    switch (vdl4) {
    case 0:
        this->trVdl4 = "No VDL Mode 4 multilateration";
        break;
    case 1:
        this->trVdl4 = "VDL Mode 4 multilateration";
        break;
    }

    switch (uat) {
    case 0:
        this->trUat = "No UAT multilateration";
        break;
    case 1:
        this->trUat = "UAT multilateration";
        break;
    }

    switch (dme) {
    case 0:
        this->trDme = "No DME/TACAN multilateration";
        break;
    case 1:
        this->trDme = "DME/TACAN multilateration";
        break;
    }

    switch (ot) {
    case 0:
        this->trOt = "No Other Technology multilateration";
        break;
    case 1:
        this->trOt = "Other Technology multilateration";
        break;
    }

    if (dataItem.length() > 1) {

        unsigned char rabMask = 128;
        unsigned char spiMask = 64;
        unsigned char chnMask = 32;
        unsigned char gbsMask = 16;
        unsigned char crtMask = 8;
        unsigned char simMask = 4;
        unsigned char tstMask = 2;

        unsigned char rab = (dataItem.at(1) & rabMask) >> 7;
        unsigned char spi = (dataItem.at(1) & spiMask) >> 6;
        unsigned char chn = (dataItem.at(1) & chnMask) >> 5;
        unsigned char gbs = (dataItem.at(1) & gbsMask) >> 4;
        unsigned char crt = (dataItem.at(1) & crtMask) >> 3;
        unsigned char sim = (dataItem.at(1) & simMask) >> 2;
        unsigned char tst = (dataItem.at(1) & tstMask) >> 1;

        switch (rab) {
        case 0:
            this->trRab = "Report from Target Transponder";
            break;
        case 1:
            this->trRab = "Report from Field Monitor";
            break;
        }

        switch (spi) {
        case 0:
            this->trSpi = "Absence of SPI";
            break;
        case 1:
            this->trSpi = "Special Position Identification";
            break;
        }

        switch (chn) {
        case 0:
            this->trChn = "Chain 1";
            break;
        case 1:
            this->trChn = "Chain 2";
            break;
        }

        switch (gbs) {
        case 0:
            this->trGbs = "Transponder Ground Bit not set";
            break;
        case 1:
            this->trGbs = "Transponder Ground Bit set";
            break;
        }

        switch (crt) {
        case 0:
            this->trCrt = "No Corrupted reply in multilateration";
            break;
        case 1:
            this->trCrt = "Corrupted Replies in multilateration";
            break;
        }

        switch (sim) {
        case 0:
            this->trSim = "Actual Target Report";
            break;
        case 1:
            this->trSim = "Simulated Target Report";
            break;
        }

        switch (tst) {
        case 0:
            this->trTst = "Default";
            break;
        case 1:
            this->trTst = "Test Target";
            break;
        }
    }

    if (dataItem.length() > 2) {
        unsigned char cfMask = 192;

        unsigned char cf = (dataItem.at(2) & cfMask) >> 6;

        switch (cf) {
        case 0:
            this->trCf = "Target with 24-bit ICAO Address";
            break;
        case 1:
            this->trCf = "Target with a non-ICAO 24-bit Address";
            break;
        case 2:
            this->trCf = "non-ADS-B Message";
            break;
        case 3:
            this->trCf = "Information not available";
            break;
        }
    }
}

void Cat20::DecodeTimeOfDay(QVector<unsigned char> &dataItem) {
    double timeResolution = pow(2,-7);
    double seconds = Utilities::DataTools::DecodeUnsignedBytesToDouble(dataItem,timeResolution);
    int mseconds = seconds * 1000;
    this->timeOfDay = QTime::fromMSecsSinceStartOfDay(mseconds);
}

void Cat20::DecodePositionInWGS84Coordinates(QVector<unsigned char> &dataItem) {
    QVector<unsigned char> latitudeBytes = {dataItem.at(0), dataItem.at(1), dataItem.at(2),dataItem.at(3)};
    QVector<unsigned char> longitudeBytes = {dataItem.at(4), dataItem.at(5), dataItem.at(6),dataItem.at(7)};
    double resolution = 180 / pow(2,30);
    this->wgs84latitude = Utilities::DataTools::DecodeTwosComplementToDouble(latitudeBytes, resolution);
    this->wgs84longitude = Utilities::DataTools::DecodeTwosComplementToDouble(longitudeBytes, resolution);
}

void Cat20::DecodePositionInCartesianCoordinates(QVector<unsigned char> &dataItem) {

    QVector<unsigned char> latitudeBytes = {dataItem.at(0), dataItem.at(1), dataItem.at(2)};
    QVector<unsigned char> longitudeBytes = {dataItem.at(3), dataItem.at(4), dataItem.at(5)};
    double resolution = 0.5;
    this->cartesianX = Utilities::DataTools::DecodeTwosComplementToDouble(latitudeBytes, resolution);
    this->cartesianY = Utilities::DataTools::DecodeTwosComplementToDouble(longitudeBytes, resolution);

}

void Cat20::DecodeTrackNumber(QVector<unsigned char> &dataItem) {
    QVector<unsigned char> trackBytes = {dataItem.at(0), dataItem.at(1)};
    double resolution = 1;
    this->trackNumber = (int) Utilities::DataTools::DecodeUnsignedBytesToDouble(trackBytes,resolution);
}

void Cat20::DecodeTrackStatus(QVector<unsigned char> &dataItem) {
    unsigned char cnfMask = 128;
    unsigned char treMask = 64;
    unsigned char cstMask = 32;
    unsigned char cdmMask = 24;
    unsigned char mahMask = 4;
    unsigned char sthMask = 2;

    unsigned char cnf = (dataItem.at(0) & cnfMask) >> 7;
    unsigned char tre = (dataItem.at(0) & treMask) >> 6;
    unsigned char cst = (dataItem.at(0) & cstMask) >> 5;
    unsigned char cdm = (dataItem.at(0) & cdmMask) >> 3;
    unsigned char mah = (dataItem.at(0) & mahMask) >> 2;
    unsigned char sth = (dataItem.at(0) & sthMask) >> 1;

    switch (cnf) {
    case 0:
        this->tsCnf = "Confirmed Track";
        break;
    case 1:
        this->tsCnf = "Track in initiation phase";
        break;
    }

    switch (tre) {
    case 0:
        this->tsTre = "Default";
        break;
    case 1:
        this->tsTre = "Last report for a track";
        break;
    }

    switch (cst) {
    case 0:
        this->tsCst = "Not Coasted";
        break;
    case 1:
        this->tsCst = "Coasted";
        break;
    }

    switch (cdm) {
    case 0:
        this->tsCdm = "Maintaining";
        break;
    case 1:
        this->tsCdm = "Climbing";
        break;
    case 2:
        this->tsCdm = "Descending";
        break;
    case 3:
        this->tsCdm = "Invalid";
        break;
    }

    switch (mah) {
    case 0:
        this->tsMah = "Default";
        break;
    case 1:
        this->tsMah = "Horizontal Manoeuvre";
        break;
    }

    switch (sth) {
    case 0:
        this->tsSth = "Measured Position";
        break;
    case 1:
        this->tsSth = "Smoothed Position";
        break;
    }

    if (dataItem.length() > 1) {

        unsigned char ghoMask = 128;
        unsigned char gho = (dataItem.at(1) & ghoMask) >> 7;

        switch (gho) {
        case 0:
            this->tsGho = "Default";
            break;
        case 1:
            this->tsGho = "Ghost Track";
            break;
        }
    }
}

void Cat20::DecodeMode3ACodeInOctalRepresentation(QVector<unsigned char> &dataItem) {
    unsigned char vMask = 0x80;
    unsigned char gMask = 0x40;
    unsigned char lMask = 0x20;

    unsigned char validated = ((dataItem.at(0) & vMask) >> 6);
    unsigned char garbled = ((dataItem.at(0) & gMask) >> 3);
    unsigned char derived = ((dataItem.at(0) & lMask) >> 1);

    switch (validated)
    {
    case 0:
        this->M3AValidated = "Code Validated";
        break;
    case 1:
        this->M3AValidated = "Code Not Validated";
        break;
    }
    switch (garbled)
    {
    case 0:
        this->M3AGarbled = "Default";
        break;
    case 1:
        this->M3AGarbled = "Garbled Code";
        break;
    }
    switch (derived)
    {
    case 0:
        this->M3ADerivation = "Mode-3/A code derived from the reply of the transponder";
        break;
    case 1:
        this->M3ADerivation = "Mode-3/A code not extracted during the last scan";
        break;
    }

    unsigned char aMask = 0x0E;

    unsigned char A = (dataItem.at(0) & aMask) >> 1;
    unsigned char B4 = (dataItem.at(0) & 0x01) << 2;
    unsigned char B21 = (dataItem.at(1) & 0xC0) >> 6;

    unsigned char B = B4 | B21;

    unsigned char C = (dataItem.at(1) & 0x38) >> 3;
    unsigned char D = (dataItem.at(1) & 0x07);
    int code = A * 1000 + B * 100 + C * 10 + D;
    this->M3ACode = QString::number(code);
}

void Cat20::DecodeCalculatedTrackVelocityInCartesianCoordinates(QVector<unsigned char> &dataItem) {

    QVector<unsigned char> xBytes = { dataItem.at(0), dataItem.at(1) };
    double xResolution = 0.25;
    this->cartesianVx = Utilities::DataTools::DecodeTwosComplementToDouble(xBytes, xResolution);
    QVector<unsigned char> yBytes = { dataItem.at(2), dataItem.at(3) };
    double yResolution = 0.25;
    this->cartesianVy = Utilities::DataTools::DecodeTwosComplementToDouble(yBytes, yResolution);

}

void Cat20::DecodeFlightLevelInBinaryRepresentation(QVector<unsigned char> &dataItem) {
    unsigned char valueMask = 0b00111111;

    unsigned char maskForFunction = 0b00011111;
    int valueForLimit = 32;

    unsigned char firstByte = (dataItem.at(0) & valueMask);
    QVector<unsigned char> bytes = {firstByte, dataItem.at(1)};
    double resolution = 0.25;
    this->flFlightLevel = Utilities::DataTools::DecodeSpecialTwosComplement(bytes,resolution,maskForFunction, valueForLimit);

    unsigned char vMask = 128;
    unsigned char gMask = 64;
    unsigned char validated = (dataItem.at(0) & vMask) >> 7;
    unsigned char garbled = (dataItem.at(0) & gMask) >> 6;

    switch (validated) {
    case 0:
        this->flValidated = "Code Validated";
        break;
    case 1:
        this->flValidated = "Code not validated";
        break;
    }

    switch (garbled) {
    case 0:
        this->flGarbled = "Default";
        break;
    case 1:
        this->flGarbled = "Garbled Code";
        break;
    }
}

void Cat20::DecodeModeCCode(QVector<unsigned char> &dataItem) {

}

void Cat20::DecodeTargetAddress(QVector<unsigned char> &dataItem) {
    QString buildAddress = "0x";

    for (unsigned char byte : dataItem) {
        short a = (short) byte;
        QString str = QString("%1").arg(a,0,16);
        buildAddress.append(str);
    }
    this->targetAddress = buildAddress;
}

void Cat20::DecodeTargetIdentification(QVector<unsigned char> &dataItem) {
    unsigned char char1 = (dataItem.at(1) & 0xFC) >> 2;
    unsigned char char2 = ((dataItem.at(1) & 0x03) << 4) | ((dataItem.at(2) & 0xF0) >> 4);
    unsigned char char3 =((dataItem.at(3) & 0xC0) >> 6) | ((dataItem.at(2) & 0x0F) << 2);
    unsigned char char4 =(dataItem.at(3) & 0x3F);
    unsigned char char5 =(dataItem.at(4) & 0xFC) >> 2;
    unsigned char char6 = ((dataItem.at(4) & 0x03) << 4) | ((dataItem.at(5) & 0xF0) >> 4);
    unsigned char char7 = ((dataItem.at(6) & 0xC0) >> 6) | ((dataItem.at(5) & 0x0F) << 2);
    unsigned char char8 = (dataItem.at(6) & 0x3F);
    QVector<unsigned char> bytes = {char1,char2,char3,char4,char5,char6,char7,char8};
    this->targetIdentification = Utilities::DataTools::GetAircraftIDFromBytes(bytes);
}

void Cat20::DecodeMeasuredHeight(QVector<unsigned char> &dataItem) {
    double resolution = 6.25;
    this->measuredHeight = Utilities::DataTools::DecodeTwosComplementToDouble(dataItem,resolution);
}

void Cat20::DecodeGeometricHeight(QVector<unsigned char> &dataItem) {
    double resolution = 6.25;
    this->geometricHeight = Utilities::DataTools::DecodeTwosComplementToDouble(dataItem,resolution);
}

void Cat20::DecodeCalculatedAcceleration(QVector<unsigned char> &dataItem) {
    QVector<unsigned char> xBytes = { dataItem.at(0) };
    double xResolution = 0.25;
    this->cartesianAx = Utilities::DataTools::DecodeTwosComplementToDouble(xBytes, xResolution);
    QVector<unsigned char> yBytes = { dataItem.at(1) };
    double yResolution = 0.25;
    this->cartesianAy = Utilities::DataTools::DecodeTwosComplementToDouble(yBytes, yResolution);
}

void Cat20::DecodeVehicleFleetIdentification(QVector<unsigned char> &dataItem) {
    switch (dataItem.at(0)) {
    case 0:
        this->VehicleFleetIdentification= "Unknown";
        break;
    case 1:
        this->VehicleFleetIdentification = "ATC equipment maintenance";
        break;
    case 2:
        this->VehicleFleetIdentification = "Airport maintenance";
        break;
    case 3:
        this->VehicleFleetIdentification = "Fire";
        break;
    case 4:
        this->VehicleFleetIdentification = "Bird scarer";
        break;
    case 5:
        this->VehicleFleetIdentification = "Snow plough";
        break;
    case 6:
        this->VehicleFleetIdentification = "Runaway Sweeper";
        break;
    case 7:
        this->VehicleFleetIdentification = "Emergency";
        break;
    case 8:
        this->VehicleFleetIdentification = "Police";
        break;
    case 9:
        this->VehicleFleetIdentification = "Bus";
        break;
    case 10:
        this->VehicleFleetIdentification = "Tug(push/tow)";
        break;
    case 11:
        this->VehicleFleetIdentification = "Grass cutter";
        break;
    case 12:
        this->VehicleFleetIdentification = "Fuel";
        break;
    case 13:
        this->VehicleFleetIdentification = "Baggage";
        break;
    case 14:
        this->VehicleFleetIdentification = "Catering";
        break;
    case 15:
        this->VehicleFleetIdentification = "Aircraft maintenance";
        break;
    case 16:
        this->VehicleFleetIdentification = "Flyco (follow me)";
        break;
    }
}

void Cat20::DecodePreProgrammedMessage(QVector<unsigned char> &dataItem) {

    unsigned char trMask = 128;
    unsigned char msgMask = 127;

    unsigned char trouble = (dataItem.at(0) & trMask) >> 7;
    unsigned char msg = (dataItem.at(0) & msgMask);

    switch (trouble) {
    case 0:
        this->ppmTrb = "Default";
        break;
    case 1:
        this->ppmTrb = "In Trouble";
        break;
    }

    switch (msg) {
    case 1:
        this->ppmMsg = "Towing Aircraft";
        break;
    case 2:
        this->ppmMsg = "'Follow me' operation";
        break;
    case 3:
        this->ppmMsg = "Runway check";
        break;
    case 4:
        this->ppmMsg = "Emergency operation(fire,medical...)";
        break;
    case 5:
        this->ppmMsg = "Work in progress(maintenance,birds scarer,sweepers...)";
        break;
    }
}

void Cat20::DecodePositionAccuracy(QVector<unsigned char> &dataItem) {


    if ((dataItem.at(0) & 128) != 0) {

        QVector<unsigned char> xBytes = { dataItem.at(1), dataItem.at(2) };
        QVector<unsigned char> yBytes = { dataItem.at(3), dataItem.at(4) };
        QVector<unsigned char> xyBytes = { dataItem.at(5), dataItem.at(6) };

        dataItem.remove(1,6);

        this->paDopX = Utilities::DataTools::DecodeUnsignedBytesToDouble(xBytes, 0.25);
        this->paDopY = Utilities::DataTools::DecodeUnsignedBytesToDouble(yBytes, 0.25);
        this->paDopXY = Utilities::DataTools::DecodeUnsignedBytesToDouble(xyBytes, 0.25);
    }

    if ((dataItem.at(0) & 64) != 0) {

        QVector<unsigned char> xBytes = { dataItem.at(1), dataItem.at(2) };
        QVector<unsigned char> yBytes = { dataItem.at(3), dataItem.at(4) };
        QVector<unsigned char> xyBytes = { dataItem.at(5), dataItem.at(6) };

        dataItem.remove(1,6);

        this->paSigmaX = Utilities::DataTools::DecodeUnsignedBytesToDouble(xBytes, 0.25);
        this->paSigmaY = Utilities::DataTools::DecodeUnsignedBytesToDouble(yBytes, 0.25);
        this->paSigmaXY = Utilities::DataTools::DecodeUnsignedBytesToDouble(xyBytes, 0.25);
    }

    if ((dataItem.at(0) & 32) != 0) {

        QVector<unsigned char> ghBytes = { dataItem.at(1), dataItem.at(2) };
        this->paSigmaGh = Utilities::DataTools::DecodeUnsignedBytesToDouble(ghBytes, 0.5);
    }
}

void Cat20::DecodeContributingDevices(QVector<unsigned char> &dataItem) {
    QString devices;
    int numberOfDevice = 1;
    dataItem.removeFirst();

    for(unsigned char byte : dataItem) {
        if (byte != 0) {
            devices.append(QString::number(numberOfDevice) + ",");
        }
        numberOfDevice++;
    }
    devices.remove(devices.length()-1);
    this->contributingDevices = devices;
}

void Cat20::DecodeBDSRegisterData(QVector<unsigned char> &dataItem) {
    int c = 0;
    unsigned char repetitions = dataItem.at(0);
    dataItem.removeFirst();
    while (c < repetitions) {
        int i = 0;
        QByteArray data;
        data.resize(7);
        while (i < 7) {
            data[i] = dataItem.at(0);
            dataItem.removeFirst();
            i++;
        }
        this->modeSMBData.append(data);
        this->modeSStoreAddress.append(dataItem.at(0));
        dataItem.removeFirst();
        c++;
    }
}

void Cat20::DecodeCommsACASCapabilityAndFlightStatus(QVector<unsigned char> &dataItem) {

    unsigned char comMask = 224;
    unsigned char statMask = 28;
    unsigned char msscMask = 128;
    unsigned char arcMask = 64;
    unsigned char aicMask = 32;
    unsigned char b1aMask = 16;
    unsigned char b1bMask = 15;

    unsigned char com = (dataItem.at(0) & comMask) >> 5;
    unsigned char stat = (dataItem.at(0) & statMask) >> 2;

    unsigned char mssc = (dataItem.at(1) & msscMask) >> 7;
    unsigned char arc = (dataItem.at(1) & arcMask) >> 6;
    unsigned char aic = (dataItem.at(1) & aicMask) >> 5;
    unsigned char b1a = (dataItem.at(1) & b1aMask) >> 4;
    unsigned char b1b = (dataItem.at(1) & b1bMask);

    switch (com)
    {
    case 0:
        this->cacfsCom= "No communications capability (surveillance only)";
        break;
    case 1:
        this->cacfsCom = "Comm. A and Comm. B capability";
        break;
    case 2:
        this->cacfsCom = "Comm. A, Comm. B and Uplink ELM";
        break;
    case 3:
        this->cacfsCom = "Comm. A, Comm. B, Uplink ELM and Downlink ELM";
        break;
    case 4:
        this->cacfsCom = "Level 5 Transponder capability";
        break;
    case 5:
        this->cacfsCom = "Not Assigned";
        break;
    case 6:
        this->cacfsCom = "Not Assigned";
        break;
    case 7:
        this->cacfsCom = "Not Assigned";
        break;
    }

    switch (stat)
    {
    case 0:
        this->cacfsStat= "No alert, no SPI, aircraft airborne";
        break;
    case 1:
        this->cacfsStat = "No alert, no SPI, aircraft on ground";
        break;
    case 2:
        this->cacfsStat = "Alert, no SPI, aircraft airborne";
        break;
    case 3:
        this->cacfsStat = "Alert, no SPI, aircraft on ground";
        break;
    case 4:
        this->cacfsStat = "Alert, SPI, aircraft airborne or on ground";
        break;
    case 5:
        this->cacfsStat = "No alert, SPI, aircraft airborne or on ground";
        break;
    case 6:
        this->cacfsStat = "Not Assigned";
        break;
    case 7:
        this->cacfsStat = "Information not yet extracted";
        break;
    }

    switch (mssc) {
    case 0:
        this->cacfsMssc = "No";
        break;
    case 1:
        this->cacfsMssc = "Yes";
        break;
    }

    switch (arc) {
    case 0:
        this->cacfsArc = "100 ft resolution";
        break;
    case 1:
        this->cacfsArc = "25 ft resolution";
        break;
    }

    switch (aic) {
    case 0:
        this->cacfsAic = "No";
        break;
    case 1:
        this->cacfsAic = "Yes";
        break;
    }

    //REVISAR LOS B1A y B1B

}

void Cat20::DecodeACASResolutionAdvisoryReport(QVector<unsigned char> &dataItem) {}

void Cat20::DecodeWarningErrorConditions(QVector<unsigned char> &dataItem) {

    for (unsigned char byte : dataItem) {
        unsigned char errorCode = (byte & 254) >> 1;
        switch (errorCode) {
        case 0:
            this->errors.append("Not defined; never used");
            break;
        case 1:
            this->errors.append("Multipath Reply (Reflection)");
            break;
        case 3:
            this->errors.append("Split plot");
            break;
        case 10:
            this->errors.append("Phantom SSR plot");
            break;
        case 11:
            this->errors.append("Non-Matching Mode-3/A Code");
            break;
        case 12:
            this->errors.append("Mode C code / Mode S altitude code abnormal value compared to the track");
            break;
        case 15:
            this->errors.append("Transponder anomaly detected");
            break;
        case 16:
            this->errors.append("Duplicated or Illegal Mode S Aircraft Address");
            break;
        case 17:
            this->errors.append("Mode S error correction applied");
            break;
        case 18:
            this->errors.append("Undecodable Mode C code / Mode S altitude cod");
            break;
        }
    }
}
void Cat20::DecodeMode1CodeInOctalRepresentation(QVector<unsigned char> &dataItem) {

    unsigned char vMask = 0x80;
    unsigned char gMask = 0x40;
    unsigned char lMask = 0x20;

    unsigned char validated = ((dataItem.at(0) & vMask) >> 6);
    unsigned char garbled = ((dataItem.at(0) & gMask) >> 3);
    unsigned char derived = ((dataItem.at(0) & lMask) >> 1);

    switch (validated)
    {
    case 0:
        this->M1Validated = "Code Validated";
        break;
    case 1:
        this->M1Validated = "Code Not Validated";
        break;
    }
    switch (garbled)
    {
    case 0:
        this->M1Garbled = "Default";
        break;
    case 1:
        this->M1Garbled = "Garbled Code";
        break;
    }
    switch (derived)
    {
    case 0:
        this->M1Derivation = "Mode-2 code derived from the reply of the transponder";
        break;
    case 1:
        this->M1Derivation = "Mode-2 code not extracted during the last scan";
        break;
    }

    unsigned char A = (dataItem.at(0) & 0b00011100) >> 2;
    unsigned char B = (dataItem.at(0) & 0b00000011);

    int code = A * 10 + B;
    this->M1Code = QString::number(code);

}

void Cat20::DecodeMode2CodeInOctalRepresentation(QVector<unsigned char> &dataItem) {
    unsigned char vMask = 0x80;
    unsigned char gMask = 0x40;
    unsigned char lMask = 0x20;

    unsigned char validated = ((dataItem.at(0) & vMask) >> 6);
    unsigned char garbled = ((dataItem.at(0) & gMask) >> 3);
    unsigned char derived = ((dataItem.at(0) & lMask) >> 1);

    switch (validated)
    {
    case 0:
        this->M2Validated = "Code Validated";
        break;
    case 1:
        this->M2Validated = "Code Not Validated";
        break;
    }
    switch (garbled)
    {
    case 0:
        this->M2Garbled = "Default";
        break;
    case 1:
        this->M2Garbled = "Garbled Code";
        break;
    }
    switch (derived)
    {
    case 0:
        this->M2Derivation = "Mode-2 code derived from the reply of the transponder";
        break;
    case 1:
        this->M2Derivation = "Mode-2 code not extracted during the last scan";
        break;
    }

    unsigned char aMask = 0x0E;

    unsigned char A = (dataItem.at(0) & aMask) >> 1;
    unsigned char B4 = (dataItem.at(0) & 0x01) << 2;
    unsigned char B21 = (dataItem.at(1) & 0xC0) >> 6;

    unsigned char B = B4 | B21;

    unsigned char C = (dataItem.at(1) & 0x38) >> 3;
    unsigned char D = (dataItem.at(1) & 0x07);
    int code = A * 1000 + B * 100 + C * 10 + D;
    this->M2Code = QString::number(code);
}

QVector<unsigned char> Cat20::GetPositionAccuracyDataItem() {
    QVector<unsigned char> dataItemStatus = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
    int subItemsLenght = 0;

    if ((dataItemStatus.at(0) & 128) != 0) {
        subItemsLenght += 6;
    }
    if ((dataItemStatus.at(0) & 64) != 0) {
        subItemsLenght += 6;
    }
    if ((dataItemStatus.at(0) & 32) != 0) {
        subItemsLenght += 2;
    }

    QVector<unsigned char> subDataItems = Utilities::DataTools::GetFixedLengthDataItem(this->data,subItemsLenght);
    dataItemStatus.append(subDataItems);
    return dataItemStatus;
}
