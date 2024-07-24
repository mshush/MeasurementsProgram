#include "widgetforcustomplot.h"

WidgetForCustomPlot::WidgetForCustomPlot(QWidget *parent)
    : QWidget{parent}
{
    this->resize(600,200);
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    HorizontalPlotLayout = new QHBoxLayout(this);

    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
        x[i] = i/50.0 - 1; // x goes from -1 to 1
        y[i] = x[i]*x[i]; // let's plot a quadratic function
    }

    customPlot = new QCustomPlot(this);


    // create graph and assign data to it:
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(-1, 1);
    customPlot->yAxis->setRange(0, 1);
    customPlot->replot();

    customPlot->resize(600,200);
    customPlot->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    customPlot->setInteractions(QCP::iRangeZoom | QCP::iRangeDrag);

    ControlsWidget = new QWidget(this);
    ControlsWidget->resize(200,200);
    ControlsWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    VerticalControlsLayout = new QVBoxLayout(this);
    ControlsWidget->setLayout(VerticalControlsLayout);
    ControlsWidget->resize(50,30);
    ControlsWidget->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    ResetButton = new QPushButton("Сброс");
    connect(ResetButton, &QPushButton::clicked, [this]()
            {
                customPlot->rescaleAxes();
                customPlot->replot();
            }
            );
    VerticalControlsLayout->addWidget(ResetButton);


    SaveButton = new QPushButton("Сохранить");
    connect(SaveButton, &QPushButton::clicked, this, &WidgetForCustomPlot::SavePlot);
    VerticalControlsLayout->addWidget(SaveButton);





    HorizontalPlotLayout->addWidget(customPlot);
    HorizontalPlotLayout->addWidget(ControlsWidget);

}




void WidgetForCustomPlot::SavePlot()
{
    qDebug()<<"Was Here!";

    QString filePath = QFileDialog::getSaveFileName(this, "Сохранить как", "", "PNG File (*.png);;JPEG File (*.jpg);;PDF File (*.pdf)");


    if (!filePath.isEmpty()) {
        // Determine the file format based on the file extension
        QString fileFormat = QFileInfo(filePath).suffix();

        // Save the plot in the selected format
        if (fileFormat == "png") {
            customPlot->savePng(filePath);
        } else if (fileFormat == "jpg") {
            customPlot->saveJpg(filePath);
        } else if (fileFormat == "pdf") {
            customPlot->savePdf(filePath);
        }
    }
}
