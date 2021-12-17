#include "hdr/gui/filtersdialog.h"
#include "ui_filtersdialog.h"

FiltersDialog::FiltersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FiltersDialog)
{
    ui->setupUi(this);
    callSign_ = "";
    address_ = "";
    trackNumber_ = -1;
    category_ = -1;
    mode3A_ = -1;
}

FiltersDialog::~FiltersDialog()
{
    delete ui;
}

void FiltersDialog::on_buttonBox_accepted()
{
    callSignChecked_ = ui->callSignCheck->isChecked();
    trackNumberChecked_ = ui->trackNumberCheck->isChecked();
    addressChecked_ = ui->AddressCheck->isChecked();
    categoryChecked_ = ui->categoryCheck->isChecked();
    m3aChecked_ = ui->mode3ACheck->isChecked();

    if (callSignChecked_) {
        callSign_ = ui->callSignText->text();
    }

    if (addressChecked_) {
        address_ = ui->addressText->text();
    }

    if (trackNumberChecked_) {
        QString text = ui->trackNumberText->text();
        trackNumber_ = text.toInt();
    }
    if (categoryChecked_) {
        category_ = ui->categoryText->text().toInt();
    }
    if (m3aChecked_) {
        mode3A_ = ui->mode3AText->text().toInt();
    }
}


void FiltersDialog::on_resetFiltersButton_clicked()
{
    emit ResetPacketsClicked();
}

