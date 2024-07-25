#include "plotclass.h"

PlotClass::PlotClass(QWidget * parent) : QCustomPlot(parent)
{

    MouseMoveMarker = new QCPItemTracer(this);
    MouseMoveLabel = new QCPItemText(this);

    MouseMoveMarker->setVisible(false);
    MouseMoveLabel->setVisible(false);
    MouseMoveMarker->setSelectable(false);

    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
        x[i] = i/50.0 - 1; // x goes from -1 to 1
        y[i] = x[i]*x[i]; // let's plot a quadratic function
    }

    // create graph and assign data to it:
    addGraph();
    graph(0)->setData(x, y);
    // give the axes some labels:
    xAxis->setLabel("x");
    yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    xAxis->setRange(-1, 1);
    yAxis->setRange(0, 1);
    replot();

    setInteractions(QCP::iRangeZoom | QCP::iRangeDrag | QCP::iSelectItems);
}


void PlotClass::mouseMoveEvent(QMouseEvent *event)
{
    QCustomPlot::mouseMoveEvent(event);

    if (markeraddbuttonactive or markerdeletebuttonactive)
    {
        MouseMoveMarker->setBrush(QBrush(Qt::red));
        MouseMoveMarker->setStyle(QCPItemTracer::TracerStyle::tsCrosshair);
        MouseMoveMarker->setGraphKey(this->xAxis->pixelToCoord(event->pos().x()));
        MouseMoveMarker->setGraph(graph());
        MouseMoveMarker->setInterpolating(true);
        MouseMoveMarker->setSize(0.1);

        MouseMoveLabel->setPositionAlignment(Qt::AlignRight|Qt::AlignBottom);
        MouseMoveLabel->position->setCoords(MouseMoveMarker->position->key(),MouseMoveMarker->position->value());
        MouseMoveLabel->setText(QString("(")+QString::number(MouseMoveMarker->position->key())+QString(",")+QString::number(MouseMoveMarker->position->value())+QString(")"));
        MouseMoveLabel->setTextAlignment(Qt::AlignLeft);
        MouseMoveLabel->setFont(QFont(font().family(), 9));
        //MouseMoveLabel->setPadding(QMargins(8, 0, 0, 0));
        replot();
    }
}


void PlotClass::mousePressEvent(QMouseEvent *event)
{
    QCustomPlot::mousePressEvent(event);

    if (markeraddbuttonactive)
    {
        QCPItemTracer * NewMarker = new QCPItemTracer(this);
        NewMarker->setBrush(QBrush(Qt::red));
        NewMarker->setStyle(QCPItemTracer::TracerStyle::tsPlus);
        NewMarker->setGraphKey(this->xAxis->pixelToCoord(event->pos().x()));
        NewMarker->setGraph(graph());
        NewMarker->setInterpolating(true);
        NewMarker->setSize(20);

        QCPItemText *NewMarkerLabel = new QCPItemText(this);
        NewMarkerLabel->setPositionAlignment(Qt::AlignRight|Qt::AlignBottom);
        NewMarkerLabel->position->setCoords(NewMarker->position->key(),NewMarker->position->value());
        NewMarkerLabel->setText(QString("(")+QString::number(NewMarker->position->key())+QString(",")+QString::number(NewMarker->position->value())+QString(")"));
        NewMarkerLabel->setTextAlignment(Qt::AlignLeft);
        NewMarkerLabel->setFont(QFont(font().family(), 9));
        NewMarkerLabel->setVisible(false);

        connect(NewMarker,&QCPItemTracer::selectionChanged,[NewMarkerLabel, NewMarker,this]()
                {
                    NewMarkerLabel->setVisible(NewMarker->selected());

                    if (markerdeletebuttonactive && NewMarker->selected())
                    {
                        removeItem(NewMarker);
                        removeItem(NewMarkerLabel);
                    }

                    /*
                    else if  (this->selectedItems().isEmpty())
                    {
                        removeItem(NewMarker);
                        removeItem(NewMarkerLabel);
                    }*/

                }
                );


        //MarkerList.append(NewMarker); //Почему ошибка?

        replot();
    }

}


void PlotClass::ResetPlot()
{
    rescaleAxes();
    replot();
}


void PlotClass::SavePlot()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Сохранить как", "", "PNG File (*.png);;JPEG File (*.jpg);;PDF File (*.pdf)");

    if (!filePath.isEmpty()) {
        // Determine the file format based on the file extension
        QString fileFormat = QFileInfo(filePath).suffix();

        // Save the plot in the selected format
        if (fileFormat == "png") {
            savePng(filePath);
        } else if (fileFormat == "jpg") {
            saveJpg(filePath);
        } else if (fileFormat == "pdf") {
            savePdf(filePath);
        }
    }
}



void PlotClass::DeleteAllMarkers()
{

    for (int i=0; i < itemCount();i++)
    {
        if (dynamic_cast<QCPItemText*>(item(i)) && dynamic_cast<QCPItemText*>(item(i))!=MouseMoveLabel)
        {
            removeItem(item(i));
        }
        else if (dynamic_cast<QCPItemTracer*>(item(i)) && dynamic_cast<QCPItemTracer*>(item(i))!=MouseMoveMarker)
        {
            removeItem(item(i));
        }
    }
}

