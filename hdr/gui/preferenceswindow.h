#ifndef PREFERENCESWINDOW_H
#define PREFERENCESWINDOW_H

#include <QDialog>

#include "QDebug"
#include "QDir"
#include "QMessageBox"
#include "QStandardItemModel"

#include <appconfig.h>
#include <sensor.h>


namespace Ui {
class PreferencesWindow;
}

class PreferencesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PreferencesWindow(QWidget *parent = nullptr);
    ~PreferencesWindow();

private slots:
    void on_addRowButton_clicked();

    void on_deleteSelectedRowButton_clicked();

    void on_saveButton_clicked();

private:

    Ui::PreferencesWindow *ui;
    AppConfig *appConfig_;
    QStandardItemModel* table_;
    void LoadSensorsToTable();


};

#endif // PREFERENCESWINDOW_H
