QT       += core gui quickwidgets positioning

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    emitter.cpp \
    src/appconfig.cpp \
    src/asterix_lib/otherdatablocks.cpp \
    src/gui/filewindow.cpp \
    src/gui/preferenceswindow.cpp \
    src/sensor.cpp \
    src/asterix_lib/cat19.cpp \
    src/asterix_lib/cat20.cpp \
    src/asterix_lib/cat21.cpp \
    src/main.cpp \
    src/gui/mainwindow.cpp \
    src/asterix_lib/asterixfile.cpp \
    src/asterix_lib/datablock.cpp \
    src/asterix_lib/utilities.cpp \
    src/asterix_lib/cat10.cpp \
    src/testwindow.cpp \
    wgs84coordinates.cpp

HEADERS += \
    emitter.h \
    hdr/appconfig.h \
    hdr/gui/filewindow.h \
    hdr/asterix_lib/cat19.h \
    hdr/asterix_lib/cat20.h \
    hdr/asterix_lib/cat21.h \
    hdr/gui/mainwindow.h \
    hdr/asterix_lib/utilities.h \
    hdr/asterix_lib/asterixfile.h \
    hdr/asterix_lib/datablock.h \
    hdr/asterix_lib/cat10.h \
    hdr/gui/preferenceswindow.h \
    hdr/asterix_lib/otherdatablocks.h \
    hdr/ensor.h \
    hdr/testwindow.h \
    wgs84coordinates.h

FORMS += \
    ui/widgets/testwindow.ui \
    ui/widgets/filewindow.ui \
    ui/widgets/preferenceswindow.ui \
    ui/widgets/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    testQml.qml

RESOURCES += \
    Resources.qrc
