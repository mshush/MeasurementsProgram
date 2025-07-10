QT       += core gui network printsupport


#MAKEFLAGS=-j%NUMBER_OF_PROCESSORS%
#MAKEFLAGS=-j4
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

SOURCES += \
    legendrow.cpp \
    legendwidget.cpp \
    measurmentscontrol.cpp \
    #errorhandler.cpp \
    printpreview.cpp \
    custommeasurementtreewidget.cpp \
    customprocessingtreewidget.cpp \
    main.cpp \
    mainwindow.cpp \
    measurementsparameterswidget.cpp \
    plotclass.cpp \
    processimitation.cpp \
    #qcustomplot.cpp \
    resultparameterswidget.cpp \
    selectionrectclass.cpp \
    tabwidgetforcharts.cpp \
    tabwidgetforparameters.cpp \
    tabwidgetfortools.cpp \
    #testvna.cpp \
    threedimensionalvector.cpp \
    treewidgetforfiles.cpp \
    widgetforcustomplot.cpp

HEADERS += \
    legendrow.h \
    legendwidget.h \
    measurmentscontrol.h \
    printpreview.h \
    custommeasurementtreewidget.h \
    customprocessingtreewidget.h \
    mainwindow.h \
    measurementsparameterswidget.h \
    plotclass.h \
    processimitation.h \
    #qcustomplot.h \
    resultparameterswidget.h \
    selectionrectclass.h \
    tabwidgetforcharts.h \
    tabwidgetforparameters.h \
    tabwidgetfortools.h \
    #testvna.h \
    threedimensionalvector.h \
    treewidgetforfiles.h \
    widgetforcustomplot.h

FORMS += \
    mainwindow.ui


FORMS += \
    mainwindow.ui



INCLUDEPATH += $$PWD/lib
INCLUDEPATH += $$PWD/dll
INCLUDEPATH += $$PWD/include_ 


LIBS += -L$$PWD/lib -llibAlgLib
LIBS += -L$$PWD/dll -lMeasLib
#LIBS += -luntitled3

#LIBS += -L$$PWD/dll -llibfftw3-3  #Задание Алексея про эту библиотеку

TRANSLATIONS += translation/MeasProg_ru.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QMAKE_CXXFLAGS += -Wa,-mbig-obj
#QT_AUTO_SCREEN_SCALE_FACTOR = 0 #? (Так не работает)

#Для добавления QCustomplot как внешней библиотеки
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../QCustomPlot/release/ -lQCustomPlot
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../QCustomPlot/debug/ -lQCustomPlot

INCLUDEPATH += $$PWD/../QCustomPlot
DEPENDPATH += $$PWD/../QCustomPlot

#INCLUDEPATH += $$PWD/lib
#LIBS += -L$$PWD/lib -llibAlgLib
#LIBS += -L$$PWD/lib -llibuntitled3
#LIBS += -L$$PWD/dll -llibfftw3-3

DISTFILES += \
    #dll/libfftw3-3.dll \
    #dll/libfftw3f-3.dll \
    #dll/libfftw3l-3.dll \
    #lib/libAlgLib.a \
    #lib/libuntitled3.a \
    translation/MeasProg_ru.qm \
    translation/MeasProg_ru.ts

