QT       += core gui
QT       += charts
QT       += gui

#MAKEFLAGS=-j%NUMBER_OF_PROCESSORS%
#MAKEFLAGS=-j4
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

SOURCES += \
    custommeasurementtreewidget.cpp \
    customprocessingtreewidget.cpp \
    main.cpp \
    mainwindow.cpp \
    measurement.cpp \
    measurementsparameterswidget.cpp \
    plotclass.cpp \
    processimitation.cpp \
    qcustomplot.cpp \
    resultparameterswidget.cpp \
    selectionrectclass.cpp \
    tabwidgetforcharts.cpp \
    tabwidgetforparameters.cpp \
    tabwidgetfortools.cpp \
    threedimensionalvector.cpp \
    treewidgetforfiles.cpp \
    widgetforcustomplot.cpp

HEADERS += \
    custommeasurementtreewidget.h \
    customprocessingtreewidget.h \
    mainwindow.h \
    measurement.h \
    measurementsparameterswidget.h \
    plotclass.h \
    processimitation.h \
    qcustomplot.h \
    resultparameterswidget.h \
    selectionrectclass.h \
    tabwidgetforcharts.h \
    tabwidgetforparameters.h \
    tabwidgetfortools.h \
    threedimensionalvector.h \
    treewidgetforfiles.h \
    widgetforcustomplot.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QMAKE_CXXFLAGS += -Wa,-mbig-obj
#QT_AUTO_SCREEN_SCALE_FACTOR = 0 #? (Так не работает)
