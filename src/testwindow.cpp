#include "hdr/testwindow.h"
#include "ui_testwindow.h"


TestWindow::TestWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestWindow)
{
    ui->setupUi(this);
    QQuickWidget *view = ui->quickWidget;
    QQmlContext *context = view->rootContext();
    view->show();
    map_ = view->rootObject();
    context->setContextProperty("testWindow", this);

    //connect(this, SIGNAL(changePosition(QGeoCoordinate)), map_, SLOT(changePos(QGeoCoordinate)));
}

TestWindow::~TestWindow()
{
    delete ui;
}

void TestWindow::on_pushButton_clicked()
{
    emit changePosition(41.301104043406234, 2.070916979442824);
}


void TestWindow::on_pushButton_2_clicked()
{
    emit addMarker(41.301104043406234, 2.070916979442824);
}


void TestWindow::on_pushButton_3_clicked()
{
    emit clearMap();
}

