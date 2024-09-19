#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QScreen>

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


    this->menuBar()->addMenu("File");
    this->menuBar()->addMenu("Measure");
    this->menuBar()->addMenu("Process");
    this->menuBar()->addMenu("Post-Process");
    this->menuBar()->addMenu("Create Pylon Compensation");


    Process = new ProcessImitation();

    Thread = new QThread(this);

    Process->moveToThread(Thread);
    Thread->start();


    //QVBoxLayout *OutermostVerticalLayout = new QVBoxLayout;

    TabOfTools = new TabWidgetForTools;
    TabOfTools->resize(800,200);
    TabOfTools->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
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

    OutermostHorizontalSplitter->addWidget(TabOfParameters);

    centralWidget()->setLayout(MainLayout);




    //this->resize(2560,1440); Не работает
    //QScreen *screen = QGuiApplication::primaryScreen();
    //screen->setProperty("QT_SCREEN_SCALE_FACTOR", "0");
    //qreal devicePixelRatio = screen->devicePixelRatio();


    ConnectObjects();

    this->setWindowState(Qt::WindowMaximized);
}




void MainWindow::SetMeasuredFunction(MeasuredFunction F)
{

    StoredFunction = F;
    // Сделать double сдесь, а округление потом?
    r = StoredFunction.FindRotationIndex(TabOfParameters->ResultTab->SetCurrentRotationAngleDoubleSpinBox->value());
    t = StoredFunction.FindTiltIndex    (TabOfParameters->ResultTab->SetCurrentTiltAngleDoubleSpinBox    ->value());

    //QVector <std::complex<double>> FreqVectorAtChosenAngle = F.GetFrequencyVectorAt(r,t);
    //this->ChartTab->UpdateMeasurementPlot(FreqVectorAtChosenAngle);

    PlotClass * PltPtr0 = this->ChartTab->PlotTabs[0]->customPlot;
    PltPtr0->graph(0)->setData(F.FreqVector(), F.AmplitudeVectorAtAngles(r,t));
    PltPtr0->rescaleAxes();
    PltPtr0->replot();

    PlotClass * PltPtr1 = this->ChartTab->PlotTabs[1]->customPlot;
    PltPtr1->graph(0)->setData(F.DistVector(), F.FourierAmplVectorAtAngles(r,t));
    PltPtr1->rescaleAxes();
    PltPtr1->replot();
}



void MainWindow::ChangeAngleOfDemonstration()
{
    PlotClass * PltPtr = this->ChartTab->PlotTabs[0]->customPlot;

    if (PltPtr->graph(0)->data()->size()>0)
    {
        r = StoredFunction.FindRotationIndex(TabOfParameters->ResultTab->SetCurrentRotationAngleDoubleSpinBox->value());
        t = StoredFunction.FindTiltIndex(TabOfParameters->ResultTab->SetCurrentTiltAngleDoubleSpinBox->value());

        PltPtr->graph(0)->setData(StoredFunction.FreqVector(), StoredFunction.AmplitudeVectorAtAngles(r,t));


        //QVector <std::complex<double>> FreqVectorAtChosenAngle = StoredFunction.GetFrequencyVectorAt(r,t);
        //this->ChartTab->UpdateMeasurementPlot(FreqVectorAtChosenAngle);

        if (PltPtr->graph(1)->data()->size()>0)
        {
            PltPtr->graph(1)->setData(BackgroundFunction.FreqVector(), BackgroundFunction.AmplitudeVectorAtAngles(r,t));

            PlotClass * PltPtr1 = this->ChartTab->PlotTabs[1]->customPlot;
            PltPtr1->graph(1)->setData(BackgroundFunction.DistVector(), BackgroundFunction.FourierAmplVectorAtAngles(r,t));

        }
        PltPtr->rescaleAxes();
        PltPtr->replot();

        PlotClass * PltPtr1 = this->ChartTab->PlotTabs[1]->customPlot;
        PltPtr1->graph(0)->setData(StoredFunction.DistVector(), StoredFunction.FourierAmplVectorAtAngles(r,t));
        PltPtr1->rescaleAxes();
        PltPtr1->replot();

    }
    else
    {
        ShowErrorMessage("Измеренных данных не обнаружено!", "Убедитесь, что измерение прошло успешно");
    }
}




void MainWindow::SaveMeasuredFunction()
{
    QString DateString = QDate::currentDate().toString("yyyy-MM-dd");
    QString TimeString = QTime::currentTime().toString("HH-mm");

    QString NameOfSavedFile = "Измерение_" + DateString + "_" + TimeString;

    QString Path = QDir::homePath() + "/" + NameOfSavedFile + ".dat";

    QString FilePath = QFileDialog::getSaveFileName(this, "Save File", Path, "Data Files (*.dat);;All Files (*)");

    QFile File(FilePath);
    if (!File.open(QIODevice::WriteOnly))
    {
        ShowErrorMessage("Не удалось открыть файл для записи!",File.errorString());
        return;
    }


    QDataStream out(&File);
    out << StoredFunction;
    File.close();
 }




 void MainWindow::SetBackground()
 {
    QFile File(TabOfParameters->ResultTab->BackgroundLineEdit->text());
    if (!File.open(QIODevice::ReadOnly))
    {
        ShowErrorMessage("Не удалось открыть файл для чтения!",File.errorString());
        return;
    }

    QDataStream in(&File);
    in >> BackgroundFunction;
    File.close();



    QVector <double> x = BackgroundFunction.FreqVector();

    r = BackgroundFunction.FindRotationIndex(TabOfParameters->ResultTab->SetCurrentRotationAngleDoubleSpinBox->value());
    t = BackgroundFunction.FindTiltIndex    (TabOfParameters->ResultTab->SetCurrentTiltAngleDoubleSpinBox    ->value());

    QVector <std::complex<double>> f = BackgroundFunction.GetFrequencyVectorAt(r,t);

    QVector <double> y(BackgroundFunction.FNum);

    for (int i=0;i<BackgroundFunction.FNum;i++)
    {
        y[i] = abs(f[i]);
    }

    if (ChartTab->PlotTabs[0]->customPlot->graphCount()==1)
    {
        ChartTab->PlotTabs[0]->customPlot->addGraph();
    }

    ChartTab->PlotTabs[0]->customPlot->graph(1)->setData(x,y);

    ChartTab->PlotTabs[0]->customPlot->replot();
 }


void MainWindow::SubstractBackground()
{

    if (BackgroundFunction.Function.size()==0)
    {
        QFile File(TabOfParameters->ResultTab->BackgroundLineEdit->text());
        if (!File.open(QIODevice::ReadOnly))
        {
            ShowErrorMessage("Не удалось открыть файл для чтения!",File.errorString());
            return;
        }

        QDataStream in(&File);
        in >> BackgroundFunction;
        File.close();
    }

    PlotClass * PltPtr = this->ChartTab->PlotTabs[0]->customPlot;


    if (PltPtr->graph(0)->data()->size()>0)
    {
        if (StoredFunction.CheckBackgroundForSuitability(BackgroundFunction) )
        {
            StoredFunction.SubstractBackground(BackgroundFunction);
            PltPtr->graph(1)->data()->clear();
            this->SetMeasuredFunction(StoredFunction);
            //this->BackgroundFunction.ClearFunction(); // Не очищать! Ещё потребуется при калибровке
        }
        else
        {
            ShowErrorMessage("Данные фона не подходят по формату!", "Убедитесь, что вы выбрали нужный файл");
            return;
        }
    }
    else
    {
        ShowErrorMessage("Нет данных!", "Убедитесь, что измеренные данные были получены");
        return;
    }
}


MainWindow::~MainWindow()
{

    Thread->quit();
    Thread->wait();
    Thread->deleteLater();
    Process->deleteLater();

    delete ui;
}



void MainWindow::SetCalibration()
{

    if (BackgroundFunction.FNum==0)
    {
        ShowErrorMessage("Не найден фон", "Сперва выберите фон");
        return;
    }
    if (CalibrationFunction.FNum==0)
    {
        QFile File(TabOfParameters->ResultTab->CalibrationLineEdit->text());
        if (!File.open(QIODevice::ReadOnly))
        {
            ShowErrorMessage("Не удалось открыть файл для чтения!", File.errorString());
            return;
        }

        QDataStream in(&File);
        in >> CalibrationFunction;
        File.close();
    }

    CalibrationFunction.SubstractBackground(BackgroundFunction);

    int SampleTypeIndex = this->TabOfParameters->ResultTab->CalibrationSampleComboBox->currentIndex();

    StoredFunction.Calibrate(CalibrationFunction,SampleTypeIndex);


    r = StoredFunction.FindRotationIndex(TabOfParameters->ResultTab->SetCurrentRotationAngleDoubleSpinBox->value());
    t = StoredFunction.FindTiltIndex(TabOfParameters->ResultTab->SetCurrentTiltAngleDoubleSpinBox->value());

    PlotClass * PltPtr = this->ChartTab->PlotTabs[0]->customPlot;
    PltPtr->graph(0)->setData(StoredFunction.FreqVector(), StoredFunction.AmplitudeVectorAtAngles(r,t));
    PltPtr->rescaleAxes();
    PltPtr->replot();


    /*
    QFile File(TabOfParameters->ResultTab->BackgroundLineEdit->text());
    if (!File.open(QIODevice::ReadOnly)) {
        qWarning() << "Не получилось открыть файл для чтения: " << File.errorString();
        return;
    }


    QDataStream in(&File);
    in >> BackgroundFunction;
    File.close();



    QVector <double> x = BackgroundFunction.FreqVector();

    r = BackgroundFunction.FindRotationIndex(TabOfParameters->ResultTab->SetCurrentRotationAngleDoubleSpinBox->value());
    t = BackgroundFunction.FindTiltIndex    (TabOfParameters->ResultTab->SetCurrentTiltAngleDoubleSpinBox    ->value());

    QVector <std::complex<double>> f = BackgroundFunction.GetFrequencyVectorAt(r,t);

    QVector <double> y(BackgroundFunction.FNum);

    for (int i=0;i<BackgroundFunction.FNum;i++)
    {
        y[i] = abs(f[i]);
    }

    if (ChartTab->PlotTabs[0]->customPlot->graphCount()==1)
    {
        ChartTab->PlotTabs[0]->customPlot->addGraph();
    }

    ChartTab->PlotTabs[0]->customPlot->graph(1)->setData(x,y);

    ChartTab->PlotTabs[0]->customPlot->replot();
    */
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



void MainWindow::ConnectObjects()
{
    connect(TabOfTools->StartMeasurementsButton, &QPushButton::clicked, Process, &ProcessImitation::Measure);

    connect(Process, &ProcessImitation::MeasurementFinished, this, &MainWindow::SetMeasuredFunction);



    connect(TabOfTools, &TabWidgetForTools::ContinuousMeasurementsButtonClickedSignal, Process, &ProcessImitation::MeasureContinuously);

    connect(TabOfTools, &TabWidgetForTools::ContinuousMeasurementsButtonClickedSignal, ChartTab->PlotTabs[0]->customPlot, &PlotClass::ContinuousMeasurementsModeChanged);



    //connect(TabOfTools->ContinuousMeasurementsButton, &QPushButton::clicked, ChartTab, &TabWidgetForCharts::ContinuousMeasurementModeChanged);



    connect(TabOfTools->StopMeasurementsButton, &QPushButton::clicked, Process, &ProcessImitation::StopEverything);

    //connect(TabOfTools->SaveDataButton  , &QPushButton::clicked, ChartTab, &TabWidgetForCharts::SaveData); // Получше придумать как соединять, чтобы по вкладкам (возможно лучше в QidgetForCustomPlot перенести)

    connect(TabOfTools->SaveMeasuredFunctionButton  , &QPushButton::clicked, this, &MainWindow::SaveMeasuredFunction);
    //connect(TabOfTools->ImportDataButton, &QPushButton::clicked, ChartTab, &TabWidgetForCharts::CreateNewTabFromImportedData);

    //connect(TabOfParameters->MeasurementTab, &MeasurementsParametersWidget::FrequencyParametersChanged, ChartTab,&TabWidgetForCharts::SetFrequencyParameters);
    //connect(TabOfParameters->MeasurementTab, &MeasurementsParametersWidget::AngleParametersChanged,     ChartTab,&TabWidgetForCharts::SetAngleParameters); // Нужно ли()

    connect(TabOfParameters->MeasurementTab, &MeasurementsParametersWidget::FrequencyParametersChanged, Process, &ProcessImitation::SetFrequencyRange);
    connect(TabOfParameters->MeasurementTab, &MeasurementsParametersWidget::AngleParametersChanged,     Process, &ProcessImitation::SetAngleRanges);

    connect(TabOfParameters->MeasurementTab, &MeasurementsParametersWidget::FrequencyParametersChanged, Process, &ProcessImitation::SetFrequencyRange);

    //connect(TabOfTools->FourierTransformButton,        &QPushButton::clicked, ChartTab, &TabWidgetForCharts::PerformFourierTransformOfCurrentPlot);
    //connect(TabOfTools->InverseFourierTransformButton, &QPushButton::clicked, ChartTab, &TabWidgetForCharts::PerformInverseFourierTransformOfCurrentPlot);

    //connect(TabOfParameters->ResultTab->SetCurrentAngleButton, &QPushButton::clicked, ChartTab, &TabWidgetForCharts::ChangeDemonstratedAngles);

    connect(TabOfParameters->ResultTab->SetCurrentAngleButton, &QPushButton::clicked, this, &MainWindow::ChangeAngleOfDemonstration);


    connect(TabOfParameters->ResultTab->BackgroundAddButton, &QPushButton::clicked, this, &MainWindow::SetBackground);
    connect(TabOfParameters->ResultTab->BackgroundSubstractButton, &QPushButton::clicked, this, &MainWindow::SubstractBackground);


    connect(TabOfParameters->ResultTab->CalibrationSetButton, &QPushButton::clicked, this, &MainWindow::SetCalibration);

    //connect(TabOfParameters->ResultTab->CalculateDistancePortraitButton, &QPushButton::clicked, this, &MainWindow::CalculateDistancePortrait);

    connect(Thread, &QThread::finished, Thread, &QThread::deleteLater);

    //connect(Process, &ProcessImitation::ProgressSignal, this->ProgressBar, &QProgressBar::setValue);

    connect(Process, &ProcessImitation::IterationOfMeasurementFinished,this, &MainWindow::HandleReceivedMeasuredFreqVector);

    //connect(TabOfParameters->FileTreeTab, &TreeWidgetForFiles::FileWasChosenSignal, TabOfParameters->ResultTab, &ResultParametersWidget::FileChosenInTreeWidget);

    connect(TabOfTools->GetPlotDataButton, &QPushButton::clicked, this, &MainWindow::GetPlotFromDat);

}



void MainWindow::HandleReceivedMeasuredFreqVector(QVector <double> ReceivedVector)
{

    PlotClass * PltPtr = ChartTab->PlotTabs[0]->customPlot;

    if (StoredFunction.CurrentIndex==0)
    {
        double FStart = TabOfParameters->MeasurementTab->FrequencyStart;
        double FStop = TabOfParameters->MeasurementTab->FrequencyStop;
        double FNum = TabOfParameters->MeasurementTab->FrequencyNumber;

        double RStart = TabOfParameters->MeasurementTab->RotationAngleStart;
        double RStop = TabOfParameters->MeasurementTab->RotationAngleStop;
        double RNum = TabOfParameters->MeasurementTab->RotationAngleNumber;

        double TStart = TabOfParameters->MeasurementTab->TiltAngleStart;
        double TStop = TabOfParameters->MeasurementTab->TiltAngleStop;
        double TNum = TabOfParameters->MeasurementTab->TiltAngleNumber;


        StoredFunction.SetRanges(FStart,FStop,FNum,   RStart,RStop,RNum,   TStart,TStop,TNum);



        PltPtr->XVector = StoredFunction.FreqVector();
        CurrentPlotIndex=0;
    }






    StoredFunction.AddMeasuredValues(ReceivedVector);


    int I = StoredFunction.CurrentIndex/2;
    int R = StoredFunction.RNum;
    int F = StoredFunction.FNum;
    int t = I / (R*F);
    int r = (I % (R*F)) / F;


    QVector<double> YVector = StoredFunction.AmplitudeVectorAtAngles(r,t);



    PltPtr->graph(0)->setData(PltPtr->XVector, YVector);

    /*
    if (r==StoredFunction.RNum-1 and t==StoredFunction.TNum-1) // Через CurrentIndex
    {
        //Сохранить, и занулить, чтобы начать следующую
        SaveMeasuredFunction();
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
