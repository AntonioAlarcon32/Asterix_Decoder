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


    this->asUnits = "N/A";
    this->asAirSpeed = nan("");


    this->tasRangeExceeded = false;
    this->tasTrueAirSpeed = nan("");

    this->targetAddress = "N/A";

    this->timeOfMessageReceptionOfPosition = QTime();

    this->timeOfMessageReceptionOfPositionHighRes = nan("");

    this->timeOfMessageReceptionOfVelocity = QTime();

    this->timeOfMessageReceptionOfVelocityHighRes = nan("");

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

    this->miWindSpeed = -32768;
    this->miWindDirection = -32768;
    this->miTemperature = -32768;
    this->miTurbulence = -32768;

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

    this->modeSMBData = QVector<QByteArray>();
    this->modeSStoreAddress = QVector<unsigned char>();

    this->ararTyp = "N/A";
    this->ararStyp = "N/A";
    this->ararAra = "N/A";
    this->ararRac = "N/A";
    this->ararRat = "N/A";
    this->ararMte = "N/A";
    this->ararTti = "N/A";
    this->ararTid = "N/A";

    this->receiverId = 1;

    this->daAOS = nanf("");
    this->daTRD = nanf("");
    this->daM3A = nanf("");
    this->daQI = nanf("");
    this->daTrI = nanf("");
    this->daMA = nanf("");
    this->daGH = nanf("");
    this->daFL = nanf("");
    this->daISSA = nanf("");
    this->daFSSA = nanf("");
    this->daAS = nanf("");
    this->daTAS = nanf("");
    this->daMH = nanf("");
    this->daBVR = nanf("");
    this->daGVR = nanf("");
    this->daGV = nanf("");
    this->daTAR = nanf("");
    this->daTaI = nanf("");
    this->daTS = nanf("");
    this->daMET = nanf("");
    this->daROA = nanf("");
    this->daARA = nanf("");
    this->daSCC = nanf("");
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
            QVector<unsigned char> dataItem = this->GetTrajectoryIntentDataItem();
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
            QVector<unsigned char> dataItem = GetDataAgesDataItem();
            this->DecodeDataAges(dataItem);
        }
    }
}

void Cat21::DecodeDataSourceIdentification(QVector<unsigned char> &dataItem) {
    this->systemAreaCode = (short)dataItem.at(0);
    this->systemIdentificationCode = (short)dataItem.at(1);
}

void Cat21::DecodeTargetReportDescriptor(QVector<unsigned char> &dataItem) {
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
                        this->trAtp = "Anonymous address";
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
                        this->trArc = "Unknown";
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
                        this->trRab = "Report from target transponder";
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

void Cat21::DecodeServiceIdentification(QVector<unsigned char> &dataItem) {
    double resolution = 1;
    double number = Utilities::DataTools::DecodeUnsignedBytesToDouble(dataItem, resolution);
    this->serviceIdentification = (char)number;
}
void Cat21::DecodeTimeOfApplicabilityForPosition(QVector<unsigned char> &dataItem) {
    double timeResolution = pow(2,-7);
    double seconds = Utilities::DataTools::DecodeUnsignedBytesToDouble(dataItem,timeResolution);
    int mseconds = (int) seconds * 1000;
    this->timeOfApplicabilityForPosition = QTime::fromMSecsSinceStartOfDay(mseconds);
}
void Cat21::DecodePositionInWGS84Coordinates(QVector<unsigned char> &dataItem) {

    QVector<unsigned char> latitudeBytes = {dataItem.at(0), dataItem.at(1), dataItem.at(2)};
    QVector<unsigned char> longitudeBytes = {dataItem.at(3), dataItem.at(4), dataItem.at(5)};

    double resolution = 180.0 / pow(2,23);
    this->wgs84latitude = Utilities::DataTools::DecodeTwosComplementToDouble(latitudeBytes, resolution);
    this->wgs84longitude = Utilities::DataTools::DecodeTwosComplementToDouble(longitudeBytes, resolution);
}

void Cat21::DecodePositionInWGS84CoordinatesHighRes(QVector<unsigned char> &dataItem) {

    QVector<unsigned char> latitudeBytes = {dataItem.at(0), dataItem.at(1), dataItem.at(2),dataItem.at(3)};
    QVector<unsigned char> longitudeBytes = {dataItem.at(4), dataItem.at(5), dataItem.at(6),dataItem.at(7)};
    double resolution = 180 / pow(2,30);
    this->wgs84latitudeHighRes = Utilities::DataTools::DecodeTwosComplementToDouble(latitudeBytes, resolution);
    this->wgs84longitudeHighRes = Utilities::DataTools::DecodeTwosComplementToDouble(longitudeBytes, resolution);
}

void Cat21::DecodeTimeOfApplicabilityForVelocity(QVector<unsigned char> &dataItem) {
    double timeResolution = pow(2,-7);
    double seconds = Utilities::DataTools::DecodeUnsignedBytesToDouble(dataItem,timeResolution);
    int mseconds = (int) seconds * 1000;
    this->timeOfApplicabilityForVelocity = QTime::fromMSecsSinceStartOfDay(mseconds);
}

void Cat21::DecodeAirSpeed(QVector<unsigned char> &dataItem) {

    unsigned char unitMask = 128;
    unsigned char valueMask = 127;

    unsigned char units = (dataItem.at(0) & unitMask) >> 7;
    unsigned char firstByte = (dataItem.at(0) & valueMask);
    QVector<unsigned char> bytes = {firstByte, dataItem.at(1)};
    double speed = Utilities::DataTools::DecodeUnsignedBytesToDouble(bytes,1);

    switch (units) {
    case 0:
        this->asUnits = "IAS";
        this->asAirSpeed = speed * pow(2,-14);
        break;
    case 1:
        this->asUnits = "Mach";
        this->asAirSpeed = speed * 0.001;
        break;
    }
}
void Cat21::DecodeTrueAirSpeed(QVector<unsigned char> &dataItem) {

    unsigned char rangeMask = 128;
    unsigned char valueMask = 127;

    unsigned char units = (dataItem.at(0) & rangeMask) >> 7;
    unsigned char firstByte = (dataItem.at(0) & valueMask);
    QVector<unsigned char> bytes = {firstByte, dataItem.at(1)};
    this->tasTrueAirSpeed = Utilities::DataTools::DecodeUnsignedBytesToDouble(bytes,1);

    switch (units) {
    case 0:
        this->tasRangeExceeded = false;
        break;
    case 1:
        this->tasRangeExceeded = true;
        break;
    }
}

void Cat21::DecodeTargetAddress(QVector<unsigned char> &dataItem){
    QString buildAddress = "0x";

    for (unsigned char byte : dataItem) {
        short a = (short) byte;
        QString str = QString("%1").arg(a,0,16);
        buildAddress.append(str);
    }
    this->targetAddress = buildAddress;
}

void Cat21::DecodeTimeOfMessageReceptionOfPosition(QVector<unsigned char> &dataItem) {
    double timeResolution = pow(2,-7);
    double seconds = Utilities::DataTools::DecodeUnsignedBytesToDouble(dataItem,timeResolution);
    int mseconds = (int) seconds * 1000;
    this->timeOfMessageReceptionOfPosition = QTime::fromMSecsSinceStartOfDay(mseconds);
}
void Cat21::DecodeTimeOfMessageReceptionOfPositionHighPrecision(QVector<unsigned char> &dataItem){

    unsigned char firstByte = (dataItem.at(0) & 0b00111111);
    QVector<unsigned char> bytes = {firstByte, dataItem.at(1), dataItem.at(2), dataItem.at(3)};
    double timeResolution = pow(2,-30);
    this->timeOfMessageReceptionOfPositionHighRes = Utilities::DataTools::DecodeUnsignedBytesToDouble(bytes,timeResolution);

}

void Cat21::DecodeTimeOfMessageReceptionOfVelocity(QVector<unsigned char> &dataItem){
    double timeResolution = pow(2,-7);
    double seconds = Utilities::DataTools::DecodeUnsignedBytesToDouble(dataItem,timeResolution);
    int mseconds = (int) seconds * 1000;
    this->timeOfMessageReceptionOfVelocity = QTime::fromMSecsSinceStartOfDay(mseconds);
}
void Cat21::DecodeTimeOfMessageReceptionOfVelocityHighPrecision(QVector<unsigned char> &dataItem){

    unsigned char firstByte = (dataItem.at(0) & 0b00111111);
    QVector<unsigned char> bytes = {firstByte, dataItem.at(1), dataItem.at(2), dataItem.at(3)};
    double timeResolution = pow(2,-30);
    this->timeOfMessageReceptionOfVelocityHighRes = Utilities::DataTools::DecodeUnsignedBytesToDouble(bytes,timeResolution);
}

void Cat21::DecodeGeometricHeight(QVector<unsigned char> &dataItem) {
    double resolution = 6.25;
    this->geometricHeight = Utilities::DataTools::DecodeTwosComplementToDouble(dataItem, resolution);
}
void Cat21::DecodeQualityIndicators(QVector<unsigned char> &dataItem){}

void Cat21::DecodeMOPSVersion(QVector<unsigned char> &dataItem){

    char vnsMask = 0b01000000;
    char vnMask = 0b00111000;
    char lttMask = 0b00000111;

    unsigned char vns = (vnsMask & dataItem.at(0)) >> 6;
    unsigned char vn = (vnMask & dataItem.at(0)) >> 3;
    unsigned char ltt = (lttMask & dataItem.at(0));

    switch (vn)
    {
    case 0:
        this->mvVn = "ED102/DO-260[Ref.8]";
        break;
    case 1:
        this->mvVn = "DO-260A[Ref.9]";
        break;
    case 2:
        this->mvVn = "ED102A/DO-260B[Ref.11]";
        break;
    }

    switch (vns)
    {
    case 0:
        this->mvVns = "The MOPS Version is supported by the GS";
        break;
    case 1:
        this->mvVns = "The MOPS Version is not supported by the GS";
        break;
    }

    switch (ltt)
    {
    case 0:
        this->mvLtt = "Other";
        break;
    case 1:
        this->mvLtt = "UAT";
        break;
    case 2:
        this->mvLtt = "1090 ES";
        break;
    case 3:
        this->mvLtt = "VDL 4";
        break;
    case 4:
        this->mvLtt = "Not assigned";
        break;
    case 5:
        this->mvLtt = "Not assigned";
        break;
    case 6:
        this->mvLtt = "Not assigned";
        break;
    case 7:
        this->mvLtt = "Not assigned";
        break;
    }
}

void Cat21::DecodeMode3ACode(QVector<unsigned char> &dataItem){
    unsigned char aMask = 0x0E;

    unsigned char A = (dataItem.at(0) & aMask) >> 1;
    unsigned char B4 = (dataItem.at(0) & 0x01) << 2;
    unsigned char B21 = (dataItem.at(1) & 0xC0) >> 6;

    unsigned char B = B4 | B21;

    unsigned char C = (dataItem.at(1) & 0x38) >> 3;
    unsigned char D = (dataItem.at(1) & 0x07);
    int code = A * 1000 + B * 100 + C * 10 + D;
    this->m3ACode = QString::number(code);
}

void Cat21::DecodeRollAngle(QVector<unsigned char> &dataItem){
    double resolution = 0.01;
    this->rollAngle = Utilities::DataTools::DecodeTwosComplementToDouble(dataItem, resolution);
}

void Cat21::DecodeFlightLevel(QVector<unsigned char> &dataItem) {
    double resolution = 0.25;
    this->flightLevel = Utilities::DataTools::DecodeTwosComplementToDouble(dataItem, resolution);
}
void Cat21::DecodeMagneticHeading(QVector<unsigned char> &dataItem) {
    double resolution = 360.0 / pow(2,16);
    this->magneticHeading = Utilities::DataTools::DecodeUnsignedBytesToDouble(dataItem, resolution);
}
void Cat21::DecodeTargetStatus(QVector<unsigned char> &dataItem) {

    char icfMask = 0b10000000;
    char lnavMask = 0b01000000;
    char psMask = 0b00011100;
    char ssMask = 0b00000011;

    unsigned char icf = (icfMask & dataItem.at(0)) >> 7;
    unsigned char lnav = (lnavMask & dataItem.at(0)) >> 6;
    unsigned char ps = (psMask & dataItem.at(0)) >> 2;
    unsigned char ss = (ssMask & dataItem.at(0));

    switch (icf)
    {
    case 0:
        this->tsIcf = "No intent change active";
        break;
    case 1:
        this->tsIcf = "Intent change flag raised";
        break;
    }

    switch (lnav)
    {
    case 0:
        this->tsLnav = "LNAV Mode engaged";
        break;
    case 1:
        this->tsLnav = "LNAV Mode not engaged";
        break;
    }
    switch (ps)
    {
    case 0:
        this->tsPs = "No emergency/not reported";
        break;
    case 1:
        this->tsPs = "General Emergency";
        break;
    case 2:
        this->tsPs = "Lifeguard/medical emergency";
        break;
    case 3:
        this->tsPs = "Minimum fuel";
        break;
    case 4:
        this->tsPs = "No communications";
        break;
    case 5:
        this->tsPs = "Unlawful interference";
        break;
    case 6:
        this->tsPs = "'Downed' Aircraft";
        break;
    }
    switch (ss)
    {
    case 0:
        this->tsSs = "No condition reported";
        break;
    case 1:
        this->tsSs = "Permanent Alert (Emergency condition)";
        break;
    case 2:
        this->tsSs = "Temporary Alert (change in Mode 3/A Code other than emergency)";
        break;
    case 3:
        this->tsSs = "SPI set";
        break;

    }
}

void Cat21::DecodeBarometricVerticalRate(QVector<unsigned char> &dataItem) {
    unsigned char rangeMask = 128;
    unsigned char valueMask = 127;

    unsigned char maskForFunction = 0b00111111;
    int valueForLimit = 64;

    unsigned char units = (dataItem.at(0) & rangeMask) >> 7;
    unsigned char firstByte = (dataItem.at(0) & valueMask);
    QVector<unsigned char> bytes = {firstByte, dataItem.at(1)};
    double resolution = 6.25;
    this->bvrBarometricVerticalRate = Utilities::DataTools::DecodeSpecialTwosComplement(bytes,resolution,maskForFunction, valueForLimit);

    switch (units) {
    case 0:
        this->bvrRangeExceeded = false;
        break;
    case 1:
        this->bvrRangeExceeded = true;
        break;
    }
}
void Cat21::DecodeGeometricVerticalRate(QVector<unsigned char> &dataItem){
    unsigned char rangeMask = 128;
    unsigned char valueMask = 127;

    unsigned char maskForFunction = 0b00111111;
    int valueForLimit = 64;

    unsigned char units = (dataItem.at(0) & rangeMask) >> 7;
    unsigned char firstByte = (dataItem.at(0) & valueMask);
    QVector<unsigned char> bytes = {firstByte, dataItem.at(1)};
    double resolution = 6.25;
    this->gvrGeometricVerticalRate = Utilities::DataTools::DecodeSpecialTwosComplement(bytes,resolution,maskForFunction, valueForLimit);

    switch (units) {
    case 0:
        this->gvrRangeExceeded = false;
        break;
    case 1:
        this->gvrRangeExceeded = true;
        break;
    }
}
void Cat21::DecodeAirborneGroundVector(QVector<unsigned char> &dataItem){

    unsigned char rangeMask = 128;
    unsigned char valueMask = 127;

    unsigned char units = (dataItem.at(0) & rangeMask) >> 7;
    unsigned char firstByte = (dataItem.at(0) & valueMask);
    QVector<unsigned char> bytes = {firstByte, dataItem.at(1)};
    double resolution = pow(2,-14);
    this->agvGroundSpeed = Utilities::DataTools::DecodeUnsignedBytesToDouble(bytes,resolution);

    switch (units) {
    case 0:
        this->agvRangeExceeded = false;
        break;
    case 1:
        this->agvRangeExceeded = true;
        break;
    }
    QVector<unsigned char> trackBytes = {dataItem.at(2), dataItem.at(3)};
    double trackResolution = 360.0 / pow(2,16);
    this->agvTrackAngle = Utilities::DataTools::DecodeUnsignedBytesToDouble(trackBytes,trackResolution);

}
void Cat21::DecodeTrackAngleRate(QVector<unsigned char> &dataItem) {
    unsigned char valueMask = 127;

    unsigned char maskForFunction = 0b00000001;
    int valueForLimit = 2;

    unsigned char firstByte = (dataItem.at(0) & valueMask);
    QVector<unsigned char> bytes = {firstByte, dataItem.at(1)};
    double resolution = 1.0/32.0;
    this->trackAngleRate = Utilities::DataTools::DecodeSpecialTwosComplement(bytes,resolution,maskForFunction, valueForLimit);
}

void Cat21::DecodeTimeOfReportTransmission(QVector<unsigned char> &dataItem) {

    double timeResolution = pow(2,-7);
    double seconds = Utilities::DataTools::DecodeUnsignedBytesToDouble(dataItem,timeResolution);
    int mseconds = (int) seconds * 1000;
    this->timeOfReportTransmission = QTime::fromMSecsSinceStartOfDay(mseconds);
}

void Cat21::DecodeTargetIdentification(QVector<unsigned char> &dataItem) {
    unsigned char char8 = (unsigned char)((dataItem.at(5) & 63));
    unsigned char char7 = (unsigned char)(((dataItem.at(5) & 192) >> 6) + ((dataItem.at(4) & 15) << 2));
    unsigned char char6 = (unsigned char)(((dataItem.at(4) & 240) >> 4) + ((dataItem.at(3) & 3) << 4));
    unsigned char char5 = (unsigned char)((dataItem.at(3) & 252) >> 2);
    unsigned char char4 = (unsigned char)((dataItem.at(2) & 63));
    unsigned char char3 = (unsigned char)(((dataItem.at(2) & 192) >> 6) + ((dataItem.at(1) & 15) << 2));
    unsigned char char2 = (unsigned char)(((dataItem.at(1) & 240) >> 4) + ((dataItem.at(0) & 3) << 4));
    unsigned char char1 = (unsigned char)((dataItem.at(0) & 252) >> 2);


    QVector<unsigned char> chars = { char1, char2, char3, char4, char5, char6, char7, char8 };

    this->targetIdentification = Utilities::DataTools::GetAircraftIDFromBytes(chars);
}

void Cat21::DecodeEmitterCategory(QVector<unsigned char> &dataItem) {

    int emitterCategory = (int)dataItem.at(0);
    switch (emitterCategory)
    {
    case 0:
        this->emitterCategory = "No ADS-B Emitter Category Information";
        break;
    case 1:
        this->emitterCategory = "light aircraft<=15500 lbs";
        break;
    case 2:
        this->emitterCategory = "15500 lbs<small aircraft<300000 lbs";
        break;
    case 3:
        this->emitterCategory = "75000 lbs<medium a/c<300000 lbs";
        break;
    case 4:
        this->emitterCategory = "High vortex Large";
        break;
    case 5:
        this->emitterCategory = "300000lbs<=heavy aircraft";
        break;
    case 6:
        this->emitterCategory = "highly manouvrable(5g acceleration capability) and high speed(>400knots cruise)";
        break;
    case 7:
        this->emitterCategory = "reserved";
        break;
    case 8:
        this->emitterCategory = "reserved";
        break;
    case 9:
        this->emitterCategory = "reserved";
        break;
    case 10:
        this->emitterCategory = "rotorcraft";
        break;
    case 11:
        this->emitterCategory = "glider/sailplane";
        break;
    case 12:
        this->emitterCategory = "lighter than air";
        break;
    case 13:
        this->emitterCategory = "unmanned aerial vehicle";
        break;
    case 14:
        this->emitterCategory = "space/transarmospheric vehicle";
        break;
    case 15:
        this->emitterCategory = "ultralight/handglider/paraglider";
        break;
    case 16:
        this->emitterCategory = "parachutist/skydiver";
        break;
    case 17:
        this->emitterCategory = "reserved";
        break;
    case 18:
        this->emitterCategory = "reserved";
        break;
    case 19:
        this->emitterCategory = "reserved";
        break;
    case 20:
        this->emitterCategory = "surface emergency vehicle";
        break;
    case 21:
        this->emitterCategory = "surface service vehicle";
        break;
    case 22:
        this->emitterCategory = "fixed ground or tethered obstruction";
        break;
    case 23:
        this->emitterCategory = "cluster obstacle";
        break;
    case 24:
        this->emitterCategory = "line obstacle";
        break;
    }
}

void Cat21::DecodeMetInformation(QVector<unsigned char> &dataItem) {

    int offset = 1;
    if ((dataItem.at(0) & 128) != 0) {
        QVector<unsigned char> windBytes = {dataItem.at(offset), dataItem.at(offset+1)};
        this->miWindSpeed = Utilities::DataTools::DecodeUnsignedBytesToDouble(windBytes,1);
        offset +=2;
    }
    if ((dataItem.at(0) & 64) != 0) {
        QVector<unsigned char> windBytes = {dataItem.at(offset), dataItem.at(offset+1)};
        this->miWindDirection = Utilities::DataTools::DecodeUnsignedBytesToDouble(windBytes,1);
        offset +=2;
    }
    if ((dataItem.at(0) & 32) != 0) {
        QVector<unsigned char> windBytes = {dataItem.at(offset), dataItem.at(offset+1)};
        this->miTemperature = Utilities::DataTools::DecodeUnsignedBytesToDouble(windBytes,1);
        offset +=2;
    }
    if ((data.at(0) & 16) != 0) {
        this->miTurbulence = dataItem.at(offset);
    }
}

void Cat21::DecodeSelectedAltitude(QVector<unsigned char> &dataItem) {

    unsigned char sasMask = 128;
    unsigned char sourceMask = 96;

    unsigned char sas = (dataItem.at(0) & sasMask) >> 7;
    unsigned char source = (dataItem.at(0) & sourceMask) >> 5;


    unsigned char valueMask = 0b00011111;

    unsigned char maskForFunction = 0b00001111;
    int valueForLimit = 16;

    unsigned char firstByte = (dataItem.at(0) & valueMask);
    QVector<unsigned char> bytes = {firstByte, dataItem.at(1)};
    double resolution = 25;
    this->saAltitude = Utilities::DataTools::DecodeSpecialTwosComplement(bytes,resolution,maskForFunction, valueForLimit);

    switch (sas) {
    case 0:
        this->saSas = "No source information provided";
    case 1:
        this->saSas = "Source information provided";
    break;
    }

    switch (source) {
    case 0:
        this->saSource = "Unknown";
        break;
    case 1:
        this->saSource = "Aircraft Altitude (Holding Altitude)";
        break;
    case 2:
        this->saSource = "MCP/FCU Selected Altitude";
        break;
    case 3:
        this->saSource = "FMS Selected Altitude";
        break;
    }
}

void Cat21::DecodeFinalStateSelectedAltitude(QVector<unsigned char> &dataItem) {

    unsigned char mvMask = 128;
    unsigned char ahMask = 64;
    unsigned char amMask = 32;

    unsigned char mv = (dataItem.at(0) & mvMask) >> 7;
    unsigned char ah = (dataItem.at(0) & ahMask) >> 6;
    unsigned char am = (dataItem.at(0) & amMask) >> 5;

    unsigned char valueMask = 0b00011111;

    unsigned char maskForFunction = 0b00001111;
    int valueForLimit = 16;

    unsigned char firstByte = (dataItem.at(0) & valueMask);
    QVector<unsigned char> bytes = {firstByte, dataItem.at(1)};
    double resolution = 25;
    this->fssaAltitude = Utilities::DataTools::DecodeSpecialTwosComplement(bytes,resolution,maskForFunction, valueForLimit);

    switch (mv) {
    case 0:
        this->fssaMv = "Not active or unknown";
    case 1:
        this->fssaMv = "Active";
    break;
    }
    switch (ah) {
    case 0:
        this->fssaAh = "Not active or unknown";
    case 1:
        this->fssaAh = "Active";
    break;
    }
    switch (am) {
    case 0:
        this->fssaAm = "Not active or unknown";
    case 1:
        this->fssaAm = "Active";
    break;
    }
}

void Cat21::DecodeTrajectoryIntent(QVector<unsigned char> &dataItem) {}

void Cat21::DecodeServiceManagement(QVector<unsigned char> &dataItem) {
    this->serviceManagement = dataItem.at(0) * 0.5;
}

void Cat21::DecodeAircraftOperationalStatus(QVector<unsigned char> &dataItem) {

    unsigned char raMask = 0b10000000;
    unsigned char tcMask = 0b01100000;
    unsigned char tsMask = 0b00010000;
    unsigned char arvMask = 0b00001000;
    unsigned char cdtiMask = 0b0000100;
    unsigned char nTcasMask = 0b00000010;
    unsigned char saMask = 0b00000001;

    unsigned char ra = ((dataItem.at(0) & raMask) >> 7);
    unsigned char tc = ((dataItem.at(0) & tcMask) >> 5);
    unsigned char ts = ((dataItem.at(0) & tsMask) >> 4);
    unsigned char arv = ((dataItem.at(0) & arvMask) >> 3);
    unsigned char cdtia = ((dataItem.at(0) & cdtiMask) >> 2);
    unsigned char notTcas = ((dataItem.at(0) & nTcasMask) >> 1);
    unsigned char sa = (dataItem.at(0) & saMask);

    switch (ra)
    {
    case 0:
        this->aosRa = "TCAS II or ACAS RA not active";
        break;
    case 1:
        this->aosRa = "TCAS RA active";
        break;
    }
    switch (tc)
    {
    case 0:
        this->aosTc = "no capability for Trajectory change report";
        break;
    case 1:
        this->aosTc = "support for TC+0 reports only";
        break;
    case 2:
        this->aosTc = "support for multiple TC reports";
        break;
    case 3:
        this->aosTc = "reserved";
        break;
    }
    switch (ts)
    {
    case 0:
        this->aosTs = "no capability to support Target State Reports";
        break;
    case 1:
        this->aosTs = "capable of supporting target State Reports";
        break;
    }
    switch (arv)
    {
    case 0:
        this->aosArv = "no capability to generate ARV-reports";
        break;
    case 1:
        this->aosArv = "capable of generate ARV-reports";
        break;
    }
    switch (cdtia)
    {
    case 0:
        this->aosCdti = "cdti not operational";
        break;
    case 1:
        this->aosCdti = "cdti operational";
        break;


    }
    switch (notTcas)
    {
    case 0:
        this->aosNotTcas = "TCAS operational";
        break;
    case 1:
        this->aosNotTcas = "TCAS not operational";
        break;
    }
    switch (sa)
    {
    case 0:
        this->aosSa = "Antenna diversity";
        break;
    case 1:
        this->aosSa = "Single Antenna Only";
        break;
    }
}

void Cat21::DecodeSurfaceCapabilitiesAndCharacteristics(QVector<unsigned char> &dataItem) {

    unsigned char poaMask = 32;
    unsigned char cdtiMask = 16;
    unsigned char b2LowMask = 8;
    unsigned char rasMask = 4;
    unsigned char identMask = 2;

    unsigned char poa = (dataItem.at(0) & poaMask) >> 5;
    unsigned char cdti = (dataItem.at(0) & cdtiMask) >> 4;
    unsigned char b2Low = (dataItem.at(0) & b2LowMask) >> 3;
    unsigned char ras = (dataItem.at(0) & rasMask) >> 2;
    unsigned char ident = (dataItem.at(0) & identMask) >> 1;

    switch (poa)
    {
    case 0:
        this->sccPoa = "Postion transmitted is not ADS-B position reference point";
        break;
    case 1:
        this->sccPoa = "Postion transmitted is the ADS-B position reference point";
        break;
    }

    switch (cdti)
    {
    case 0:
        this->sccCdti = "CDTI not operational";
        break;
    case 1:
        this->sccCdti = "CDTI operational";
        break;
    }

    switch (b2Low)
    {
    case 0:
        this->sccB2Low = ">=70 Watts";
        break;
    case 1:
        this->sccB2Low = "<70 Watts";
        break;
    }

    switch (ras)
    {
    case 0:
        this->sccRas = "aircraft not receiving ATC-services";
        break;
    case 1:
        this->sccRas = "aircraft receiving ATC-services";
        break;
    }

    switch (ident)
    {
    case 0:
        this->sccIdent = "IDENT switch not active";
        break;
    case 1:
        this->sccIdent = "IDENT switch active";
        break;
    }

    if (dataItem.length() >= 2) {
        unsigned char lwMask = 15;
        unsigned char lw = (dataItem.at(1) & lwMask);

        switch (lw)
        {
        case 0:
            this->sccLengthPlusWidth = "L<15 & W<11.5";
            break;
        case 1:
            this->sccLengthPlusWidth = "L<15 & W<23";
            break;
        case 2:
            this->sccLengthPlusWidth = "L<25 & W<28.5";
            break;
        case 3:
            this->sccLengthPlusWidth = "L<25 & W<34";
            break;
        case 4:
            this->sccLengthPlusWidth = "L<35 & W<33";
            break;
        case 5:
            this->sccLengthPlusWidth = "L<35 & W<38";
            break;
        case 6:
            this->sccLengthPlusWidth = "L<45 & W<39.5";
            break;
        case 7:
            this->sccLengthPlusWidth = "L<45 & W<45";
            break;
        case 8:
            this->sccLengthPlusWidth = "L<55 & W<45";
            break;
        case 9:
            this->sccLengthPlusWidth = "L<55 & W<52";
            break;
        case 10:
            this->sccLengthPlusWidth = "L<65 & W<59.5";
            break;
        case 11:
            this->sccLengthPlusWidth = "L<65 & W<67";
            break;
        case 12:
            this->sccLengthPlusWidth = "L<75 & W<72.5";
            break;
        case 13:
            this->sccLengthPlusWidth = "L<75 & W<80";
            break;
        case 14:
            this->sccLengthPlusWidth = "L<85 & W<80";
            break;
        case 15:
            this->sccLengthPlusWidth = "L>85 & W>80";
            break;
        }
    }
}

void Cat21::DecodeMessageAmplitude(QVector<unsigned char> &dataItem) {
    this->messageAmplitude = (char) dataItem.at(0);
}
void Cat21::DecodeModeSMBData(QVector<unsigned char> &dataItem) {
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

void Cat21::DecodeACASResolutionAdvisoryReport(QVector<unsigned char> &dataItem) {}
void Cat21::DecodeReceiverID(QVector<unsigned char> &dataItem) {
    this->receiverId = dataItem.at(0);
}
void Cat21::DecodeDataAges(QVector<unsigned char> &dataItem) {

    int dataAgesOffset = 1;
    bool firstPresenceBit = false, secondPresenceBit = false, thirdPresenceBit = false;;
    firstPresenceBit = dataItem.at(0) & 1;
    if (firstPresenceBit) {
        dataAgesOffset++;
        secondPresenceBit = dataItem.at(1) & 1;
        if (secondPresenceBit) {
            dataAgesOffset++;
            thirdPresenceBit = dataItem.at(2) & 1;
            if (thirdPresenceBit) {
                dataAgesOffset++;
            }
        }
    }

    if ((dataItem.at(0) & 128) != 0) {
        this->daAOS = dataItem.at(dataAgesOffset) * 0.1;
        dataAgesOffset++;
    }
    if ((dataItem.at(0) & 64) != 0) {
        this->daTRD = dataItem.at(dataAgesOffset) * 0.1;
        dataAgesOffset++;
    }
    if ((dataItem.at(0) & 32) != 0) {
        this->daM3A = dataItem.at(dataAgesOffset) * 0.1;
        dataAgesOffset++;
    }
    if ((dataItem.at(0) & 16) != 0) {
        this->daQI = dataItem.at(dataAgesOffset) * 0.1;
        dataAgesOffset++;
    }
    if ((dataItem.at(0) & 8) != 0) {
        this->daTrI = dataItem.at(dataAgesOffset) * 0.1;
        dataAgesOffset++;
    }
    if ((dataItem.at(0) & 4) != 0) {
        this->daMA = dataItem.at(dataAgesOffset) * 0.1;
        dataAgesOffset++;
    }
    if ((dataItem.at(0) & 2) != 0) {
        this->daGH = dataItem.at(dataAgesOffset) * 0.1;
        dataAgesOffset++;
    }

    if (firstPresenceBit) {
        if ((dataItem.at(1) & 128) != 0) {
            this->daFL = dataItem.at(dataAgesOffset) * 0.1;
            dataAgesOffset++;
        }
        if ((dataItem.at(1) & 64) != 0) {
            this->daISSA = dataItem.at(dataAgesOffset) * 0.1;
            dataAgesOffset++;
        }
        if ((dataItem.at(1) & 32) != 0) {
            this->daFSSA = dataItem.at(dataAgesOffset) * 0.1;
            dataAgesOffset++;
        }
        if ((dataItem.at(1) & 16) != 0) {
            this->daAS = dataItem.at(dataAgesOffset) * 0.1;
            dataAgesOffset++;
        }
        if ((dataItem.at(1) & 8) != 0) {
            this->daTAS = dataItem.at(dataAgesOffset) * 0.1;
            dataAgesOffset++;
        }
        if ((dataItem.at(1) & 4) != 0) {
            this->daMH = dataItem.at(dataAgesOffset) * 0.1;
            dataAgesOffset++;
        }
        if ((dataItem.at(1) & 2) != 0) {
            this->daBVR = dataItem.at(dataAgesOffset) * 0.1;
            dataAgesOffset++;
        }
    }
    if (secondPresenceBit) {
        if ((dataItem.at(2) & 128) != 0) {
            this->daGVR = dataItem.at(dataAgesOffset) * 0.1;
            dataAgesOffset++;
        }
        if ((dataItem.at(2) & 64) != 0) {
            this->daGV = dataItem.at(dataAgesOffset) * 0.1;
            dataAgesOffset++;
        }
        if ((dataItem.at(2) & 32) != 0) {
            this->daTAR = dataItem.at(dataAgesOffset) * 0.1;
            dataAgesOffset++;
        }
        if ((dataItem.at(2) & 16) != 0) {
            this->daTaI = dataItem.at(dataAgesOffset) * 0.1;
            dataAgesOffset++;
        }
        if ((dataItem.at(2) & 8) != 0) {
            this->daTS = dataItem.at(dataAgesOffset) * 0.1;
            dataAgesOffset++;
        }
        if ((dataItem.at(2) & 4) != 0) {
            this->daMET = dataItem.at(dataAgesOffset) * 0.1;
            dataAgesOffset++;
        }
        if ((dataItem.at(2) & 2) != 0) {
            this->daROA = dataItem.at(dataAgesOffset) * 0.1;
            dataAgesOffset++;
        }
    }
    if (thirdPresenceBit) {
        if ((dataItem.at(3) & 128) != 0) {
            this->daARA = dataItem.at(dataAgesOffset) * 0.1;
            dataAgesOffset++;
        }
        if ((dataItem.at(3) & 64) != 0) {
            this->daSCC = dataItem.at(dataAgesOffset) * 0.1;
            dataAgesOffset++;
        }
    }
}

QVector<unsigned char> Cat21::GetDataAgesDataItem() {
    QVector<unsigned char> dataItemStatus = Utilities::DataTools::GetVariableLengthDataItem(this->data);
    int count = 0;
    for (unsigned char byte : dataItemStatus) {
        while (byte != 0) {
            if (byte & 0x1 == 1) count++;
            byte = byte / 2;
        }
    }
    count = count - (dataItemStatus.length() - 1);
    QVector<unsigned char> subDataItems = Utilities::DataTools::GetFixedLengthDataItem(this->data,count);
    dataItemStatus.append(subDataItems);
    return dataItemStatus;
}

QVector<unsigned char> Cat21::GetMetInformationDataItem() {
    QVector<unsigned char> dataItemStatus = Utilities::DataTools::GetVariableLengthDataItem(this->data);
    int subItemsLenght = 0;

    if ((dataItemStatus.at(0) & 128) != 0) {
        subItemsLenght += 2;
    }
    if ((dataItemStatus.at(0) & 64) != 0) {
        subItemsLenght += 2;
    }
    if ((dataItemStatus.at(0) & 32) != 0) {
        subItemsLenght += 2;
    }
    if ((dataItemStatus.at(0) & 16) != 0) {
        subItemsLenght += 1;
    }
    QVector<unsigned char> subDataItems = Utilities::DataTools::GetFixedLengthDataItem(this->data,subItemsLenght);
    dataItemStatus.append(subDataItems);
    return dataItemStatus;
}

QVector<unsigned char> Cat21::GetTrajectoryIntentDataItem() {
    QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);

    if ((dataItem.at(0) & 128) != 0 ) {
        QVector<unsigned char> subDataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1);
        dataItem.append(subDataItem);
    }
    if ((dataItem.at(0) & 64) != 0 ) {
        QVector<unsigned char> subDataItem = Utilities::DataTools::GetRepetitiveDataItem(this->data,15);
        dataItem.append(subDataItem);
    }
    return dataItem;
}

