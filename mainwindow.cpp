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

    InnerVerticalLayout->addWidget(ChartTab);

    TabOfParameters = new TabWidgetForParameters;

    //QHBoxLayout * BottomHorizontalLayout = new QHBoxLayout;


    MiddleHorizontalLayout->addWidget(TabOfParameters);
    MiddleHorizontalLayout->addLayout(InnerVerticalLayout);

    OutermostVerticalLayout->addLayout(MiddleHorizontalLayout);
    //OutermostVerticalLayout->addLayout(BottomHorizontalLayout);

    centralWidget()->setLayout(OutermostVerticalLayout);

    connect(TabOfTools->StartMeasurementsButton, &QPushButton::clicked, Process, &ProcessImitation::Measure);
    connect(Process, &ProcessImitation::MeasurementFinished, this, &MainWindow::ProcessMeasuredFunction);



    //connect(TabOfTools->ContinuousMeasurementsButton, &QPushButton::clicked, Process, &ProcessImitation::MeasureContinuously);
    //connect(TabOfTools->ContinuousMeasurementsButton, &QPushButton::clicked, ChartTab, &TabWidgetForCharts::ContinuousMeasurementModeChanged);



    connect(TabOfTools->StopMeasurementsButton, &QPushButton::clicked, this,[this]()
            {
                qDebug()<<this->size();
            }
            );


    connect(TabOfTools->SaveDataButton  , &QPushButton::clicked, ChartTab, &TabWidgetForCharts::SaveData); // Получше придумать как соединять, чтобы по вкладкам (возможно лучше в QidgetForCustomPlot перенести)
    connect(TabOfTools->ImportDataButton, &QPushButton::clicked, ChartTab, &TabWidgetForCharts::CreateNewTabFromImportedData);

    connect(TabOfParameters->MeasurementTab, &MeasurementsParametersWidget::FrequencyParametersChanged, ChartTab,&TabWidgetForCharts::SetFrequencyParameters);
    //connect(TabOfParameters->MeasurementTab, &MeasurementsParametersWidget::AngleParametersChanged,     ChartTab,&TabWidgetForCharts::SetAngleParameters); // Нужно ли()

    connect(TabOfParameters->MeasurementTab, &MeasurementsParametersWidget::FrequencyParametersChanged, Process, &ProcessImitation::SetFrequencyRange);
    connect(TabOfParameters->MeasurementTab, &MeasurementsParametersWidget::AngleParametersChanged,     Process, &ProcessImitation::SetAngleRanges);

    connect(TabOfTools->FourierTransformButton,        &QPushButton::clicked, ChartTab, &TabWidgetForCharts::PerformFourierTransformOfCurrentPlot);
    connect(TabOfTools->InverseFourierTransformButton, &QPushButton::clicked, ChartTab, &TabWidgetForCharts::PerformInverseFourierTransformOfCurrentPlot);

    //this->resize(2560,1440); Не работает
    //QScreen *screen = QGuiApplication::primaryScreen();
    //screen->setProperty("QT_SCREEN_SCALE_FACTOR", "0");
    //qreal devicePixelRatio = screen->devicePixelRatio();

    this->setWindowState(Qt::WindowMaximized);
}




void MainWindow::ProcessMeasuredFunction(MeasuredFunction F)
{
    StoredFunction = F;
    qDebug() << "MW=" << F.ReadFrom(5,5,5).real();
    int r = TabOfParameters->ResultTab->SetCurrentRotationAngleEdit->text().toInt();
    int t = TabOfParameters->ResultTab->SetCurrentTiltAngleEdit    ->text().toInt();
    QVector <std::complex<double>> FreqVectorAtChosenAngle = F.GetFrequencyVectorAt(r,t);

    this->ChartTab->UpdateMeasurementPlot(FreqVectorAtChosenAngle);
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




