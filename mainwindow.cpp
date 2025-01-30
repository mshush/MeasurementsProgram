#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QScreen>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    //QLocale::setDefault(QLocale(QLocale::Russian, QLocale::Russia));



    //qputenv("QT_SCALE_FACTOR", "1.5");
    //QGuiApplication::setAttribute(Qt::AA_Use96Dpi);

    //QGuiApplication::setAttribute(Qt::AA_Use96Dpi); // Разобраться, что делает
    //qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "0");

    QFont Font("Segoe UI", 12); // Был QFont(Segoe UI,9,-1,5,400,0,0,0,0,0,0,0,0,0,0,1)
    QApplication::setFont(Font);

    ui->setupUi(this);


    FillMenu();



    Process = new ProcessImitation();

    Thread = new QThread(this);

    //Process->moveToThread(Thread);
    //Thread->start();


    //QVBoxLayout *OutermostVerticalLayout = new QVBoxLayout;

    TabOfTools = new TabWidgetForTools;
    //TabOfTools->resize(800,200);
    //TabOfTools->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    //OutermostVerticalLayout->addWidget(TabOfTools);

    //QHBoxLayout * MiddleHorizontalLayout = new QHBoxLayout;


    //QVBoxLayout * InnerVerticalLayout = new QVBoxLayout;

    ChartTab = new TabWidgetForCharts;
    //InnerVerticalLayout->addWidget(ChartTab);

    TabOfParameters = new TabWidgetForParameters;

    //QHBoxLayout * BottomHorizontalLayout = new QHBoxLayout;


    //MiddleHorizontalLayout->addWidget(TabOfParameters);
    //MiddleHorizontalLayout->addLayout(InnerVerticalLayout);

    //OutermostVerticalLayout->addLayout(MiddleHorizontalLayout);
    //OutermostVerticalLayout->addLayout(BottomHorizontalLayout);

    //ProgressBar = new QProgressBar(this);
    //OutermostVerticalLayout->addWidget(ProgressBar);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    QHBoxLayout * OutermostHorizontalLayout = new QHBoxLayout(this);
    QVBoxLayout * LeftVerticalLayout = new QVBoxLayout(this);
    OutermostHorizontalLayout->addLayout(LeftVerticalLayout);

    LeftVerticalLayout->addWidget(ChartTab);
    LeftVerticalLayout->addWidget(TabOfTools);

    OutermostHorizontalLayout->addWidget(TabOfParameters);

    centralWidget()->setLayout(OutermostHorizontalLayout);
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    QLayout * MainLayout = new QVBoxLayout(); // Задавать абстрактным лучше или хуже?
    QSplitter * OutermostHorizontalSplitter = new QSplitter(Qt::Horizontal, this);
    MainLayout->addWidget(OutermostHorizontalSplitter);

    QSplitter * LeftVerticalSplitter = new QSplitter(Qt::Vertical,this);
    OutermostHorizontalSplitter->addWidget(LeftVerticalSplitter);

    LeftVerticalSplitter->addWidget(ChartTab);
    LeftVerticalSplitter->addWidget(TabOfTools);

    ChartTab    ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    TabOfTools  ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    OutermostHorizontalSplitter->addWidget(TabOfParameters);

    centralWidget()->setLayout(MainLayout);




    //this->resize(2560,1440); Не работает
    //QScreen *screen = QGuiApplication::primaryScreen();
    //screen->setProperty("QT_SCREEN_SCALE_FACTOR", "0");
    //qreal devicePixelRatio = screen->devicePixelRatio();


    ConnectObjects();

    this->setWindowState(Qt::WindowMaximized);
    //this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);


    qDebug()<<this->size();
}




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




 void MainWindow::SetBackground()
 {
    // !!! Переделать !!!
    /*
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
    */
 }


void MainWindow::SubstractBackground()
{
    // !!! Переделать !!!
    /*
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
    */
}


MainWindow::~MainWindow()
{

    Thread->quit();
    Thread->wait();
    Thread->deleteLater();
    Process->deleteLater();

    delete ui;
}


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


    """
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



void MainWindow::ConnectObjects()
{
    /*
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
    //connect(Process, &ProcessImitation::ProgressSignal, this->ProgressBar, &QProgressBar::setValue);
    //connect(TabOfParameters->FileTreeTab, &TreeWidgetForFiles::FileWasChosenSignal, TabOfParameters->ResultTab, &ResultParametersWidget::FileChosenInTreeWidget);
    //connect(TabOfTools->GetPlotDataButton, &QPushButton::clicked, this, &MainWindow::GetPlotFromDat);
    //connect(TabOfParameters->ResultTab->CalculateDistancePortraitButton, &QPushButton::clicked, this, &MainWindow::CalculateDistancePortrait);



    connect(Process, &ProcessImitation::MeasurementFinished, this, &MainWindow::SetThreeDimensionalVector);

    connect(TabOfTools, &TabWidgetForTools::ContinuousMeasurementsButtonClickedSignal, Process,                           &ProcessImitation::MeasureContinuously);
    connect(TabOfTools, &TabWidgetForTools::ContinuousMeasurementsButtonClickedSignal, ChartTab->PlotTabs[0]->customPlot, &PlotClass::ContinuousMeasurementsModeChanged);
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


    connect(Thread, &QThread::finished, Thread, &QThread::deleteLater); // Можно убрать

    connect(Process, &ProcessImitation::IterationOfMeasurementFinished, this, &MainWindow::HandleReceivedMeasuredFreqVector);




    //Menu Actions: (Действия в меню сверху)
    connect(SaveFileAction,     &QAction::triggered, ChartTab->PlotTabs[0]->customPlot, &PlotClass::SaveAs);
    connect(OpenFileAction,     &QAction::triggered, ChartTab->PlotTabs[0]->customPlot, &PlotClass::OpenFile);
    connect(StartMeasureAction, &QAction::triggered, Process ,                          &ProcessImitation::Measure);
    connect(StopMeasureAction,  &QAction::triggered, Process ,                          &ProcessImitation::StopEverything);
    // Перенести функцию сохранения в другое место
    // Как осуществлять отдельно сохранение графика от угла?

    */

    //Ошибки
    /*
    connect(this,                               &MainWindow                     ::ErrorOccured, TabOfTools, &TabWidgetForTools::DisplayError);
    connect(TabOfParameters->MeasurementTab,    &MeasurementsParametersWidget   ::ErrorOccured, TabOfTools, &TabWidgetForTools::DisplayError);
    connect(TabOfParameters->ResultTab,         &ResultParametersWidget         ::ErrorOccured, TabOfTools, &TabWidgetForTools::DisplayError);
    connect(this->ChartTab->PlotTabs[0],        &WidgetForCustomPlot            ::ErrorOccured, TabOfTools, &TabWidgetForTools::DisplayError);
    connect(this->ChartTab->PlotTabs[1],        &WidgetForCustomPlot            ::ErrorOccured, TabOfTools, &TabWidgetForTools::DisplayError);
    connect(this->ChartTab->PlotTabs[2],        &WidgetForCustomPlot            ::ErrorOccured, TabOfTools, &TabWidgetForTools::DisplayError);
    connect(ChartTab->PlotTabs[0]->customPlot,  &PlotClass                      ::ErrorOccured, TabOfTools, &TabWidgetForTools::DisplayError);
    connect(TabOfTools,                         &TabWidgetForTools              ::ErrorOccured, TabOfTools, &TabWidgetForTools::DisplayError);
    */
}



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







    /*
    if (r==StoredFunction.RNum-1 and t==StoredFunction.TNum-1) // Через CurrentIndex
    {
        //Сохранить, и занулить, чтобы начать следующую
        SaveThreeDimensionalVector();
        StoredFunction.ClearFunction();
    }
    */


}




void MainWindow::GetPlotFromDat()
{
    WidgetForCustomPlot * NewPlotWidget = new WidgetForCustomPlot;
    this->ChartTab->addTab(NewPlotWidget,"Загружено");
    //NewPlotWidget->customPlot=;
}





/*
void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    this->setWindowState(Qt::WindowMaximized);
}
*/



void MainWindow::FillMenu()
{

    //File
    QMenu * MenuFile = this->menuBar()->addMenu("File");

    QMenu * MenuFileWrite = new QMenu("Write", this);
    MenuFileWrite->addAction("Sketch");
    MenuFileWrite->addSeparator();
    MenuFileWrite->addAction("Bkgnd Calibration");
    MenuFileWrite->addAction("Response Calibration");
    MenuFileWrite->addSeparator();
    MenuFile->addMenu(MenuFileWrite);
    QMenu * MenuFileRead = new QMenu("Read", this);
    MenuFileRead->addAction("Sketch");
    MenuFileRead->addSeparator();
    MenuFileRead->addAction("Bkgnd Calibration");
    MenuFileRead->addAction("Response Calibration");
    MenuFileRead->addSeparator();
    MenuFile->addMenu(MenuFileRead);
    MenuFile->addSeparator();
    MenuFile->addAction("Change Database Folder");
    MenuFile->addAction("Print...");
    MenuFile->addSeparator();
    MenuFile->addAction("Exit");
    //Удалить --------------------
    /*
    SaveFileAction = new QAction("Save as...", this);
    OpenFileAction = new QAction("Load", this);
    MenuFile->addAction(SaveFileAction);
    MenuFile->addAction(OpenFileAction);
    */
    //Удалить --------------------









    QMenu * MenuMeasure = this->menuBar()->addMenu("Measure");
    MenuMeasure->addAction("Measure");
    MenuMeasure->addAction("Measure Current Aspect");
    MenuMeasure->addSeparator();
    MenuMeasure->addAction("Single Angle Bkgnd Calibration");
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
    //Удалить --------------------
    /*
    StartMeasureAction = new QAction("Start",       this);
    StopMeasureAction  = new QAction("Stop" ,       this);
    MeasureBackground  = new QAction("Background",  this);
    MeasureCalibration = new QAction("Calibration", this);

    MenuMeasure->addAction(StartMeasureAction);
    MenuMeasure->addAction(StopMeasureAction);
    MenuMeasure->addAction(MeasureBackground);
    MenuMeasure->addAction(MeasureCalibration);
    */
    //Удалить --------------------




    QMenu * MenuProcess = this->menuBar()->addMenu("Process");
    MenuProcess->addAction("Process");
    MenuProcess->addSeparator();
    MenuProcess->addAction("Swap Az/El");



    QMenu * MenuPost_Process = this->menuBar()->addMenu("Post-Process");
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


    QMenu * MenuOptions = this->menuBar()->addMenu("Post-Process");
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


    this->menuBar()->addMenu("Create Pylon Compensation");

}
