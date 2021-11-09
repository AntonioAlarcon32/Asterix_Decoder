QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    appconfig.cpp \
    filewindow.cpp \
    src/gui/preferenceswindow.cpp \
    sensor.cpp \
    src/asterix_lib/cat19.cpp \
    src/asterix_lib/cat20.cpp \
    src/asterix_lib/cat21.cpp \
    src/main.cpp \
    src/gui/mainwindow.cpp \
    src/asterix_lib/asterixfile.cpp \
    src/asterix_lib/datablock.cpp \
    src/asterix_lib/utilities.cpp \
    src/asterix_lib/cat10.cpp

HEADERS += \
    appconfig.h \
    filewindow.h \
    hdr/asterix_lib/cat19.h \
    hdr/asterix_lib/cat20.h \
    hdr/asterix_lib/cat21.h \
    hdr/gui/mainwindow.h \
    hdr/asterix_lib/utilities.h \
    hdr/asterix_lib/asterixfile.h \
    hdr/asterix_lib/datablock.h \
    hdr/asterix_lib/cat10.h \
    hdr/gui/preferenceswindow.h \
    sensor.h

FORMS += \
    filewindow.ui \
    ui/preferenceswindow.ui \
    ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
