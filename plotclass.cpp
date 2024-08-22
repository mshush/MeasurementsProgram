#include "plotclass.h"

PlotClass::PlotClass(QWidget * parent) : QCustomPlot(parent)
{

    this->setMinimumSize(1000,600);
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    //RefreshTimer = new QTimer(this);
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

    /*
    x = QVector <double> (NumberOfPoints);
    for (int i=0;i<NumberOfPoints;i++)
    {
        x[i] = FreqStart + i* (FreqStop-FreqStart)/(NumberOfPoints-1);
    }
    y = QVector <double> (NumberOfPoints);
    f = QVector <std::complex<double>> (NumberOfPoints);
    */


    addGraph();
    addGraph();
    //graph(0)->setData(x, y);


    xAxis->setLabel("Частота");
    yAxis->setLabel("Амплитуда");

    //graph(0)->pen().setWidth(1);
    //xAxis->setRange(0,1600);
    //rescaleAxes();
    //replot();

    setInteractions(QCP::iRangeZoom | QCP::iRangeDrag | QCP::iSelectItems);


    SelectionRectClass * SelectionRectangle = new SelectionRectClass(this);
    this->setSelectionRect(SelectionRectangle);
}


void PlotClass::mouseMoveEvent(QMouseEvent *event)
{
    QCustomPlot::mouseMoveEvent(event);

    if (markeraddbuttonactive or markerdeletebuttonactive)
    {

        MouseMoveMarker->setGraphKey(this->xAxis->pixelToCoord(event->pos().x()));
        MouseMoveMarker->setGraph(graph(0));

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
        AddNewMarker(this->xAxis->pixelToCoord(event->pos().x()), MarkerStyle, MarkerColour);
        replot();
    }

}


void PlotClass::ResetPlot()
{
    rescaleAxes();
    replot();
    //qDebug()<<this->axisRect()->rect().size();
}


void PlotClass::SavePlot()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Сохранить как", "", "PNG File (*.png);;JPEG File (*.jpg);;PDF File (*.pdf)");

    if (!filePath.isEmpty()) {
        QString fileFormat = QFileInfo(filePath).suffix();

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
    }
    AddedMarkersList.clear();
    AddedMarkerLabelsList.clear();

    replot();

}



void PlotClass::SaveData()
{
//Перенесено в TabWidgetForCharts
}




// ПЕРЕНЕСТИ В MAINWINDOW
/*
void PlotClass::FourierTransform()
{

    QVector <std::complex<double>> Transform(1601);
    for (int i=0;i<1601;i++)
    {
        Transform[i] = 0;
        for (int j=0;j<1601;j++)
        {
            Transform[i] += f[j] * exp( - std::complex<double>(0, 2 * M_PI * j * i / 1601));
        }
        Transform[i]/=1601;

    }
    f = Transform;
    for (int i=0;i<1601;i++)
    y[i] = abs(Transform[i]);

    graph(0)->setData(x, y);
    rescaleAxes();
    replot();
}
*/




/*
void PlotClass::InverseFourierTransform()
{


    QVector <std::complex<double>> Transform(1601);
    for (int i=0;i<1601;i++)
    {
        Transform[i] = 0;
        for (int j=0;j<1601;j++)
        {
            Transform[i] += f[j] * exp( std::complex<double>(0, 2 * M_PI * j * i / 1601));
        }
    }
    f = Transform;
    for (int i=0;i<1601;i++)
        y[i] = abs(Transform[i]);

    graph(0)->setData(x,y);
    rescaleAxes();
    replot();
}
*/




void PlotClass::AddNewMarker(double Key, int Style, QColor Colour)
{

    QCPItemTracer * NewMarker = new QCPItemTracer(this);
    //NewMarker->setGraph(nullptr);//Чтобы открепить от graph
    NewMarker->setPen(QPen(Colour));
    NewMarker->setBrush(QBrush(Colour));
    NewMarker->setStyle(QCPItemTracer::TracerStyle(Style));
    NewMarker->setGraph(graph(0));
    NewMarker->setGraphKey( Key ); //Разобраться как работает pixelToCoord
    //NewMarker->setInterpolating(true); // Плавное передвижение вдоль линий
    NewMarker->setSize(15);
    //qDebug()<<Key;

    QCPItemText * NewMarkerLabel = new QCPItemText(this); // Сделать подпись в углу, фиксированной
    NewMarkerLabel->setPositionAlignment(Qt::AlignRight|Qt::AlignBottom);
    NewMarkerLabel->position->setCoords(NewMarker->position->key(),NewMarker->position->value());
    QString LabelText = "(" + QString::number(NewMarker->position->key()) + "," + QString::number(NewMarker->position->value()) + ")";
    NewMarkerLabel->setText(LabelText);
    NewMarkerLabel->setTextAlignment(Qt::AlignLeft);
    NewMarkerLabel->setFont(QFont(font().family(), 9));
    NewMarkerLabel->setColor(Colour);
    NewMarkerLabel->setVisible(false);


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


    AddedMarkersList.push_back(NewMarker);
    AddedMarkerLabelsList.push_back(NewMarkerLabel);

}

/*
QVector <std::complex<double>> PlotClass::FourierTransformVector(QVector <std::complex<double>> Vector) // Перенести куда-нибудь (наверное в TabWidgetForCharts)
{
    int VectorSize = Vector.size();

    QVector <std::complex<double>> Transform(1601);
    for (int i=0;i<VectorSize;i++)
    {
        Transform[i] = 0;
        for (int j=0;j<VectorSize;j++)
        {
            Transform[i] += Vector[j] * exp( - std::complex<double>(0, 2 * M_PI * j * i / VectorSize));
        }
        Transform[i]/=VectorSize;
    }
    return Transform;
}
*/



/*
void PlotClass::UpdateMeasuredData(QVector <std::complex<double>> MeasuredData)
{
    f = MeasuredData;
    for (int i=0;i<NumberOfPoints;i++)
    {
        y[i] = abs(f[i]);
    }
    graph(0)->setData(x, y);
    if (!ContinuousMeasurementMode)
    {
        rescaleAxes();
    }
    replot();
}
*/


/*
void PlotClass::UpdateBackgroundPlot (QVector <std::complex<double>> bf)
{
    QVector <double> by(bf.size());
    for (int i=0;i<bf.size();i++)
    {
        by[i] = abs(bf[i]);
    }
    graph(1)->setData(x, by);

    if (ContinuousMeasurementMode)
    {
        //Выдать какую-нибудь ошибку
    }

    rescaleAxes();// Вызывать отдельно, чтобы графики менялись не по-очереди!!!
    replot();
}
*/





PlotClass::~PlotClass()
{
    /*
    delete MouseMoveMarker;
    delete MouseMoveLabel;

    for (auto marker : AddedMarkersList) {
        delete marker;
    }
    for (auto label : AddedMarkerLabelsList) {
        delete label;
    }
    delete RefreshTimer;
    */
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


/*
void PlotClass::Measure()
{
    y[0] = 0;
    x[0] = 0;
    f[0] = std::complex<double>(0,0);

    for (int i=1; i<1601; ++i)
    {
        x[i] = i;
        //y[i] = y[i-1] + distribution(generator);
        f[i] = f[i-1] + std::complex<double> (distribution(generator),distribution(generator)) ;
        y[i] = abs(f[i]);
    }

    graph(0)->setData(x, y);
    rescaleAxes();
    replot();


    //qDebug()<<"Размер виджета графика = " <<this->rect().size() << ", Размер графика = " << this->axisRect()->rect().size();

    // Не используется
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
    // ----

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
    //не используется----
    y[0] = 0;
    f[0] = std::complex<double>(0,0);

    for (int i=1; i<1601; ++i)
    {
        //y[i] = y[i-1] + distribution(generator);
        f[i] = f[i-1] + std::complex<double> (distribution(generator),distribution(generator)) ;
        y[i] = abs(f[i]);
    }
    //-------------------


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
// +Добавить Rubberband: квадратный, гориз (увел с запретом на увел по одной из осей), верт
// valgrind perf perfmon profiler. Попробовать qt профайлер
// Обрезание графика и сохранение обрезанного

// Measure в новой вкладке + сразу название файла с датой и временем.

// Сколько точек
// ЭПР сферы

// Добавить ProgressBar в QMainWindow
// Убрать из plotclass все комплексные функции -- оставить только абсолютные значения



