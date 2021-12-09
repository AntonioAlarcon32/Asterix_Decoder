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
    int i = 0;
    this->fspec.append(data[this->offset]);
    while((data[this->offset+i] & 1) != 0) {
        this->fspec.append(data[offset+i+1]);
        i++;
    }
    offset += fspec.length();

}
