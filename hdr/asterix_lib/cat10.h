#ifndef CAT10_H
#define CAT10_H

#include "QTime"

#include "hdr/asterix_lib/datablock.h"
#include "hdr/asterix_lib/utilities.h"


class Cat10: public DataBlock
{
public:

    short systemAreaCode;
    short systemIdentificationCode;

    QString typeOfMessage;

    QString trTYP;
    QString trDCR;
    QString trCHN;
    QString trGBS;
    QString trCRT;
    QString trSIM;
    QString trTST;
    QString trRAB;
    QString trLOP;
    QString trTOT;
    QString trSPI;

    QTime timeOfDay;

    Cat10();
    void FullDecode();

    void DecodeDataSourceIdentifier(QVector<char> &dataItem);
    void DecodeMessageType(QVector<char> &dataItem);
    void DecodeTargetReportDescriptor(QVector<char> &dataItem);
    void DecodeTimeOfDay(QVector<char> &dataItem);

};

#endif // CAT10_H
