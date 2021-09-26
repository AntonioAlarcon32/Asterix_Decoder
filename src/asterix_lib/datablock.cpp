#include "hdr/asterix_lib/datablock.h"


int DataBlock::GetCategory() {
    return this->category;
};

int DataBlock::GetLength() {
    return this->length;
};

void DataBlock::SetLength(int len) {
    this->length = len;
};

QVector<char> DataBlock::GetData() {
    return this->data;
}

void DataBlock::SetData(QVector<char> data) {
    this->data = data;
}
