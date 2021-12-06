#include "hdr/testwindow.h"
#include "ui_testwindow.h"


TestWindow::TestWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestWindow)
{
    ui->setupUi(this);
    QTreeWidgetItem *root = new QTreeWidgetItem();
    root->setText(0, "Packet");
    QTreeWidgetItem *child = new QTreeWidgetItem();
    child->setText(0,"child");
    root->addChild(child);
    ui->treeWidget->addTopLevelItem(root);
}

TestWindow::~TestWindow()
{
    delete ui;
}

void TestWindow::on_toolButton_clicked()
{
}
