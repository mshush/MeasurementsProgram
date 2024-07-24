QT       += core gui
QT       += charts
QT       += gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    customchartview.cpp \
    main.cpp \
    mainwindow.cpp \
    measurementsparameterswidget.cpp \
    processingparameterswidget.cpp \
    tabwidgetforcharts.cpp \
    tabwidgetforparameters.cpp \
    tabwidgetfortools.cpp \
    treewidgetforfiles.cpp \
    widgetforchart.cpp

HEADERS += \
    customchartview.h \
    mainwindow.h \
    measurementsparameterswidget.h \
    processingparameterswidget.h \
    tabwidgetforcharts.h \
    tabwidgetforparameters.h \
    tabwidgetfortools.h \
    treewidgetforfiles.h \
    widgetforchart.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
