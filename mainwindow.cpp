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


    ui->setupUi(this);


    this->menuBar()->addMenu("Файл");
    this->menuBar()->addMenu("Свойства");
    this->menuBar()->addMenu("Постобработка");
    this->menuBar()->addMenu("...");


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

    QHBoxLayout * BottomHorizontalLayout = new QHBoxLayout;

    MiddleHorizontalLayout->addLayout(InnerVerticalLayout);

    MiddleHorizontalLayout->addWidget(TabOfParameters);

    OutermostVerticalLayout->addLayout(MiddleHorizontalLayout);

    OutermostVerticalLayout->addLayout(BottomHorizontalLayout);

    centralWidget()->setLayout(OutermostVerticalLayout);

    connect(TabOfTools->StartMeasurementsButton, &QPushButton::clicked, ChartTab->PlotTabs[0]->customPlot, &PlotClass::Measure);
    connect(TabOfTools->ContinuousMeasurementsButton, &QPushButton::clicked, ChartTab->PlotTabs[0]->customPlot, &PlotClass::MeasureContinuously);

    connect(TabOfTools->StopMeasurementsButton, &QPushButton::clicked, this,[this]()
            {
                qDebug()<<this->ChartTab->PlotTabs[0]->customPlot->antialiasedElements();
                if (this->ChartTab->PlotTabs[0]->customPlot->antialiasedElements() & QCP::aeAll)
                    {
                        this->ChartTab->PlotTabs[0]->customPlot->setAntialiasedElements(QCP::aeNone);
                    }
                else
                {
                    this->ChartTab->PlotTabs[0]->customPlot->setAntialiasedElements(QCP::aeAll);
                }
            }
            );

    connect(TabOfTools->SaveDataButton  , &QPushButton::clicked, ChartTab->PlotTabs[0]->customPlot, &PlotClass::SaveData); // Получше придумать как соединять, чтобы по вкладкам
    connect(TabOfTools->ImportDataButton, &QPushButton::clicked, ChartTab, &TabWidgetForCharts::CreateNewTabFromImportedData);

    connect(TabOfParameters->Tab1, &MeasurementsParametersWidget::StartStopFrequenciesChanged, ChartTab,&TabWidgetForCharts::SetStartStopFrequencies);//Переименовать поудобнее



    //this->resize(2560,1440); Не работает
    //QScreen *screen = QGuiApplication::primaryScreen();
    //screen->setProperty("QT_SCREEN_SCALE_FACTOR", "0");
    //qreal devicePixelRatio = screen->devicePixelRatio();

    this->setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow()
{
    delete ui;
}




