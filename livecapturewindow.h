#ifndef LIVECAPTUREWINDOW_H
#define LIVECAPTUREWINDOW_H

#include <QMainWindow>

namespace Ui {
class LiveCaptureWindow;
}

class LiveCaptureWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LiveCaptureWindow(QWidget *parent = nullptr);
    ~LiveCaptureWindow();

private:
    Ui::LiveCaptureWindow *ui;
};

#endif // LIVECAPTUREWINDOW_H
