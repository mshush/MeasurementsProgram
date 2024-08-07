QT       += core gui
QT       += charts
QT       += gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    measurementsparameterswidget.cpp \
    plotclass.cpp \
    processimitation.cpp \
    qcustomplot.cpp \
    tabwidgetforcharts.cpp \
    tabwidgetforparameters.cpp \
    tabwidgetfortools.cpp \
    treewidgetforfiles.cpp \
    widgetforcustomplot.cpp

HEADERS += \
    mainwindow.h \
    measurementsparameterswidget.h \
    plotclass.h \
    processimitation.h \
    qcustomplot.h \
    tabwidgetforcharts.h \
    tabwidgetforparameters.h \
    tabwidgetfortools.h \
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
