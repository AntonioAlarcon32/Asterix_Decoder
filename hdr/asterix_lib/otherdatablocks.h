#ifndef OTHERDATABLOCKS_H
#define OTHERDATABLOCKS_H

#include "hdr/asterix_lib/datablock.h"


class OtherDataBlocks: public DataBlock
{
public:
    OtherDataBlocks(int category);

    void FullDecode();
    QString GetTypeOfMessage();
    QTime GetTimeOfReception();
    QString GetSACSIC();
    WGS84Coordinates GetPosition();
    QString GetIdentifier();
    QString GetCallSign();
    QString GetAddress();
    QString GetTrackNumber();
    QTreeWidgetItem* GetPacketInfo();
};

#endif // OTHERDATABLOCKS_H
