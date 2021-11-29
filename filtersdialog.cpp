#include "filtersdialog.h"
#include "ui_filtersdialog.h"

FiltersDialog::FiltersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FiltersDialog)
{
    ui->setupUi(this);
    callSign_ = "";
    trackNumber_ = "";
    trackNumber_ = "";
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

    if (callSignChecked_) {
        callSign_ = ui->callSignText->text();
    }

    if (trackNumberChecked_) {
        address_ = ui->addressText->text();
    }

    if (addressChecked_) {
        trackNumber_ = ui->trackNumberText->text();
    }
}

