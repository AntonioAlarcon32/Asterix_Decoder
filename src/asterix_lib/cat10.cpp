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

    this->wgs84latitude = nan("");
    this->wgs84longitude = nan("");

    this->polarRho = nan("");
    this->polarTheta = nan("");

    this->cartesianX = nan("");
    this->cartesianY = nan("");

    this->M3AValidated = "N/A";
    this->M3AGarbled = "N/A";
    this->M3ACode = "N/A";
    this->M3ADerivation= "N/A";

    this->targetAddress = "N/A";

    this->targetIdentification = "N/A";

    this->polarGroundSpeed = nan("");
    this->polarTrackAngle = nan("");

    this->cartesianVx = nan("");
    this->cartesianVy = nan("");

    this->trackNumber = -1;

    this->tsCNF = "N/A";
    this->tsTRE = "N/A";
    this->tsCST = "N/A";
    this->tsMAH = "N/A";
    this->tsTCC = "N/A";
    this->tsSTH = "N/A";
    this->tsTOM = "N/A";
    this->tsDOU = "N/A";
    this->tsMRS = "N/A";
    this->tsGHO = "N/A";

    this->targetLength = nan("");
    this->targetOrientation = nan("");
    this->targetWidth = nan("");

    this->calcAccelerationX = nan("");
    this->calcAccelerationY = nan("");

    this->ssNOGO = "N/A";
    this->ssOVL = "N/A";
    this->ssTSV = "N/A";
    this->ssDIV = "N/A";
    this->ssTTF = "N/A";

    this->flFlightLevel = nan("");
    this->flGarbled = "N/A";
    this->flValidated = "N/A";

    this->vehicleFleetId= "N/A";

    this->measuredHeight = nan("");

    this->ppmTRB = "N/A";
    this->ppMSG= "N/A";

    this->standardDeviationX = nan("");
    this->standardDeviationY = nan("");
    this->standardDeviationXY = nan("");
    this->amplitudeOfPrimaryPlot= nan("");


    //this->ModeSMBData = new List<byte[]>();
    //this->ModeSMBCodes = new List<byte[]>();
}

void Cat10::FullDecode() {

    if (this->fspec.length() > 0) {

        if ((this->fspec.at(0) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeDataSourceIdentifier(dataItem);
        }
        if ((this->fspec.at(0) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
            this->DecodeMessageType(dataItem);
        }
        if ((this->fspec.at(0) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetVariableLengthDataItem(this->data);
            this->DecodeTargetReportDescriptor(dataItem);
        }
        if ((this->fspec.at(0) & 0x10) == 0x10) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,3);
            this->DecodeTimeOfDay(dataItem);
        }
        if ((this->fspec.at(0) & 0x08) == 0x08) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,8);
            this->DecodePositionInWGS84Coordinates(dataItem);
        }
        if ((this->fspec.at(0) & 0x04) == 0x04) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,4);
            this->DecodeMeasuredPositionInPolarCoordinates(dataItem);
        }
        if ((this->fspec.at(0) & 0x02) == 0x02) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,4);
            this->DecodePositionInCartesianCoordinates(dataItem);
        }
    }

    if (this->fspec.length() > 1) {

        if ((this->fspec.at(1) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,4);
            this->DecodeCalculatedTrackVelocityInPolarCoordinates(dataItem);
        }
        if ((this->fspec.at(1) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,4);
            this->DecodeCalculatedTrackVelocityInCartesianCoordinates(dataItem);
        }
        if ((this->fspec.at(1) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeTrackNumber(dataItem);
        }
        if ((this->fspec.at(1) & 0x10) == 0x10) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetVariableLengthDataItem(this->data);
            this->DecodeTrackStatus(dataItem);
        }
        if ((this->fspec.at(1) & 0x08) == 0x08) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeMode3ACodeInOctalRepresentation(dataItem);
        }
        if ((this->fspec.at(1) & 0x04) == 0x04) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,3);
            this->DecodeTargetAddress(dataItem);
        }
        if ((this->fspec.at(1) & 0x02) == 0x02) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,7);
            this->DecodeTargetIdentification(dataItem);
        }
    }
    if (this->fspec.length() > 2) {

        if ((this->fspec.at(2) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetRepetitiveDataItem(this->data,8);
            this->DecodeModeSMBData(dataItem);
        }
        if ((this->fspec.at(2) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
            this->DecodeVehicleFleetIdentification(dataItem);
        }
        if ((this->fspec.at(2) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeFlightLevelInBinaryRepresentation(dataItem);
        }
        if ((this->fspec.at(2) & 0x10) == 0x10) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeMeasuredHeight(dataItem);
        }
        if ((this->fspec.at(2) & 0x08) == 0x08) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetVariableLengthDataItem(this->data);
            this->DecodeTargetSizeAndOrientation(dataItem);
        }
        if ((this->fspec.at(2) & 0x04) == 0x04) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
            this->DecodeSystemStatus(dataItem);
        }
        if ((this->fspec.at(2) & 0x02) == 0x02) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
            this->DecodePreProgrammedMessage(dataItem);
        }
    }
    if (this->fspec.length() > 3) {

        if ((this->fspec.at(3) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,4);
            this->DecodeStandardDeviationOfPosition(dataItem);
        }
        if ((this->fspec.at(3) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetRepetitiveDataItem(this->data,2);
            this->DecodePresence(dataItem);
        }
        if ((this->fspec.at(3) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
            this->DecodeAmplitudeOfPrimaryPlot(dataItem);
        }
        if ((this->fspec.at(3) & 0x10) == 0x10) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeCalculatedAcceleration(dataItem);
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

void Cat10::DecodeDataSourceIdentifier(QVector<unsigned char> &dataItem) {
    this->systemAreaCode = (short)dataItem.at(0);
    this->systemIdentificationCode = (short)dataItem.at(1);
}

void Cat10::DecodeMessageType(QVector<unsigned char> &dataItem) {

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

void Cat10:: DecodeTargetReportDescriptor(QVector<unsigned char> &dataItem) {
    unsigned char typMask = 0xE0;
    unsigned char dcrMask = 0x10;
    unsigned char chnMask = 0x08;
    unsigned char gbsMask = 0x04;
    unsigned char crtMask = 0x02;

    unsigned char typ = ((dataItem.at(0) & typMask) >> 5);
    unsigned char dcr = ((dataItem.at(0) & dcrMask) >> 4);
    unsigned char chn = ((dataItem.at(0) & chnMask) >> 3);
    unsigned char gbs = ((dataItem.at(0) & gbsMask) >> 2);
    unsigned char crt = ((dataItem.at(0) & crtMask) >> 1);

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

        unsigned char simMask = 0x80;
        unsigned char tstMask = 0x40;
        unsigned char rabMask = 0x20;
        unsigned char lopMask = 0x18;
        unsigned char totMask = 0x06;

        unsigned char sim = ((dataItem.at(1) & simMask) >> 7);
        unsigned char tst = ((dataItem.at(1) & tstMask) >> 6);
        unsigned char rab = ((dataItem.at(1) & rabMask) >> 5);
        unsigned char lop = ((dataItem.at(1) & lopMask) >> 3);
        unsigned char tot = ((dataItem.at(1) & totMask) >> 1);

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

void Cat10::DecodeTimeOfDay(QVector<unsigned char> &dataItem) {
    double timeResolution = pow(2,-7);
    double seconds = Utilities::DataTools::DecodeUnsignedBytesToDouble(dataItem,timeResolution);
    int mseconds = (int) seconds * 1000;
    this->timeOfDay = QTime::fromMSecsSinceStartOfDay(mseconds);
}

void Cat10::DecodePositionInWGS84Coordinates(QVector<unsigned char> &dataItem) {

    int i = 0;
    QVector<unsigned char> latitudeBytes(4);
    QVector<unsigned char> longitudeBytes(4);
    while (i < dataItem.length())
    {
        if (i <= 3)
            latitudeBytes[i] = dataItem[i];
        else if (i > 3)
            longitudeBytes[i - 4] = dataItem[i];
        i++;
    }
    double resolution = 180 / pow(2,31);
    this->wgs84latitude = Utilities::DataTools::DecodeTwosComplementToDouble(latitudeBytes, resolution);
    this->wgs84longitude = Utilities::DataTools::DecodeTwosComplementToDouble(longitudeBytes, resolution);
    int c = 1;
}

void Cat10::DecodeMeasuredPositionInPolarCoordinates(QVector<unsigned char> &dataItem) {

    QVector<unsigned char> rhoBytes = {dataItem.at(0), dataItem.at(1)};
    QVector<unsigned char> thetaBytes = {dataItem.at(2), dataItem.at(3)};

    double rhoResolution = 1;
    double thetaResolution = 360 / pow(2, 16);

    this->polarRho = Utilities::DataTools::DecodeUnsignedBytesToDouble(rhoBytes, rhoResolution);
    this->polarTheta = Utilities::DataTools::DecodeUnsignedBytesToDouble(thetaBytes, thetaResolution);
}

void Cat10::DecodePositionInCartesianCoordinates(QVector<unsigned char> &dataItem) {

    QVector<unsigned char> xBytes = {dataItem.at(0), dataItem.at(1)};
    QVector<unsigned char> yBytes = {dataItem.at(2), dataItem.at(3)};

    double xResolution = 1;
    double yResolution = 1;

    this->cartesianX = Utilities::DataTools::DecodeTwosComplementToDouble(xBytes,xResolution);
    this->cartesianY = Utilities::DataTools::DecodeTwosComplementToDouble(yBytes,yResolution);
}

void Cat10::DecodeCalculatedTrackVelocityInPolarCoordinates(QVector<unsigned char> &dataItem) {

    QVector<unsigned char> speedBytes = {dataItem.at(0), dataItem.at(1)};
    QVector<unsigned char> angleBytes = {dataItem.at(2), dataItem.at(3)};

    double speedResolution = 0.22;
    double angleResolution = 360 / pow(2,16);

    this->polarGroundSpeed = Utilities::DataTools::DecodeUnsignedBytesToDouble(speedBytes, speedResolution);
    this->polarTrackAngle = Utilities::DataTools::DecodeUnsignedBytesToDouble(angleBytes, angleResolution);
}

void Cat10::DecodeCalculatedTrackVelocityInCartesianCoordinates(QVector<unsigned char> &dataItem) {

    QVector<unsigned char> xBytes = {dataItem.at(0), dataItem.at(1)};
    QVector<unsigned char> yBytes = {dataItem.at(2), dataItem.at(3)};

    double xResolution = 0.25;
    double yResolution = 0.25;

    this->cartesianVx = Utilities::DataTools::DecodeTwosComplementToDouble(xBytes,xResolution);
    this->cartesianVy = Utilities::DataTools::DecodeTwosComplementToDouble(yBytes,yResolution);
}

void Cat10::DecodeTrackNumber(QVector<unsigned char> &dataItem) {
    QVector<unsigned char> trackBytes = {dataItem.at(0), dataItem.at(1)};
    double resolution = 1;
    this->trackNumber = (int) Utilities::DataTools::DecodeUnsignedBytesToDouble(trackBytes,resolution);
}
void Cat10::DecodeTrackStatus(QVector<unsigned char> &dataItem) {

    unsigned char cnfMask = 0x80;
    unsigned char treMask = 0x40;
    unsigned char cstMask = 0x30;
    unsigned char mahMask = 0x08;
    unsigned char tccMask = 0x04;
    unsigned char sthMask = 0x02;
    unsigned char cnf = ((dataItem[0] & cnfMask) >> 7);
    unsigned char tre = ((dataItem[0] & treMask) >> 6);
    unsigned char cst = ((dataItem[0] & cstMask) >> 4);
    unsigned char mah = ((dataItem[0] & mahMask) >> 3);
    unsigned char tcc = ((dataItem[0] & tccMask) >> 2);
    unsigned char sth = ((dataItem[0] & sthMask) >> 1);

    switch (cnf)
    {
    case 0:
        this->tsCNF = "Confirmed Track";
        break;
    case 1:
        this->tsCNF = "Track in Initialization Phase";
        break;
    }
    switch (tre)
    {
    case 0:
        this->tsTRE = "Default";
        break;
    case 1:
        this->tsTRE = "Last Report for a Track";
        break;
    }
    switch (cst)
    {
    case 0:
        this->tsCST = "No extrapolation";
        break;
    case 1:
        this->tsCST = "Predictable extrapolation due to sensor refresh period";
        break;
    case 2:
        this->tsCST = "Predictable extrapolation in masked area";
        break;
    case 3:
        this->tsCST = "Extrapolation due to unpredictable absence of detection";
        break;
    }
    switch (mah)
    {
    case 0:
        this->tsMAH = "Default";
        break;
    case 1:
        this->tsMAH = "Horizontal manoeuvre";
        break;
    }
    switch (tcc)
    {
    case 0:
        this->tsTCC = "Tracking performed in 'Sensor Plane'";
        break;
    case 1:
        this->tsTCC = "Slant range correction";
        break;
    }
    switch (sth)
    {
    case 0:
        this->tsSTH = "Measured position";
        break;
    case 1:
        this->tsSTH = "Smoothed position";
        break;
    }
    if (dataItem.length() >= 2) {
        unsigned char tomMask = 0xC0;
        unsigned char douMask = 0x38;
        unsigned char mrsMask = 0x06;
        unsigned char tom = ((dataItem[1] & tomMask) >> 6);
        unsigned char dou = ((dataItem[1] & douMask) >> 3);
        unsigned char mrs = ((dataItem[1] & mrsMask) >> 1);
        switch (tom)
        {
        case 0:
            this->tsTOM = "Unknown type of movement";
            break;
        case 1:
            this->tsTOM = "Taking-off";
            break;
        case 2:
            this->tsTOM = "Landing";
            break;
        case 3:
            this->tsTOM = "Other types of movement";
            break;
        }
        switch (dou)
        {
        case 0:
            this->tsDOU = "No doubt";
            break;
        case 1:
            this->tsDOU = "Doubtful correlation (undetermined reason)";
            break;
        case 2:
            this->tsDOU = "Doubtful correlation in clutter";
            break;
        case 3:
            this->tsDOU = "Loss of accuracy";
            break;
        case 4:
            this->tsDOU = "Loss of accuracy in clutter";
            break;
        case 5:
            this->tsDOU = "Unstable track";
            break;
        case 6:
            this->tsDOU = "Previously coasted";
            break;
        }
        switch (mrs)
        {
        case 0:
            this->tsMRS = "Merge or split indication undetermined";
            break;
        case 1:
            this->tsMRS = "Track merged by association to plot";
            break;
        case 2:
            this->tsMRS = "Track merged by non-association to plot";
            break;
        case 3:
            this->tsMRS = "Splittrack";
            break;
        }
        if (dataItem.length() >= 3)
        {
            if (dataItem.at(2) == 0)
                this->tsGHO = "Default";
            else if (dataItem.at(2) > 0)
                this->tsGHO = "Ghost track";
        }
    }
}

void Cat10::DecodeMode3ACodeInOctalRepresentation(QVector<unsigned char> &dataItem) {
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

void Cat10::DecodeTargetAddress(QVector<unsigned char> &dataItem) {

    QString buildAddress = "0x";

    for (unsigned char byte : dataItem) {
        short a = (short) byte;
        QString str = QString("%1").arg(a,0,16);
        buildAddress.append(str);
    }
    this->targetAddress = buildAddress;
}

void Cat10::DecodeTargetIdentification(QVector<unsigned char> &dataItem) {



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

void Cat10::DecodeModeSMBData(QVector<unsigned char> &dataItem) {



}

void Cat10::DecodeVehicleFleetIdentification(QVector<unsigned char> &dataItem) {

    switch (dataItem.at(0)) {
    case 0:
        this->vehicleFleetId= "Unknown";
        break;
    case 1:
        this->vehicleFleetId = "ATC equipment maintenance";
        break;
    case 2:
        this->vehicleFleetId = "Airport maintenance";
        break;
    case 3:
        this->vehicleFleetId = "Fire";
        break;
    case 4:
        this->vehicleFleetId = "Bird scarer";
        break;
    case 5:
        this->vehicleFleetId = "Snow plough";
        break;
    case 6:
        this->vehicleFleetId = "Runaway Sweeper";
        break;
    case 7:
        this->vehicleFleetId = "Emergency";
        break;
    case 8:
        this->vehicleFleetId = "Police";
        break;
    case 9:
        this->vehicleFleetId = "Bus";
        break;
    case 10:
        this->vehicleFleetId = "Tug(push/tow)";
        break;
    case 11:
        this->vehicleFleetId = "Grass cutter";
        break;
    case 12:
        this->vehicleFleetId = "Fuel";
        break;
    case 13:
        this->vehicleFleetId = "Baggage";
        break;
    case 14:
        this->vehicleFleetId = "Catering";
        break;
    case 15:
        this->vehicleFleetId = "Aircraft maintenance";
        break;
    case 16:
        this->vehicleFleetId = "Flyco (follow me)";
        break;
    }
}

void Cat10::DecodeFlightLevelInBinaryRepresentation(QVector<unsigned char> &dataItem) {
    unsigned char vMask = 128;
    unsigned char gMask = 64;
    unsigned char flFirstByteMask = 63;



    unsigned char validated = ((dataItem.at(0) & vMask) >> 7);
    unsigned char garbled = ((dataItem.at(0) & gMask) >> 6);
    unsigned char flFirstByte = (dataItem.at(0) & flFirstByteMask);

    QVector<unsigned char> bytes = {flFirstByte, dataItem.at(1)};

    switch (validated)
    {
    case 0:
        this->flValidated = "Code Validated";
        break;
    case 1:
        this->flValidated = "Code not Validated";
        break;
    }
    switch (garbled)
    {
    case 0:
        this->flGarbled = "Default";
        break;
    case 1:
        this->flGarbled = "Garbled Code";
        break;
    }

    double resolution = 0.25;
    this->flFlightLevel = Utilities::DataTools::DecodeTwosComplementToDouble(bytes,resolution);
}

void Cat10::DecodeMeasuredHeight(QVector<unsigned char> &dataItem) {

    double resolution = 6.25;
    this->measuredHeight = Utilities::DataTools::DecodeTwosComplementToDouble(dataItem,resolution);
}

void Cat10::DecodeTargetSizeAndOrientation(QVector<unsigned char> &dataItem) {

    unsigned char mask = 254;
    QVector<unsigned char> length, orientation, width;
    double lengthRes = 1;
    double orRes = 360.0 / 128.0;
    double widthRes = 1;
    length.append((dataItem.at(0) & mask) >> 1);
    this->targetLength = Utilities::DataTools::DecodeUnsignedBytesToDouble(length, lengthRes);

    if (dataItem.length() >= 2) {
        orientation.append((dataItem.at(1) & mask) >> 1);
        this->targetOrientation = Utilities::DataTools::DecodeUnsignedBytesToDouble(orientation, orRes);
    }

    if (dataItem.length() >= 3) {
        width.append((dataItem.at(2) & mask) >> 1);
        this->targetWidth = Utilities::DataTools::DecodeUnsignedBytesToDouble(width, widthRes);
    }
}

void Cat10::DecodeSystemStatus(QVector<unsigned char> &dataItem) {

    unsigned char nogoMask = 192;
    unsigned char ovlMask = 32;
    unsigned char tsvMask = 16;
    unsigned char divMask = 8;
    unsigned char ttfMask = 4;

    unsigned char nogo = ((dataItem[0] & nogoMask) >> 6);
    unsigned char ovl = ((dataItem[0] & ovlMask) >> 5);
    unsigned char tsv = ((dataItem[0] & tsvMask) >> 4);
    unsigned char div = ((dataItem[0] & divMask) >> 3);
    unsigned char ttf = ((dataItem[0] & ttfMask) >> 2);

    switch(nogo)
    {
    case 0:
        this->ssNOGO = "Operational";
        break;
    case 1:
        this->ssNOGO = "Degraded";
        break;

    case 2:
        this->ssNOGO = "NOGO";
        break;
    }
    switch (ovl)
    {
    case 0:
        this->ssOVL = "No overload";
        break;
    case 1:
        this->ssOVL = "Overload";
        break;
    }
    switch (tsv)
    {
    case 0:
        this->ssTSV = "valid";
        break;
    case 1:
        this->ssTSV = "invalid";
        break;
    }
    switch (div)
    {
    case 0:
        this->ssDIV = "Normal Operation";
        break;
    case 1:
        this->ssDIV = "Diversity degraded";
        break;
    }
    switch (ttf)
    {
    case 0:
        this->ssTTF = "Test Target Operative";
        break;
    case 1:
        this->ssTTF = "Test Target Failure";
        break;
    }
}

void Cat10::DecodePreProgrammedMessage(QVector<unsigned char> &dataItem) {

    unsigned char trMask = 128;
    unsigned char msgMask = 127;

    unsigned char trouble = (dataItem.at(0) & trMask) >> 7;
    unsigned char msg = (dataItem.at(0) & msgMask);

    switch (trouble) {
    case 0:
        this->ppmTRB = "Default";
        break;
    case 1:
        this->ppmTRB = "In Trouble";
        break;
    }

    switch (msg) {
    case 1:
        this->ppMSG = "Towing Aircraft";
        break;
    case 2:
        this->ppMSG = "'Follow me' operation";
        break;
    case 3:
        this->ppMSG = "Runway check";
        break;
    case 4:
        this->ppMSG = "Emergency operation(fire,medical...)";
        break;
    case 5:
        this->ppMSG = "Work in progress(maintenance,birds scarer,sweepers...)";
        break;
    }
}

void Cat10::DecodeStandardDeviationOfPosition(QVector<unsigned char> &dataItem) {
    QVector<unsigned char> xstandarddeviation = { dataItem.at(0) };
    QVector<unsigned char> ystandarddeviation = { dataItem.at(1) };
    QVector<unsigned char> xystandardeviation = {dataItem.at(2),dataItem.at(3)};

    this->standardDeviationX = Utilities::DataTools::DecodeUnsignedBytesToDouble(xstandarddeviation, 0.25);
    this->standardDeviationY= Utilities::DataTools::DecodeUnsignedBytesToDouble(ystandarddeviation, 0.25);
    this->standardDeviationXY= Utilities::DataTools::DecodeUnsignedBytesToDouble(xystandardeviation, 0.25);
}

void Cat10::DecodePresence(QVector<unsigned char> &dataItem) {

}

void Cat10::DecodeAmplitudeOfPrimaryPlot(QVector<unsigned char> &dataItem) {

    this->amplitudeOfPrimaryPlot = Utilities::DataTools::DecodeUnsignedBytesToDouble(dataItem, 1);
}

void Cat10::DecodeCalculatedAcceleration(QVector<unsigned char> &dataItem) {

    QVector<unsigned char> xBytes = { dataItem.at(0) };
    double xResolution = 0.25;
    this->calcAccelerationX = Utilities::DataTools::DecodeTwosComplementToDouble(xBytes, xResolution);
    QVector<unsigned char> yBytes = { dataItem.at(1) };
    double yResolution = 0.25;
    this->calcAccelerationY = Utilities::DataTools::DecodeTwosComplementToDouble(yBytes, yResolution);
}

void Cat10::DecodeSpecialPurposeField(QVector<unsigned char> &dataItem) {

}


