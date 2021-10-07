QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    module/mybutton.cpp \
    module/mylabel.cpp \
    module/qwhbreathwidget.cpp \
    mysetwindow.cpp \
    namebox.cpp \
    playerwidget.cpp \
    playwidget.cpp \
    widget.cpp

HEADERS += \
    module/mybutton.h \
    module/mylabel.h \
    module/qwhbreathwidget.h \
    mysetwindow.h \
    namebox.h \
    playerwidget.h \
    playwidget.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../res.qrc
