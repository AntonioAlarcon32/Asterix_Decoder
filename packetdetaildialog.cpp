#include "packetdetaildialog.h"
#include "ui_packetdetaildialog.h"

PacketDetailDialog::PacketDetailDialog(QWidget *parent, QTreeWidgetItem* packetStruct) :
    QDialog(parent),
    ui(new Ui::PacketDetailDialog)
{
    ui->setupUi(this);
    ui->treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->treeWidget->addTopLevelItem(packetStruct);
}

PacketDetailDialog::~PacketDetailDialog()
{
    delete ui;
}
