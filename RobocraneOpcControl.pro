#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T12:47:20
#
#-------------------------------------------------

QT       += core gui
QT      += serialport
QT       += network \
        datavisualization   #added for Grippoint 23.11.17

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RobocraneOpcControl
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

#START added for Grippoint 23.11.17
DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += /usr/local/include/opencv2 \
                /usr/include/c++/5

LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc \
            -L$$OUT_PWD/../../../lib -lpthread

#END added for Grippoint 23.11.17

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp\
   $$PWD/open62541.c\
        csvHandling.cpp\
        laserscanner.cpp \
    surfacegraph.cpp\ #added for Grippoint 23.11.17
    grippoint.cpp \   #added for Grippoint 23.11.17
    teachIn.cpp \
    gp_InvKine.cpp
      # gpButtons.cpp #added for Grippoint 23.11.17



HEADERS  += mainwindow.h\
    $$PWD/open62541.h \
        grippoint.h \ #added for Grippoint 23.11.17
    surfacegraph.h \ #added for Grippoint 23.11.17
    diagramm.h  #added for Grippoint 23.11.17



FORMS    += $$PWD/mainwindow.ui
