#include "hdr/asterix_lib/otherdatablocks.h"

OtherDataBlocks::OtherDataBlocks(int category)
{
    this->category = category;
}

OtherDataBlocks::~OtherDataBlocks() {

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
QString OtherDataBlocks::GetMode3A() {
    return "N/A";
}

QString OtherDataBlocks::GetTypeOfTransmission() {
    return "N/A";
}

double OtherDataBlocks::GetTrackAngle() {
        return nan("");
}


QTreeWidgetItem* OtherDataBlocks::GetPacketInfo() {
    QTreeWidgetItem *root = new QTreeWidgetItem();
    root->setText(0, "Packet " + QString::number(this->numOfPacket));

    QTreeWidgetItem *cat = new QTreeWidgetItem();
    cat->setText(0, "Category");
    cat->setText(1,QString::number(this->category));
    root->addChild(cat);

    QTreeWidgetItem *len = new QTreeWidgetItem();
    len->setText(0, "Length");
    len->setText(1,QString::number(this->length));
    root->addChild(len);

    return root;

}


