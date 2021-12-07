#ifndef PACKETDETAILDIALOG_H
#define PACKETDETAILDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>

namespace Ui {
class PacketDetailDialog;
}

class PacketDetailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PacketDetailDialog(QWidget *parent = nullptr, QTreeWidgetItem* packetStruct = new QTreeWidgetItem());
    ~PacketDetailDialog();

private:
    Ui::PacketDetailDialog *ui;
};

#endif // PACKETDETAILDIALOG_H
