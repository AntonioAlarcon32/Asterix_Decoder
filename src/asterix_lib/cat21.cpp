#include "hdr/asterix_lib/cat21.h"

Cat21::Cat21()
{
    this->category = 21;
    this->length = 0;

    this->systemAreaCode = 0;
    this->systemIdentificationCode = 0;

    this->trAtp = "N/A";
    this->trArc = "N/A";
    this->trRc = "N/A";
    this->trRab = "N/A";
    this->trDcr = "N/A";
    this->trGbs = "N/A";
    this->trSim = "N/A";
    this->trTst = "N/A";
    this->trSaa = "N/A";
    this->trCl = "N/A";
    this->trIpc = "N/A";
    this->trNogo = "N/A";
    this->trCpr = "N/A";
    this->trLdpj = "N/A";
    this->trRcf = "N/A";

    this->trackNumber = -1;

    this->serviceIdentification = 1;

    this->timeOfApplicabilityForPosition = QTime();

    this->wgs84latitude = nan("");
    this->wgs84longitude = nan("");

    this->wgs84latitudeHighRes = nan("");
    this->wgs84longitudeHighRes = nan("");

    this->timeOfApplicabilityForVelocity = QTime();

    this->airSpeed = nan("");

    this->trueAirSpeed = nan("");

    this->targetAddress = "N/A";

    this->timeOfMessageReceptionOfPosition = QTime();

    this->timeOfMessageReceptionOfPositionHighRes = QTime();

    this->timeOfMessageReceptionOfVelocity = QTime();

    this->timeOfMessageReceptionOfVelocityHighRes = QTime();

    this->geometricHeight = nan("");

    this->qiNucrOrNacv = "N/A";
    this->qiNucpOrNic = "N/A";
    this->qiNicBaro = "N/A";
    this->qiSil = "N/A";
    this->qiNacp = "N/A";
    this->qiSilSupplement = "N/A";
    this->qiSda = "N/A";
    this->qiGva = "N/A";
    this->qiPic = "N/A";

    this->mvVns = "N/A";
    this->mvVn = "N/A";
    this->mvLtt = "N/A";

    this->m3ACode = "N/A";

    this->rollAngle = nan("");

    this->flightLevel = nan("");

    this->magneticHeading = nan("");

    this->tsIcf = "N/A";
    this->tsLnav = "N/A";
    this->tsPs = "N/A";
    this->tsSs = "N/A";

    this->bvrRangeExceeded = 0;
    this->bvrBarometricVerticalRate = nan("");

    this->gvrRangeExceeded = 0;
    this->gvrGeometricVerticalRate = nan("");

    this->agvRangeExceeded = 0;
    this->agvGroundSpeed = nan("");
    this->agvTrackAngle = nan("");

    this->trackAngleRate = nan("");

    this->timeOfReportTransmission = QTime();

    this->targetIdentification = "N/A";

    this->emitterCategory = "N/A";

    this->metInfo = "N/A"; //REVISAR

    this->saSas = "N/A";
    this->saSource = "N/A";
    this->saAltitude = nan("");

    this->fssaMv = "N/A";
    this->fssaAh = "N/A";
    this->fssaAm = "N/A";
    this->fssaAltitude = nan("");

    this->trajectoryIntent = "N/A"; //REVISAR

    this->serviceManagement = nan("");

    this->aosRa = "N/A";
    this->aosTc = "N/A";
    this->aosTs = "N/A";
    this->aosArv = "N/A";
    this->aosCdti = "N/A";
    this->aosNotTcas = "N/A";
    this->aosSa = "N/A";

    this->sccPoa = "N/A";
    this->sccCdti = "N/A";
    this->sccB2Low = "N/A";
    this->sccRas = "N/A";
    this->sccIdent = "N/A";
    this->sccLengthPlusWidth = "N/A";

    this->messageAmplitude = 1;

    this->ararTyp = "N/A";
    this->ararStyp = "N/A";
    this->ararAra = "N/A";
    this->ararRac = "N/A";
    this->ararRat = "N/A";
    this->ararMte = "N/A";
    this->ararTti = "N/A";
    this->ararTid = "N/A";

    this->receiverId = 1;

    this->dataAges = "N/A"; //REVISAR
}

void Cat21::FullDecode() {

    if (this->fspec.length() > 0) {

        if ((this->fspec.at(0) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeDataSourceIdentification(dataItem);
        }
        if ((this->fspec.at(0) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetVariableLengthDataItem(this->data);
            this->DecodeTargetReportDescriptor(dataItem);
        }
        if ((this->fspec.at(0) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeTrackNumber(dataItem);
        }
        if ((this->fspec.at(0) & 0x10) == 0x10) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
            this->DecodeServiceIdentification(dataItem);
        }
        if ((this->fspec.at(0) & 0x08) == 0x08) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,3);
            this->DecodeTimeOfApplicabilityForPosition(dataItem);
        }
        if ((this->fspec.at(0) & 0x04) == 0x04) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,6);
            this->DecodePositionInWGS84Coordinates(dataItem);
        }
        if ((this->fspec.at(0) & 0x02) == 0x02) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,8);
            this->DecodePositionInWGS84CoordinatesHighRes(dataItem);
        }
    }

    if (this->fspec.length() > 1) {

        if ((this->fspec.at(1) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,3);
            this->DecodeTimeOfApplicabilityForVelocity(dataItem);
        }
        if ((this->fspec.at(1) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeAirSpeed(dataItem);
        }
        if ((this->fspec.at(1) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeTrueAirSpeed(dataItem);
        }
        if ((this->fspec.at(1) & 0x10) == 0x10) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,3);
            this->DecodeTargetAddress(dataItem);
        }
        if ((this->fspec.at(1) & 0x08) == 0x08) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,3);
            this->DecodeTimeOfMessageReceptionOfPosition(dataItem);
        }
        if ((this->fspec.at(1) & 0x04) == 0x04) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,4);
            this->DecodeTimeOfMessageReceptionOfPositionHighPrecision(dataItem);
        }
        if ((this->fspec.at(1) & 0x02) == 0x02) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,3);
            this->DecodeTimeOfMessageReceptionOfVelocity(dataItem);
        }
    }
    if (this->fspec.length() > 2) {

        if ((this->fspec.at(2) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,4);
            this->DecodeTimeOfMessageReceptionOfVelocityHighPrecision(dataItem);
        }
        if ((this->fspec.at(2) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeGeometricHeight(dataItem);
        }
        if ((this->fspec.at(2) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetVariableLengthDataItem(this->data);
            this->DecodeQualityIndicators(dataItem);
        }
        if ((this->fspec.at(2) & 0x10) == 0x10) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
            this->DecodeMOPSVersion(dataItem);
        }
        if ((this->fspec.at(2) & 0x08) == 0x08) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeMode3ACode(dataItem);
        }
        if ((this->fspec.at(2) & 0x04) == 0x04) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeRollAngle(dataItem);
        }
        if ((this->fspec.at(2) & 0x02) == 0x02) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeFlightLevel(dataItem);
        }
    }
    if (this->fspec.length() > 3) {

        if ((this->fspec.at(3) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeMagneticHeading(dataItem);
        }
        if ((this->fspec.at(3) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
            this->DecodeTargetStatus(dataItem);
        }
        if ((this->fspec.at(3) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeBarometricVerticalRate(dataItem);
        }
        if ((this->fspec.at(3) & 0x10) == 0x10) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeGeometricVerticalRate(dataItem);
        }
        if ((this->fspec.at(3) & 0x08) == 0x08) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,4);
            this->DecodeAirborneGroundVector(dataItem);
        }
        if ((this->fspec.at(3) & 0x04) == 0x04) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeTrackAngleRate(dataItem);
        }
        if ((this->fspec.at(3) & 0x02) == 0x02) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,3);
            this->DecodeTimeOfReportTransmission(dataItem);
        }
    }

    if (this->fspec.length() > 4) {

        if ((this->fspec.at(4) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,6);
            this->DecodeTargetIdentification(dataItem);
        }
        if ((this->fspec.at(4) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
            this->DecodeEmitterCategory(dataItem);
        }
        if ((this->fspec.at(4) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetVariableLengthDataItem(this->data);
            this->DecodeMetInformation(dataItem);
        }
        if ((this->fspec.at(4) & 0x10) == 0x10) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeSelectedAltitude(dataItem);
        }
        if ((this->fspec.at(4) & 0x08) == 0x08) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2);
            this->DecodeFinalStateSelectedAltitude(dataItem);
        }
        if ((this->fspec.at(4) & 0x04) == 0x04) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetVariableLengthDataItem(this->data);
            this->DecodeTrajectoryIntent(dataItem);
        }
        if ((this->fspec.at(4) & 0x02) == 0x02) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
            this->DecodeServiceManagement(dataItem);
        }
    }

    if (this->fspec.length() > 5) {

        if ((this->fspec.at(5) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
            this->DecodeAircraftOperationalStatus(dataItem);
        }
        if ((this->fspec.at(5) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetVariableLengthDataItem(this->data);
            this->DecodeSurfaceCapabilitiesAndCharacteristics(dataItem);
        }
        if ((this->fspec.at(5) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
            this->DecodeMessageAmplitude(dataItem);
        }
        if ((this->fspec.at(5) & 0x10) == 0x10) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetRepetitiveDataItem(this->data,8);
            this->DecodeModeSMBData(dataItem);
        }
        if ((this->fspec.at(5) & 0x08) == 0x08) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,7);
            this->DecodeACASResolutionAdvisoryReport(dataItem);
        }
        if ((this->fspec.at(5) & 0x04) == 0x04) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
            this->DecodeReceiverID(dataItem);
        }
        if ((this->fspec.at(5) & 0x02) == 0x02) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetVariableLengthDataItem(this->data);
            this->DecodeDataAges(dataItem);
        }
    }
}

void Cat21::DecodeDataSourceIdentification(QVector<unsigned char> &dataItem) {
    this->systemAreaCode = (short)dataItem.at(0);
    this->systemIdentificationCode = (short)dataItem.at(1);
}

void Cat21::DecodeTargetReportDescriptor(QVector<unsigned char> &dataItem){
    unsigned char atpMask = 224;

                unsigned char arcMask = 24;
                unsigned char rcMask = 4;
                unsigned char rabMask = 2;

                int atp = ((dataItem.at(0) & atpMask) >> 5);

                int arc = ((dataItem.at(0) & arcMask) >> 3);
                int rc = ((dataItem.at(0) & rcMask) >> 2);
                int rab = ((dataItem.at(0) & rabMask) >> 1);
                switch (atp)
                {
                    case 0:
                        this->trAtp = "24-BIT ICAO address";
                        break;
                    case 1:
                        this->trAtp = "Duplicate address";
                        break;
                    case 2:
                        this->trAtp = "Surface vehicle address";
                        break;
                    case 3:
                        this->trAtp = "Anonmous address";
                        break;
                    case 4:
                        this->trAtp = "Reserved for future use";
                        break;
                    case 5:
                        this->trAtp = "Reserved for future use";
                        break;
                    case 6:
                        this->trAtp = "Reserved for future use";
                        break;
                    case 7:
                        this->trAtp = "Reserved for future use";
                        break;
                }
                switch (arc)
                {
                    case 0:
                        this->trArc = "25 ft";
                        break;
                    case 1:
                        this->trArc = "100 ft";
                        break;
                    case 2:
                        this->trArc = "Uknown";
                        break;
                    case 3:
                        this->trArc = "Invalid";
                        break;
                }
                switch (rc)
                {
                    case 0:
                        this->trRc = "Default";
                        break;
                    case 1:
                        this->trRc = "Range Check passed, CPR Validation pending";
                        break;
                }
                switch (rab)
                {
                    case 0:
                        this->trRab = "Report from taget transponder";
                        break;
                    case 1:
                        this->trRab = "Report from field monitor(fixed transponder)";
                        break;
                }

                if (dataItem.length() >= 2)
                {
                    unsigned char dcrMask = 128;
                    unsigned char gbsMask = 64;
                    unsigned char simMask = 32;
                    unsigned char tstMask = 16;
                    unsigned char saaMask = 8;
                    unsigned char clMask = 6;

                    int dcr = ((dataItem.at(1) & dcrMask) >> 7);
                    int gbs = ((dataItem.at(1) & gbsMask) >> 6);
                    int sim = ((dataItem.at(1) & simMask) >> 5);
                    int tst = ((dataItem.at(1) & tstMask) >> 4);
                    int saa = ((dataItem.at(1) & saaMask) >> 3);
                    int cl = ((dataItem.at(1) & clMask) >> 1);
                    switch (dcr)
                    {
                        case 0:
                            this->trDcr = "No differential correction(ADS-B)";
                            break;
                        case 1:
                            this->trDcr = "Differential correction(ADS-B)";
                            break;
                    }
                    switch (gbs)
                    {
                        case 0:
                            this->trGbs = "Ground Bit no set";
                            break;
                        case 1:
                            this->trGbs = "Ground bit set";
                            break;
                    }
                    switch (sim)
                    {
                        case 0:
                            this->trSim = "Actual target report";
                            break;
                        case 1:
                            this->trSim = "Simulated target report";
                            break;
                    }
                    switch (tst)
                    {
                        case 0:
                            this->trTst = "Default";
                            break;
                        case 1:
                            this->trTst = "Test target";
                            break;
                    }
                    switch (saa)
                    {
                        case 0:
                            this->trSaa = "equipment capable to provide selected altitude";
                            break;
                        case 1:
                            this->trSaa = "Equipment not capable to provide selected altitude";
                            break;
                    }
                    switch (dcr)
                    {
                        case 0:
                            this->trDcr = "No differential correction(ADS-B)";
                            break;
                        case 1:
                            this->trDcr = "Differential correction(ADS-B)";
                            break;
                    }

                    switch (cl)
                    {
                        case 0:
                            this->trCl = "Report Valid";
                            break;
                        case 1:
                            this->trCl = "Report suspect";
                            break;
                        case 2:
                            this->trCl = "No information";
                            break;
                        case 3:
                            this->trCl = "Reserved future use";
                            break;
                    }
                }
                if (dataItem.length() >= 3)
                {
                    unsigned char ipcMask = 32;
                    unsigned char nogoMask = 16;
                    unsigned char cprMask = 8;
                    unsigned char ldpjMask = 4;
                    unsigned char rcfMask = 2;
                    int ipc = ((dataItem.at(2) & ipcMask) >> 5);
                    int nogo = ((dataItem.at(2) & nogoMask) >> 4);
                    int cpr = ((dataItem.at(2) & cprMask) >> 3);
                    int ldpj = ((dataItem.at(2) & ldpjMask) >> 2);
                    int rcf = ((dataItem.at(2) & rcfMask) >> 1);

                    switch (ipc)
                    {
                        case 0:
                            this->trIpc = "default(see note)";
                            break;
                        case 1:
                            this->trIpc = "independent Position Check failed";
                            break;
                    }
                    switch (nogo)
                    {
                        case 0:
                            this->trNogo = "NOGO-bit not set";
                            break;
                        case 1:
                            this->trNogo = "NOGO-bit set";
                            break;
                    }
                    switch (cpr)
                    {
                        case 0:
                            this->trCpr = "CPR Validation correct";
                            break;
                        case 1:
                            this->trCpr = "CPR Validation failed";
                            break;
                    }
                    switch (ldpj)
                    {
                        case 0:
                            this->trLdpj = "LDPJ not detected";
                            break;
                        case 1:
                            this->trLdpj = "LDPJ detected";
                            break;
                    }
                    switch (rcf)
                    {
                        case 0:
                            this->trRcf = "default";
                            break;
                        case 1:
                            this->trRcf = "Range Check failed";
                            break;
                    }
                }

}

void Cat21::DecodeTrackNumber(QVector<unsigned char> &dataItem){
    QVector<unsigned char> trackBytes = { dataItem.at(0), dataItem.at(1) };
    double resolution = 1;
    double number = Utilities::DataTools::DecodeUnsignedBytesToDouble(trackBytes, resolution);
    this->trackNumber = (int)number;
}

void Cat21::DecodeServiceIdentification(QVector<unsigned char> &dataItem){
    double resolution = 1;
    double number = Utilities::DataTools::DecodeUnsignedBytesToDouble(dataItem, resolution);
    this->serviceIdentification = (char)number;
}
void Cat21::DecodeTimeOfApplicabilityForPosition(QVector<unsigned char> &dataItem){}
void Cat21::DecodePositionInWGS84Coordinates(QVector<unsigned char> &dataItem){
}

void Cat21::DecodePositionInWGS84CoordinatesHighRes(QVector<unsigned char> &dataItem){
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
    double resolution = 180 / pow(2,30);
    this->wgs84latitude = Utilities::DataTools::DecodeTwosComplementToDouble(latitudeBytes, resolution);
    this->wgs84longitude = Utilities::DataTools::DecodeTwosComplementToDouble(longitudeBytes, resolution);
}

void Cat21::DecodeTimeOfApplicabilityForVelocity(QVector<unsigned char> &dataItem){}
void Cat21::DecodeAirSpeed(QVector<unsigned char> &dataItem){}
void Cat21::DecodeTrueAirSpeed(QVector<unsigned char> &dataItem){}
void Cat21::DecodeTargetAddress(QVector<unsigned char> &dataItem){}
void Cat21::DecodeTimeOfMessageReceptionOfPosition(QVector<unsigned char> &dataItem){}
void Cat21::DecodeTimeOfMessageReceptionOfPositionHighPrecision(QVector<unsigned char> &dataItem){}
void Cat21::DecodeTimeOfMessageReceptionOfVelocity(QVector<unsigned char> &dataItem){}
void Cat21::DecodeTimeOfMessageReceptionOfVelocityHighPrecision(QVector<unsigned char> &dataItem){}
void Cat21::DecodeGeometricHeight(QVector<unsigned char> &dataItem){}
void Cat21::DecodeQualityIndicators(QVector<unsigned char> &dataItem){}
void Cat21::DecodeMOPSVersion(QVector<unsigned char> &dataItem){}
void Cat21::DecodeMode3ACode(QVector<unsigned char> &dataItem){}
void Cat21::DecodeRollAngle(QVector<unsigned char> &dataItem){}
void Cat21::DecodeFlightLevel(QVector<unsigned char> &dataItem){}
void Cat21::DecodeMagneticHeading(QVector<unsigned char> &dataItem){}
void Cat21::DecodeTargetStatus(QVector<unsigned char> &dataItem){}
void Cat21::DecodeBarometricVerticalRate(QVector<unsigned char> &dataItem){}
void Cat21::DecodeGeometricVerticalRate(QVector<unsigned char> &dataItem){}
void Cat21::DecodeAirborneGroundVector(QVector<unsigned char> &dataItem){}
void Cat21::DecodeTrackAngleRate(QVector<unsigned char> &dataItem){}
void Cat21::DecodeTimeOfReportTransmission(QVector<unsigned char> &dataItem){}
void Cat21::DecodeTargetIdentification(QVector<unsigned char> &dataItem){}
void Cat21::DecodeEmitterCategory(QVector<unsigned char> &dataItem){}
void Cat21::DecodeMetInformation(QVector<unsigned char> &dataItem){}
void Cat21::DecodeSelectedAltitude(QVector<unsigned char> &dataItem){}
void Cat21::DecodeFinalStateSelectedAltitude(QVector<unsigned char> &dataItem){}
void Cat21::DecodeTrajectoryIntent(QVector<unsigned char> &dataItem){}
void Cat21::DecodeServiceManagement(QVector<unsigned char> &dataItem){}
void Cat21::DecodeAircraftOperationalStatus(QVector<unsigned char> &dataItem){}
void Cat21::DecodeSurfaceCapabilitiesAndCharacteristics(QVector<unsigned char> &dataItem){}
void Cat21::DecodeMessageAmplitude(QVector<unsigned char> &dataItem){}
void Cat21::DecodeModeSMBData(QVector<unsigned char> &dataItem){}
void Cat21::DecodeACASResolutionAdvisoryReport(QVector<unsigned char> &dataItem){}
void Cat21::DecodeReceiverID(QVector<unsigned char> &dataItem){}
void Cat21::DecodeDataAges(QVector<unsigned char> &dataItem){}
