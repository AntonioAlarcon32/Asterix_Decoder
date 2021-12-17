#ifndef FILTERSDIALOG_H
#define FILTERSDIALOG_H

#include <QDialog>

namespace Ui {
class FiltersDialog;
}

class FiltersDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FiltersDialog(QWidget *parent = nullptr);
    ~FiltersDialog();

    bool callSignChecked_;
    bool addressChecked_;
    bool trackNumberChecked_;
    bool categoryChecked_;
    bool m3aChecked_;

    QString callSign_;
    QString address_;
    int trackNumber_;
    int category_;
    int mode3A_;

signals:
    void ResetPacketsClicked();

private slots:
    void on_buttonBox_accepted();
    void on_resetFiltersButton_clicked();

private:
    Ui::FiltersDialog *ui;
};

#endif // FILTERSDIALOG_H
