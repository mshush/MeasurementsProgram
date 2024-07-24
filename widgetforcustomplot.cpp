#include "widgetforcustomplot.h"

WidgetForCustomPlot::WidgetForCustomPlot(QWidget *parent)
    : QWidget{parent}
{
    this->resize(600,200);
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    HorizontalPlotLayout = new QHBoxLayout(this);


    customPlot = new PlotClass(this);



    customPlot->resize(600,200);
    customPlot->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    ControlsWidget = new QWidget(this);
    ControlsWidget->resize(200,200);
    ControlsWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    VerticalControlsLayout = new QVBoxLayout(this);
    ControlsWidget->setLayout(VerticalControlsLayout);
    ControlsWidget->resize(50,30);
    ControlsWidget->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    ResetButton = new QPushButton("Сброс");
    connect(ResetButton, &QPushButton::clicked, customPlot, &PlotClass::ResetPlot);
    VerticalControlsLayout->addWidget(ResetButton);

    MarkerAddButton = new QPushButton("+Маркер"); //Добавить смену значка и цвета где-нибудь в продвинутых опциях. Переместить лямбда-функцию в PlotClass?
    MarkerAddButton->setCheckable(true);
    connect(MarkerAddButton, &QPushButton::clicked, [this]()
            {
                customPlot->markerbuttonactive = !customPlot->markerbuttonactive;
                customPlot->MouseMoveMarker->setVisible(customPlot->markerbuttonactive);
                customPlot->MouseMoveLabel->setVisible(customPlot->markerbuttonactive);
                customPlot->replot();
            }
            );
    VerticalControlsLayout->addWidget(MarkerAddButton);

    MarkerDeleteButton = new QPushButton("-Маркер"); //Добавить смену значка и цвета где-нибудь в продвинутых опциях. Переместить лямбда-функцию в PlotClass?
    MarkerDeleteButton->setCheckable(true);
    connect(MarkerDeleteButton, &QPushButton::clicked, [this]()
            {
                customPlot->markerbuttonactive = !customPlot->markerbuttonactive;
                customPlot->MouseMoveMarker->setVisible(customPlot->markerbuttonactive);
                customPlot->MouseMoveLabel->setVisible(customPlot->markerbuttonactive);
                customPlot->replot();
            }
            );
    VerticalControlsLayout->addWidget(MarkerDeleteButton);



    SaveButton = new QPushButton("Сохранить");
    connect(SaveButton, &QPushButton::clicked, customPlot, &PlotClass::SavePlot);
    VerticalControlsLayout->addWidget(SaveButton);
    HorizontalPlotLayout->addWidget(customPlot);
    HorizontalPlotLayout->addWidget(ControlsWidget);

}




