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

WGS84Coordinates OtherDataBlocks::GetPosition() {
    return WGS84Coordinates(0,0,0);
}
QString OtherDataBlocks::GetIdentifier() {
    return "N/A";
}

QString OtherDataBlocks::GetCallSign() {
    return "N/A";
}
QString OtherDataBlocks::GetAddress() {
    return "N/A";
}
QString OtherDataBlocks::GetTrackNumber() {
    return "N/A";
}

