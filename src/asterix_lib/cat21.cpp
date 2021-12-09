#include "hdr/asterix_lib/cat21.h"

Cat21::Cat21()
{
    this->category = 21;
    this->length = 0;
    this->offset = 0;

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

    this->serviceIdentification = -128;

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

    this->tiNav = "N/A";
    this->tiNvb = "N/A";

    this->tiTca = QVector<QString>();
    this->tiNc = QVector<QString>();
    this->tiTcpNumber = QVector<unsigned char>();
    this->tiAltitude = QVector<double>();
    this->tiLatitude = QVector<double>();
    this->tiLongitude = QVector<double>();
    this->tiPointType = QVector<QString>();
    this->tiTd = QVector<QString>();
    this->tiTra = QVector<QString>();
    this->tiToa = QVector<QString>();
    this->tiTov = QVector<int>();
    this->tiTtr = QVector<double>();

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

QString Cat21::GetTypeOfMessage() {
    return "N/A";
}

QTime Cat21::GetTimeOfReception() {
    return this->timeOfReportTransmission;
}

QString Cat21::GetSACSIC() {

    AppConfig *conf = AppConfig::GetInstance();
    Sensor sensor = conf->GetSensorFromSACSIC(systemAreaCode,systemIdentificationCode);
    if (sensor.systemAreaCode == systemAreaCode && sensor.systemIdCode == systemIdentificationCode) {
        return sensor.sensorDescription;
    }
    else {
        return QString::number(systemAreaCode) + "/" + QString::number(systemIdentificationCode);
    }

}

WGS84Coordinates Cat21::GetPosition() {
    return WGS84Coordinates(wgs84latitude,wgs84longitude, geometricHeight*0.3048);
}

QString Cat21::GetIdentifier() {

    if (targetIdentification != "N/A") {
            return targetIdentification;
    }

    else if (targetAddress != "N/A") {
        return targetAddress;
    }

    else if (trackNumber != -1) {
        return QString::number(trackNumber);
    }

    else {
        return "N/A";
    }
}

QString Cat21::GetCallSign() {
    return targetIdentification;
}
QString Cat21::GetAddress() {
    return targetAddress;
}
QString Cat21::GetTrackNumber() {
    return QString::number(trackNumber);
}

QTreeWidgetItem* Cat21::GetPacketInfo() {
    QTreeWidgetItem *root = new QTreeWidgetItem();
    root->setText(0, "Packet " + QString::number(this->numOfPacket));

    QTreeWidgetItem *cat = new QTreeWidgetItem();
    cat->setText(0, "Category");
    cat->setText(1,QString::number(this->category));
    root->addChild(cat);

    QTreeWidgetItem *len = new QTreeWidgetItem();
    len->setText(0, "Length");
    len->setText(1,QString::number(this->length));
    root->addChild(len);

    QTreeWidgetItem *dataItems = new QTreeWidgetItem();
    dataItems->setText(0, "Data Items");
    root->addChild(dataItems);

    if (this->aosRa != "N/A") {

        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/008, Aircraft Operational Status");
        dataItems->addChild(child);

        QTreeWidgetItem *v = new QTreeWidgetItem();
        QTreeWidgetItem *v2 = new QTreeWidgetItem();
        QTreeWidgetItem *v3 = new QTreeWidgetItem();
        QTreeWidgetItem *v4 = new QTreeWidgetItem();
        QTreeWidgetItem *v5 = new QTreeWidgetItem();
        QTreeWidgetItem *v6 = new QTreeWidgetItem();
        QTreeWidgetItem *v7 = new QTreeWidgetItem();

        v->setText(0,"TCAS Resolution Advisory active");
        v->setText(1,this->aosRa);
        child->addChild(v);
        v2->setText(0,"Target Trajectory Change Report Capability");
        v2->setText(1,this->aosTc);
        child->addChild(v2);
        v3->setText(0,"Target State Report Capability");
        v3->setText(1,this->aosTs);
        child->addChild(v3);
        v4->setText(0,"Air-Referenced Velocity Report Capability");
        v4->setText(1,this->aosArv);
        child->addChild(v4);
        v5->setText(0,"Cockpit Display of Traffic Information airborne");
        v5->setText(1,this->aosCdti);
        child->addChild(v5);
        v6->setText(0,"TCAS System Status");
        v6->setText(1,this->aosNotTcas);
        child->addChild(v6);
        v7->setText(0,"Single Antenna");
        v7->setText(1,this->aosSa);
        child->addChild(v7);
    }


    QTreeWidgetItem *dataSourceId = new QTreeWidgetItem();
    dataSourceId->setText(0, "I021/010, Data Source Identification");
    dataItems->addChild(dataSourceId);
    QTreeWidgetItem *systemAreaCode = new QTreeWidgetItem();
    systemAreaCode->setText(0,"System Area Code");
    systemAreaCode->setText(1,QString::number(this->systemAreaCode));
    dataSourceId->addChild(systemAreaCode);
    QTreeWidgetItem *systemIdCode = new QTreeWidgetItem();
    systemIdCode->setText(0,"System Identification Code");
    systemIdCode->setText(1,QString::number(this->systemIdentificationCode));
    dataSourceId->addChild(systemIdCode);

    if (this->serviceIdentification != -128) {

        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/015, Service Identification");
        dataItems->addChild(child);

        QTreeWidgetItem *v = new QTreeWidgetItem();
        v->setText(0,"Service Identification");
        v->setText(1,QString::number(this->serviceIdentification));
        child->addChild(v);
    }

    if (!isnan(this->serviceManagement)) {

        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/016, Service Management");
        dataItems->addChild(child);

        QTreeWidgetItem *v = new QTreeWidgetItem();
        v->setText(0,"Report Period");
        v->setText(1,QString::number(this->serviceManagement));
        child->addChild(v);
    }

    if (this->emitterCategory != "N/A") {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/020, Emitter Category");
        dataItems->addChild(child);

        QTreeWidgetItem *v = new QTreeWidgetItem();
        v->setText(0,"Emitter Category");
        v->setText(1,emitterCategory);
        child->addChild(v);
    }

    if (this->trAtp != "N/A") {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/040, Target Report Descriptor");
        dataItems->addChild(child);

        QTreeWidgetItem *v = new QTreeWidgetItem();
        QTreeWidgetItem *v2 = new QTreeWidgetItem();
        QTreeWidgetItem *v3 = new QTreeWidgetItem();
        QTreeWidgetItem *v4 = new QTreeWidgetItem();


        v->setText(0,"Address Type");
        v->setText(1,this->trAtp);
        child->addChild(v);
        v2->setText(0,"Altitude Reporting Capability");
        v2->setText(1,this->trArc);
        child->addChild(v2);
        v3->setText(0,"Range Check");
        v3->setText(1,this->trRc);
        child->addChild(v3);
        v4->setText(0,"Report Type");
        v4->setText(1,this->trRab);
        child->addChild(v4);

        if (this->trDcr != "N/A") {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            QTreeWidgetItem *v2 = new QTreeWidgetItem();
            QTreeWidgetItem *v3 = new QTreeWidgetItem();
            QTreeWidgetItem *v4 = new QTreeWidgetItem();
            QTreeWidgetItem *v5 = new QTreeWidgetItem();
            QTreeWidgetItem *v6 = new QTreeWidgetItem();

            v->setText(0,"Differential Correction");
            v->setText(1,this->trDcr);
            child->addChild(v);
            v2->setText(0,"Ground Bit Setting");
            v2->setText(1,this->trGbs);
            child->addChild(v2);
            v3->setText(0,"Simulated Target");
            v3->setText(1,this->trSim);
            child->addChild(v3);
            v4->setText(0,"Test Target");
            v4->setText(1,this->trTst);
            child->addChild(v4);
            v5->setText(0,"Selected Altitude Available");
            v5->setText(1,this->trSaa);
            child->addChild(v5);
            v6->setText(0,"Confidence Level");
            v6->setText(1,this->trSaa);
            child->addChild(v6);
        }

        if (this->trIpc != "N/A") {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            QTreeWidgetItem *v2 = new QTreeWidgetItem();
            QTreeWidgetItem *v3 = new QTreeWidgetItem();
            QTreeWidgetItem *v4 = new QTreeWidgetItem();
            QTreeWidgetItem *v5 = new QTreeWidgetItem();

            v->setText(0,"Independent Position Check");
            v->setText(1,this->trIpc);
            child->addChild(v);
            v2->setText(0,"No-go Bit Status");
            v2->setText(1,this->trNogo);
            child->addChild(v2);
            v3->setText(0,"Compact Position Reporting");
            v3->setText(1,this->trCpr);
            child->addChild(v3);
            v4->setText(0,"Local Decoding Position Jump");
            v4->setText(1,this->trLdpj);
            child->addChild(v4);
            v5->setText(0,"Range Check");
            v5->setText(1,this->trRcf);
            child->addChild(v5);
        }
    }

    if (this->m3ACode != "N/A") {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/070, Mode-3/A Code in Octal Representation");
        dataItems->addChild(child);

        QTreeWidgetItem *m3a = new QTreeWidgetItem();
        m3a->setText(0,"Mode 3/A Code");
        m3a->setText(1,this->m3ACode);
        child->addChild(m3a);
    }

    if (this->timeOfApplicabilityForPosition != QTime()) {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/071, Time of Applicability for Position");
        dataItems->addChild(child);
        QTreeWidgetItem *v = new QTreeWidgetItem();
        v->setText(0,"Time of Applicability for Position");
        v->setText(1,this->timeOfApplicabilityForPosition.toString("hh:mm:ss:zzz"));
        child->addChild(v);
    }

    if (this->timeOfApplicabilityForVelocity != QTime()) {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/072, Time of Applicability for Velocity");
        dataItems->addChild(child);
        QTreeWidgetItem *v = new QTreeWidgetItem();
        v->setText(0,"Time of Applicability for Velocity");
        v->setText(1,this->timeOfApplicabilityForVelocity.toString("hh:mm:ss:zzz"));
        child->addChild(v);
    }

    if (this->timeOfMessageReceptionOfPosition != QTime()) {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/073, Time of Message Reception for Position");
        dataItems->addChild(child);
        QTreeWidgetItem *v = new QTreeWidgetItem();
        v->setText(0,"Time of Message Reception for Position");
        v->setText(1,this->timeOfMessageReceptionOfPosition.toString("hh:mm:ss:zzz"));
        child->addChild(v);
    }

    if (!isnan(this->timeOfMessageReceptionOfPositionHighRes)) {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/074, Time of Message Reception of Position–High Precision");
        dataItems->addChild(child);
        QTreeWidgetItem *v = new QTreeWidgetItem();
        v->setText(0,"Time of Message Reception of Position–High Precision");
        v->setText(1,QString::number(this->timeOfMessageReceptionOfPositionHighRes));
        child->addChild(v);
    }

    if (this->timeOfMessageReceptionOfVelocity != QTime()) {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/075, Time of Message Reception for Velocity");
        dataItems->addChild(child);
        QTreeWidgetItem *v = new QTreeWidgetItem();
        v->setText(0,"Time of Message Reception for Position");
        v->setText(1,this->timeOfMessageReceptionOfVelocity.toString("hh:mm:ss:zzz"));
        child->addChild(v);
    }

    if (!isnan(this->timeOfMessageReceptionOfVelocityHighRes)) {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/076, Time of Message Reception of Velocity–High Precision");
        dataItems->addChild(child);
        QTreeWidgetItem *v = new QTreeWidgetItem();
        v->setText(0,"Time of Message Reception of Velocity–High Precision");
        v->setText(1,QString::number(this->timeOfMessageReceptionOfVelocityHighRes));
        child->addChild(v);
    }

    if (this->timeOfReportTransmission != QTime()) {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/077, Time of ASTERIX Report Transmission");
        dataItems->addChild(child);
        QTreeWidgetItem *v = new QTreeWidgetItem();
        v->setText(0,"Time of Report Transmission");
        v->setText(1,this->timeOfReportTransmission.toString("hh:mm:ss:zzz"));
        child->addChild(v);
    }

    if (this->targetAddress != "N/A") {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/080, Target Address");
        dataItems->addChild(child);
        QTreeWidgetItem *v = new QTreeWidgetItem();
        v->setText(0,"Target Address");
        v->setText(1,this->targetAddress);
        child->addChild(v);
    }

    if (!isnan(this->wgs84latitude)) {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/130, Position in WGS-84 Co-ordinates");
        dataItems->addChild(child);
        QTreeWidgetItem *lat = new QTreeWidgetItem();
        QTreeWidgetItem *lon = new QTreeWidgetItem();
        lat->setText(0,"Latitude [º]");
        lat->setText(1,QString::number(this->wgs84latitude));
        child->addChild(lat);
        lon->setText(0,"Longitude [º]");
        lon->setText(1,QString::number(this->wgs84longitude));
        child->addChild(lon);
    }

    if (!isnan(this->wgs84latitudeHighRes)) {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/131, High-Resolution Position in WGS-84 Co-ordinates");
        dataItems->addChild(child);
        QTreeWidgetItem *lat = new QTreeWidgetItem();
        QTreeWidgetItem *lon = new QTreeWidgetItem();
        lat->setText(0,"Latitude [º]");
        lat->setText(1,QString::number(this->wgs84latitudeHighRes));
        child->addChild(lat);
        lon->setText(0,"Longitude [º]");
        lon->setText(1,QString::number(this->wgs84longitudeHighRes));
        child->addChild(lon);
    }

    if (this->messageAmplitude != 1) {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/132, Message Amplitude");
        dataItems->addChild(child);
        QTreeWidgetItem *v = new QTreeWidgetItem();
        v->setText(0,"Message Amplitude [dBm]");
        v->setText(1,QString::number(this->messageAmplitude));
        child->addChild(v);
    }

    if (!isnan(this->geometricHeight)) {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/140, Geometric Height");
        dataItems->addChild(child);
        QTreeWidgetItem *v = new QTreeWidgetItem();
        v->setText(0,"Geometric Height [ft]");
        v->setText(1,QString::number(this->geometricHeight));
        child->addChild(v);
    }

    if (!isnan(this->flightLevel)) {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/145, Flight Level");
        dataItems->addChild(child);
        QTreeWidgetItem *fl = new QTreeWidgetItem();
        fl->setText(0,"Flight Level");
        fl->setText(1,QString::number(this->flightLevel));
        child->addChild(fl);
    }

    if (!isnan(this->saAltitude)) {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/146, Selected Altitude");
        dataItems->addChild(child);
        QTreeWidgetItem *v = new QTreeWidgetItem();
        QTreeWidgetItem *g = new QTreeWidgetItem();
        QTreeWidgetItem *fl = new QTreeWidgetItem();
        v->setText(0,"Source Availability");
        v->setText(1,this->saSas);
        child->addChild(v);
        g->setText(0,"Source");
        g->setText(1,this->saSource);
        child->addChild(g);
        fl->setText(0,"Altitude [ft]");
        fl->setText(1,QString::number(this->saAltitude));
        child->addChild(fl);
    }

    if (!isnan(this->fssaAltitude)) {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/148, Final State Selected Altitude");
        dataItems->addChild(child);
        QTreeWidgetItem *v = new QTreeWidgetItem();
        QTreeWidgetItem *g = new QTreeWidgetItem();
        QTreeWidgetItem *fl = new QTreeWidgetItem();
        QTreeWidgetItem *fl2 = new QTreeWidgetItem();
        v->setText(0,"Manage Vertical Mode");
        v->setText(1,this->fssaMv);
        child->addChild(v);
        g->setText(0,"Altitude Hold Mode");
        g->setText(1,this->fssaAh);
        child->addChild(g);
        fl->setText(0,"Approach Mode");
        fl->setText(1,this->fssaAm);
        child->addChild(fl);
        fl2->setText(0,"Altitude [ft]");
        fl2->setText(1,QString::number(this->fssaAltitude));
        child->addChild(fl2);
    }

    if (!isnan(this->saAltitude)) {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/150, Air Speed");
        dataItems->addChild(child);
        QTreeWidgetItem *v = new QTreeWidgetItem();
        QTreeWidgetItem *fl = new QTreeWidgetItem();
        v->setText(0,"Type of Speed");
        v->setText(1,this->asUnits);
        child->addChild(v);
        fl->setText(0,"Air Speed");
        fl->setText(1,QString::number(this->asAirSpeed));
        child->addChild(fl);
    }

    if (!isnan(this->tasTrueAirSpeed)) {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/151 True Airspeed");
        dataItems->addChild(child);
        QTreeWidgetItem *v = new QTreeWidgetItem();
        QTreeWidgetItem *fl = new QTreeWidgetItem();
        v->setText(0,"Range Exceeded");
        v->setText(1, this->tasRangeExceeded ? "Exceeds Range" : "In Defined Range");
        child->addChild(v);
        fl->setText(0,"True Air Speed [knot]");
        fl->setText(1,QString::number(this->tasTrueAirSpeed));
        child->addChild(fl);
    }

    if (!isnan(this->magneticHeading)) {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/152, Magnetic Heading");
        dataItems->addChild(child);
        QTreeWidgetItem *v = new QTreeWidgetItem();
        v->setText(0,"Magnetic Heading [º]");
        v->setText(1,QString::number(this->magneticHeading));
        child->addChild(v);
    }

    if (!isnan(this->tasTrueAirSpeed)) {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/155, Barometric Vertical Rate");
        dataItems->addChild(child);
        QTreeWidgetItem *v = new QTreeWidgetItem();
        QTreeWidgetItem *fl = new QTreeWidgetItem();
        v->setText(0,"Range Exceeded");
        v->setText(1, this->bvrRangeExceeded ? "Exceeds Range" : "In Defined Range");
        child->addChild(v);
        fl->setText(0,"Barometric Vertical Rate [feet/minute]");
        fl->setText(1,QString::number(this->bvrBarometricVerticalRate));
        child->addChild(fl);
    }

    if (!isnan(this->gvrGeometricVerticalRate)) {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/157, Geometric Vertical Rate");
        dataItems->addChild(child);
        QTreeWidgetItem *v = new QTreeWidgetItem();
        QTreeWidgetItem *fl = new QTreeWidgetItem();
        v->setText(0,"Range Exceeded");
        v->setText(1, this->gvrRangeExceeded ? "Exceeds Range" : "In Defined Range");
        child->addChild(v);
        fl->setText(0,"Geometric Vertical Rate [feet/minute]");
        fl->setText(1,QString::number(this->gvrGeometricVerticalRate));
        child->addChild(fl);
    }

    if (!isnan(this->agvGroundSpeed)) {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/160, Airborne Ground Vector");
        dataItems->addChild(child);
        QTreeWidgetItem *v = new QTreeWidgetItem();
        QTreeWidgetItem *fl = new QTreeWidgetItem();
        QTreeWidgetItem *fl2 = new QTreeWidgetItem();
        v->setText(0,"Range Exceeded");
        v->setText(1, this->agvRangeExceeded ? "Exceeds Range" : "In Defined Range");
        child->addChild(v);
        fl->setText(0,"Ground Speed");
        fl->setText(1,QString::number(this->agvGroundSpeed));
        child->addChild(fl);
        fl2->setText(0,"Track Angle");
        fl2->setText(1,QString::number(this->agvTrackAngle));
        child->addChild(fl2);
    }

    if (this->trackNumber != -1) {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/161, Track Number");
        dataItems->addChild(child);
        QTreeWidgetItem *v = new QTreeWidgetItem();
        v->setText(0,"Track Number");
        v->setText(1,QString::number(this->trackNumber));
        child->addChild(v);
    }

    if (!isnan(this->trackAngleRate)) {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/165, Track Angle Rate");
        dataItems->addChild(child);
        QTreeWidgetItem *v = new QTreeWidgetItem();
        v->setText(0,"Track Angle Rate");
        v->setText(1, QString::number(this->trackAngleRate));
        child->addChild(v);
    }

    if (this->targetIdentification != "N/A") {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/170, Target Identification");
        dataItems->addChild(child);
        QTreeWidgetItem *v = new QTreeWidgetItem();
        v->setText(0,"Target Identification");
        v->setText(1,this->targetIdentification);
        child->addChild(v);
    }

    if (this->tsIcf != "N/A") {
    //FALTA
    }

    if (this->mvVns != "N/A") {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/210, MOPS Version");
        dataItems->addChild(child);
        QTreeWidgetItem *v = new QTreeWidgetItem();
        v->setText(0,"Version Not Supported");
        v->setText(1,this->mvVns);
        child->addChild(v);
        QTreeWidgetItem *v2 = new QTreeWidgetItem();
        v2->setText(0,"Version Number");
        v2->setText(1,this->mvVn);
        child->addChild(v2);
        QTreeWidgetItem *v3 = new QTreeWidgetItem();
        v3->setText(0,"Version Not Supported");
        v3->setText(1,this->mvLtt);
        child->addChild(v3);
    }

    if (this->miTemperature != -32768 || this->miTurbulence != -32768 || this->miWindDirection != -32768 || this->miWindSpeed != -32768) {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/220, Met Information");
        dataItems->addChild(child);
        if (this->miWindSpeed != -32768) {
            QTreeWidgetItem *v1 = new QTreeWidgetItem();
            v1->setText(0,"Subfield #1: Wind Speed");
            QTreeWidgetItem *v11 = new QTreeWidgetItem();
            v11->setText(0,"Wind Speed [knot]");
            v11->setText(1,QString::number(this->miWindSpeed));
            v1->addChild(v11);
            child->addChild(v1);
        }

        if (this->miWindDirection != -32768) {
            QTreeWidgetItem *v1 = new QTreeWidgetItem();
            v1->setText(0,"Subfield #2: Wind Direction");
            QTreeWidgetItem *v11 = new QTreeWidgetItem();
            v11->setText(0,"Wind Direction [º]");
            v11->setText(1,QString::number(this->miWindDirection));
            v1->addChild(v11);
            child->addChild(v1);
        }

        if (this->miWindDirection != -32768) {
            QTreeWidgetItem *v1 = new QTreeWidgetItem();
            v1->setText(0,"Subfield #3: Temperature");
            QTreeWidgetItem *v11 = new QTreeWidgetItem();
            v11->setText(0,"Temperature [ºC]");
            v11->setText(1,QString::number(this->miTemperature));
            v1->addChild(v11);
            child->addChild(v1);
        }

        if (this->miWindDirection != -32768) {
            QTreeWidgetItem *v1 = new QTreeWidgetItem();
            v1->setText(0,"Subfield #4: Turbulence");
            QTreeWidgetItem *v11 = new QTreeWidgetItem();
            v11->setText(0,"Turbulence []");
            v11->setText(1,QString::number(this->miTurbulence));
            v1->addChild(v11);
            child->addChild(v1);
        }
    }

    if (!isnan(this->rollAngle)) {
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/230, Roll Angle");
        dataItems->addChild(child);
        QTreeWidgetItem *v = new QTreeWidgetItem();
        v->setText(0,"Roll Angle [º]");
        v->setText(1, QString::number(this->rollAngle));
        child->addChild(v);
    }

    if (this->sccPoa != "N/A") {

        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/271, Surface Capabilities and Characteristics");
        dataItems->addChild(child);

        QTreeWidgetItem *v = new QTreeWidgetItem();
        QTreeWidgetItem *v2 = new QTreeWidgetItem();
        QTreeWidgetItem *v3 = new QTreeWidgetItem();
        QTreeWidgetItem *v4 = new QTreeWidgetItem();
        QTreeWidgetItem *v5 = new QTreeWidgetItem();


        v->setText(0,"Position Offset Applied");
        v->setText(1,this->sccPoa);
        child->addChild(v);
        v2->setText(0,"Cockpit Display of Traffic Information Surface");
        v2->setText(1,this->sccCdti);
        child->addChild(v2);
        v3->setText(0,"Class B2 transmit power less than 70 Watts");
        v3->setText(1,this->sccB2Low);
        child->addChild(v3);
        v4->setText(0,"Receiving ATC Services");
        v4->setText(1,this->sccRas);
        child->addChild(v4);
        v5->setText(0,"Setting of “IDENT”-switch");
        v5->setText(1,this->sccIdent);
        child->addChild(v5);

        if (this->sccLengthPlusWidth != "N/A") {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            v->setText(0,"Length and width of the aircraft");
            v->setText(1,this->sccLengthPlusWidth);
            child->addChild(v);
        }
    }

    if (!isnan(this->daAOS) || !isnan(this->daARA) || !isnan(this->daAS) || !isnan(this->daBVR) || !isnan(this->daBVR)
            || !isnan(this->daFL) || !isnan(this->daFSSA) || !isnan(this->daGH) || !isnan(this->daGV)
            || !isnan(this->daGVR) || !isnan(this->daISSA) || !isnan(this->daM3A) || !isnan(this->daMA)
            || !isnan(this->daMET) || !isnan(this->daMH) || !isnan(this->daQI) || !isnan(this->daROA) || !isnan(this->daSCC)
            || !isnan(this->daTAR) || !isnan(this->daTAS) || !isnan(this->daTRD) || !isnan(this->daTS) || !isnan(this->daTaI)
            || !isnan(this->daTrI)) {

        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, "I021/295, Data Ages");
        dataItems->addChild(child);

        if (!isnan(this->daAOS)) {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            v->setText(0, "Aircraft Operational Status Age");
            v->setText(1, QString::number(this->daAOS));
            child->addChild(v);
        }
        if (!isnan(this->daTRD)) {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            v->setText(0, "Target Report Descriptor Age");
            v->setText(1, QString::number(this->daTRD));
            child->addChild(v);
        }

        if (!isnan(this->daM3A)) {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            v->setText(0, "Mode 3/A Age");
            v->setText(1, QString::number(this->daM3A));
            child->addChild(v);
        }

        if (!isnan(this->daQI)) {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            v->setText(0, "Quality Indicators Age");
            v->setText(1, QString::number(this->daQI));
            child->addChild(v);
        }

        if (!isnan(this->daTrI)) {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            v->setText(0, "Trajectory Intent Age");
            v->setText(1, QString::number(this->daTrI));
            child->addChild(v);
        }

        if (!isnan(this->daMA)) {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            v->setText(0, "Message Amplitude Age");
            v->setText(1, QString::number(this->daMA));
            child->addChild(v);
        }

        if (!isnan(this->daGH)) {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            v->setText(0, "Geometric Height Age");
            v->setText(1, QString::number(this->daGH));
            child->addChild(v);
        }

        if (!isnan(this->daFL)) {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            v->setText(0, "Flight Level Age");
            v->setText(1, QString::number(this->daFL));
            child->addChild(v);
        }

        if (!isnan(this->daISSA)) {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            v->setText(0, "Intermediate State Selected Altitude Age");
            v->setText(1, QString::number(this->daISSA));
            child->addChild(v);
        }

        if (!isnan(this->daFSSA)) {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            v->setText(0, "Final State Selected Altitude Age");
            v->setText(1, QString::number(this->daFSSA));
            child->addChild(v);
        }

        if (!isnan(this->daAS)) {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            v->setText(0, "Air Speed Age");
            v->setText(1, QString::number(this->daAS));
            child->addChild(v);
        }

        if (!isnan(this->daTAS)) {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            v->setText(0, "True Air Speed Age");
            v->setText(1, QString::number(this->daTAS));
            child->addChild(v);
        }

        if (!isnan(this->daMH)) {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            v->setText(0, "Magnetic Heading Age");
            v->setText(1, QString::number(this->daMH));
            child->addChild(v);
        }

        if (!isnan(this->daBVR)) {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            v->setText(0, "Barometric Vertical Rate Age");
            v->setText(1, QString::number(this->daBVR));
            child->addChild(v);
        }

        if (!isnan(this->daGVR)) {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            v->setText(0, "Geometric Vertical Rate Age");
            v->setText(1, QString::number(this->daGVR));
            child->addChild(v);
        }
        if (!isnan(this->daTAR)) {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            v->setText(0, "Track Angle Rate Age");
            v->setText(1, QString::number(this->daTAR));
            child->addChild(v);
        }

        if (!isnan(this->daTaI)) {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            v->setText(0, "Target Identification Age");
            v->setText(1, QString::number(this->daTaI));
            child->addChild(v);
        }

        if (!isnan(this->daTS)) {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            v->setText(0, "Target Status Age");
            v->setText(1, QString::number(this->daTS));
            child->addChild(v);
        }

        if (!isnan(this->daMET)) {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            v->setText(0, "Met Information Age");
            v->setText(1, QString::number(this->daGVR));
            child->addChild(v);
        }

        if (!isnan(this->daROA)) {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            v->setText(0, "Roll Angle Age");
            v->setText(1, QString::number(this->daROA));
            child->addChild(v);
        }

        if (!isnan(this->daARA)) {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            v->setText(0, "ACAS Resolution Advisory Age");
            v->setText(1, QString::number(this->daARA));
            child->addChild(v);
        }

        if (!isnan(this->daSCC)) {
            QTreeWidgetItem *v = new QTreeWidgetItem();
            v->setText(0, "Surface Capabilities and Characteristics Age");
            v->setText(1, QString::number(this->daSCC));
            child->addChild(v);
        }
    }

    return root;
}


void Cat21::FullDecode() {

    if (this->fspec.length() > 0) {

        if ((this->fspec.at(0) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2,this->offset);
            this->DecodeDataSourceIdentification(dataItem);
        }
        if ((this->fspec.at(0) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetVariableLengthDataItem(this->data,this->offset);
            this->DecodeTargetReportDescriptor(dataItem);
        }
        if ((this->fspec.at(0) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2,this->offset);
            this->DecodeTrackNumber(dataItem);
        }
        if ((this->fspec.at(0) & 0x10) == 0x10) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1,this->offset);
            this->DecodeServiceIdentification(dataItem);
        }
        if ((this->fspec.at(0) & 0x08) == 0x08) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,3,this->offset);
            this->DecodeTimeOfApplicabilityForPosition(dataItem);
        }
        if ((this->fspec.at(0) & 0x04) == 0x04) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,6,this->offset);
            this->DecodePositionInWGS84Coordinates(dataItem);
        }
        if ((this->fspec.at(0) & 0x02) == 0x02) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,8,this->offset);
            this->DecodePositionInWGS84CoordinatesHighRes(dataItem);
        }
    }

    if (this->fspec.length() > 1) {

        if ((this->fspec.at(1) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,3,this->offset);
            this->DecodeTimeOfApplicabilityForVelocity(dataItem);
        }
        if ((this->fspec.at(1) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2,this->offset);
            this->DecodeAirSpeed(dataItem);
        }
        if ((this->fspec.at(1) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2,this->offset);
            this->DecodeTrueAirSpeed(dataItem);
        }
        if ((this->fspec.at(1) & 0x10) == 0x10) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,3,this->offset);
            this->DecodeTargetAddress(dataItem);
        }
        if ((this->fspec.at(1) & 0x08) == 0x08) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,3,this->offset);
            this->DecodeTimeOfMessageReceptionOfPosition(dataItem);
        }
        if ((this->fspec.at(1) & 0x04) == 0x04) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,4,this->offset);
            this->DecodeTimeOfMessageReceptionOfPositionHighPrecision(dataItem);
        }
        if ((this->fspec.at(1) & 0x02) == 0x02) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,3,this->offset);
            this->DecodeTimeOfMessageReceptionOfVelocity(dataItem);
        }
    }
    if (this->fspec.length() > 2) {

        if ((this->fspec.at(2) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,4,this->offset);
            this->DecodeTimeOfMessageReceptionOfVelocityHighPrecision(dataItem);
        }
        if ((this->fspec.at(2) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2,this->offset);
            this->DecodeGeometricHeight(dataItem);
        }
        if ((this->fspec.at(2) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetVariableLengthDataItem(this->data,this->offset);
            this->DecodeQualityIndicators(dataItem);
        }
        if ((this->fspec.at(2) & 0x10) == 0x10) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1,this->offset);
            this->DecodeMOPSVersion(dataItem);
        }
        if ((this->fspec.at(2) & 0x08) == 0x08) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2,this->offset);
            this->DecodeMode3ACode(dataItem);
        }
        if ((this->fspec.at(2) & 0x04) == 0x04) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2,this->offset);
            this->DecodeRollAngle(dataItem);
        }
        if ((this->fspec.at(2) & 0x02) == 0x02) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2,this->offset);
            this->DecodeFlightLevel(dataItem);
        }
    }
    if (this->fspec.length() > 3) {

        if ((this->fspec.at(3) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2,this->offset);
            this->DecodeMagneticHeading(dataItem);
        }
        if ((this->fspec.at(3) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1,this->offset);
            this->DecodeTargetStatus(dataItem);
        }
        if ((this->fspec.at(3) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2,this->offset);
            this->DecodeBarometricVerticalRate(dataItem);
        }
        if ((this->fspec.at(3) & 0x10) == 0x10) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2,this->offset);
            this->DecodeGeometricVerticalRate(dataItem);
        }
        if ((this->fspec.at(3) & 0x08) == 0x08) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,4,this->offset);
            this->DecodeAirborneGroundVector(dataItem);
        }
        if ((this->fspec.at(3) & 0x04) == 0x04) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2,this->offset);
            this->DecodeTrackAngleRate(dataItem);
        }
        if ((this->fspec.at(3) & 0x02) == 0x02) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,3,this->offset);
            this->DecodeTimeOfReportTransmission(dataItem);
        }
    }

    if (this->fspec.length() > 4) {

        if ((this->fspec.at(4) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,6,this->offset);
            this->DecodeTargetIdentification(dataItem);
        }
        if ((this->fspec.at(4) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1,this->offset);
            this->DecodeEmitterCategory(dataItem);
        }
        if ((this->fspec.at(4) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetVariableLengthDataItem(this->data,this->offset);
            this->DecodeMetInformation(dataItem);
        }
        if ((this->fspec.at(4) & 0x10) == 0x10) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2,this->offset);
            this->DecodeSelectedAltitude(dataItem);
        }
        if ((this->fspec.at(4) & 0x08) == 0x08) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,2,this->offset);
            this->DecodeFinalStateSelectedAltitude(dataItem);
        }
        if ((this->fspec.at(4) & 0x04) == 0x04) {
            QVector<unsigned char> dataItem = this->GetTrajectoryIntentDataItem();
            this->DecodeTrajectoryIntent(dataItem);
        }
        if ((this->fspec.at(4) & 0x02) == 0x02) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1,this->offset);
            this->DecodeServiceManagement(dataItem);
        }
    }

    if (this->fspec.length() > 5) {

        if ((this->fspec.at(5) & 0x80) == 0x80) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1,this->offset);
            this->DecodeAircraftOperationalStatus(dataItem);
        }
        if ((this->fspec.at(5) & 0x40) == 0x40) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetVariableLengthDataItem(this->data,this->offset);
            this->DecodeSurfaceCapabilitiesAndCharacteristics(dataItem);
        }
        if ((this->fspec.at(5) & 0x20) == 0x20) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1,this->offset);
            this->DecodeMessageAmplitude(dataItem);
        }
        if ((this->fspec.at(5) & 0x10) == 0x10) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetRepetitiveDataItem(this->data,8,this->offset);
            this->DecodeModeSMBData(dataItem);
        }
        if ((this->fspec.at(5) & 0x08) == 0x08) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,7,this->offset);
            this->DecodeACASResolutionAdvisoryReport(dataItem);
        }
        if ((this->fspec.at(5) & 0x04) == 0x04) {
            QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1,this->offset);
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
    int mseconds = seconds * 1000;
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
    int mseconds = seconds * 1000;
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
    int mseconds = seconds * 1000;
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
    int mseconds = seconds * 1000;
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
    int mseconds = seconds * 1000;
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

void Cat21::DecodeTrajectoryIntent(QVector<unsigned char> &dataItem) {

    bool firstSubfield = false;
    bool secondSubfield = false;

    if ((dataItem.at(0) & 128) != 0) {
        firstSubfield = true;
    }
    if ((dataItem.at(0) & 64) != 0) {
        secondSubfield = true;
    }
    dataItem.removeFirst();

    if (firstSubfield) {
        unsigned char nav = (dataItem.first() & 128) >> 7;
        unsigned char nvb = (dataItem.first() & 64) >> 6;
        dataItem.removeFirst();

        switch (nav) {
        case 0:
            this->tiNav = "Trajectory Intent Data is available for this aircraft";
            break;
        case 1:
            this->tiNav = "Trajectory Intent Data is not available for this aircraft";
            break;
        }
        switch (nvb) {
        case 0:
            this->tiNvb = "Trajectory Intent Data is valid";
            break;
        case 1:
            this->tiNvb = "Trajectory Intent Data is not valid";
            break;
        }
    }

    if (secondSubfield) {
        int repetitions = dataItem.first();
        dataItem.removeFirst();

        for (int c = 0; c < repetitions; c++) {

            bool tca = (dataItem.first() & 128) >> 7;
            bool nc = (dataItem.first() & 64) >> 6;
            unsigned char tcpNumber = dataItem.first() & 0b00111111;
            dataItem.removeFirst();
            QVector<unsigned char> altBytes = {dataItem.first(), dataItem.at(1)};
            QVector<unsigned char> latitudeBytes = {dataItem.at(2), dataItem.at(3),dataItem.at(4)};
            QVector<unsigned char> longitudeBytes = {dataItem.at(5), dataItem.at(6),dataItem.at(7)};
            dataItem.remove(0,7);
            unsigned char pointType = (dataItem.at(0) & 0b11110000) >> 4;
            unsigned char td = (dataItem.at(0) & 0b00001100) >> 2;
            bool tra = (dataItem.at(0) & 0b00000010) >> 1;
            bool toa = (dataItem.at(0) & 0b00000001);
            dataItem.removeFirst();
            QVector<unsigned char> tov = {dataItem.at(0), dataItem.at(1),dataItem.at(2)};
            QVector<unsigned char> ttr = {dataItem.at(3), dataItem.at(4)};
            dataItem.remove(0,5);

            if (!tca) {
                this->tiTca.append("TCP number available");
            }
            else if (tca) {
                this->tiTca.append("TCP number not available");
            }

            if (!nc) {
                this->tiTca.append("TCP compliance");
            }
            else if (nc) {
                this->tiTca.append("TCP non-compliance");
            }

            double altRes = 10;
            double wgs84Res = 180.0 / pow(2,23);

            this->tiTcpNumber.append(tcpNumber);
            this->tiAltitude.append(Utilities::DataTools::DecodeTwosComplementToDouble(altBytes,altRes));
            this->tiLatitude.append(Utilities::DataTools::DecodeTwosComplementToDouble(latitudeBytes,wgs84Res));
            this->tiLongitude.append(Utilities::DataTools::DecodeTwosComplementToDouble(longitudeBytes,wgs84Res));

            switch (pointType) {
            case 0:
                this->tiPointType.append("Unknown");
                break;
            case 1:
                this->tiPointType.append("Fly by waipoint (LT)");
                break;
            case 2:
                this->tiPointType.append("Fly over waipoint (LT)");
                break;
            case 3:
                this->tiPointType.append("Hold pattern (LT)");
                break;
            case 4:
                this->tiPointType.append("Procedure Hold (LT)");
                break;
            case 5:
                this->tiPointType.append("Procedure Turn (LT)");
                break;
            case 6:
                this->tiPointType.append("RF Leg (LT)");
                break;
            case 7:
                this->tiPointType.append("Top of Climb (VT)");
                break;
            case 8:
                this->tiPointType.append("Top of descent (VT)");
                break;
            case 9:
                this->tiPointType.append("Start of Level (VT)");
                break;
            case 10:
                this->tiPointType.append("Cross-over altitude (VT)");
                break;
            case 11:
                this->tiPointType.append("Transition altitude (VT)");
                break;
            }

            switch (td) {
            case 0:
                this->tiTd.append("N/A");
                break;
            case 1:
                this->tiTd.append("Turn right");
                break;
            case 2:
                this->tiTd.append("Turn left");
                break;
            case 3:
                this->tiTd.append("No turn");
                break;
            }

            if (!tra) {
                this->tiTra.append("TTR not available");
            }
            else if (tra) {
                this->tiTra.append("TTR available");
            }

            if (!toa) {
                this->tiToa.append("TOV available");
            }
            else if (toa) {
                this->tiToa.append("TOV not available");
            }

            this->tiTov.append(Utilities::DataTools::DecodeUnsignedBytesToDouble(tov,1));
            this->tiTtr.append(Utilities::DataTools::DecodeUnsignedBytesToDouble(ttr,0.01));
        }
    }
}

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
    QVector<unsigned char> dataItemStatus = Utilities::DataTools::GetVariableLengthDataItem(this->data,this->offset);
    int count = 0;

    for (unsigned char byte : dataItemStatus) {
        int jumps = 1;
        while (jumps <= 7) {
            bool presence = (byte >> jumps) & 1;
            if (presence) {
                count++;
            }
            jumps++;
        }
    }

    QVector<unsigned char> subDataItems = Utilities::DataTools::GetFixedLengthDataItem(this->data,count,this->offset);
    dataItemStatus.append(subDataItems);
    return dataItemStatus;
}

QVector<unsigned char> Cat21::GetMetInformationDataItem() {
    QVector<unsigned char> dataItemStatus = Utilities::DataTools::GetVariableLengthDataItem(this->data,this->offset);
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
    QVector<unsigned char> subDataItems = Utilities::DataTools::GetFixedLengthDataItem(this->data,subItemsLenght,this->offset);
    dataItemStatus.append(subDataItems);
    return dataItemStatus;
}

QVector<unsigned char> Cat21::GetTrajectoryIntentDataItem() {
    QVector<unsigned char> dataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1,this->offset);

    if ((dataItem.at(0) & 128) != 0 ) {
        QVector<unsigned char> subDataItem = Utilities::DataTools::GetFixedLengthDataItem(this->data,1,this->offset);
        dataItem.append(subDataItem);
    }
    if ((dataItem.at(0) & 64) != 0 ) {
        QVector<unsigned char> subDataItem = Utilities::DataTools::GetRepetitiveDataItem(this->data,15,this->offset);
        dataItem.append(subDataItem);
    }
    return dataItem;
}

