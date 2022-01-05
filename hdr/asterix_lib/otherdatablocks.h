#ifndef OTHERDATABLOCKS_H
#define OTHERDATABLOCKS_H

#include "datablock.h"


class OtherDataBlocks: public DataBlock
{
public:
    OtherDataBlocks(int category);
    ~OtherDataBlocks();

    void FullDecode();
    QString GetTypeOfMessage();
    QTime GetTimeOfReception();
    QString GetSACSIC();
    WGS84Coordinates GetPosition();
    QString GetIdentifier();
    QString GetCallSign();
    QString GetAddress();
    QString GetTrackNumber();
    QString GetMode3A();
    QTreeWidgetItem* GetPacketInfo();
    QString GetTypeOfTransmission();
    double GetTrackAngle();
};

#endif // OTHERDATABLOCKS_H
