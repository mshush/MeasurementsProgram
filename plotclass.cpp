#include "plotclass.h"

PlotClass::PlotClass(QWidget * parent) : QCustomPlot(parent)
{
    // ??? antialiased
    //this->resize(1800,1000);
    //this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    RefreshTimer = new QTimer(this);
    MarkerStyle=1;
    AddedMarkersList.clear();
    AddedMarkerLabelsList.clear();


    MouseMoveMarker = new QCPItemTracer(this);
    MouseMoveLabel = new QCPItemText(this);

    MouseMoveMarker->setBrush(QBrush(Qt::black));
    MouseMoveMarker->setPen(QPen(Qt::black));
    MouseMoveMarker->setStyle(QCPItemTracer::TracerStyle(2));
    MouseMoveMarker->setSize(0.1);

    MouseMoveLabel->setPositionAlignment(Qt::AlignRight|Qt::AlignBottom);
    MouseMoveLabel->setTextAlignment(Qt::AlignLeft);
    MouseMoveLabel->setFont(QFont(font().family(), 9));

    MouseMoveMarker->setVisible(false);
    MouseMoveLabel->setVisible(false);
    MouseMoveMarker->setSelectable(false);
    MouseMoveLabel->setSelectable(false);

    x = QVector <double> (1601);
    y = QVector <double> (1601);


    y[0] = 0;
    x[0] = -800;

    generator = std::default_random_engine (time(0));
    distribution = std::normal_distribution<double> (0.0, 1.0);
    //distribution = std::gamma_distribution<double> (0.0, 1.0);
    //distribution = std::cauchy_distribution<double> (0.0, 1.0);
    for (int i=1; i<1601; ++i)
    {
        x[i] = i - 800;
        y[i] = y[i-1] + distribution(generator);
    }
    for (int i=1; i<1601; ++i)
    {
        if (i % 100 == 0)
            {
                y[i] += 20.0 * distribution(generator);
            }
    }

    addGraph();
    graph(0)->setData(x, y);

    xAxis->setLabel("Частота");
    yAxis->setLabel("Амплитуда");

    rescaleAxes();
    replot();

    setInteractions(QCP::iRangeZoom | QCP::iRangeDrag | QCP::iSelectItems);

}


void PlotClass::mouseMoveEvent(QMouseEvent *event)
{
    QCustomPlot::mouseMoveEvent(event);

    if (markeraddbuttonactive or markerdeletebuttonactive)
    {

        MouseMoveMarker->setGraphKey(this->xAxis->pixelToCoord(event->pos().x()));
        MouseMoveMarker->setGraph(graph());

        MouseMoveLabel->position->setCoords(MouseMoveMarker->position->key(),MouseMoveMarker->position->value());
        MouseMoveLabel->setText(QString("(")+QString::number(MouseMoveMarker->position->key())+QString(",")+QString::number(MouseMoveMarker->position->value())+QString(")"));
        replot();
    }
}


void PlotClass::mousePressEvent(QMouseEvent *event)
{
    QCustomPlot::mousePressEvent(event);

    if (markeraddbuttonactive)
    {
        QCPItemTracer * NewMarker = new QCPItemTracer(this); //Чтобы открепить от graph можно NewMarker->setGraph(nullptr);
        NewMarker->setPen(QPen(MarkerColour));
        NewMarker->setBrush(QBrush(MarkerColour));
        NewMarker->setStyle(QCPItemTracer::TracerStyle(MarkerStyle));
        NewMarker->setGraphKey( this->xAxis->pixelToCoord( event->pos().x() ) ); //Разобраться как работает
        NewMarker->setGraph(graph());
        //NewMarker->setInterpolating(true);
        NewMarker->setSize(15);

        QCPItemText * NewMarkerLabel = new QCPItemText(this);
        NewMarkerLabel->setPositionAlignment(Qt::AlignRight|Qt::AlignBottom);
        NewMarkerLabel->position->setCoords(NewMarker->position->key(),NewMarker->position->value());
        QString LabelText = "(" + QString::number(NewMarker->position->key()) + "," + QString::number(NewMarker->position->value()) + ")";
        NewMarkerLabel->setText(LabelText);
        NewMarkerLabel->setTextAlignment(Qt::AlignLeft);
        NewMarkerLabel->setFont(QFont(font().family(), 9));
        NewMarkerLabel->setVisible(false);


        //connect(this,&PlotClass:: // Сделать так, чтобы менялось положение NewMarkerLabel при движении графика.

        connect(NewMarker,&QCPItemTracer::selectionChanged,this, [NewMarkerLabel, NewMarker,this]()
                {
                    NewMarkerLabel->setVisible(NewMarker->selected());

                    if (markerdeletebuttonactive && NewMarker->selected())
                    {
                        removeItem(NewMarker);
                        removeItem(NewMarkerLabel);
                        AddedMarkersList.remove(NewMarker);
                        AddedMarkerLabelsList.remove(NewMarkerLabel);
                    }
                 }
                );


        AddedMarkersList.push_back(NewMarker); //Почему аварийно завершается?
        AddedMarkerLabelsList.push_back(NewMarkerLabel);

        replot();
    }

}


void PlotClass::ResetPlot()
{
    rescaleAxes();
    replot();
    qDebug()<<this->axisRect()->rect().size();
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

void PlotClass::CopyPlot()
{
    QPixmap PlotPixmap = this->toPixmap();
    QImage PlotImage = PlotPixmap.toImage();
    QClipboard *ClipBoard = QApplication::clipboard();
    ClipBoard->setImage(PlotImage);
}



void PlotClass::DeleteAllMarkers()
{
    for (QCPItemTracer* MarkerIterator : AddedMarkersList) {
        removeItem(MarkerIterator);
    }
    for (QCPItemText* MarkerLabelIterator : AddedMarkerLabelsList) {
        removeItem(MarkerLabelIterator);
        //qDebug()<<"Was Here";
    }
    AddedMarkersList.clear();
    AddedMarkerLabelsList.clear();

    replot();

    /*
    //qDebug()<<itemCount();
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
    */
}



void PlotClass::Measure()
{
    //qDebug()<<"Размер виджета графика = " <<this->rect().size() << ", Размер графика = " << this->axisRect()->rect().size();

    y[0] = y[1600];
    for (int i=1; i<1601; ++i)
    {
        y[i] = y[i-1] + distribution(generator);
    }
    for (int i=1; i<1601; ++i)
    {
        if (i % 100 == 0)
        {
            y[i] += 10.0 * distribution(generator);
        }
    }
    graph(0)->setData(x, y);
    rescaleAxes();
    replot();
}


void PlotClass::MeasureContinuously()
{
    if (qobject_cast<QPushButton*>(sender())->isChecked())
    {
        connect(RefreshTimer, &QTimer::timeout, this, &PlotClass::RefreshPlot);

        RefreshTimer->start(100);
    }
    else
    {
        disconnect(RefreshTimer, &QTimer::timeout, this, &PlotClass::RefreshPlot);
    }
}


void PlotClass::RefreshPlot()
{

    for (int i=0; i<1600; ++i)
    {
        y[i] = y[i+1];
    }
    y[1600] = y[1599]+distribution(generator);

    if (time(0)%10==0)
    {
        y[1599] += distribution(generator)*30.0;
    }

    graph(0)->setData(x, y);
    //rescaleAxes();
    replot();
}


void PlotClass::SaveData()
{
    //QString SaveDirectory = QFileDialog::getExistingDirectory(this, "Select Directory", QDir::homePath());
    QString FilePath = QFileDialog::getSaveFileName(this, "Save File", QDir::homePath() + "/MyData.dat", "Data Files (*.dat);;All Files (*)");

    QFile File(FilePath);
    if (!File.open(QIODevice::WriteOnly)) {
        qWarning() << "Could not open file for writing:" << File.errorString();
        return;
    }

    QDataStream out(&File);
    out << x << y;
    File.close();

}

/*
void PlotClass::ImportData()
{
    QString FilePath = QFileDialog::getOpenFileName(this, "Select File to Load", QDir::homePath(), "Data Files (*.dat)");

    QFile File(FilePath);
    if (!File.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open file for reading:" << File.errorString();
    }

    QDataStream in(&File);
    in >> x >> y;
    File.close();

    graph(0)->setData(x, y);
    rescaleAxes();
    replot();
}
*/





// Убедиться, что ошибается не более чем на один пиксель
// Размер графика нельзя менять. Люди привыкают как выглядит -- привыкают, могут сказать, что ошибка. Интерфейс как прибор
// Прорежевание -- опасно, так как острые пики может неправильно показать
// Посмотреть, как с этим работает QCustomPlot.
// dynamic_cast не надо использовать. Лучше хранить массив. В Qt есть автоматический сборщик мусора (определяет -- используется или нет, можно не удалять). Всё наследуется из QObject, вся память -- древовидная структура (у всех parent).
// При удалении виджета рекурсивно удаляются дети. Если удалять вручную, то программа упадёт. не факт, что из-за delete программа падала.
// Сколько занимает dynamic_cast?+
// Псевдо бэкенд. Что там нужно?
// Результаты измерений. Сделать создание, сохранение массива и подгрузку.
// Как обновляется график? Какой-то сигнал от бэкенда? Измерить -- посылаем данные в backend.
// Программа должна выглядеть полностью работающей, но с бэкендом.
// 1. задание параметров, 2. Измер backgr response единичн , многократное, отобр графиков результатов: дальн портрет, диаграмму. +
// Помимо сохранения, копирование в clipboard (чтобы cntrl+V) +
// Кто сохраняет данные в (в .dat) массив из x и y. Чтобы открывать в др программах
// Кто обрабатывает, существует ли прорежевание, сохраняет (не в .dat, лучше непонятное расширение)(в .dat).
// Загрузить background и response. RubberBand
// Добавить Rubberband: квадратный, гориз (увел с запретом на увел по одной из осей), верт
// valgrind perf perfmon profiler. Попробовать qt профайлер
// Обрезание графика и сохранение обрезанного






