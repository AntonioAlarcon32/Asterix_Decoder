#include "hdr/gui/filtersdialog.h"
#include "ui_filtersdialog.h"

FiltersDialog::FiltersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FiltersDialog)
{
    ui->setupUi(this);
    callSigns_ = QStringList();
    addresses_ = QStringList();
    trackNumbers_ = QList<int>();
    categories_ = QList<int>();
    mode3ACodes_ = QList<int>();
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
        callSigns_ = ui->callSignText->text().split(";");
    }

    if (addressChecked_) {
        addresses_ = ui->addressText->text().split(";");
    }

    if (trackNumberChecked_) {
        QStringList text = ui->trackNumberText->text().split(";");
        for (QString trackNumber : text) {
            trackNumbers_.append(trackNumber.toInt());
        }

    }
    if (categoryChecked_) {
        QStringList text = ui->categoryText->text().split(";");
        for (QString trackNumber : text) {
            categories_.append(trackNumber.toInt());
        }
    }
    if (m3aChecked_) {
        QStringList text = ui->mode3AText->text().split(";");
        for (QString trackNumber : text) {
            mode3ACodes_.append(trackNumber.toInt());
        }
    }
}


void FiltersDialog::on_resetFiltersButton_clicked()
{
    emit ResetPacketsClicked();
}

