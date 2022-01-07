#ifndef EMITFILEDIALOG_H
#define EMITFILEDIALOG_H

#include <QDialog>
#include <QTime>
#include <QTimer>
#include "QHostAddress"
#include "QUdpSocket"

#include <hdr/asterix_lib/asterixfile.h>

namespace Ui {
class EmitFileDialog;
}

class EmitFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EmitFileDialog(QWidget *parent = nullptr,AsterixFile *astFile = nullptr);
    ~EmitFileDialog();

private:
    void EmitPacket(DataBlock* dataBlock);
private slots:
    void on_startEmitButton_clicked();
    void on_TimerTick();

    void on_StopEmitButton_clicked();

    void on_horizontalSlider_sliderMoved(int position);

private:
    Ui::EmitFileDialog *ui;
    AsterixFile *astFile_;
    int senderPort_;
    QHostAddress senderIp_;
    QUdpSocket senderSocket_;
    int currentPacket;

    QTimer *emitTimer_;
    QTime currentTime_;

};

#endif // EMITFILEDIALOG_H
