QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    module/mybutton.cpp \
    module/mydialog.cpp \
    module/mylabel.cpp \
    mysetwindow.cpp \
    namebox.cpp \
    playerwidget.cpp \
    playwidget.cpp \
    prizedialog.cpp \
    widget.cpp

HEADERS += \
    module/mybutton.h \
    module/mydialog.h \
    module/mylabel.h \
    mysetwindow.h \
    namebox.h \
    playerwidget.h \
    playwidget.h \
    prizedialog.h \
    widget.h

FORMS += \
    module/mydialog.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../res.qrc
