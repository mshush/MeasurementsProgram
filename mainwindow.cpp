#include "mainwindow.h"
#include "ui_mainwindow.h"



//#include <QScreen>
//#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    //this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint | Qt::WindowMinMaxButtonsHint);


    ui->setupUi(this);

    QFont Font("Segoe UI", 12); // Был QFont(Segoe UI,9,-1,5,400,0,0,0,0,0,0,0,0,0,0,1)
    QApplication::setFont(Font);

    /*
    setStyleSheet("QWidget {"  // Добавить только где надо
                  "border-style: outset;"
                  "border-width: 2px;"
                  "border-color: gray"
                  "}");
    */




    HKL hkl = GetKeyboardLayout(0);
    DWORD langId = LOWORD(hkl);
    char langCode[10];
    GetLocaleInfoA(langId, LOCALE_SISO639LANGNAME, langCode, sizeof(langCode));


    if (strcmp(langCode, "ru") == 0)
    {
        if (translator.load("C:/Users/HP/Documents/MeasurementsProgram/translation/MeasProg_ru.qm"))
        {
            qApp->installTranslator(&translator);
            QCoreApplication::installTranslator(&translator);
        }
        else
        {
            qDebug() << "Failed to load translation file For Russian";
        }
        ui->retranslateUi(this);
    }




    FillMenu();
    ConnectMenu();

    TabOfTools = new TabWidgetForTools;
    ChartTab = new TabWidgetForCharts;
    TabOfParameters = new TabWidgetForParameters;


    QLayout * MainLayout = new QVBoxLayout();
    QSplitter * OutermostHorizontalSplitter = new QSplitter(Qt::Horizontal, this);
    MainLayout->addWidget(OutermostHorizontalSplitter);

    QSplitter * LeftVerticalSplitter = new QSplitter(Qt::Vertical,this);
    OutermostHorizontalSplitter->addWidget(LeftVerticalSplitter);

    LeftVerticalSplitter->addWidget(ChartTab);
    LeftVerticalSplitter->addWidget(TabOfTools);

    ChartTab    ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    TabOfTools  ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    OutermostHorizontalSplitter->addWidget(TabOfParameters);

    centralWidget()->setLayout(MainLayout);


    MeasControl = new MeasurmentsControl;

    //MeasThread = new QThread;
    //MeasControl->moveToThread(MeasThread);
    //MeasThread->start(QThread::TimeCriticalPriority);



    //Timer = new QTimer(this);
    //connect(Timer, &QTimer::timeout, this, &MainWindow::UpdatePlots); // Куда-нибудь в другое место




    for (int i = 0; i < 1601; i++)  {X1601.push_back(i);}


    connect(MeasControl,&MeasurmentsControl::updateGraph,this, &MainWindow::UpdateAzimuthPlot);


    //VNATest = new TestVNA();



    this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint | Qt::WindowMinMaxButtonsHint);
    this->setWindowState(Qt::WindowMaximized);




}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::ShowErrorMessage(QString Description, QString Advice)
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setWindowTitle("Ошибка!");
    msgBox.setText(Description);
    msgBox.setInformativeText(Advice);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}





void MainWindow::ConnectMenu()
{
    connect(SaveFileAction,&QAction::triggered, this, &MainWindow::OnSaveAsActionPressed); // Что и как должно сохраняться?

    connect(MeasureAzTargetAction,&QAction::triggered, this, &MainWindow::OnMeasureAzTargetActionPressed);
    connect(MeasureResponseAtSingleAnglAction,&QAction::triggered, this, &MainWindow::OnMeasureResponseAtSingleAnglActionPressed);
    connect(MeasureBckgndAtSingleAnglAction,&QAction::triggered, this, &MainWindow::OnMeasureBckgndAtSingleAnglActionPressed);
    connect(MeasureCurrentAspectAction,&QAction::triggered, this, &MainWindow::OnMeasureCurrentAspectActionPressed);
    connect(AbortAction,&QAction::triggered, this, &MainWindow::OnAbortActionPressed);

    connect(this->PaintPlotsAction,&QAction::triggered, this, &MainWindow::PaintAllPlots);

    // Перевод
    connect(SetRussianLanguageAction,&QAction::triggered, this, &MainWindow::ChangeLanguageToRussian);
    connect(SetEnglishLanguageAction,&QAction::triggered, this, &MainWindow::ChangeLanguageToEnglish);
}




void MainWindow::GetPlotFromDat() // Куда его строить?
{
    //WidgetForCustomPlot * NewPlotWidget = new WidgetForCustomPlot;
    //this->ChartTab->addTab(NewPlotWidget,"Загружено");
    //NewPlotWidget->customPlot=;
}



void MainWindow::FillMenu()
{
    //File
    MenuFile = this->menuBar()->addMenu(tr("File"));
    SaveFileAction = new QAction(tr("Save as"));
    MenuFile->addAction(SaveFileAction);

    MenuFileWrite = new QMenu(tr("Write"), this);
    MenuFileWrite->addAction(tr("Sketch"));
    MenuFileWrite->addSeparator();
    MenuFileWrite->addAction(tr("Bkgnd Calibration"));
    MenuFileWrite->addAction(tr("Response Calibration"));
    MenuFileWrite->addSeparator();
    MenuFile->addMenu(MenuFileWrite);

    MenuFileRead = new QMenu(tr("Read"), this);
    MenuFileRead->addAction(tr("Sketch"));
    MenuFileRead->addSeparator();
    MenuFileRead->addAction(tr("Bkgnd Calibration"));
    MenuFileRead->addAction(tr("Response Calibration"));
    MenuFileRead->addSeparator();
    MenuFile->addMenu(MenuFileRead);
    MenuFile->addSeparator();
    MenuFile->addAction(tr("Change Database Folder"));
    MenuFile->addAction(tr("Print..."));
    MenuFile->addSeparator();
    MenuFile->addAction(tr("Exit"));



    MenuMeasure = new QMenu("Measure");
    menuBar()->addMenu(MenuMeasure);

    // Аринины функции

    MeasureAzTargetAction = new QAction("MeasureAzTarget");
    MeasureResponseAtSingleAnglAction = new QAction("MeasureResponseAtSingleAngl");
    MeasureBckgndAtSingleAnglAction = new QAction("MeasureBckgndAtSingleAngl");
    MeasureCurrentAspectAction = new QAction("MeasureCurrentAspect");
    AbortAction = new QAction("Abort");
    PaintPlotsAction = new QAction("PaintAllPlots");
    MenuMeasure->addAction(MeasureAzTargetAction);
    MenuMeasure->addAction(MeasureResponseAtSingleAnglAction);
    MenuMeasure->addAction(MeasureBckgndAtSingleAnglAction);
    MenuMeasure->addAction(MeasureCurrentAspectAction);
    MenuMeasure->addAction(AbortAction);
    //MenuMeasure->addAction(PaintPlotsAction);
    MenuMeasure->addSeparator();


    //Дальше меню как в старой проге
    MenuMeasure->addAction("Measure");
    MenuMeasure->addAction("Single Angle Bkgnd Measure");
    MenuMeasure->addAction("Measure Target");
    MenuMeasure->addSeparator();
    MenuMeasure->addAction("Measure Current Aspect");
    MenuMeasure->addSeparator();
    MenuMeasure->addAction("Single Angle Bkgnd Measure");
    MenuMeasure->addAction("Response Calibration");
    MenuMeasure->addSeparator();
    MenuMeasure->addSeparator();
    MenuMeasure->addAction("Abort");
    MenuMeasure->addSeparator();
    MenuMeasure->addAction("Bkgnd (Screen Open)");
    MenuMeasure->addAction("Bkgnd (Screen Closed)");
    MenuMeasure->addAction("Target (Screen Open)");
    MenuMeasure->addAction("Target (Screen Closed)");
    MenuMeasure->addAction("Calculate (Screen)");
    MenuMeasure->addAction("Use Background Calibration");
    MenuMeasure->addAction("Use Response Calibration");
    MenuMeasure->addSeparator();
    MenuMeasure->addAction("Use Reverse Direction");
    MenuMeasure->addSeparator();
    MenuMeasure->addAction("Use Average Bkgnd");
    MenuMeasure->addSeparator();
    MenuMeasure->addAction("Reset Bkgnd Cal");
    MenuMeasure->addAction("Reset Response Cal");



    MenuProcess = this->menuBar()->addMenu(QObject::tr("Process"));
    MenuProcess->addAction("Process");
    MenuProcess->addSeparator();
    MenuProcess->addAction("Swap Az/El");




    MenuPost_Process = this->menuBar()->addMenu(tr("Post-Process"));
    MenuPost_Process->addAction("Post-Process");
    MenuProcess->addSeparator();
    MenuPost_Process->addAction("Frequency-Azimuth");
    MenuPost_Process->addAction("Down-Range - Azimuth");
    MenuPost_Process->addAction("Frequency - Cross-Range");
    MenuPost_Process->addAction("ISAR");
    MenuProcess->addSeparator();
    MenuPost_Process->addAction("Create S-Files");
    MenuPost_Process->addAction("AutoCreate S-Files");
    MenuProcess->addSeparator();
    MenuProcess->addSeparator();
    MenuPost_Process->addAction("Use Pylon Compensation");
    MenuProcess->addSeparator();
    MenuPost_Process->addAction("Create Az-El File");


    MenuOptions = this->menuBar()->addMenu(tr("Options"));
    MenuOptions->addAction("Show Sketch");
    MenuProcess->addSeparator();
    MenuOptions->addAction("Delete Sketch");
    MenuProcess->addSeparator();
    MenuOptions->addAction("Auto Close Polygon");
    MenuProcess->addSeparator();
    MenuOptions->addAction("Flip Sketch");
    MenuOptions->addAction("ChangeSketchColourToGreen");
    MenuOptions->addAction("Rotate Sketch");
    MenuProcess->addSeparator();
    MenuOptions->addAction("Image Equal Scaling");
    MenuOptions->addAction("Reverse Sketch Rotation");
    MenuProcess->addSeparator();
    MenuProcess->addSeparator();
    MenuOptions->addAction("Move El Cut to Az Cut");


    MenuCreatePylComp = new QMenu(tr("Create Pylon Compensation"));
    menuBar()->addMenu(MenuCreatePylComp);

    MenuLanguage = new QMenu(tr("Language"));
    SetRussianLanguageAction = new QAction(tr("Russian"));
    SetEnglishLanguageAction = new QAction(tr("English"));
    MenuLanguage->addAction(SetRussianLanguageAction);
    MenuLanguage->addAction(SetEnglishLanguageAction);
    menuBar()->addMenu(MenuLanguage);
}



void MainWindow::SetAllVNAParamsFromInterface()
{

    double Pow       = TabOfParameters->MeasurementTab->PNAGeneratorEdit        ->text().toDouble(); // 10 -- слишком много
    double CenterFreq= TabOfParameters->MeasurementTab->FrequencyRangeCenterEdit->text().toDouble();
    double SpanFreq  = TabOfParameters->MeasurementTab->FrequencyRangeSpanEdit  ->text().toDouble();
    double StartFreq = CenterFreq - SpanFreq / 2;
    double StopFreq  = CenterFreq + SpanFreq / 2;
    int    NumOfPoi  = TabOfParameters->MeasurementTab->FrequencyRangeNEdit     ->text().toDouble();
    int    IF        = TabOfParameters->MeasurementTab->IFValues[TabOfParameters->MeasurementTab->PNAIFBox->currentIndex()] ;
    QString Datatype = "double";
    QString MeasParameter = "S21";

    qDebug()<< "Input Parameters: " << Pow<< StartFreq<< StopFreq<< NumOfPoi<< IF<< Datatype<< MeasParameter;
    try
    {
        MeasData.SetAllVNAParamsNoAction(Pow, StartFreq, StopFreq, NumOfPoi, IF, Datatype, MeasParameter);
        //MeasData.SetAllVNAParamsNoAction(0, 2.0, 4.0, 1601, 10000, "double", "S21");
    }
    catch(const std::exception& e)
    {
        std::cerr << "An error occurred in SetAllVNAParamsNoAction: " << e.what() << std::endl;
    }
    catch(...)
    {
        std::cerr << "An UNKNOWN error occurred in SetAllVNAParamsNoAction: " << std::endl;
    }
}





void MainWindow::SetAllOPUParamsFromInterface()
{
    double centerAzAngl = TabOfParameters->MeasurementTab->AzimuthRangeCenterEdit  ->text().toDouble();
    double spanAzAngl   = TabOfParameters->MeasurementTab->AzimuthRangeSpanEdit    ->text().toDouble();
    double startAzAngl  = centerAzAngl - spanAzAngl / 2;
    double stopAzAngl   = centerAzAngl + spanAzAngl / 2;

    // У Арины пока нет таких параметров, но в интерфейсе есть:
    //double centerElAngl= TabOfParameters->MeasurementTab->ElevationRangeCenterEdit->text().toDouble();
    //double spanElAngl  = TabOfParameters->MeasurementTab->ElevationRangeSpanEdit  ->text().toDouble();
    //double startElAngl = centerElAngl - spanElAngl / 2;
    //double stopElAngl  = centerElAngl + spanElAngl / 2;

    double startElAngl  = 0; //Пока без них
    double stopElAngl   = 0;

    int Speed           = TabOfParameters->MeasurementTab->AzimuthRangeCenterEdit  ->text().toInt();
    int AzTrigPoints    = 1601;
    int ElTrigPoints    = 1;
    QString MoveMode    = "CCW";


    try
    {
        MeasData.SetAllOPUParamsNoAction(startAzAngl, stopAzAngl, startElAngl, stopElAngl, Speed, AzTrigPoints, ElTrigPoints, MoveMode);
    }
    catch(const std::exception& e)
    {
        std::cerr << "An error occurred in SetAllVNAParamsNoAction: " << e.what() << std::endl;
    }
    catch(...)
    {
        std::cerr << "An UNKNOWN error occurred in SetAllVNAParamsNoAction: " << std::endl;
    }

}





void MainWindow::ChangeLanguageToRussian()
{
    if (translator.load("C:/Users/HP/Documents/MeasurementsProgram/translation/MeasProg_ru"))
    {
        qApp->installTranslator(&translator);
        QCoreApplication::installTranslator(&translator);
    }
    else
    {
        qDebug() << "Failed to load translation file For Russian";
    }
}



void MainWindow::ChangeLanguageToEnglish()
{
    qApp->removeTranslator(&translator);
    ui->retranslateUi(this);
}




void MainWindow::OnMeasureAzTargetActionPressed()
{
    SetAllOPUParamsFromInterface();
    SetAllVNAParamsFromInterface();

    Timer->start(100);
    ResetPlotNeeded = true;

    try
    {
        MeasControl->MeasureAzTarget(MeasData);
    }
    catch(const std::exception& e)
    {
        std::cerr << "An error occurred in SetAllVNAParamsNoAction: " << e.what() << std::endl;
    }
    catch(...)
    {
        std::cerr << "An UNKNOWN error occurred in SetAllVNAParamsNoAction: " << std::endl;
    }

}

void MainWindow::OnMeasureResponseAtSingleAnglActionPressed()
{
    SetAllOPUParamsFromInterface();
    SetAllVNAParamsFromInterface();

    try
    {
        MeasControl->MeasureResponseAtSignleAngl(MeasData); // Попросить Арину переименовать
    }
    catch(const std::exception& e)
    {
        std::cerr << "An error occurred in SetAllVNAParamsNoAction: " << e.what() << std::endl;
    }
    catch(...)
    {
        std::cerr << "An UNKNOWN error occurred in SetAllVNAParamsNoAction: " << std::endl;
    }
    PaintAllPlots();
}

void MainWindow::OnMeasureBckgndAtSingleAnglActionPressed()
{
    this->SetAllOPUParamsFromInterface();
    this->SetAllVNAParamsFromInterface();

    try
    {
        MeasControl->MeasureBckgndAtSingleAngl(MeasData);
    }
    catch(const std::exception& e)
    {
        std::cerr << "An error occurred in SetAllVNAParamsNoAction: " << e.what() << std::endl;
    }
    catch(...)
    {
        std::cerr << "An UNKNOWN error occurred in SetAllVNAParamsNoAction: " << std::endl;
    }
    PaintAllPlots();

}
void MainWindow::OnMeasureCurrentAspectActionPressed()
{
    this->SetAllOPUParamsFromInterface();
    this->SetAllVNAParamsFromInterface();
    try
    {
        MeasControl->MeasureCurrentAspect(MeasData);
    }
    catch(const std::exception& e)
    {
        std::cerr << "An error occurred in SetAllVNAParamsNoAction: " << e.what() << std::endl;
    }
    catch(...)
    {
        std::cerr << "An UNKNOWN error occurred in SetAllVNAParamsNoAction: " << std::endl;
    }
    PaintAllPlots();
}

void MainWindow::OnAbortActionPressed()
{
    try
    {
        this->MeasControl->Abort();
    }
    catch(const std::exception& e)
    {
        std::cerr << "An error occurred in SetAllVNAParamsNoAction: " << e.what() << std::endl;
    }
    catch(...)
    {
        std::cerr << "An UNKNOWN error occurred in SetAllVNAParamsNoAction: " << std::endl;
    }
    Timer->stop();
}

void MainWindow::PaintAllPlots()
{
    for (int i=0;i<8;i++)
    {ChartTab->PlotTabs[0]->customPlot->addGraph();}

    QComplexVector CASweepVector = MeasData.ReadSweepFrom(MeasDataClass::MeasDataType::CurrentAspect);
    QDoubleVector CASweepVector_abs(CASweepVector.size());
    for (int i = 0; i < CASweepVector.size(); i++)  {CASweepVector_abs[i] = std::abs(CASweepVector[i]);}
    QVector<double> XCA;
    for (int i = 0; i < CASweepVector.size(); ++i)  {XCA.push_back(i);}


    QComplexVector RTSweepVector = MeasData.ReadSweepFrom(MeasDataClass::MeasDataType::RawTarget);
    QDoubleVector RTSweepVector_abs(RTSweepVector.size());
    for (int i = 0; i < RTSweepVector.size(); i++)  {RTSweepVector_abs[i] = std::abs(RTSweepVector[i]);}
    QVector<double> XRT;
    for (int i = 0; i < RTSweepVector.size(); ++i)  {XRT.push_back(i);}

    QComplexVector RBSweepVector = MeasData.ReadSweepFrom(MeasDataClass::MeasDataType::RawBcknd);
    QDoubleVector RBSweepVector_abs(RBSweepVector.size());
    for (int i = 0; i < RBSweepVector.size(); i++)  {RBSweepVector_abs[i] = std::abs(RBSweepVector[i]);}
    QVector<double> XRB;
    for (int i = 0; i < RBSweepVector.size(); ++i)  {XRB.push_back(i);}

    QComplexVector RRSweepVector = MeasData.ReadSweepFrom(MeasDataClass::MeasDataType::RawRsp);
    QDoubleVector RRSweepVector_abs(RRSweepVector.size());
    for (int i = 0; i < RRSweepVector.size(); i++)  {RRSweepVector_abs[i] = std::abs(RRSweepVector[i]);}
    QVector<double> XRR;
    for (int i = 0; i < RRSweepVector.size(); ++i)  {XRR.push_back(i);}

    QComplexVector ClbrSweepVector = MeasData.ReadSweepFrom(MeasDataClass::MeasDataType::CalibrationArr);
    QDoubleVector ClbrSweepVector_abs(ClbrSweepVector.size());
    for (int i = 0; i < ClbrSweepVector.size(); i++)  {ClbrSweepVector_abs[i] = std::abs(ClbrSweepVector[i]);}
    QVector<double> XClbr;
    for (int i = 0; i < ClbrSweepVector.size(); ++i)  {XClbr.push_back(i);}


    QComplexVector PttrnSweepVector = MeasData.ReadSweepFrom(MeasDataClass::MeasDataType::PatternArr);
    QDoubleVector PttrnSweepVector_abs(PttrnSweepVector.size());
    for (int i = 0; i < PttrnSweepVector.size(); i++)  {PttrnSweepVector_abs[i] = std::abs(PttrnSweepVector[i]);}
    QVector<double> XPttrn;
    for (int i = 0; i < PttrnSweepVector.size(); ++i)  {XPttrn.push_back(i);}


    ChartTab->PlotTabs[0]->customPlot->graph(0)->setData(MeasData.GetFreqVectorGHz(), CASweepVector_abs);
    ChartTab->PlotTabs[0]->customPlot->graph(0)->setPen(QPen(Qt::red));

    ChartTab->PlotTabs[1]->customPlot->graph(0)->setData(MeasData.GetFreqVectorGHz(), RTSweepVector_abs);
    ChartTab->PlotTabs[1]->customPlot->graph(0)->setPen(QPen(Qt::yellow));

    ChartTab->PlotTabs[2]->customPlot->graph(0)->setData(MeasData.GetFreqVectorGHz(), RBSweepVector_abs);
    ChartTab->PlotTabs[2]->customPlot->graph(0)->setPen(QPen(Qt::blue));

    ChartTab->PlotTabs[3]->customPlot->graph(0)->setData(MeasData.GetFreqVectorGHz(), RRSweepVector_abs);
    ChartTab->PlotTabs[3]->customPlot->graph(0)->setPen(QPen(Qt::cyan));

    ChartTab->PlotTabs[4]->customPlot->graph(0)->setData(MeasData.GetFreqVectorGHz(), ClbrSweepVector_abs);
    ChartTab->PlotTabs[4]->customPlot->graph(0)->setPen(QPen(Qt::green));

    ChartTab->PlotTabs[5]->customPlot->graph(0)->setData(MeasData.GetFreqVectorGHz(), PttrnSweepVector_abs);
    ChartTab->PlotTabs[5]->customPlot->graph(0)->setPen(QPen(Qt::magenta));

    UpdatePlots();

    for (int i=0;i<8;i++)
    {ChartTab->PlotTabs[i]->customPlot->ResetPlot();}

    /*
    ChartTab->PlotTabs[0]->customPlot->graph(4)->setData(RefTargetArrX, RefTargetArr);
    ChartTab->PlotTabs[0]->customPlot->graph(4)->setPen(QPen(Qt::cyan));
    */
}





void MainWindow::UpdatePlots()
{

    QVector<double> XVect;
    for (int i = 0; i < 2048; i++)  {XVect.push_back(i);}

    QDoubleVector CurrentAspectVector(MeasData.GetNFreqPoints());
    MeasData.GetAmplVectordB(MeasDataClass::MeasDataType::CurrentAspect, CurrentAspectVector,0,0);
    ChartTab->PlotTabs[6]->customPlot->graph(0)->setData(MeasData.GetFreqVectorGHz(), CurrentAspectVector);
    ChartTab->PlotTabs[6]->customPlot->graph(0)->setPen(QPen(Qt::blue));

    QDoubleVector CurrentProfRangeVector(2048);
    MeasData.GetAmplVectordB(MeasDataClass::MeasDataType::CurrentProfRange, CurrentProfRangeVector,0,0);
    ChartTab->PlotTabs[7]->customPlot->graph(0)->setData(XVect, CurrentProfRangeVector);
    ChartTab->PlotTabs[7]->customPlot->graph(0)->setPen(QPen(Qt::red));

    QDoubleVector CurrentGatedProfRangeVector(2048);
    MeasData.GetAmplVectordB(MeasDataClass::MeasDataType::CurrentGatedProfRange, CurrentGatedProfRangeVector,0,0);
    ChartTab->PlotTabs[7]->customPlot->graph(1)->setData(XVect, CurrentGatedProfRangeVector);
    ChartTab->PlotTabs[7]->customPlot->graph(1)->setPen(QPen(Qt::yellow));


    ChartTab->PlotTabs[6]->customPlot->replot();
    ChartTab->PlotTabs[7]->customPlot->replot();

    if (true)
    {
        ChartTab->PlotTabs[6]->customPlot->ResetPlot();
        ChartTab->PlotTabs[7]->customPlot->ResetPlot();
        ResetPlotNeeded = false;
    }
}


void MainWindow::UpdateAzimuthPlot(int iaz, int iel)
{
    //Сделать так, чтобы не дёргалось
    UpdatePlots();

    double CurrentAmpl;
    int f = 0;
    CurrentAmpl =std::abs(MeasData.ReadValueFrom(MeasDataClass::MeasDataType::PatternArr,f, iaz,iel));

    //ChartTab->PlotTabs[8]->customPlot->xAxis->setRange(0,1601);
    //ChartTab->PlotTabs[8]->customPlot->ResetPlot();
    //QVector<double> XVect;
    //for (int i = 0; i < 1601; i++)  {XVect.push_back(i);}

    ChartTab->PlotTabs[8]->customPlot->graph(0)->addData(iaz,CurrentAmpl);
    //ChartTab->PlotTabs[8]->customPlot->graph(0)->setPen(QPen(Qt::blue));

    //ChartTab->PlotTabs[8]->customPlot->replot();
    //ChartTab->PlotTabs[8]->customPlot->xAxis->setRange(0,1601);
    ChartTab->PlotTabs[8]->customPlot->yAxis->rescale();

    /*
    QDoubleVector CurrentAspectVector(MeasData.GetAzTrigPoints());
    MeasData.GetAmplVectordB(MeasDataClass::MeasDataType::CurrentAspect, CurrentAspectVector,0,0);
    ChartTab->PlotTabs[8]->customPlot->graph(0)->setData(MeasData.GetAzimuthVector(), CurrentAspectVector);
    ChartTab->PlotTabs[8]->customPlot->graph(0)->setPen(QPen(Qt::blue));

    ChartTab->PlotTabs[8]->customPlot->replot();

    if (ResetPlotNeeded)
    {
        ChartTab->PlotTabs[8]->customPlot->ResetPlot();
        ResetPlotNeeded = false;
    }
    */




}
















void MainWindow::addRandomError(QDoubleVector& data, double mean, double sigma)
{

    std::random_device rd;
    std::mt19937 eng(rd());
    std::normal_distribution<> distr(mean, sigma);
    for (int i = 0; i < data.size(); ++i) {
        double error = distr(eng);
        data[i] += i + error;
    }
}






void MainWindow::OnSaveAsActionPressed()
{

    if (ChartTab->currentIndex() < ChartTab->PlotTabs.size())
    {
        ChartTab->PlotTabs[ChartTab->currentIndex()]->customPlot->SaveAs();
    }
    else
    {
        QMessageBox::warning(this, "Сохранение графика недоступно для вкладки предварительного просмотра", "Выберите вкладку с графиком");
    }
}



void MainWindow::changeEvent(QEvent *event)
{

    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
        MenuFile->setTitle(tr("File"));
        MenuFileWrite->setTitle(tr("Write"));
        MenuFileRead->setTitle(tr("Read"));
        MenuMeasure->setTitle(tr("Measure"));
        MenuProcess->setTitle(tr("Process"));
        MenuPost_Process->setTitle(tr("Post-Process"));
        MenuOptions->setTitle(tr("Options"));
        MenuCreatePylComp->setTitle(tr("Create Pylon Compensation"));
        MenuLanguage->setTitle(tr("Language"));
        //.....
    }
    QWidget::changeEvent(event);
}










































// Дальше устаревшие функции



/*
void MainWindow::SetCalibration()
{

    if (BackgroundFunction.VNAParameters.NumOfPoi==0)
    {
        emit ErrorOccured("mainwindow : Не найден фон.");
        //ShowErrorMessage("Не найден фон", "Сперва выберите фон");
        return;
    }
    if (CalibrationFunction.VNAParameters.NumOfPoi==0)
    {
        QFile File(TabOfParameters->ResultTab->CalibrationLineEdit->text());
        if (!File.open(QIODevice::ReadOnly))
        {
            emit ErrorOccured("mainwindow : Не удалось открыть файл для чтения.");
            //ShowErrorMessage("Не удалось открыть файл для чтения!", File.errorString());
            return;
        }

        QDataStream in(&File);
        in >> CalibrationFunction;
        File.close();
    }

    //CalibrationFunction.SubstractBackground(BackgroundFunction);

    int SampleTypeIndex = this->TabOfParameters->ResultTab->CalibrationSampleComboBox->currentIndex();

    //StoredFunction.Calibrate(CalibrationFunction,SampleTypeIndex);


    azim = StoredFunction.FindAzimuthIndex(TabOfParameters->ResultTab->SetCurrentAzimuthDoubleSpinBox->value());
    elev = StoredFunction.FindElevationIndex(TabOfParameters->ResultTab->SetCurrentElevationDoubleSpinBox->value());

    PlotClass * PltPtr = this->ChartTab->PlotTabs[0]->customPlot;
    //PltPtr->graph(0)->setData(StoredFunction.FreqVector(), StoredFunction.AmplitudeVectorAtAngles(azim,elev));
    PltPtr->rescaleAxes();
    PltPtr->replot();


    QFile File(TabOfParameters->ResultTab->BackgroundLineEdit->text());
    if (!File.open(QIODevice::ReadOnly)) {
        qWarning() << "Не получилось открыть файл для чтения: " << File.errorString();
        return;
    }


    QDataStream in(&File);
    in >> BackgroundFunction;
    File.close();



    QVector <double> x = BackgroundFunction.FreqVector();

    r = BackgroundFunction.FindAzimuthIndex(TabOfParameters->ResultTab->SetCurrentAzimuthDoubleSpinBox->value());
    t = BackgroundFunction.FindElevationIndex    (TabOfParameters->ResultTab->SetCurrentElevationDoubleSpinBox    ->value());

    QVector <std::complex<double>> f = BackgroundFunction.GetFrequencyVectorAt(r,t);

    QVector <double> y(BackgroundFunction.VNAParameters.NumOfPoi);

    for (int i=0;i<BackgroundFunction.VNAParameters.NumOfPoi;i++)
    {
        y[i] = abs(f[i]);
    }

    if (ChartTab->PlotTabs[0]->customPlot->graphCount()==1)
    {
        ChartTab->PlotTabs[0]->customPlot->addGraph();
    }

    ChartTab->PlotTabs[0]->customPlot->graph(1)->setData(x,y);

    ChartTab->PlotTabs[0]->customPlot->replot();
    """
}
*/





/*
void MainWindow::SaveThreeDimensionalVector()
{
    QString DateString = QDate::currentDate().toString("yyyy-MM-dd");
    QString TimeString = QTime::currentTime().toString("HH-mm");

    QString NameOfSavedFile = "Измерение_" + DateString + "_" + TimeString;

    QString Path = QDir::homePath() + "/" + NameOfSavedFile + ".dat";

    QString FilePath = QFileDialog::getSaveFileName(this, "Save File", Path, "Data Files (*.dat);;All Files (*)");

    QFile File(FilePath);
    if (!File.open(QIODevice::WriteOnly))
    {
        emit ErrorOccured("mainwindow : Не удалось открыть файл для записи.");
        //ShowErrorMessage("Не удалось открыть файл для записи!",File.errorString());
        return;
    }


    QDataStream out(&File);
    out << StoredFunction;
    File.close();
 }
*/











/*
void MainWindow::UpdateSweepGraphSlot(QDoubleVector SweepArrayAmpl) //От частоты
{
    //DoubleVector XVector = ChartTab->FrequencyTab->customPlot->KeyVector;
    int N = SweepArrayAmpl.size();
    QVector<double> XVector;
    for (int i=0;i<N;i++)
    {
        XVector.append(double(i));
    }
    this->ChartTab->SweepTab->customPlot->graph(0)->setData(XVector, SweepArrayAmpl);

    void ResetPlot();
}
void MainWindow::UpdateProfRangeSlot(QDoubleVector ProfRangeArrayAmpl) // От расстояния
{
    //DoubleVector XVector = ChartTab->FrequencyTab->customPlot->KeyVector;
    int N = ProfRangeArrayAmpl.size();
    QVector<double> XVector;
    for (int i=0;i<N;i++)
    {
        XVector.append(double(i));
    }
    this->ChartTab->ProfRangeTab->customPlot->graph(0)->setData(XVector, ProfRangeArrayAmpl);

    void ResetPlot();
}
void MainWindow::UpdateGatedProfileRangeSlot(QDoubleVector SweepArrayAmpl)// От расстояния
{
    //DoubleVector XVector = ChartTab->FrequencyTab->customPlot->KeyVector;
    int N = SweepArrayAmpl.size();
    QVector<double> XVector;
    for (int i=0;i<N;i++)
    {
        XVector.append(double(i));
    }
    this->ChartTab->GatedProfileTab->customPlot->graph(0)->setData(XVector, SweepArrayAmpl);

    void ResetPlot();
}











void MainWindow::UpdatePatternSlot(QDoubleVector DiagAnglArrayAmpl) // От угла
{
    //DoubleVector XVector = ChartTab->FrequencyTab->customPlot->KeyVector;
    int N = DiagAnglArrayAmpl.size();
    QVector<double> XVector;
    for (int i=0;i<N;i++)
    {
        XVector.append(double(i));
    }
    this->ChartTab->PatternTab->customPlot->graph(0)->setData(XVector, DiagAnglArrayAmpl);//Переименовать в Pattern

    void ResetPlot();
}
*/



/*
void MainWindow::SetThreeDimensionalVector(ThreeDimensionalVector F)
{

    StoredFunction = F;
    // !!! ПЕРЕДЕЛАТЬ !!!
    //azim = StoredFunction.FindAzimuthIndex   (TabOfParameters->ResultTab->SetCurrentAzimuthDoubleSpinBox    ->value());
    //elev = StoredFunction.FindElevationIndex (TabOfParameters->ResultTab->SetCurrentElevationDoubleSpinBox  ->value());

    //QVector <std::complex<double>> FreqVectorAtChosenAngle = F.GetFrequencyVectorAt(azim, elev);
    //this->ChartTab->UpdateMeasurementPlot(FreqVectorAtChosenAngle);

    auto start0 = std::chrono::system_clock::now();

    PlotClass * PltPtr0 = this->ChartTab->PlotTabs[0]->customPlot;
    PltPtr0->graph(0)->setData(F.FreqVector(), F.AmplitudeVectorAtAngles(azim,elev));
    PltPtr0->rescaleAxes();
    PltPtr0->replot();


    PlotClass * PltPtr1 = this->ChartTab->PlotTabs[1]->customPlot;
    PltPtr1->graph(0)->setData(F.AzimuthVector(), F.AmplitudeVectorAtFrequencyElevation(0,elev));
    PltPtr1->rescaleAxes();
    PltPtr1->replot();

    // Сделать ли зависимость от угла наклона?

    PlotClass * PltPtr2 = this->ChartTab->PlotTabs[2]->customPlot;
    PltPtr2->graph(0)->setData(F.DistVector(), F.FourierAmplVectorAtAngles(azim,elev));
    PltPtr2->rescaleAxes();
    PltPtr2->replot();

    auto end0 = std::chrono::system_clock::now();
    auto elapsed0 =  std::chrono::duration_cast<std::chrono::milliseconds>(end0 - start0);
    qDebug() << " Время отрисовки всех графиков " << elapsed0.count() << '\n';

}
*/
























/*
 void MainWindow::SetBackground()
 {
    // !!! Переделать !!!

    QFile File(TabOfParameters->ResultTab->BackgroundLineEdit->text());
    if (!File.open(QIODevice::ReadOnly))
    {
        emit ErrorOccured("mainwindow : Не удалось открыть файл для чтения");
        //ShowErrorMessage("Не удалось открыть файл для чтения!",File.errorString());
        return;
    }

    QDataStream in(&File);
    in >> BackgroundFunction;
    File.close();



    QVector <double> x = BackgroundFunction.FreqVector();

    // !!! Переделать !!!
    //azim = BackgroundFunction.FindAzimuthIndex(TabOfParameters->ResultTab->SetCurrentAzimuthDoubleSpinBox->value());
    //elev = BackgroundFunction.FindElevationIndex    (TabOfParameters->ResultTab->SetCurrentElevationDoubleSpinBox    ->value());

    QVector <std::complex<double>> f = BackgroundFunction.GetFrequencyVectorAt(azim,elev);

    QVector <double> y(BackgroundFunction.VNAParameters.NumOfPoi);

    for (int i=0;i<BackgroundFunction.VNAParameters.NumOfPoi;i++)
    {
        y[i] = abs(f[i]);
    }

    if (ChartTab->PlotTabs[0]->customPlot->graphCount()==1)
    {
        ChartTab->PlotTabs[0]->customPlot->AddEmptyGraphToPlot();
    }

    ChartTab->PlotTabs[0]->customPlot->graph(1)->setData(x,y);

    ChartTab->PlotTabs[0]->customPlot->replot();

 }


void MainWindow::SubstractBackground()
{
    // !!! Переделать !!!

    if (BackgroundFunction.ObjectMeasurementResult.size()==0)
    {
        QFile File(TabOfParameters->ResultTab->BackgroundLineEdit->text());
        if (!File.open(QIODevice::ReadOnly))
        {
             emit ErrorOccured("mainwindow : Не удалось открыть файл для чтения.");
            //ShowErrorMessage("Не удалось открыть файл для чтения!",File.errorString());
            return;
        }

        QDataStream in(&File);
        in >> BackgroundFunction;
        File.close();
    }

    PlotClass * PltPtr = this->ChartTab->PlotTabs[0]->customPlot;


    if (PltPtr->graph(0)->data()->size()>0)
    {
        //if (StoredFunction.CheckBackgroundForSuitability(BackgroundFunction) )
        {
            //StoredFunction.SubstractBackground(BackgroundFunction);
            PltPtr->graph(1)->data()->clear();
            this->SetThreeDimensionalVector(StoredFunction);
            //this->BackgroundFunction.ClearFunction(); // Не очищать! Ещё потребуется при калибровке
        }
        //else
        {
            emit ErrorOccured("mainwindow : Данные фона не подходят по формату.");
            ShowErrorMessage("Данные фона не подходят по формату!", "Убедитесь, что вы выбрали нужный файл");
            return;
        }
    }
    else
    {
        emit ErrorOccured("mainwindow : Нет данных.");
        //ShowErrorMessage("Нет данных!", "Убедитесь, что измеренные данные были получены");
        return;
    }

}
*/



















/*
void MainWindow::ConnectObjects()
{



    //connect(TabOfTools->StartMeasurementsButton, &QPushButton::clicked, Process, &ProcessImitation::Measure);
    //connect(TabOfTools->ContinuousMeasurementsButton, &QPushButton::clicked, ChartTab, &TabWidgetForCharts::ContinuousMeasurementModeChanged);
    //connect(TabOfTools->SaveDataButton  , &QPushButton::clicked, ChartTab, &TabWidgetForCharts::SaveData); // Получше придумать как соединять, чтобы по вкладкам (возможно лучше в QidgetForCustomPlot перенести)
    //connect(TabOfTools->SaveThreeDimensionalVectorButton  , &QPushButton::clicked, this, &MainWindow::SaveThreeDimensionalVector);
    //connect(TabOfTools->ImportDataButton, &QPushButton::clicked, ChartTab, &TabWidgetForCharts::CreateNewTabFromImportedData);
    //connect(TabOfParameters->MeasurementTab, &MeasurementsParametersWidget::FrequencyParametersChanged, ChartTab,&TabWidgetForCharts::SetFrequencyParameters);
    //connect(TabOfParameters->MeasurementTab, &MeasurementsParametersWidget::AngleParametersChanged,     ChartTab,&TabWidgetForCharts::SetAngleParameters); // Нужно ли()
    //connect(TabOfTools->FourierTransformButton,        &QPushButton::clicked, ChartTab, &TabWidgetForCharts::PerformFourierTransformOfCurrentPlot);
    //connect(TabOfTools->InverseFourierTransformButton, &QPushButton::clicked, ChartTab, &TabWidgetForCharts::PerformInverseFourierTransformOfCurrentPlot);
    //connect(TabOfParameters->ResultTab->SetCurrentAngleButton, &QPushButton::clicked, ChartTab, &TabWidgetForCharts::ChangeDemonstratedAngles);
    //connect(TabOfParameters->FileTreeTab, &TreeWidgetForFiles::FileWasChosenSignal, TabOfParameters->ResultTab, &ResultParametersWidget::FileChosenInTreeWidget);
    //connect(TabOfTools->GetPlotDataButton, &QPushButton::clicked, this, &MainWindow::GetPlotFromDat);
    //connect(TabOfParameters->ResultTab->CalculateDistancePortraitButton, &QPushButton::clicked, this, &MainWindow::CalculateDistancePortrait);



    //connect(Process, &ProcessImitation::MeasurementFinished, this, &MainWindow::SetThreeDimensionalVector);

    //connect(TabOfTools, &TabWidgetForTools::ContinuousMeasurementsButtonClickedSignal, Process,                           &ProcessImitation::MeasureContinuously);
    //connect(TabOfTools, &TabWidgetForTools::ContinuousMeasurementsButtonClickedSignal, ChartTab->PlotTabs[0]->customPlot, &PlotClass::ContinuousMeasurementsModeChanged);
    // Такой же connect для PlotTabs[1]???? Или наоборот только для углов?

    //!!!ПЕРЕДЕЛАТЬ!!!
    //connect(TabOfParameters->MeasurementTab, &MeasurementsParametersWidget::FrequencyParametersChanged, Process, &ProcessImitation::SetFrequencyRange);
    //connect(TabOfParameters->MeasurementTab, &MeasurementsParametersWidget::AngleParametersChanged,     Process, &ProcessImitation::SetAngleRanges);
    //connect(TabOfParameters->MeasurementTab, &MeasurementsParametersWidget::FrequencyParametersChanged, Process, &ProcessImitation::SetFrequencyRange);

    // !!! Переделать !!!
    //connect(TabOfParameters->ResultTab->SetCurrentAngleButton,      &QPushButton::clicked, this, &MainWindow::ChangeAngleOfDemonstration);
    //connect(TabOfParameters->ResultTab->BackgroundAddButton,        &QPushButton::clicked, this, &MainWindow::SetBackground);
    //connect(TabOfParameters->ResultTab->BackgroundSubstractButton,  &QPushButton::clicked, this, &MainWindow::SubstractBackground);
    //connect(TabOfParameters->ResultTab->CalibrationSetButton,       &QPushButton::clicked, this, &MainWindow::SetCalibration);


    //connect(Thread, &QThread::finished, Thread, &QThread::deleteLater); // Можно убрать

    //connect(Process, &ProcessImitation::IterationOfMeasurementFinished, this, &MainWindow::HandleReceivedMeasuredFreqVector);




    //Menu Actions: (Действия в меню сверху)
    //connect(SaveFileAction,     &QAction::triggered, ChartTab->PlotTabs[0]->customPlot, &PlotClass::SaveAs);
    //connect(OpenFileAction,     &QAction::triggered, ChartTab->PlotTabs[0]->customPlot, &PlotClass::OpenFile);
    //connect(StartMeasureAction, &QAction::triggered, Process ,                          &ProcessImitation::Measure);
    //connect(StopMeasureAction,  &QAction::triggered, Process ,                          &ProcessImitation::StopEverything);
    // Перенести функцию сохранения в другое место
    // Как осуществлять отдельно сохранение графика от угла?



    //Ошибки

    connect(this,                               &MainWindow                     ::ErrorOccured, TabOfTools, &TabWidgetForTools::DisplayError);
    connect(TabOfParameters->MeasurementTab,    &MeasurementsParametersWidget   ::ErrorOccured, TabOfTools, &TabWidgetForTools::DisplayError);
    connect(TabOfParameters->ResultTab,         &ResultParametersWidget         ::ErrorOccured, TabOfTools, &TabWidgetForTools::DisplayError);
    connect(this->ChartTab->PlotTabs[0],        &WidgetForCustomPlot            ::ErrorOccured, TabOfTools, &TabWidgetForTools::DisplayError);
    connect(this->ChartTab->PlotTabs[1],        &WidgetForCustomPlot            ::ErrorOccured, TabOfTools, &TabWidgetForTools::DisplayError);
    connect(this->ChartTab->PlotTabs[2],        &WidgetForCustomPlot            ::ErrorOccured, TabOfTools, &TabWidgetForTools::DisplayError);
    connect(ChartTab->PlotTabs[0]->customPlot,  &PlotClass                      ::ErrorOccured, TabOfTools, &TabWidgetForTools::DisplayError);
    connect(TabOfTools,                         &TabWidgetForTools              ::ErrorOccured, TabOfTools, &TabWidgetForTools::DisplayError);

}
*/


















/*
void MainWindow::HandleReceivedMeasuredFreqVector(QVector <double> ReceivedVector)
{

    PlotClass * PltPtr = ChartTab->PlotTabs[0]->customPlot;

    if (StoredFunction.CurrentIndex==0)
    {
        double FStart = TabOfParameters->MeasurementTab->FrequencyStart;
        double FStop = TabOfParameters->MeasurementTab->FrequencyStop;
        double FNum = TabOfParameters->MeasurementTab->FrequencyNumber;

        double AStart = TabOfParameters->MeasurementTab->AzimuthStart;
        double AStop = TabOfParameters->MeasurementTab->AzimuthStop;
        double ANum = TabOfParameters->MeasurementTab->AzimuthNumber;

        double EStart = TabOfParameters->MeasurementTab->ElevationStart;
        double EStop = TabOfParameters->MeasurementTab->ElevationStop;
        double ENum = TabOfParameters->MeasurementTab->ElevationNumber;


        StoredFunction.SetRanges(FStart,FStop, FNum,   AStart, AStop, ANum,   EStart, EStop, ENum);

        CurrentPlotIndex=0;
    }

    //StoredFunction.AddMeasuredValues(ReceivedVector);


    int I = StoredFunction.CurrentIndex/2;
    int A = StoredFunction.OPUParameters.AzTrigPoints;
    int F = StoredFunction.VNAParameters.NumOfPoi;
    int e =  I / (A*F);
    int a = (I % (A*F)) / F;
    int f = (I % (A*F)) % F;
    //QVector<double> YVector = StoredFunction.AmplitudeVectorAtAngles(r,t);


    PlotClass * PltPtrAz = ChartTab->PlotTabs[1]->customPlot;

    //PltPtr  ->graph(0)->setData(StoredFunction.FreqVector()   , StoredFunction.AmplitudeVectorAtAngles(a,e));

    //PltPtrAz->graph(0)->setData(StoredFunction.AzimuthVector(), StoredFunction.AmplitudeVectorAtFrequencyElevation(f,e));

    qDebug()<<"Was Here!"<<PltPtrAz->graph(0)->data() ->dataRange();

}
*/


/*
void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    this->setWindowState(Qt::WindowMaximized);
}
*/




/*
// Нужно переделать!!!
void MainWindow::ChangeAngleOfDemonstration()
{
    PlotClass * PltPtr = this->ChartTab->PlotTabs[0]->customPlot;

    if (PltPtr->graph(0)->data()->size()>0)
    {
        // !!! Переделать !!!
        //azim = StoredFunction.FindAzimuthIndex(TabOfParameters->ResultTab->SetCurrentAzimuthDoubleSpinBox->value());
        //elev = StoredFunction.FindElevationIndex(TabOfParameters->ResultTab->SetCurrentElevationDoubleSpinBox->value());

        PltPtr->graph(0)->setData(StoredFunction.FreqVector(), StoredFunction.AmplitudeVectorAtAngles(azim,elev));


        //QVector <std::complex<double>> FreqVectorAtChosenAngle = StoredFunction.GetFrequencyVectorAt(r,t);
        //this->ChartTab->UpdateMeasurementPlot(FreqVectorAtChosenAngle);

        if (PltPtr->graph(1)->data()->size()>0)
        {
            //PltPtr->graph(1)->setData(BackgroundFunction.FreqVector(), BackgroundFunction.AmplitudeVectorAtAngles(azim,elev));

            //PlotClass * PltPtr1 = this->ChartTab->PlotTabs[1]->customPlot;
            //PltPtr1->graph(1)->setData(BackgroundFunction.DistVector(), BackgroundFunction.FourierAmplVectorAtAngles(azim,elev));

        }
        PltPtr->rescaleAxes();
        PltPtr->replot();

        PlotClass * PltPtr1 = this->ChartTab->PlotTabs[1]->customPlot;
        //PltPtr1->graph(0)->setData(StoredFunction.DistVector(), StoredFunction.FourierAmplVectorAtAngles(azim,elev));
        PltPtr1->rescaleAxes();
        PltPtr1->replot();

    }
    else
    {
        emit ErrorOccured("mainwindow : Измеренных данных не обнаружено.");
        //ShowErrorMessage("Измеренных данных не обнаружено!", "Убедитесь, что измерение прошло успешно");
    }
}
*/

