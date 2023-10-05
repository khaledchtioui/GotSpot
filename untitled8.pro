QT       += core gui sql network charts printsupport  multimedia serialport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    client.cpp \
    connection.cpp \
    ddt.cpp \
    emp.cpp \
    entretien.cpp \
    exportexcelobject.cpp \
    facteur.cpp \
    formation.cpp \
    historique.cpp \
    mailing.cpp \
    main.cpp \
    mainwindow.cpp \
    piechartwidget.cpp \
    piechartwidget_j.cpp \
    popup.cpp \
    presence.cpp \
    smtp.cpp \
    user.cpp

HEADERS += \
    arduino.h \
    client.h \
    connection.h \
    ddt.h \
    emp.h \
    entretien.h \
    exportexcelobject.h \
    facteur.h \
    formation.h \
    historique.h \
    mailing.h \
    mainwindow.h \
    piechartwidget.h \
    piechartwidget_j.h \
    popup.h \
    presence.h \
    smtp.h \
    user.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    anglais.qm \
    configuration.jpeg

RESOURCES += \
    My_Resources.qrc
RC_ICONS=gotspot.ico
