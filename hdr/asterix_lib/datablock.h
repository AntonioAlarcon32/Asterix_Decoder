#ifndef DATABLOCK_H
#define DATABLOCK_H

#include "QString"
#include "QVector"
#include "QTime"
#include "wgs84coordinates.h"
#include "QTreeWidgetItem"


class DataBlock
{
public:

    virtual ~DataBlock()=0;

    int category;
    int length;
    int numOfPacket;
    int offset;
    QByteArray data;
    QVector<unsigned char> fspec;

    void SetLength(int len);
    void SetNumOfPacket(int len);
    int GetNumOfPacket();

    void SetData(QByteArray data);
    void DecodeFSPEC();
    virtual void FullDecode() = 0;

    //Get Methods

    int GetLength();
    int GetCategory();
    QByteArray GetData();

    virtual QString GetTypeOfMessage() = 0;
    virtual QTime GetTimeOfReception() = 0;
    virtual QString GetSACSIC() = 0;
    virtual WGS84Coordinates GetPosition() = 0;

    virtual QString GetCallSign() = 0;
    virtual QString GetAddress() = 0;
    virtual QString GetTrackNumber() = 0;
    virtual QString GetMode3A() = 0;
    virtual QString GetTypeOfTransmission() = 0;

    virtual QTreeWidgetItem* GetPacketInfo() = 0;
};

#endif // DATABLOCK_H
