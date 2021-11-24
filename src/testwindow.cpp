#include "hdr/testwindow.h"
#include "ui_testwindow.h"


TestWindow::TestWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestWindow)
{
    ui->setupUi(this);
    map_ = ui->testMap;
    map_->SetZoom(13);
    map_->SetPosition(WGS84Coordinates(41.280100977219696, 1.9766510362841287,0));
    map_->AddItem(WGS84Coordinates(41.280100977219696, 1.9766510362841287,0));
}

TestWindow::~TestWindow()
{
    delete ui;
}


