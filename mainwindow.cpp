#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //qputenv("QT_SCALE_FACTOR", "1.5");
    //QGuiApplication::setAttribute(Qt::AA_Use96Dpi);

    //QGuiApplication::setAttribute(Qt::AA_Use96Dpi); // Разобраться, что делает
    //qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "0");

    QFont Font("Segoe UI", 12); // Был QFont(Segoe UI,9,-1,5,400,0,0,0,0,0,0,0,0,0,0,1)
    QApplication::setFont(Font);

    ui->setupUi(this);


    this->menuBar()->addMenu("Файл");
    this->menuBar()->addMenu("Свойства");
    this->menuBar()->addMenu("Постобработка");
    this->menuBar()->addMenu("Вид");


    Process = new ProcessImitation(this);


    QVBoxLayout *OutermostVerticalLayout = new QVBoxLayout;

    TabOfTools = new TabWidgetForTools;
    TabOfTools->resize(800,200);
    TabOfTools->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    OutermostVerticalLayout->addWidget(TabOfTools);

    QHBoxLayout * MiddleHorizontalLayout = new QHBoxLayout;


    QVBoxLayout * InnerVerticalLayout = new QVBoxLayout;

    ChartTab = new TabWidgetForCharts;

    InnerVerticalLayout->addWidget(ChartTab); // ?????

    TabOfParameters = new TabWidgetForParameters;

    //QHBoxLayout * BottomHorizontalLayout = new QHBoxLayout;


    MiddleHorizontalLayout->addWidget(TabOfParameters);
    MiddleHorizontalLayout->addLayout(InnerVerticalLayout);

    OutermostVerticalLayout->addLayout(MiddleHorizontalLayout);
    //OutermostVerticalLayout->addLayout(BottomHorizontalLayout);

    centralWidget()->setLayout(OutermostVerticalLayout);

    connect(TabOfTools->StartMeasurementsButton, &QPushButton::clicked, Process, &ProcessImitation::Measure);
    connect(Process, &ProcessImitation::MeasurementFinished, this, &MainWindow::SetMeasuredFunction);



    //connect(TabOfTools->ContinuousMeasurementsButton, &QPushButton::clicked, Process, &ProcessImitation::MeasureContinuously);
    //connect(TabOfTools->ContinuousMeasurementsButton, &QPushButton::clicked, ChartTab, &TabWidgetForCharts::ContinuousMeasurementModeChanged);



    connect(TabOfTools->StopMeasurementsButton, &QPushButton::clicked, this,[this]()
            {
                qDebug()<<this->size();
            }
            );

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


    //this->resize(2560,1440); Не работает
    //QScreen *screen = QGuiApplication::primaryScreen();
    //screen->setProperty("QT_SCREEN_SCALE_FACTOR", "0");
    //qreal devicePixelRatio = screen->devicePixelRatio();

    this->setWindowState(Qt::WindowMaximized);
}




void MainWindow::SetMeasuredFunction(MeasuredFunction F)
{

    StoredFunction = F;
    int r = StoredFunction.FindRotationIndex(TabOfParameters->ResultTab->SetCurrentRotationAngleDoubleSpinBox->value());
    int t = StoredFunction.FindTiltIndex    (TabOfParameters->ResultTab->SetCurrentTiltAngleDoubleSpinBox    ->value());

    //QVector <std::complex<double>> FreqVectorAtChosenAngle = F.GetFrequencyVectorAt(r,t);
    //this->ChartTab->UpdateMeasurementPlot(FreqVectorAtChosenAngle);

    PlotClass * PltPtr = this->ChartTab->PlotTabs[0]->customPlot;
    PltPtr->graph(0)->setData(F.XVector(), F.YVectorAtAngles(r,t));
    PltPtr->rescaleAxes();
    PltPtr->replot();
}



void MainWindow::ChangeAngleOfDemonstration()
{
    PlotClass * PltPtr = this->ChartTab->PlotTabs[0]->customPlot;

    if (PltPtr->graph(0)->data()->size()>0)
    {
        int r = StoredFunction.FindRotationIndex(TabOfParameters->ResultTab->SetCurrentRotationAngleDoubleSpinBox->value());
        int t = StoredFunction.FindTiltIndex(TabOfParameters->ResultTab->SetCurrentTiltAngleDoubleSpinBox->value());

        PltPtr->graph(0)->setData(StoredFunction.XVector(), StoredFunction.YVectorAtAngles(r,t));


        //QVector <std::complex<double>> FreqVectorAtChosenAngle = StoredFunction.GetFrequencyVectorAt(r,t);
        //this->ChartTab->UpdateMeasurementPlot(FreqVectorAtChosenAngle);

        if (PltPtr->graph(1)->data()->size()>0)
        {
            PltPtr->graph(1)->setData(StoredFunction.XVector(), StoredFunction.YVectorAtAngles(r,t));
        }
        PltPtr->rescaleAxes();
        PltPtr->replot();
    }
    else
    {
        ShowErrorMessage("Измерений ещё не проводилось!", "Проведите измерение и попробуйте ещё раз");
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
        ShowErrorMessage("Не удалось открыть файл для записи!",File.errorString());
        return;
    }

    QDataStream in(&File);
    in >> BackgroundFunction;
    File.close();



    QVector <double> x = BackgroundFunction.XVector();

    int r = BackgroundFunction.FindRotationIndex(TabOfParameters->ResultTab->SetCurrentRotationAngleDoubleSpinBox->value());
    int t = BackgroundFunction.FindTiltIndex    (TabOfParameters->ResultTab->SetCurrentTiltAngleDoubleSpinBox    ->value());

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
    PlotClass * PltPtr = this->ChartTab->PlotTabs[0]->customPlot;

    if (PltPtr->graph(0)->data()->size()>0)
    {
        if (PltPtr->graph(0)->data()->size() == PltPtr->graph(1)->data()->size())
        {
            StoredFunction.SubstractBackground(BackgroundFunction);
            PltPtr->graph(1)->data()->clear();
            this->SetMeasuredFunction(StoredFunction);
            this->BackgroundFunction.Resize(0,0,0);
        }
        else
        {

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
    delete ui;
    /*
    delete TabOfParameters;
    delete TabOfTools;
    delete ChartTab;
    delete CustomPlotWidget;
    */
}



void MainWindow::SetCalibration()
{
    /*
    QFile File(TabOfParameters->ResultTab->BackgroundLineEdit->text());
    if (!File.open(QIODevice::ReadOnly)) {
        qWarning() << "Не получилось открыть файл для чтения: " << File.errorString();
        return;
    }


    QDataStream in(&File);
    in >> BackgroundFunction;
    File.close();



    QVector <double> x = BackgroundFunction.XVector();

    //qDebug()<< "xMax = " << x[1600];

    int r = BackgroundFunction.FindRotationIndex(TabOfParameters->ResultTab->SetCurrentRotationAngleDoubleSpinBox->value());
    int t = BackgroundFunction.FindTiltIndex    (TabOfParameters->ResultTab->SetCurrentTiltAngleDoubleSpinBox    ->value());

    //qDebug()<<r << " = r, t = " << t;

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




void ShowErrorMessage(QString Description, QString Advice)
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setWindowTitle("Ошибка!");
    msgBox.setText(Description);
    msgBox.setInformativeText(Advice);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

