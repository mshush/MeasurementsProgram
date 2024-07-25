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
        MouseMoveMarker->setBrush(QBrush(MarkerColour));
        MouseMoveMarker->setStyle(QCPItemTracer::TracerStyle::tsCrosshair); //tsCrosshair
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
        NewMarker->setBrush(QBrush(MarkerColour));
        NewMarker->setStyle(QCPItemTracer::TracerStyle::tsSquare);//tsPlus
        NewMarker->setGraphKey( this->xAxis->pixelToCoord( event->pos().x() ) ); //Разобраться как работает
        NewMarker->setGraph(graph());
        NewMarker->setInterpolating(true);
        NewMarker->setSize(20);

        QCPItemText * NewMarkerLabel = new QCPItemText(this);
        NewMarkerLabel->setPositionAlignment(Qt::AlignRight|Qt::AlignBottom);
        NewMarkerLabel->position->setCoords(NewMarker->position->key(),NewMarker->position->value());
        QString LabelText = "(" + QString::number(NewMarker->position->key()) + "," + QString::number(NewMarker->position->value()) + ")";
        NewMarkerLabel->setText(LabelText);
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
    qDebug()<<itemCount();
    for (int i=0; i < itemCount();i++)
    {   //Зря итерируемся по всем элементам. Так оставлять нельзя, чтобы не итерироваться долго в будущем, когда появятся новые элементы
        if (dynamic_cast<QCPItemText*>(item(i)) && dynamic_cast<QCPItemText*>(item(i))!=MouseMoveLabel) // Проверить, сколько itemов, Сохранять в QList
        { //Не всё сразу удаляет, оставляет label,
            removeItem(item(i));
        }
        else if (dynamic_cast<QCPItemTracer*>(item(i)) && dynamic_cast<QCPItemTracer*>(item(i))!=MouseMoveMarker)
        {
            removeItem(item(i));
        }
    }
    replot();
}


// Убедиться, что ошибается не более чем на один пиксель
// Размер графика нельзя менять. Люди привыкают как выглядит -- привыкают, могут сказать, что ошибка. Интерфейс как прибор
// Прорежевание -- опасно, так как острые пики может неправильно показать
// Посмотреть, как с этим работает QCustomPlot.
// dynamic_cast не надо использовать. Лучше хранить массив. В Qt есть автоматический сборщик мусора (определяет -- используется или нет, можно не удалять). Всё наследуется из QObject, вся память -- древовидная структура (у всех parent).
// При удалении виджета рекурсивно удаляются дети. Если удалять вручную, то программа упадёт. не факт, что из-за delete программа падала.
// Сколько занимает dynamic_cast?
// Псевдо бэкенд. Что там нужно?
// Результаты измерений. Сделать создание, сохранение массива и подгрузку.
// Как обновляется график? Какой-то сигнал от бэкенда? Измерить -- посылаем данные в backend.
// Программа должна выглядеть полностью работающей, но с бэкендом.
// 1. задание параметров, 2. Измер backgr response единичн , многократное, отобр графиков результатов: дальн портрет, диаграмму.
// Помимо сохранения, копирование в clipboard (чтобы cntrl+V)
// Кто сохраняет данные в .dat массив из x и y. Чтобы открывать в др программах
// Кто обрабатывает, существует ли прорежевание, Загрузить

