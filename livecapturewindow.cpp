#include "livecapturewindow.h"
#include "ui_livecapturewindow.h"

LiveCaptureWindow::LiveCaptureWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LiveCaptureWindow)
{
    ui->setupUi(this);
}

LiveCaptureWindow::~LiveCaptureWindow()
{
    delete ui;
}
