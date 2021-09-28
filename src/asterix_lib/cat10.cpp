#include "hdr/asterix_lib/cat10.h"
#include "hdr/asterix_lib/utilities.h"


Cat10::Cat10()
{
    this->category = 10;
    this->length = 0;

    this->systemAreaCode = 0;
    this->systemIdentificationCode = 0;

    this->typeOfMessage = "N/A";
    this->trTYP = "N/A";
    this->trDCR = "N/A";
    this->trCHN = "N/A";
    this->trGBS = "N/A";
    this->trCRT = "N/A";
    this->trSIM = "N/A";
    this->trTST = "N/A";
    this->trRAB = "N/A";
    this->trLOP = "N/A";
    this->trTOT = "N/A";
    this->trSPI = "N/A";

    this->timeOfDay = QTime();
}

void Cat10::FullDecode() {

    if (this->fspec.length() > 0) {

        if ((this->fspec.at(0) & 0x80) == 0x80) {
            QVector<char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeDataSourceIdentifier(dataItem);
        }
        if ((this->fspec.at(0) & 0x40) == 0x40) {
            QVector<char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
            this->DecodeMessageType(dataItem);
        }
        if ((this->fspec.at(0) & 0x20) == 0x20) {
            QVector<char> dataItem = Utilities::DataTools::GetVariableLengthDataItem(this->data);
            this->DecodeTargetReportDescriptor(dataItem);
        }
        if ((this->fspec.at(0) & 0x10) == 0x10) {
            QVector<char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,3);
            this->DecodeTimeOfDay(dataItem);
        }
        if ((this->fspec.at(0) & 0x08) == 0x08) {
            //this->DecodePositionInWGS84Coordinates(dataItem);
        }
        if ((this->fspec.at(0) & 0x04) == 0x04) {
            //this->DecodeMeasuredPositionInPolarCoordinates(dataItem);
        }
        if ((this->fspec.at(0) & 0x02) == 0x02) {
            //this->DecodePositionInCartesianCoordinates(dataItem);
        }
    }

    if (this->fspec.length() > 1) {

        if ((this->fspec.at(1) & 0x80) == 0x80) {
            //this->DecodeCalculatedTrackVelocityInPolarCoordinates(dataItem);
        }
        if ((this->fspec.at(1) & 0x40) == 0x40) {
            //this->DecodeCalculatedTrackVelocityInCartesianCoordinates(dataItem);
        }
        if ((this->fspec.at(1) & 0x20) == 0x20) {
            //this->DecodeTrackNumber(dataItem);
        }
        if ((this->fspec.at(1) & 0x10) == 0x10) {
            //this->DecodeTrackStatus(dataItem);
        }
        if ((this->fspec.at(1) & 0x08) == 0x08) {
            //this->DecodeMode3ACodeInOctalRepresentation(dataItem);
        }
        if ((this->fspec.at(1) & 0x04) == 0x04) {
            //this->DecodeTargetAddress(dataItem);
        }
        if ((this->fspec.at(1) & 0x02) == 0x02) {
            //this->DecodeTargetIdentification(dataItem);
        }
    }
    if (this->fspec.length() > 2) {

        if ((this->fspec.at(2) & 0x80) == 0x80) {
            //this->DecodeModeSMBData(dataItem);
        }
        if ((this->fspec.at(2) & 0x40) == 0x40) {
            //this->DecodeVehicleFleetIdentification(dataItem);
        }
        if ((this->fspec.at(2) & 0x20) == 0x20) {
            //this->DecodeFlightLevelInBinaryRepresentation(dataItem);
        }
        if ((this->fspec.at(2) & 0x10) == 0x10) {
            //this->DecodeMeasuredHeight(dataItem);
        }
        if ((this->fspec.at(2) & 0x08) == 0x08) {
            //this->DecodeTargetSizeAndOrientation(dataItem);
        }
        if ((this->fspec.at(2) & 0x04) == 0x04) {
            //this->DecodeSystemStatus(dataItem);
        }
        if ((this->fspec.at(2) & 0x02) == 0x02) {
            //this->DecodePreProgrammedMessage(dataItem);
        }
    }
    if (this->fspec.length() > 3) {

        if ((this->fspec.at(3) & 0x80) == 0x80) {
            //this->DecodeStandardDeviationOfPosition(dataItem);
        }
        if ((this->fspec.at(3) & 0x40) == 0x40) {
            //this->DecodePresence(dataItem);
        }
        if ((this->fspec.at(3) & 0x20) == 0x20) {
            //this->DecodeAmplitudeOfPrimaryPlot(dataItem);
        }
        if ((this->fspec.at(3) & 0x10) == 0x10) {
            //this->DecodeCalculatedAcceleration(dataItem);
        }
        if ((this->fspec.at(3) & 0x08) == 0x08) {
            //Spare
        }
        if ((this->fspec.at(3) & 0x04) == 0x04) {
            //this->DecodeSpecialPurposeField(dataItem);
        }
        if ((this->fspec.at(2) & 0x02) == 0x02) {
            //Reserved Expansion Field
        }
    }
}

void Cat10::DecodeDataSourceIdentifier(QVector<char> &dataItem) {
    this->systemAreaCode = (short)dataItem.at(0);
    this->systemIdentificationCode = (short)dataItem.at(1);
}

void Cat10::DecodeMessageType(QVector<char> &dataItem) {

    switch (dataItem.at(0)) {
    case 0x01:
        this->typeOfMessage = "Target Report";
        break;
    case 0x02:
        this->typeOfMessage = "Start of Update Cycle";
        break;
    case 0x03:
        this->typeOfMessage = "Periodic Status Message";
        break;
    case 0x04:
        this->typeOfMessage = "Event-triggered Status Message";
        break;
    }
}

void Cat10:: DecodeTargetReportDescriptor(QVector<char> &dataItem) {
    char typMask = 0xE0;
    char dcrMask = 0x10;
    char chnMask = 0x08;
    char gbsMask = 0x04;
    char crtMask = 0x02;

    char typ = ((dataItem.at(0) & typMask) >> 5);
    char dcr = ((dataItem.at(0) & dcrMask) >> 4);
    char chn = ((dataItem.at(0) & chnMask) >> 3);
    char gbs = ((dataItem.at(0) & gbsMask) >> 2);
    char crt = ((dataItem.at(0) & crtMask) >> 1);

    switch (typ)
    {
    case 0x00:
        this->trTYP = "SSR multilateration";
        break;
    case 0x01:
        this->trTYP = "Mode S multilateration";
        break;
    case 0x02:
        this->trTYP = "ADS-B";
        break;
    case 0x03:
        this->trTYP = "PSR";
        break;
    case 0x04:
        this->trTYP = "Magnetic Loop System";
        break;
    case 0x05:
        this->trTYP = "HF multilateration";
        break;
    case 0x06:
        this->trTYP = "Not defined";
        break;
    case 0x07:
        this->trTYP = "Other types";
        break;
    }

    switch (dcr)
    {
    case 0:
        this->trDCR = "No differential correction";
        break;
    case 1:
        this->trDCR = "Differential correction";
        break;
    }
    switch (chn)
    {
    case 0:
        this->trCHN = "Chain 1";
        break;
    case 1:
        this->trCHN = "Chain 2";
        break;
    }
    switch (gbs)
    {
    case 0:
        this->trGBS = "Transponder Ground bit not set";
        break;
    case 1:
        this->trGBS = "Transponder Ground bit set";
        break;
    }
    switch (crt)
    {
    case 0:
        this->trCRT = "No Corrupted reply in multilateration";
        break;
    case 1:
        this->trCRT = "Corrupted replies in multilateration";
        break;
    }

    if (dataItem.length() >= 2) {

        char simMask = 0x80;
        char tstMask = 0x40;
        char rabMask = 0x20;
        char lopMask = 0x18;
        char totMask = 0x06;

        char sim = ((dataItem.at(1) & simMask) >> 7);
        char tst = ((dataItem.at(1) & tstMask) >> 6);
        char rab = ((dataItem.at(1) & rabMask) >> 5);
        char lop = ((dataItem.at(1) & lopMask) >> 3);
        char tot = ((dataItem.at(1) & totMask) >> 1);

        switch (sim)
        {
        case 0:
            this->trSIM = "Actual target report";
            break;
        case 1:
            this->trSIM = "Simulated target report";
            break;
        }
        switch (tst)
        {
        case 0:
            this->trTST = "Default";
            break;
        case 1:
            this->trTST = "Test Target";
            break;
        }
        switch (rab)
        {
        case 0:
            this->trRAB = "Report from target transponder";
            break;
        case 1:
            this->trRAB = "Report from field monitor (fixed transponder)";
            break;
        }
        switch (lop)
        {
        case 0:
            this->trLOP = "Undetermined";
            break;
        case 1:
            this->trLOP = "Loop Start";
            break;
        case 2:
            this->trLOP = "Loop Finish";
            break;
        }
        switch (tot)
        {
        case 0:
            this->trTOT = "Undetermined";
            break;
        case 1:
            this->trTOT = "Aircraft";
            break;
        case 2:
            this->trTOT = "Ground Vehicle";
            break;
        case 3:
            this->trTOT = "Helicopter";
            break;
        }
    }
    if (dataItem.length() >= 3) {

        if (dataItem.at(2) == 0) {
            this->trSPI = "Absence of PSI";
        }
        else {
            this->trSPI = "Special Position Identification";
        }
    }
}

void Cat10::DecodeTimeOfDay(QVector<char> &dataItem) {
    double timeResolution = pow(2,-7);
    double seconds = Utilities::DataTools::DecodeUnsignedBytesToDouble(dataItem,timeResolution);
    int mseconds = (int) seconds * 1000;
    this->timeOfDay = QTime::fromMSecsSinceStartOfDay(mseconds);
    int t = 1;
}



