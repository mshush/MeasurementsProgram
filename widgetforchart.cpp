#include "widgetforchart.h"



WidgetForChart::WidgetForChart(QWidget *parent)
    : QWidget{parent}
{


    freq1 = 20;
    freq2= 5;

    HorizontalChartLayout = new QHBoxLayout(this);


    ChartSeries = new QLineSeries();
    for (int i=0;i<10;i++)
    {
        ChartSeries->append(static_cast<double>(i),sin(static_cast<double>(i)/freq1)*(sin(static_cast<double>(i)/freq2)));
    }

    Chart = new QChart;
    Chart->createDefaultAxes();

    Chart->setTitle("График 1");

    Chart->setMargins(QMargins(0, 0, 0, 0));

    QPen pen;
    pen.setWidth(2);
    /*
    QValueAxis * XAxis = new QValueAxis(Chart);
    XAxis->setLinePen(pen);
    XAxis->setTickCount(5);
    Chart->addAxis(XAxis, Qt::AlignBottom);
    ChartSeries->attachAxis(XAxis);
    XAxis->setGridLineVisible(true);
    */
    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, 10);
    axisX->setTickCount(10);
    axisX->setLabelFormat("%.2f");
    Chart->addAxis(axisX, Qt::AlignBottom);

    /*
    QValueAxis * axisY = new QValueAxis();
    axisY->setTickCount(5);
    ChartSeries->attachAxis(axisY);
    axisY->setGridLineVisible(true);
    Chart->addAxis(axisY, Qt::AlignLeft);
    */

    axisY = new QValueAxis;
    axisY->setRange(0, 10);
    axisY->setTickCount(10);
    axisY->setLabelFormat("%.2f");
    Chart->addAxis(axisY, Qt::AlignLeft);


    Chart->addSeries(ChartSeries);
    Chart->legend()->hide();


    ChartView = new CustomChartView(Chart,this);

    //ChartView->setRenderHint(QPainter::Antialiasing);


    //connect(ChartView, &QChartView::rubberBandChanged, this, &WidgetForChart::ScaleToZoom);


    /*
    connect(ChartView->chart()->plotArea(), &QGraphicsView::rubberBandChanged, [=](const QRectF &rect, const QPointF &fromScenePoint, const QPointF &toScenePoint) {
        qreal minY = ChartView->chart()->mapToValue(fromScenePoint).y();
        qreal maxY = ChartView->chart()->mapToValue(toScenePoint).y();
        axisY->setRange(minY, maxY);
    });
    */


    HorizontalChartLayout->addWidget(ChartView);


    QTabWidget *ChartManipulationTabs = new QTabWidget;

    QWidget * Tab1 = new QWidget;
    QWidget * Tab2 = new QWidget;
    //QWidget * Tab3 = new QWidget;


    ChartManipulationTabs->addTab(Tab1,"Управление");
    //ChartManipulationTabs->addTab(Tab2,"Частоты");
    //ChartManipulationTabs->addTab(Tab3,"Угол");



    QVBoxLayout * Tab1OuterLayout = new QVBoxLayout(Tab1);

    QPushButton * EnableMovementButton = new QPushButton("Двигать",this);
    EnableMovementButton->setCheckable(true);
    connect(EnableMovementButton, &QPushButton::clicked, [this,EnableMovementButton]()
        {
            ChartView->MovementEnabled = EnableMovementButton->isChecked();
            ChartView->setRubberBand(QChartView::NoRubberBand);
        }
            );
    Tab1OuterLayout->addWidget(EnableMovementButton);

    QPushButton * ToggleRubberBandZoomingButton = new QPushButton("Приблизить",this); // Попробовать zoom через колёсико мышки
    ToggleRubberBandZoomingButton->setCheckable(true);
    connect(ToggleRubberBandZoomingButton, &QPushButton::clicked, [ToggleRubberBandZoomingButton,this]()
        {
            ChartView->RubberBandEnabled = ToggleRubberBandZoomingButton->isChecked();

            if (ToggleRubberBandZoomingButton->isChecked())
            {
                ChartView->setRubberBand(QChartView::RectangleRubberBand);

            }
            else
            {
                ChartView->setRubberBand(QChartView::NoRubberBand);
            }
        }
            );
    Tab1OuterLayout->addWidget(ToggleRubberBandZoomingButton);



    QPushButton * ResetChartButton = new QPushButton("Сброс",this);



    connect(ResetChartButton, &QPushButton::clicked, [this]()
            {
                qDebug()<<ChartView->viewport()->rect();
                ChartView->chart()->scroll(ChartView->CurrentChartPosition.x(),-ChartView->CurrentChartPosition.y());
                ChartView->CurrentChartPosition=QPoint(0,0);

                //ChartView->transform().reset();
            }
            );
    connect(ResetChartButton, &QPushButton::clicked, Chart, &QChart::zoomReset);

    Tab1OuterLayout->addWidget(ResetChartButton);



    //Tab1OuterLayout->addWidget(new QPushButton("Открепить"));



    //ChartManipulationMainLayout->addWidget(ChartManipulationTabs);


    HorizontalChartLayout->addWidget(ChartManipulationTabs);


    ChartManipulationTabs->resize(200,600);
    ChartManipulationTabs->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding );



    QGridLayout * LayoutOfParameters = new QGridLayout(Tab2);

    LayoutOfParameters->addWidget(new QLabel("Частота 1"),0,0);
    LayoutOfParameters->addWidget(new QLabel("Частота 2"),0,1);

    QLineEdit * Freq1LineEdit = new QLineEdit();
    QLineEdit * Freq2LineEdit = new QLineEdit();


    LayoutOfParameters->addWidget(Freq1LineEdit,1,0);
    LayoutOfParameters->addWidget(Freq2LineEdit,1,1);




    /*
    Freq1Slider = new QSlider(Qt::Horizontal);
    Freq1Slider->setRange(1,100);
    Freq1Slider->setValue(5);
    connect(Freq1Slider, &QSlider::valueChanged, this, &WidgetForChart::RedrawChart);
    LayoutOfParameters->addWidget(Freq1Slider,2,0, Qt::AlignCenter);


    Freq2Slider = new QSlider(Qt::Horizontal);
    Freq2Slider->setRange(1,100);
    Freq2Slider->setValue(20);
    connect(Freq2Slider, &QSlider::valueChanged, this, &WidgetForChart::RedrawChart);
    LayoutOfParameters->addWidget(Freq2Slider,2,1, Qt::AlignCenter);
    */

    //LayoutOfParameters->setRowStretch(2, 1);
    //LayoutOfParameters->setRowStretch(0, 0);
    //LayoutOfParameters->setRowStretch(1, 0);

/*
    QHBoxLayout * FrequencyStartLayout = new QHBoxLayout;
    QLabel * FrequencyStartLabel = new QLabel("Начало");
    QLineEdit * FrequencyStartEdit = new QLineEdit;
    QComboBox * FrequencyStartComboBox = new QComboBox;
    FrequencyStartComboBox->addItem("ГГц");
    FrequencyStartLayout->addWidget(FrequencyStartLabel);
    FrequencyStartLayout->addWidget(FrequencyStartEdit);
    FrequencyStartLayout->addWidget(FrequencyStartComboBox);

    Tab2->resize(100,600);
    Tab2->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);


    setColumnStretch(0, 1); // QSlider column with higher stretch factor
    layout.setColumnStretch(1, 0);


    /*
    QHBoxLayout * FrequencyStopLayout = new QHBoxLayout;
    QLabel * FrequencyStopLabel = new QLabel("Конец");
    QLineEdit * FrequencyStopEdit = new QLineEdit;
    QComboBox * FrequencyStopComboBox = new QComboBox;
    FrequencyStopComboBox->addItem("ГГц");
    FrequencyStopLayout->addWidget(FrequencyStopLabel);
    FrequencyStopLayout->addWidget(FrequencyStopEdit);
    FrequencyStopLayout->addWidget(FrequencyStopComboBox);

    QHBoxLayout * FrequencyNumberOfPointsLayout = new QHBoxLayout;
    QLabel * FrequencyNumberOfPointsLabel = new QLabel("Число точек");
    QLineEdit * FrequencyNumberOfPointsEdit = new QLineEdit;
    FrequencyNumberOfPointsLayout->addWidget(FrequencyNumberOfPointsLabel);
    FrequencyNumberOfPointsLayout->addWidget(FrequencyNumberOfPointsEdit);



    FrequencyGroupMainLayout->addLayout(FrequencyButtonLayout);
    FrequencyGroupMainLayout->addLayout(FrequencyStartLayout);
    FrequencyGroupMainLayout->addLayout(FrequencyStopLayout);
    FrequencyGroupMainLayout->addLayout(FrequencyNumberOfPointsLayout);

    FrequencyGroup->setLayout(FrequencyGroupMainLayout);

    QGroupBox * AngleGroup = new QGroupBox("Диапазон углов");
    QLabel * ExplanationLabel3 = new QLabel("Аналогично частотам");
    QVBoxLayout * AngleGroupMainLayout = new QVBoxLayout;
    AngleGroupMainLayout->addWidget(ExplanationLabel3);
    AngleGroup->setLayout(AngleGroupMainLayout);


    QGroupBox * CalibrationSampleGroup = new QGroupBox("Калибровочный образец");
    QLabel * ExplanationLabel4 = new QLabel("Здесь QComboBox образцов и набор параметров \nобразца, определяемый QComboBox-ом");
    QVBoxLayout * CalibrationSampleGroupMainLayout = new QVBoxLayout;
    CalibrationSampleGroupMainLayout->addWidget(ExplanationLabel4);
    CalibrationSampleGroup->setLayout(CalibrationSampleGroupMainLayout);
    //QPushButton * button1 = new QPushButton("Press!!!");


    QLabel * ExplanationLabel1 = new QLabel("Справа, также как в старой программе,\nчтобы было привычнее. Последовательность,\nв которой расположены параметры если менять,\nто перераспределить в порядке частоты\nиспользования, чтобы далеко мышку не вести");
    ExplanationLabel1->setWordWrap(true);

    ExplanationLabel->resize(160,50);
    ExplanationLabel1->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    VerticalLayoutOfParameters->addWidget(ExplanationLabel);
    VerticalLayoutOfParameters->addWidget(FrequencyGroup);
    VerticalLayoutOfParameters->addWidget(AngleGroup);
    VerticalLayoutOfParameters->addWidget(CalibrationSampleGroup);
    VerticalLayoutOfParameters->addWidget(ExplanationLabel1);

    setLayout(VerticalLayoutOfParameters);
    */
}


void WidgetForChart::RedrawChart()
{
    freq1 = Freq1Slider->value();
    freq2 = Freq2Slider->value();
    ChartSeries->clear();
    for (int i=0;i<10;i++)
    {
        ChartSeries->append(static_cast<double>(i),sin(static_cast<double>(i)/freq1)*(sin(static_cast<double>(i)/freq2)));
    }
    ChartView->repaint();
    ChartView->update();

}



/*
void WidgetForChart::ScaleToZoom(QRectF rect, QPointF fromScenePoint, QPointF toScenePoint) // Не работает!
{
    qDebug()<< "Was here!";
    //QValueAxis *axisX = qobject_cast<QValueAxis*>(Chart->axisX());
    //QValueAxis *axisY = qobject_cast<QValueAxis*>(Chart->axisY());

    double minX = std::min(fromScenePoint.x(), toScenePoint.x());
    double maxX = std::max(fromScenePoint.x(), toScenePoint.x());
    double minY = std::min(fromScenePoint.y(), toScenePoint.y());
    double maxY = std::max(fromScenePoint.y(), toScenePoint.y());

    Chart->axisX()->setRange(minX, maxX);
    Chart->axisY()->setRange(minY, maxY);
}
*/


