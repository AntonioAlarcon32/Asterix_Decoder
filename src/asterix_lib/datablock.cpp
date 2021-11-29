#include "hdr/asterix_lib/datablock.h"


int DataBlock::GetCategory() {
    return this->category;
};

int DataBlock::GetLength() {
    return this->length;
};

void DataBlock::SetNumOfPacket(int number) {
    this->numOfPacket = number;
};

int DataBlock::GetNumOfPacket() {
    return this->numOfPacket;
};

void DataBlock::SetLength(int len) {
    this->length = len;
};

QByteArray DataBlock::GetData() {
    return this->data;
}

void DataBlock::SetData(QByteArray data) {
    this->data = data;
}

void DataBlock::DecodeFSPEC() {
    while((data[0] & 1) != 0) {
        this->fspec.append(data[0]);
        data.remove(0,1);
    }
    this->fspec.append(data[0]);
    data.remove(0,1);
}
