#ifndef EMITTERDETAILSWINDOW_H
#define EMITTERDETAILSWINDOW_H

#include <QMainWindow>
#include "hdr/wgs84coordinates.h"
#include "hdr/emitter.h"

namespace Ui {
class EmitterDetailsWindow;
}

class EmitterDetailsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EmitterDetailsWindow(QWidget *parent = nullptr, Emitter *emitter = nullptr);
    ~EmitterDetailsWindow();

private:
    Ui::EmitterDetailsWindow *ui;
    Emitter *emitter_;
};

#endif // EMITTERDETAILSWINDOW_H
