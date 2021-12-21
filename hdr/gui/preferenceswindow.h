#ifndef PREFERENCESWINDOW_H
#define PREFERENCESWINDOW_H

#include <QDialog>

#include "QDebug"
#include "QDir"
#include "QMessageBox"
#include "QStandardItemModel"

#include <hdr/appconfig.h>
#include <hdr/asterix_lib/sensor.h>


namespace Ui {
class PreferencesWindow;
}

class PreferencesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PreferencesWindow(QWidget *parent = nullptr);
    ~PreferencesWindow();
    void LoadSensorsToTable();

private slots:
    void on_addRowButton_clicked();

    void on_deleteSelectedRowButton_clicked();

    void on_saveButton_clicked();

    void on_cancelButton_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

private:

    Ui::PreferencesWindow *ui;
    AppConfig *appConfig_;
    QStandardItemModel* table_;
    bool changesMade_;

    void SaveSensorsToConfig();
    void reject();


};

#endif // PREFERENCESWINDOW_H
