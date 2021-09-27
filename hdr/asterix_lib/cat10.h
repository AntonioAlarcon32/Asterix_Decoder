#ifndef CAT10_H
#define CAT10_H

#include "hdr/asterix_lib/datablock.h"
#include "hdr/asterix_lib/utilities.h"


class Cat10: public DataBlock
{
public:

    short systemAreaCode;
    short systemIdentificationCode;

    Cat10();
    void FullDecode();

    void DecodeDataSourceIdentifier(QVector<char> &dataItem);

};

#endif // CAT10_H
