#include "emitfiledialog.h"
#include "ui_emitfiledialog.h"

EmitFileDialog::EmitFileDialog(QWidget *parent, AsterixFile *astFile) :
    QDialog(parent),
    ui(new Ui::EmitFileDialog)
{
    ui->setupUi(this);
    astFile_ = astFile;
    QTime startTime = astFile_->dataBlocks->first()->GetTimeOfReception();
    QTime lastTime = astFile_->dataBlocks->last()->GetTimeOfReception();

    currentTime_ = startTime;
    emitTimer_ = new QTimer();
    this->ui->startHourLabel->setText(startTime.toString("hh:mm:ss:zzz"));
    this->ui->currentTimeLabel->setText(startTime.toString("hh:mm:ss:zzz"));
    this->ui->endHourLabel->setText(lastTime.toString("hh:mm:ss:zzz"));
    this->ui->horizontalSlider->setMinimum(0);
    this->ui->horizontalSlider->setMaximum(astFile_->numberOfPackets_-1);
    currentPacket = 0;
    connect(emitTimer_, &QTimer::timeout, this, &EmitFileDialog::on_TimerTick);
}

EmitFileDialog::~EmitFileDialog()
{
    delete ui;
}

void EmitFileDialog::on_startEmitButton_clicked()
{
    senderIp_ = QHostAddress(this->ui->ipEdit->text());
    senderPort_ = this->ui->udpEdit->text().toInt();
    senderSocket_.bind(QHostAddress(QHostAddress::AnyIPv4), 0);
    emitTimer_->setInterval(1);
    emitTimer_->start();
}

void EmitFileDialog::on_TimerTick() {

    DataBlock *currentData = astFile_->dataBlocks->at(currentPacket);

    for (;currentTime_.msecsTo(currentData->GetTimeOfReception()) <= 0 ;) {
        EmitPacket(currentData);
        this->ui->horizontalSlider->setValue(currentPacket);
        currentPacket++;
        currentData = astFile_->dataBlocks->at(currentPacket);
    }
    currentTime_ = currentTime_.addMSecs(1);
    this->ui->currentTimeLabel->setText(currentTime_.toString("hh:mm:ss:zzz"));
    this->ui->sentPacketsLabel->setText("Packets Sent: " + QString::number(currentPacket));
}


void EmitFileDialog::on_StopEmitButton_clicked()
{
    emitTimer_->stop();
}

void EmitFileDialog::EmitPacket(DataBlock* dataBlock) {
    QByteArray datagram = dataBlock->GetData();
    senderSocket_.writeDatagram(datagram, senderIp_, senderPort_);
}


void EmitFileDialog::on_horizontalSlider_sliderMoved(int position)
{
    currentPacket = position;
    DataBlock *currentData = astFile_->dataBlocks->at(currentPacket);
    currentTime_ = currentData->GetTimeOfReception();
    this->ui->currentTimeLabel->setText(currentTime_.toString("hh:mm:ss:zzz"));
    this->ui->sentPacketsLabel->setText("Packets Sent: " + QString::number(currentPacket));
}

