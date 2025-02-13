QT       += core gui network
QT       += charts
QT       += gui

#MAKEFLAGS=-j%NUMBER_OF_PROCESSORS%
#MAKEFLAGS=-j4
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

SOURCES += \
    01_DataProcessing/MeasData.cpp \
    01_DataProcessing/MeasDataClass.cpp \
    01_DataProcessing/MeasDataClassOld/MeasDataClass.cpp \
    01_DataProcessing/measmultivector.cpp \
    01_DataProcessing/primarydaraproc.cpp \
    02_SpectralTransforms/spectraltransforms.cpp \
    03_HardwareConnection/opu.cpp \
    03_HardwareConnection/tcpsocket.cpp \
    03_HardwareConnection/vna.cpp \
    classforstoringqlineseries.cpp \
    common.cpp \
    custommeasurementtreewidget.cpp \
    customprocessingtreewidget.cpp \
    errorhandler.cpp \
    main.cpp \
    mainwindow.cpp \
    measurement.cpp \
    measurementsparameterswidget.cpp \
    measurmentscontrol.cpp \
    opu.cpp \
    plotclass.cpp \
    preandpostparameters.cpp \
    processimitation.cpp \
    #qcustomplot.cpp \
    referencercs.cpp \
    referencetarget.cpp \
    resultparameterswidget.cpp \
    selectionrectclass.cpp \
    socketvna.cpp \
    tabwidgetforcharts.cpp \
    tabwidgetforparameters.cpp \
    tabwidgetfortools.cpp \
    threedimensionalvector.cpp \
    treewidgetforfiles.cpp \
    widgetforcustomplot.cpp

HEADERS += \
    01_DataProcessing/MeasData.h \
    01_DataProcessing/MeasDataClass.h \
    01_DataProcessing/MeasDataClassOld/MeasDataClass.h \
    01_DataProcessing/measmultivector.h \
    01_DataProcessing/primarydaraproc.h \
    02_SpectralTransforms/alglib.h \
    02_SpectralTransforms/alglibinternal.h \
    02_SpectralTransforms/alglibmisc.h \
    02_SpectralTransforms/alglibwrap.h \
    02_SpectralTransforms/ap.h \
    02_SpectralTransforms/dataanalysis.h \
    02_SpectralTransforms/diffequations.h \
    02_SpectralTransforms/fasttransforms.h \
    02_SpectralTransforms/fftw3.h \
    02_SpectralTransforms/integration.h \
    02_SpectralTransforms/interpolation.h \
    02_SpectralTransforms/kernels_avx2.h \
    02_SpectralTransforms/kernels_fma.h \
    02_SpectralTransforms/kernels_sse2.h \
    02_SpectralTransforms/linalg.h \
    02_SpectralTransforms/optimization.h \
    02_SpectralTransforms/solvers.h \
    02_SpectralTransforms/specialfunctions.h \
    02_SpectralTransforms/spectraltransforms.h \
    03_HardwareConnection/opu.h \
    03_HardwareConnection/tcpsocket.h \
    03_HardwareConnection/vna.h \
    classforstoringqlineseries.h \
    common.h \
    custommeasurementtreewidget.h \
    customprocessingtreewidget.h \
    errorhandler.h \
    lib/qcustomplot.h \
    mainwindow.h \
    measurement.h \
    measurementsparameterswidget.h \
    measurmentscontrol.h \
    opu.h \
    plotclass.h \
    preandpostparameters.h \
    processimitation.h \
    #qcustomplot.h \
    referencercs.h \
    referencetarget.h \
    resultparameterswidget.h \
    selectionrectclass.h \
    socketvna.h \
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

#Для добавления QCustomplot как внешней библиотеки
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../QCustomPlot/release/ -lQCustomPlot
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../QCustomPlot/debug/ -lQCustomPlot

INCLUDEPATH += $$PWD/../QCustomPlot
DEPENDPATH += $$PWD/../QCustomPlot

DISTFILES += \
    dll/libfftw3-3.dll \
    dll/libfftw3f-3.dll \
    dll/libfftw3l-3.dll \
    lib/libAlgLib.a \
    lib/libuntitled3.a
