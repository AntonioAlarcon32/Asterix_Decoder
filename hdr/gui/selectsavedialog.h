#ifndef SELECTSAVEDIALOG_H
#define SELECTSAVEDIALOG_H

#include <QDialog>

namespace Ui {
class SelectSaveDialog;
}

class SelectSaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectSaveDialog(QWidget *parent = nullptr);
    ~SelectSaveDialog();

private slots:
    void on_saveFilteredButton_clicked();

    void on_saveAllButton_clicked();

private:
    Ui::SelectSaveDialog *ui;
};

#endif // SELECTSAVEDIALOG_H
