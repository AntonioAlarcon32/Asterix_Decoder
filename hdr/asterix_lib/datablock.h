#ifndef DATABLOCK_H
#define DATABLOCK_H
#include "QString"
#include "QVector"


class DataBlock
{
public:

    int category;
    int length;
    QVector<char> data;

    void SetLength(int len);
    int GetLength();
    int GetCategory();
    void SetData(QVector<char> data);
    QVector<char> GetData();
    //virtual QString GetTypeOfMessage() = 0;
    //virtual void FullDecode() = 0;
    virtual int TestFunction() = 0;

};

#endif // DATABLOCK_H
