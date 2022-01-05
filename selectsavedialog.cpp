#include "selectsavedialog.h"
#include "ui_selectsavedialog.h"

SelectSaveDialog::SelectSaveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectSaveDialog)
{
    ui->setupUi(this);
}

SelectSaveDialog::~SelectSaveDialog()
{
    delete ui;
}

void SelectSaveDialog::on_saveFilteredButton_clicked()
{
    int c = 1;
    QDialog::done(5);
}


void SelectSaveDialog::on_saveAllButton_clicked()
{
    int c = 1;
    QDialog::done(6);
}

