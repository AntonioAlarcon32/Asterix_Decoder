#ifndef CAT21_H
#define CAT21_H

#include "hdr/asterix_lib/datablock.h"

class Cat21: public DataBlock
{
public:
    Cat21();
    void FullDecode();
};

#endif // CAT21_H
