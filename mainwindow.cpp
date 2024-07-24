#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    this->menuBar()->addMenu("Файл");
    this->menuBar()->addMenu("Свойства");
    this->menuBar()->addMenu("Постобработка");
    this->menuBar()->addMenu("...");


    QVBoxLayout *OutermostVerticalLayout = new QVBoxLayout(this);

    TabOfTools = new TabWidgetForTools;
    TabOfTools->resize(800,200);
    TabOfTools->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    OutermostVerticalLayout->addWidget(TabOfTools);


    QHBoxLayout * MiddleHorizontalLayout = new QHBoxLayout(this);


    QVBoxLayout * InnerVerticalLayout = new QVBoxLayout(this);

    ChartTab = new TabWidgetForCharts;
    //QHBoxLayout * HorizontalChartLayout = new QHBoxLayout(this);


    //HorizontalChartLayout->addWidget(ChartManipulationGroupBox);

    //InnerVerticalLayout->addLayout(HorizontalChartLayout);

    InnerVerticalLayout->addWidget(ChartTab);

    TabOfParameters = new TabWidgetForParameters;

    QHBoxLayout * BottomHorizontalLayout = new QHBoxLayout(this);

    //FileTreeWidget = new TreeWidgetForFiles();
    //InnerVerticalLayout->addWidget(FileTreeWidget);

    CustomPlotWidget = new WidgetForCustomPlot(this);
    InnerVerticalLayout->addWidget(CustomPlotWidget);

    MiddleHorizontalLayout->addLayout(InnerVerticalLayout);


    MiddleHorizontalLayout->addWidget(TabOfParameters);

    OutermostVerticalLayout->addLayout(MiddleHorizontalLayout);

    OutermostVerticalLayout->addLayout(BottomHorizontalLayout);

    centralWidget()->setLayout(OutermostVerticalLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}




