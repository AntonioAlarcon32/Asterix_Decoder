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

    QString callSign_;
    QString address_;
    QString trackNumber_;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::FiltersDialog *ui;
};

#endif // FILTERSDIALOG_H
