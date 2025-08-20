#include "mainwindow.h"
#include "ui_mainwindow.h"



//#include <QScreen>
//#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ChangeLanguageToRussian(); // Меняет язык на русский

    SetUpGeneralStyle(); // Устанавливает общее оформление

    SetUpMeasControlAndTimer(); // Инициирует класс управления измерениями и таймер

    FillMainWindow(); // Заполняет главное окно виджетами

    SetUpConnections(); // Устанавливает соединения между частями программы
}


MainWindow::~MainWindow()
{
    Timer->stop();
    delete ui;
}


void MainWindow::ShowErrorMessage(QString Description, QString Advice) // Добавить сюда отправку в легенду
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
    // Действия из меню
    connect(SaveFileAction,                     &QAction::triggered, this, &MainWindow::OnSaveAsActionTriggered);
    connect(MeasureAzTargetAction,              &QAction::triggered, this, &MainWindow::OnMeasureAzTargetActionTriggered);
    connect(MeasureResponseAtSingleAnglAction,  &QAction::triggered, this, &MainWindow::OnMeasureResponseAtSingleAnglActionTriggered);
    connect(MeasureBckgndAtSingleAnglAction,    &QAction::triggered, this, &MainWindow::OnMeasureBckgndAtSingleAnglActionTriggered);
    connect(MeasureCurrentAspectAction,         &QAction::triggered, this, &MainWindow::OnMeasureCurrentAspectActionTriggered);
    connect(AbortAction,                        &QAction::triggered, this, &MainWindow::OnAbortActionTriggered);

    connect(PaintPlotsAction,&QAction::triggered, this, &MainWindow::PaintAllPlots);

    // Перевод
    connect(SetRussianLanguageAction,&QAction::triggered, this, &MainWindow::ChangeLanguageToRussian);
    connect(SetEnglishLanguageAction,&QAction::triggered, this, &MainWindow::ChangeLanguageToEnglish);


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



    MenuProcess = menuBar()->addMenu(tr("Process"));
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

void MainWindow::OnSaveAsActionTriggered()
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

void MainWindow::OnMeasureAzTargetActionTriggered()
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

void MainWindow::OnMeasureResponseAtSingleAnglActionTriggered()
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

void MainWindow::OnMeasureBckgndAtSingleAnglActionTriggered()
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

void MainWindow::OnMeasureCurrentAspectActionTriggered()
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

void MainWindow::OnAbortActionTriggered()
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
    int NumberOfPlots = ChartTab->PlotTabs.size();

    for (int i=0;i<NumberOfPlots;i++)
    {
        if (ChartTab->PlotTabs[i]->customPlot->graphCount() == 0)
            ChartTab->PlotTabs[0]->customPlot->addGraph();
    }

    QComplexVector CASweepVector = MeasData.ReadSweepFrom(MeasDataClass::MeasDataType::CurrentAspect);
    QDoubleVector CASweepVector_abs(CASweepVector.size());
    for (int i = 0; i < CASweepVector.size(); i++)  {CASweepVector_abs[i] = std::abs(CASweepVector[i]);}

    QComplexVector RTSweepVector = MeasData.ReadSweepFrom(MeasDataClass::MeasDataType::RawTarget);
    QDoubleVector RTSweepVector_abs(RTSweepVector.size());
    for (int i = 0; i < RTSweepVector.size(); i++)  {RTSweepVector_abs[i] = std::abs(RTSweepVector[i]);}
    QVector<double> XRT = MeasData.GetFreqVectorGHz();

    QComplexVector RBSweepVector = MeasData.ReadSweepFrom(MeasDataClass::MeasDataType::RawBcknd);
    QDoubleVector RBSweepVector_abs(RBSweepVector.size());
    for (int i = 0; i < RBSweepVector.size(); i++)  {RBSweepVector_abs[i] = std::abs(RBSweepVector[i]);}
    QVector<double> XRB = MeasData.GetFreqVectorGHz();

    QComplexVector RRSweepVector = MeasData.ReadSweepFrom(MeasDataClass::MeasDataType::RawRsp);
    QDoubleVector RRSweepVector_abs(RRSweepVector.size());
    for (int i = 0; i < RRSweepVector.size(); i++)  {RRSweepVector_abs[i] = std::abs(RRSweepVector[i]);}
    QVector<double> XRR = MeasData.GetFreqVectorGHz();

    QComplexVector ClbrSweepVector = MeasData.ReadSweepFrom(MeasDataClass::MeasDataType::CalibrationArr);
    QDoubleVector ClbrSweepVector_abs(ClbrSweepVector.size());
    for (int i = 0; i < ClbrSweepVector.size(); i++)  {ClbrSweepVector_abs[i] = std::abs(ClbrSweepVector[i]);}
    QVector<double> XClbr = MeasData.GetFreqVectorGHz();


    QComplexVector PttrnSweepVector = MeasData.ReadSweepFrom(MeasDataClass::MeasDataType::PatternArr);
    QDoubleVector PttrnSweepVector_abs(PttrnSweepVector.size());
    for (int i = 0; i < PttrnSweepVector.size(); i++)  {PttrnSweepVector_abs[i] = std::abs(PttrnSweepVector[i]);}

    QVector<double> FreqVector = MeasData.GetFreqVectorGHz();


    QDoubleVector DistVect = MeasData.GetDistVector();

    QDoubleVector CurrentProfRangeVector(DistVect.size());
    MeasData.GetAmplVectordB(MeasDataClass::MeasDataType::CurrentProfRange, CurrentProfRangeVector,0,0);
    ChartTab->PlotTabs[0]->customPlot->graph(0)->setData(DistVect, CurrentProfRangeVector);
    ChartTab->PlotTabs[0]->customPlot->graph(0)->setPen(QPen(Qt::red));

    QDoubleVector CurrentGatedProfRangeVector(DistVect.size());
    MeasData.GetAmplVectordB(MeasDataClass::MeasDataType::CurrentGatedProfRange, CurrentGatedProfRangeVector,0,0);
    ChartTab->PlotTabs[1]->customPlot->graph(0)->setData(DistVect, CurrentGatedProfRangeVector);
    ChartTab->PlotTabs[1]->customPlot->graph(0)->setPen(QPen(Qt::yellow));

    /*
    ChartTab->PlotTabs[0]->customPlot->graph(0)->setData(MeasData.GetFreqVectorGHz(), CASweepVector_abs);
    ChartTab->PlotTabs[0]->customPlot->graph(0)->setPen(QPen(Qt::yellow));

    ChartTab->PlotTabs[1]->customPlot->graph(0)->setData(MeasData.GetFreqVectorGHz(), RTSweepVector_abs);
    ChartTab->PlotTabs[1]->customPlot->graph(0)->setPen(QPen(Qt::yellow));
    */

    ChartTab->PlotTabs[2]->customPlot->graph(0)->setData(MeasData.GetFreqVectorGHz(), RBSweepVector_abs);
    ChartTab->PlotTabs[2]->customPlot->graph(0)->setPen(QPen(Qt::yellow));

    ChartTab->PlotTabs[3]->customPlot->graph(0)->setData(MeasData.GetFreqVectorGHz(), RRSweepVector_abs);
    ChartTab->PlotTabs[3]->customPlot->graph(0)->setPen(QPen(Qt::yellow));






    //ChartTab->PlotTabs[4]->customPlot->graph(0)->setData(MeasData.GetFreqVectorGHz(), ClbrSweepVector_abs);
    //ChartTab->PlotTabs[4]->customPlot->graph(0)->setPen(QPen(Qt::yellow));

    //ChartTab->PlotTabs[5]->customPlot->graph(0)->setData(MeasData.GetFreqVectorGHz(), PttrnSweepVector_abs);
    //ChartTab->PlotTabs[5]->customPlot->graph(0)->setPen(QPen(Qt::magenta));

    UpdatePlots();

    for (int i=0;i<NumberOfPlots;i++)
    {ChartTab->PlotTabs[i]->customPlot->ResetPlot();}


    TabOfTools->LegendTab->FillFirstRows(MeasData);


    /*
    ChartTab->PlotTabs[0]->customPlot->graph(4)->setData(RefTargetArrX, RefTargetArr);
    ChartTab->PlotTabs[0]->customPlot->graph(4)->setPen(QPen(Qt::cyan));
    */
}

void MainWindow::UpdatePlots()
{
    /*
    QDoubleVector CurrentAspectVector(MeasData.GetNFreqPoints());
    MeasData.GetAmplVectordB(MeasDataClass::MeasDataType::CurrentAspect, CurrentAspectVector,0,0);
    ChartTab->PlotTabs[6]->customPlot->graph(0)->setData(MeasData.GetFreqVectorGHz(), CurrentAspectVector);
    ChartTab->PlotTabs[6]->customPlot->graph(0)->setPen(QPen(Qt::blue));


    QDoubleVector DistVect = MeasData.GetDistVector();

    QDoubleVector CurrentProfRangeVector(DistVect.size());
    MeasData.GetAmplVectordB(MeasDataClass::MeasDataType::CurrentProfRange, CurrentProfRangeVector,0,0);
    ChartTab->PlotTabs[7]->customPlot->graph(0)->setData(DistVect, CurrentProfRangeVector);
    ChartTab->PlotTabs[7]->customPlot->graph(0)->setPen(QPen(Qt::red));

    QDoubleVector CurrentGatedProfRangeVector(DistVect.size());
    MeasData.GetAmplVectordB(MeasDataClass::MeasDataType::CurrentGatedProfRange, CurrentGatedProfRangeVector,0,0);
    ChartTab->PlotTabs[7]->customPlot->graph(1)->setData(DistVect, CurrentGatedProfRangeVector);
    ChartTab->PlotTabs[7]->customPlot->graph(1)->setPen(QPen(Qt::yellow));


    ChartTab->PlotTabs[6]->customPlot->replot();
    ChartTab->PlotTabs[7]->customPlot->replot();

    if (true)
    {
        ChartTab->PlotTabs[6]->customPlot->ResetPlot();
        ChartTab->PlotTabs[7]->customPlot->ResetPlot();
        ResetPlotNeeded = false;
    }
    */
}

void MainWindow::UpdateAzimuthPlot(int iaz, int iel)
{
    /*
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
    */


    /* // Устаревшее
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

void MainWindow::PaintSomePlot(int TabID, LegendWidget::DataFromLegendRow LD)
{
    // Добавить рассмотрение случая Gated/ Не Gated????
    MeasDataClass::MeasDataType DType = DataTypeVector[TabID];
    PlotClass::ComplexInfo CompInfo = ChartTab->PlotTabs[TabID]->customPlot->ComplexDisplayMode;

    QString Title   = LD.Title;
    //int Data        = LD.Data;    // Ничего не делает
    int Plane       = LD.Plane;
    int Freq        = LD.Freq;
    int Az          = LD.Az;
    int El          = LD.El;
    //int Channel     = LD.Channel; // Ничего не делает
    //int Smooth      = LD.Smooth;  // Ничего не делает
    //int Percent     = LD.Percent; // Ничего не делает
    int Colour      = LD.Colour;

    QComplexVector YComplexData;
    QDoubleVector XData;
    QDoubleVector YData;

    switch (Plane)
    {
        case 0: // Частота
        {
            XData = MeasData.GetFreqVectorGHz();
            YComplexData = MeasData.ReadSweepFrom(DType, Az, El);
            break;
        }
        case 1: // Азимут
        {
            XData = MeasData.GetAzimuthVector();
            int AzPoints = MeasData.GetAzTrigPoints();
            YComplexData.resize(AzPoints);
            for (int az=0; az<AzPoints; az++)
            {
            YComplexData[az] = MeasData.ReadValueFrom(DType, Freq, az, El);
            }
            break;
        }
        case 2: // Подъём
        {
            XData = MeasData.GetElevationVector();
            int ElPoints = MeasData.GetElTrigPoints();
            YComplexData.resize(ElPoints);
            for (int el=0; el<ElPoints; el++)
            {
                YComplexData[el] = MeasData.ReadValueFrom(DType, Freq, Az, el);
            }
            break;
        }
        case 3: // Метры как отдельный случай рассмотрим пока (Тоже лучше сделать через enum?)
        {
            XData = MeasData.GetDistVector();
            int DistPoints = XData.size();
            YComplexData.resize(DistPoints);
            for (int m=0; m<DistPoints; m++)
            {
                YComplexData[m] = MeasData.ReadValueFrom(DType, m, Az, El);
            }
            break;
        }
    }


    YData.resize(YComplexData.size());

    switch (CompInfo)
    {
        case PlotClass::ComplexInfo::Amplitude:
        {
            for (int i=0; i<YData.size(); i++)
            {
                YData[i] = std::abs(YComplexData[i]);
            }
            break;
        }
        case PlotClass::ComplexInfo::Phase:
        {
            for (int i=0; i<YData.size(); i++)
            {
                YData[i] = std::arg(YComplexData[i]);
            }
            break;
        }
        case PlotClass::ComplexInfo::Real_Part:
        {
            for (int i=0; i<YData.size(); i++)
            {
                YData[i] = std::real(YComplexData[i]);
            }
            break;
        }
        case PlotClass::ComplexInfo::Imaginary_Part:
        {
            for (int i=0; i<YData.size(); i++)
            {
                YData[i] = std::imag(YComplexData[i]);
            }
            break;
        }
    }

    ChartTab->PlotTabs[TabID]->customPlot->graph(0)->setData(XData, YData);
    QColor PlotColour = TabOfTools->LegendTab->ColourVector[Colour];
    ChartTab->PlotTabs[TabID]->customPlot->graph(0)->setPen(QPen(PlotColour));
    ChartTab->PlotTabs[TabID]->customPlot->rescaleAxes(); // Всегда ли менять масштаб?
    ChartTab->PlotTabs[TabID]->customPlot->replot();

}

void MainWindow::changeEvent(QEvent *event) // Именно здесь меняется язык!!!
{

    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);

        // Смена языка в меню:
        MenuFile->setTitle(tr("File"));
        MenuFileWrite->setTitle(tr("Write"));
        MenuFileRead->setTitle(tr("Read"));
        MenuMeasure->setTitle(tr("Measure"));
        MenuProcess->setTitle(tr("Process"));
        MenuPost_Process->setTitle(tr("Post-Process"));
        MenuOptions->setTitle(tr("Options"));
        MenuCreatePylComp->setTitle(tr("Create Pylon Compensation"));
        MenuLanguage->setTitle(tr("Language"));

        // Смена языка в дочерних виджетах
        TabOfParameters->UpdateText();
        TabOfTools->UpdateText();
        ChartTab->UpdateText();

    }
    QWidget::changeEvent(event);
}

void MainWindow::ConnectLegendAndChartTabs()
{
    // Сигналы от легенды к главному окну MainWindow
    // Кнопки
    connect(TabOfTools->LegendTab, &LegendWidget::ReadDataSignal        , this, &MainWindow::OnReadDataSignalReceived);
    connect(TabOfTools->LegendTab, &LegendWidget::WriteDataSignal       , this, &MainWindow::OnWriteDataSignalReceived);
    connect(TabOfTools->LegendTab, &LegendWidget::AddLineSignal         , this, &MainWindow::OnAddLineSignalReceived);
    connect(TabOfTools->LegendTab, &LegendWidget::DeleteLineSignal      , this, &MainWindow::OnDeleteLineSignalReceived);
    connect(TabOfTools->LegendTab, &LegendWidget::ClearAllSignal        , this, &MainWindow::OnClearAllSignalReceived);
    connect(TabOfTools->LegendTab, &LegendWidget::UpLineSignal          , this, &MainWindow::OnUpLineSignalReceived);
    connect(TabOfTools->LegendTab, &LegendWidget::DownLineSignal        , this, &MainWindow::OnDownLineSignalReceived);
    connect(TabOfTools->LegendTab, &LegendWidget::CopyToMemoryLineSignal, this, &MainWindow::CopyToMemoryLineSignalReceived);
    connect(TabOfTools->LegendTab, &LegendWidget::RefreshSignal         , this, &MainWindow::RefreshSignalReceived);

    // Строки таблицы
    connect(TabOfTools->LegendTab, &LegendWidget::VisibilityCheckedSignal, this, &MainWindow::OnVisibilityCheckedSignalReceived);
    connect(TabOfTools->LegendTab, &LegendWidget::TitleChangedSignal, this, &MainWindow::OnTitleChangedSignalReceived);
    connect(TabOfTools->LegendTab, &LegendWidget::RedrawPlotSignal, this, &MainWindow::OnRedrawPlotSignalReceived);











    // Сигналы от вкладок графиков к легенде
    connect(ChartTab, &TabWidgetForCharts::SendCurrentPlotIndexToLegendSignal,TabOfTools->LegendTab, &LegendWidget::OnChartTabChanged);





}

QComplexVector MainWindow::Fill3DArrayFromMeasData(MeasDataClass::MeasDataType DType)
{
    QComplexVector FilledArray;

    int F_or_D_Num;
    if (DType == MeasDataClass::MeasDataType::CurrentProfRange or DType == MeasDataClass::MeasDataType::CurrentGatedProfRange)
    {
        F_or_D_Num =    MeasData.GetDistVector().size();
    }
    else
    {
        F_or_D_Num =    MeasData.GetNFreqPoints();
    }


    F_or_D_Num = MeasData.GetNFreqPoints();
    int ANum = MeasData.GetAzTrigPoints();
    int ENum = MeasData.GetElTrigPoints();

    for (int fd=0;fd<F_or_D_Num;fd++)
    {
        for (int a=0;a<ANum;a++)
        {
            for (int e=0;e<ENum;e++)
            {
                std::complex<double> Value = MeasData.ReadValueFrom(DType, fd, a, e);
                FilledArray.append(Value);
            }
        }
    }
    return FilledArray;
}



QComplexVector MainWindow::Fill1DArrayFromMeasDataForAnglePlane(MeasDataClass::MeasDataType DType, QString AnglePlane, int freq_or_dist, int another_angle)
{
    QComplexVector FilledArray;

    if (AnglePlane == "Az")
    {
        int ANum = MeasData.GetAzTrigPoints();
        for (int a=0; a < ANum; a++)
        {
            std::complex<double> Value = MeasData.ReadValueFrom(DType, freq_or_dist, a, another_angle);
            FilledArray.append(Value);
        }
    }

    if (AnglePlane == "El")
    {
        int ENum = MeasData.GetElTrigPoints();
        for (int e=0; e < ENum; e++)
        {
            std::complex<double> Value = MeasData.ReadValueFrom(DType, freq_or_dist, another_angle, e);
            FilledArray.append(Value);
        }
    }

    return FilledArray;
}














void MainWindow::FillMainWindow()
{
    FillMenu(); // Заполняет меню в верхней строке окна программы

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

    int NumberOfPlotTabs = ChartTab->PlotTabs.size();
    TabOfTools  ->LegendTab->SetNumberOfPlots(NumberOfPlotTabs);

    OutermostHorizontalSplitter->addWidget(TabOfParameters);

    centralWidget()->setLayout(MainLayout);
}

void MainWindow::SetUpMeasControlAndTimer()
{
    MeasControl = new MeasurmentsControl;
    connect(MeasControl,&MeasurmentsControl::updateGraph,this, &MainWindow::UpdateAzimuthPlot);

    Timer = new QTimer(this);
    connect(Timer, &QTimer::timeout, this, &MainWindow::UpdatePlots);

    //MeasThread = new QThread;
    //MeasControl->moveToThread(MeasThread);
    //MeasThread->start(QThread::TimeCriticalPriority);
}

void MainWindow::SetUpGeneralStyle()
{
    ui->setupUi(this);

    QFont Font("Arial", 12); // Был QFont(Segoe UI,9,-1,5,400,0,0,0,0,0,0,0,0,0,0,1)
    QApplication::setFont(Font);

    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint | Qt::WindowMinMaxButtonsHint);
    setWindowState(Qt::WindowMaximized);

    /*
    setStyleSheet("QWidget {"  // Добавить только где надо
                  "border-style: outset;"
                  "border-width: 2px;"
                  "border-color: gray"
                  "}");
    */
}

void MainWindow::SetUpConnections()
{
    ConnectMenu();
    ConnectLegendAndChartTabs();
    ConnectMessages();
    ConnectDebugMessages();
}

void MainWindow::ConnectMessages()
{

}

void MainWindow::ConnectDebugMessages()
{

}

void MainWindow::OnReadDataSignalReceived()
{

}

void MainWindow::OnWriteDataSignalReceived()
{

}

void MainWindow::OnAddLineSignalReceived()
{

}

void MainWindow::OnDeleteLineSignalReceived()
{

}

void MainWindow::OnClearAllSignalReceived()
{

}

void MainWindow::OnUpLineSignalReceived()
{

}

void MainWindow::OnDownLineSignalReceived()
{

}

void MainWindow::CopyToMemoryLineSignalReceived()
{

}

void MainWindow::RefreshSignalReceived()
{

}










void MainWindow::OnVisibilityCheckedSignalReceived  (int TabId, int GraphId, bool Visible)
{
    ChartTab->PlotTabs[TabId]->customPlot->graph(GraphId)->setVisible(Visible);
}

void MainWindow::OnTitleChangedSignalReceived       (int TabId, int GraphId, QString Title)
{
    // Должна быть смена легенды на графике
    // ChartTab->PlotTabs[TabId]->customPlot->legend;//graph(GraphId)->();

}

void MainWindow::OnRedrawPlotSignalReceived         (int TabId, int GraphId,
                                    MeasDataClass::MeasDataType DataType,
                                    QString Plane,
                                    int Frequency,
                                    int Azimuth,
                                    int Elevation,
                                    int Distance,
                                    QColor Colour
)
{
    QDoubleVector XVector;
    QDoubleVector YVector;
    bool PlotIsLogarithmic;
    PlotIsLogarithmic = ChartTab->PlotTabs[TabId]->YLogScaleButton->isChecked();

    if (Plane == "Dist")
    {
        if (DataType == MeasDataClass::MeasDataType::CurrentProfRange or DataType == MeasDataClass::MeasDataType::CurrentGatedProfRange)
        {
            XVector = MeasData.GetDistVector();

            if (PlotIsLogarithmic)
            {MeasData.GetAmplVectordB(DataType, YVector, Azimuth, Elevation);}
            else
            {MeasData.GetAmplVectorSqrt(DataType, YVector, Azimuth, Elevation);}
        }
        else
        {
            qDebug()<< "Тип данных не соответствует оси";
        }
    }

    if (Plane == "Freq")
    {
        if (DataType != MeasDataClass::MeasDataType::CurrentProfRange and DataType != MeasDataClass::MeasDataType::CurrentGatedProfRange)
        {
            XVector = MeasData.GetFreqVectorGHz();

            if (PlotIsLogarithmic)
                MeasData.GetAmplVectordB(DataType, YVector, Azimuth, Elevation);
            else
                MeasData.GetAmplVectorSqrt(DataType, YVector, Azimuth, Elevation);
        }
        else
        {
            qDebug()<< "Тип данных не соответствует оси";
        }
    }

    if (Plane == "Az")
    {

        XVector = MeasData.GetAzimuthVector();

        int freq_or_dist;
        if (DataType == MeasDataClass::MeasDataType::CurrentProfRange or DataType == MeasDataClass::MeasDataType::CurrentGatedProfRange)
        {
            freq_or_dist = Distance;
        }
        else
        {
            freq_or_dist = Frequency;
        }

        QComplexVector PreYVector = Fill1DArrayFromMeasDataForAnglePlane(DataType, Plane, freq_or_dist, Elevation);

        if (PlotIsLogarithmic)
        {
            for (int a=0; a<PreYVector.size(); a++)
            {
                double real = PreYVector[a].real();
                double imag = PreYVector[a].imag();
                YVector.append(log10(real*real + imag*imag)*10);
            }
        }
        else
        {
            for (int a=0; a<PreYVector.size(); a++)
            {
                double real = PreYVector[a].real();
                double imag = PreYVector[a].imag();
                YVector.append(sqrt(real*real + imag*imag));
            }
        }
    }

    if (Plane == "El")
    {

        XVector = MeasData.GetElevationVector();

        int freq_or_dist;
        if (DataType == MeasDataClass::MeasDataType::CurrentProfRange or DataType == MeasDataClass::MeasDataType::CurrentGatedProfRange)
        {
            freq_or_dist = Distance;
        }
        else
        {
            freq_or_dist = Frequency;
        }

        QComplexVector PreYVector = Fill1DArrayFromMeasDataForAnglePlane(DataType, Plane, freq_or_dist, Azimuth);

        if (PlotIsLogarithmic)
        {
            for (int e=0; e<PreYVector.size(); e++)
            {
                double real = PreYVector[e].real();
                double imag = PreYVector[e].imag();
                YVector.append(log10(real*real + imag*imag)*10);
            }
        }
        else
        {
            for (int e=0; e<PreYVector.size(); e++)
            {
                double real = PreYVector[e].real();
                double imag = PreYVector[e].imag();
                YVector.append(sqrt(real*real + imag*imag));
            }
        }
    }

    ChartTab->PlotTabs[TabId]->customPlot->graph(GraphId)->setData(XVector, YVector);
    ChartTab->PlotTabs[TabId]->customPlot->graph(GraphId)->setPen(QPen(Qt::yellow));
    ChartTab->PlotTabs[TabId]->customPlot->ResetPlot();


}
















// Дальше устаревшие функции
/*
void MainWindow::GetPlotFromDat() // Куда его строить?
{
    //WidgetForCustomPlot * NewPlotWidget = new WidgetForCustomPlot;
    //this->ChartTab->addTab(NewPlotWidget,"Загружено");
    //NewPlotWidget->customPlot=;
}
*/
/*
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
*/
/*
    HKL hkl = GetKeyboardLayout(0);// Перевод сменой языка раскладки
    DWORD langId = LOWORD(hkl);
    char langCode[10];
    GetLocaleInfoA(langId, LOCALE_SISO639LANGNAME, langCode, sizeof(langCode));
    if (strcmp(langCode, "ru") == 0)
*/
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
