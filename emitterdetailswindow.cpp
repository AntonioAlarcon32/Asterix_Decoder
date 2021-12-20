#include "emitterdetailswindow.h"
#include "ui_emitterdetailswindow.h"

EmitterDetailsWindow::EmitterDetailsWindow(QWidget *parent, Emitter *emitter) :
    QMainWindow(parent),
    ui(new Ui::EmitterDetailsWindow),
    emitter_(emitter)

{
    ui->setupUi(this);

    int i = 0;
    WGS84Coordinates middleCoord = WGS84Coordinates(41.29760688636795, 2.0837311365820046);

    if (emitter_->pointsCat21.length() != 0) {
        for (WGS84Coordinates coord : emitter_->pointsCat21) {

            this->ui->detailsMap->AddCircleMarker(coord,10,"red",QString::number(i));
            i++;
        }
        middleCoord = emitter_->pointsCat21.at(emitter->pointsCat21.length()/2);
    }


    this->ui->detailsMap->SetPosition(middleCoord);
    this->ui->detailsMap->SetZoom(7);

    this->ui->detailsList->addItem("CallSign: " + emitter_->GetCallSign());
    this->ui->detailsList->addItem("Address: " + emitter_->GetTargetAddress());
    this->ui->detailsList->addItem("Mode 3/A Code: " + emitter_->GetMode3ACode());
    this->ui->detailsList->addItem("Track Number: " + emitter_->GetTrackNumber());

    this->ui->detailsList->addItem("First Packet: " + emitter_->GetFirstReport().toString("hh:mm:ss:zzz"));
    this->ui->detailsList->addItem("Last Packet: " + emitter_->GetLastReport().toString("hh:mm:ss:zzz"));
    this->ui->detailsList->addItem("Number of Packets of CAT10 SMR: " + QString::number(emitter_->pointsCat10Smr.length()));
    this->ui->detailsList->addItem("Number of Packets of CAT10 MLAT: " + QString::number(emitter_->pointsCat10Mlat.length()));
    this->ui->detailsList->addItem("Number of Packets of CAT20: " + QString::number(emitter_->pointsCat20.length()));
    this->ui->detailsList->addItem("Number of Packets of CAT21: " + QString::number(emitter_->pointsCat21.length()));

}

EmitterDetailsWindow::~EmitterDetailsWindow()
{
    delete ui;
}
