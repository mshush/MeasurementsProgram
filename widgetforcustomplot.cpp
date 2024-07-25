#include "widgetforcustomplot.h"

WidgetForCustomPlot::WidgetForCustomPlot(QWidget *parent)
    : QWidget{parent}
{
    this->resize(600,200);
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    VerticalPlotLayout = new QVBoxLayout(this);
    HorizontalControlsLayout = new QHBoxLayout(this);
    HorizontalControlsLayout->setAlignment(Qt::AlignLeft);

    customPlot = new PlotClass(this);
    customPlot->resize(600,200);
    customPlot->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);


    ControlsWidget = new QWidget(this);
    ControlsWidget->resize(200,200);
    ControlsWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ControlsWidget->setLayout(HorizontalControlsLayout);
    ControlsWidget->resize(50,30);
    ControlsWidget->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);


    ResetButton = new QPushButton("Обратно");
    connect(ResetButton, &QPushButton::clicked, customPlot, &PlotClass::ResetPlot);


    MarkerAddButton = new QPushButton("Добавить"); //Добавить смену значка и цвета где-нибудь в продвинутых опциях. Переместить лямбда-функцию в PlotClass?
    MarkerAddButton->setCheckable(true); // Подпись к маркеру QCPItemText должна не вылазить за пределы графика.
    connect(MarkerAddButton, &QPushButton::clicked, this, [this]()
            {
                customPlot->markeraddbuttonactive = MarkerAddButton->isChecked(); //!customPlot->markeraddbuttonactive;
                customPlot->markerdeletebuttonactive = false;
                MarkerDeleteButton->setChecked(false);
                customPlot->MouseMoveMarker->setVisible(customPlot->markeraddbuttonactive);
                customPlot->MouseMoveLabel->setVisible(customPlot->markeraddbuttonactive);
                customPlot->replot();
            }
            );


    MarkerDeleteButton = new QPushButton("Убрать");
    MarkerDeleteButton->setCheckable(true);
    connect(MarkerDeleteButton, &QPushButton::clicked, this, [this]()
            {
                for (QCPAbstractItem* item : customPlot->selectedItems())
                {
                    if (dynamic_cast<QCPItemTracer*>(item))
                    {
                        dynamic_cast<QCPItemTracer*>(item)->setSelected(false);
                    }
                }

                customPlot->markeraddbuttonactive = false;
                customPlot->markerdeletebuttonactive = MarkerDeleteButton->isChecked();
                MarkerAddButton->setChecked(false);
                customPlot->MouseMoveMarker->setVisible(customPlot->markerdeletebuttonactive);
                customPlot->MouseMoveLabel->setVisible(customPlot->markerdeletebuttonactive);

/*
                for (int i=0; i < customPlot->itemCount();i++)
                {
                    if (dynamic_cast<QCPItemText*>(customPlot->item(i)))
                    {
                        if (dynamic_cast<QCPItemText*>(customPlot->item(i))->visible() && dynamic_cast<QCPItemText*>(customPlot->item(i))!=customPlot->MouseMoveLabel)
                        {
                            customPlot->removeItem(customPlot->item(i));

                        }
                    }
                }
*/
                customPlot->replot();
            }
            );


    DeleteAllMarkersButton = new QPushButton("Очистить");
    connect(DeleteAllMarkersButton, &QPushButton::clicked, customPlot, &PlotClass::DeleteAllMarkers);


    SaveButton = new QPushButton("Сохранить");
    connect(SaveButton, &QPushButton::clicked, customPlot, &PlotClass::SavePlot);


    HorizontalControlsLayout->addWidget(ResetButton);
    HorizontalControlsLayout->addWidget(MarkerAddButton);
    HorizontalControlsLayout->addWidget(MarkerDeleteButton);
    HorizontalControlsLayout->addWidget(DeleteAllMarkersButton);
    HorizontalControlsLayout->addWidget(SaveButton);


    VerticalPlotLayout->addWidget(ControlsWidget);
    VerticalPlotLayout->addWidget(customPlot);

}




