#ifndef DATABLOCK_H
#define DATABLOCK_H

#include "QString"
#include "QVector"
#include "QTime"
#include "wgs84coordinates.h"


class DataBlock
{
public:

    int category;
    int length;
    QByteArray data;
    QVector<unsigned char> fspec;

    void SetLength(int len);

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
    virtual QString GetIdentifier() = 0;
};

#endif // DATABLOCK_H
