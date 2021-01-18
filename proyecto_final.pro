QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    angry_bee.cpp \
    bala.cpp \
    base.cpp \
    bee.cpp \
    friction_layer.cpp \
    frog.cpp \
    main.cpp \
    mainwindow.cpp \
    maty.cpp \
    platform.cpp \
    tadpole.cpp \
    tong.cpp

HEADERS += \
    angry_bee.h \
    bala.h \
    base.h \
    bee.h \
    friction_layer.h \
    frog.h \
    mainwindow.h \
    maty.h \
    platform.h \
    tadpole.h \
    tong.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
