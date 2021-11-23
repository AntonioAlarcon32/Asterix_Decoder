#include "hdr/asterix_lib/otherdatablocks.h"

OtherDataBlocks::OtherDataBlocks(int category)
{
    this->category = category;
}

void OtherDataBlocks::FullDecode() {

}
QString OtherDataBlocks::GetTypeOfMessage() {
    return "N/A";

}
QTime OtherDataBlocks::GetTimeOfReception() {
  return QTime();
}

QString OtherDataBlocks::GetSACSIC() {
    return "N/A//N/A";
}
