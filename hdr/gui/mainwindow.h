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
#include <hdr/gui/filewindow.h>

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

    void on_openFileButton_clicked();

    void on_preferencesButton_clicked();

    void on_exitButton_clicked();

    void on_PacketLoaded();

private:
    Ui::MainWindow *ui;
    AppConfig *appConfig_;
    int numberOfPackets_;

    PreferencesWindow *prefWindow_;

    void InitialConfig();
};
#endif // MAINWINDOW_H
