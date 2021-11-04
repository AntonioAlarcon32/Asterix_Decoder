#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QFileDialog"
#include "QXmlStreamReader"
#include "QDebug"
#include "QDir"
#include "QMessageBox"

#include <../AsterixDecoder/hdr/asterix_lib/asterixfile.h>
#include <appconfig.h>
#include <sensor.h>

#include <hdr/gui/preferenceswindow.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_actionOpen_File_triggered();

    void on_actionPreferences_triggered();

private:
    Ui::MainWindow *ui;
    AsterixFile *astFile;
    AppConfig *appConfig_;

    void InitialConfig();
};
#endif // MAINWINDOW_H
