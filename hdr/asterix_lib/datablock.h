#ifndef DATABLOCK_H
#define DATABLOCK_H
#include "QString"
#include "QVector"


class DataBlock
{
public:

    int category;
    int length;
    QByteArray data;
    QVector<unsigned char> fspec;

    void SetLength(int len);
    int GetLength();
    int GetCategory();
    void SetData(QByteArray data);
    void DecodeFSPEC();
    QByteArray GetData();
    //virtual QString GetTypeOfMessage() = 0;
    virtual void FullDecode() = 0;

};

#endif // DATABLOCK_H
