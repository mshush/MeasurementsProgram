#include "plotclass.h"

PlotClass::PlotClass(QWidget * parent) : QCustomPlot(parent)
{

    //this->setMinimumSize(800,600);
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);


    setBackground(QBrush(Qt::black));
    xAxis->setBasePen(QPen(Qt::white));
    yAxis->setBasePen(QPen(Qt::white));
    xAxis->setTickPen(QPen(Qt::white));
    yAxis->setTickPen(QPen(Qt::white));
    xAxis->setLabelColor(Qt::white);
    yAxis->setLabelColor(Qt::white);
    xAxis->setTickLabelColor(Qt::white);
    yAxis->setTickLabelColor(Qt::white);


    //RefreshTimer = new QTimer(this);
    MarkerStyle=1;
    AddedMarkersList.clear();
    AddedMarkerLabelsList.clear();


    MouseMoveMarker = new QCPItemTracer(this); // Перенести маркер в отдельный QCPLayer? Затем Layer->setMode(QCPLayer::lmBuffered); (Чтобы работало быстрее можно попробовать так)
    MouseMoveLabel = new QCPItemText(this);

    MouseMoveMarker->setBrush(QBrush(Qt::white));
    MouseMoveMarker->setPen(QPen(Qt::white));
    MouseMoveMarker->setStyle(QCPItemTracer::TracerStyle(2));
    MouseMoveMarker->setSize(0.1);

    MouseMoveLabel->setPositionAlignment(Qt::AlignRight|Qt::AlignBottom);
    MouseMoveLabel->setTextAlignment(Qt::AlignLeft);
    MouseMoveLabel->setFont(QFont(font().family(), 9));

    MouseMoveMarker->setVisible(false);
    MouseMoveLabel->setVisible(false);
    MouseMoveMarker->setSelectable(false);
    MouseMoveLabel->setSelectable(false);

    //MouseMoveMarker->setGraph(graph(SelectedGraph));

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
    graph(0)->setPen(QPen(Qt::green));
    graph(0)->setPen(QPen(Qt::yellow));


    xAxis->setLabel("Частота");
    yAxis->setLabel("Амплитуда");



    PlotLabel = new QCPItemText(this);
    PlotLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignRight);
    PlotLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    PlotLabel->position->setCoords(1, 0);
    PlotLabel->setText("x=0.00\ny=0.00");
    //PlotLabel->setFont(QFont());//(QFont(font().family(), 16));
    PlotLabel->setColor(Qt::white);
    PlotLabel->setPen(QPen(Qt::white));
    PlotLabel->setClipToAxisRect(false);



    setInteractions(QCP::iRangeZoom | QCP::iRangeDrag | QCP::iSelectItems);


    SelectionRectClass * SelectionRectangle = new SelectionRectClass(this);
    this->setSelectionRect(SelectionRectangle);


    Timer = new QTimer(this);

    this->layer(0)->setMode(QCPLayer::lmBuffered);

}


void PlotClass::mouseMoveEvent(QMouseEvent *event)
{
    QCustomPlot::mouseMoveEvent(event);

    QString xpos = QString::number(xAxis->pixelToCoord(event->pos().x()), 'f', 2); // f = fixed point notation, e = scientific notation
    QString ypos = QString::number(yAxis->pixelToCoord(event->pos().y()), 'f', 2);
    PlotLabel->setText("x="+xpos+"\n"+"y="+ypos);
    replot();

    if (markeraddbuttonactive or markerdeletebuttonactive) // Здесь менять видимость label с положением курсора
    {

        MouseMoveMarker->setGraphKey(this->xAxis->pixelToCoord(event->pos().x()));
        MouseMoveMarker->setGraph(graph(SelectedGraph));

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
        AddNewMarker(this->xAxis->pixelToCoord(event->pos().x()), MarkerStyle, MarkerColour, SelectedGraph);
        replot();
    }

}


void PlotClass::ResetPlot()
{
    rescaleAxes();
    replot();
}


void PlotClass::SaveAs()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Сохранить как", "", "PNG File (*.png);;JPEG File (*.jpg);;PDF File (*.pdf);;DAT File (*.dat);;CSV File (*.csv)");

    if (!filePath.isEmpty()) {
        QString fileFormat = QFileInfo(filePath).suffix();

        if (fileFormat == "png")
        {
            this->PlotLabel->setVisible(false); // Если не нужно добавить другой информации в PlotLabel кроме положения курсора, то сделать так везде.
            savePng(filePath);
            this->PlotLabel->setVisible(true);
        }
        else if (fileFormat == "jpg")
        {
            saveJpg(filePath);
        }
        else if (fileFormat == "pdf")
        {
            savePdf(filePath);
        }
        else if (fileFormat == "dat")
        {
            saveDat(filePath);
        }
        else if (fileFormat == "csv")
        {
            saveCsv(filePath);
        }
    }
}


void PlotClass::OpenFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Открыть", "", "DAT File (*.dat);;CSV File (*.csv)");

    if (!filePath.isEmpty()) {
        QString fileFormat = QFileInfo(filePath).suffix();

        if (fileFormat == "dat")
        {
            loadDat(filePath);
        }
        else if (fileFormat == "csv")
        {
            loadCsv(filePath);
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
    for (QCPItemTracer* MarkerIterator : AddedMarkersList)
    {
        removeItem(MarkerIterator);
    }
    for (QCPItemText* MarkerLabelIterator : AddedMarkerLabelsList)
    {
        removeItem(MarkerLabelIterator);
    }
    AddedMarkersList.clear();
    AddedMarkerLabelsList.clear();

    CurrentMarkerIndex = 0;
    replot();
    emit AllMarkersDeletedSignal();
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




void PlotClass::AddNewMarker(double Key, int Style, QColor Colour, int GraphNumber)
{

    QCPItemTracer * NewMarker = new QCPItemTracer(this);
    //NewMarker->setGraph(nullptr);//Чтобы открепить от graph
    NewMarker->setPen(QPen(Colour));
    NewMarker->setBrush(QBrush(Colour));
    NewMarker->setStyle(QCPItemTracer::TracerStyle(Style));
    NewMarker->setGraph(graph(GraphNumber)); // Как обозначать null?
    NewMarker->setGraphKey( Key ); //+Разобраться как работает pixelToCoord

    NewMarker->setInterpolating(false); //Плавное передвижение вдоль линий -- не нужно ставить маркер между точками
    NewMarker->setSize(15);
    //qDebug()<<Key;

    QCPItemText * NewMarkerLabel = new QCPItemText(this); // +Сделать подпись в углу, фиксированной.// +Скрывать видимость на время сохранения?
    NewMarkerLabel->setPositionAlignment(Qt::AlignRight|Qt::AlignBottom);
    NewMarkerLabel->position->setCoords(NewMarker->position->key(),NewMarker->position->value());
    //QString LabelText = "(" + QString::number(NewMarker->position->key()) + "," + QString::number(NewMarker->position->value()) + ")";
    QString LabelText = QString::number(CurrentMarkerIndex);
    CurrentMarkerIndex++;
    NewMarkerLabel->setText(LabelText);
    NewMarkerLabel->position->setCoords(NewMarker->position->key(), NewMarker->position->value());
    NewMarkerLabel->setTextAlignment(Qt::AlignLeft);
    NewMarkerLabel->setFont(QFont(font().family(), 9));
    NewMarkerLabel->setColor(Colour);
    NewMarkerLabel->setVisible(false);



    connect(NewMarker,&QCPItemTracer::selectionChanged,this, [NewMarkerLabel, NewMarker,this]()
            {
                NewMarkerLabel->setVisible(NewMarker->selected());

                if (markerdeletebuttonactive && NewMarker->selected())
                {


                    int DeletedMarkerIndex = 0;
                    std::list<QCPItemTracer*>::iterator it = AddedMarkersList.begin();
                    while (it != AddedMarkersList.end())
                    {
                        if (*it == NewMarker)
                        {
                            break;
                        }
                        it++;
                        DeletedMarkerIndex++;
                    }
                    emit MarkerDeletedSignal(DeletedMarkerIndex);

                    removeItem(NewMarker);
                    removeItem(NewMarkerLabel);
                    AddedMarkersList.remove(NewMarker);
                    AddedMarkerLabelsList.remove(NewMarkerLabel);

                }
                else if (NewMarker->selected())
                {
                    int SelectedMarkerIndex = 0;
                    std::list<QCPItemTracer*>::iterator it = AddedMarkersList.begin();
                    while (it != AddedMarkersList.end())
                    {
                        if (*it == NewMarker)
                        {
                            break;
                        }
                        it++;
                        SelectedMarkerIndex++;
                    }
                    emit MarkerSelectedSignal(SelectedMarkerIndex);
                }
                else if (!NewMarker->selected())
                {
                    int UnSelectedMarkerIndex = 0;
                    std::list<QCPItemTracer*>::iterator it = AddedMarkersList.begin();
                    while (it != AddedMarkersList.end())
                    {
                        if (*it == NewMarker)
                        {
                            break;
                        }
                        it++;
                        UnSelectedMarkerIndex++;
                    }
                    emit MarkerUnSelectedSignal(UnSelectedMarkerIndex);
                }

            }
            );


    AddedMarkersList.push_back(NewMarker);
    AddedMarkerLabelsList.push_back(NewMarkerLabel);
    emit MarkerAddedSignal(NewMarker);

}



void PlotClass::ContinuousMeasurementsModeChanged(bool ModeStatus)
{
    ContinuousMeasurementMode = ModeStatus;

    if (ModeStatus)
    {
        connect(Timer, &QTimer::timeout, this, &PlotClass::ResetPlot);

        Timer->setInterval(10);
        Timer->start();
        //qDebug()<<"Replotted!";
    }
    else
    {
        disconnect(Timer, &QTimer::timeout, this, &PlotClass::ResetPlot);
        Timer->stop();
    }
}


void PlotClass::ChangeSelectedGraph(int GraphId)
{
    SelectedGraph = GraphId;
    if (graph(GraphId)->data()->isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Предупреждение!");
        msgBox.setText("Выбранный график пуст");
        msgBox.setInformativeText("Убедитесь, что вы добавили график");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
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



void PlotClass::saveDat(QString FilePath)  //Доделать сохранение внешнего вида (Или по умолчанию везде одинаковые цвета?)
{

    QFile File(FilePath);
    if (!File.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<< "Не получилось записать";
        return;
    }

    QDataStream QOut(&File);

    QOut << graphCount();

    for (int i = 0; i < graphCount(); i++)  //Сохраняем все данные графиков
    {
        QCPGraph *graph = this->graph(i);
        //QOut << i;

        QOut<< graph->data()->size();       //Число точек графика
        for (int j = 0; j < graph->data()->size(); j++)
        {
            double x = graph->data()->at(j)->key;
            double y = graph->data()->at(j)->value;
            QOut << x << y;
        }

        QOut << AddedMarkersList.size();

        QOut << this->AddedMarkersList.size();
        for (const auto& marker : this->AddedMarkersList)
        {
            QOut << marker->position->key() << marker->position->value();
            QOut << marker->style();
            QOut << marker->brush().color();
        }
    }

    File.close();

}



void PlotClass::loadDat(QString FilePath) //Перенести туда, где будет использоваться. Что не так???????
{

    QFile File(FilePath);
    if (!File.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<< "Не получилось прочитать";  // Ошибки в отдельную вкладку
        return;
    }

    QDataStream QIn(&File);

    PlotClass * LoadedPlot = this;

    int NumberOfGraphs = 0 ;
    QIn >> NumberOfGraphs;

    for (int i = 0; i < NumberOfGraphs; i++)    //Выгружаем все данные графиков
    {
        LoadedPlot->addGraph();


        int NumberOfPointsInGraph;

        QIn >>NumberOfPointsInGraph;            //Число точек графика

        QVector <double> LoadedXVector, LoadedYVector;


        for (int j = 0; j < NumberOfPointsInGraph; j++)
        {
            double x;
            double y;
            QIn >> x >> y;
            qDebug()<<"x,y="<<x<<y;
            LoadedXVector.append(x);
            LoadedYVector.append(y);
        }

        //LoadedPlot->XVector = LoadedXVector;
        //LoadedPlot->YVector = LoadedYVector;

        LoadedPlot->graph(i)->setData(LoadedXVector, LoadedYVector);

        int NumberOfMarkersInGraph;

        QIn >> NumberOfMarkersInGraph;

        qDebug()<<NumberOfMarkersInGraph;
        this->AddedMarkersList.clear();

        for (const auto& marker : this->AddedMarkersList)
        {
            double MKey, MValue;
            int MStyle;
            QColor MColour;

            QIn >> MKey;
            QIn >> MValue;
            QIn >> MStyle;
            QIn >> MColour;
            qDebug()<<MColour;

            LoadedPlot->AddNewMarker( MKey, MStyle, MColour, i); //
        }
    }

    replot();
    File.close();

}


void PlotClass::loadCsv(QString FilePath) //Проверить в Origin и Excel
{
    QFile File(FilePath);
    if (!File.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Не удалось открыть файл для чтения");
        return;
    }


    clearGraphs();

    QVector <double> XVector, YVector;

    QTextStream in(&File);

    QString Header = in.readLine();

    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        if (fields.size() >= 2)
        {
            bool XIndicatorOfSuccessfulConversion, YIndicatorOfSuccessfulConversion;
            double x = fields[0].toDouble(&XIndicatorOfSuccessfulConversion);
            double y = fields[1].toDouble(&YIndicatorOfSuccessfulConversion);

            if (XIndicatorOfSuccessfulConversion && YIndicatorOfSuccessfulConversion)
            {
                XVector.append(x);
                YVector.append(y);
            }
        }
    }

    graph(0)->setData(XVector, YVector);
    replot();
    File.close();
}


void PlotClass::saveCsv(QString FilePath)
{
    QFile File(FilePath);
    if (!File.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<< "Не получилось прочитать";  // Ошибки в отдельную вкладку
        return;
    }

    QDataStream QIn(&File);

    PlotClass * LoadedPlot = this;

    int NumberOfGraphs = 0 ;
    QIn >> NumberOfGraphs;

    for (int i = 0; i < NumberOfGraphs; i++)    //Выгружаем все данные графиков
    {
        LoadedPlot->addGraph();


        int NumberOfPointsInGraph;

        QIn >>NumberOfPointsInGraph;            //Число точек графика

        QVector <double> LoadedXVector, LoadedYVector;


        for (int j = 0; j < NumberOfPointsInGraph; j++)
        {
            double x;
            double y;
            QIn >> x >> y;
            qDebug()<<"x,y="<<x<<y;
            LoadedXVector.append(x);
            LoadedYVector.append(y);
        }

        //LoadedPlot->XVector = LoadedXVector;
        //LoadedPlot->YVector = LoadedYVector;

        LoadedPlot->graph(i)->setData(LoadedXVector, LoadedYVector);

        int NumberOfMarkersInGraph;

        QIn >> NumberOfMarkersInGraph;

        qDebug()<<NumberOfMarkersInGraph;
        this->AddedMarkersList.clear();

        for (const auto& marker : this->AddedMarkersList)
        {
            double MKey, MValue;
            int MStyle;
            QColor MColour;

            QIn >> MKey;
            QIn >> MValue;
            QIn >> MStyle;
            QIn >> MColour;
            qDebug()<<MColour;

            LoadedPlot->AddNewMarker( MKey, MStyle, MColour, i); //
        }
    }

    replot();
    File.close();

}



double PlotClass::SubstractMarkers(QCPItemTracer * Marker1, QCPItemTracer * Marker2)
{
    double Result = Marker1->position->value()-Marker2->position->value();
    return Result;
}






void PlotClass::ToNextMax()
{
// Перенесено в WidgetForCustomPlot
}


void PlotClass::ToPrevMax()
{

}













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




// +Убедиться, что ошибается не более чем на один пиксель
// +Размер графика нельзя менять. Люди привыкают как выглядит -- привыкают, могут сказать, что ошибка. Интерфейс как прибор
// +Прорежевание -- опасно, так как острые пики может неправильно показать
// +Посмотреть, как с этим работает QCustomPlot.
// +dynamic_cast не надо использовать. Лучше хранить массив. В Qt есть автоматический сборщик мусора (определяет -- используется или нет, можно не удалять). Всё наследуется из QObject, вся память -- древовидная структура (у всех parent).
// +При удалении виджета рекурсивно удаляются дети. Если удалять вручную, то программа упадёт. не факт, что из-за delete программа падала.
// +Сколько занимает dynamic_cast?+
// +-Псевдо бэкенд. Что там нужно?
// +Результаты измерений. Сделать создание, сохранение массива и подгрузку.
// +Как обновляется график? Какой-то сигнал от бэкенда? Измерить -- посылаем данные в backend.
// +Программа должна выглядеть полностью работающей, но с бэкендом.
// +1. задание параметров, 2. Измер backgr response единичн , многократное, отобр графиков результатов: дальн портрет, диаграмму. +
// +Помимо сохранения, копирование в clipboard (чтобы cntrl+V) +
// Кто сохраняет данные в (в .dat) массив из x и y. Чтобы открывать в др программах
// +Загрузить background и response. RubberBand
// +Добавить Rubberband: квадратный, гориз (увел с запретом на увел по одной из осей), верт
// /valgrind perf perfmon profiler. Попробовать qt профайлер
// !!!Обрезание графика и сохранение обрезанного

// Measure в новой вкладке + сразу название файла с датой и временем.

// Сколько точек
// ЭПР сферы

// +Добавить ProgressBar в QMainWindow
// +Убрать из plotclass все комплексные функции -- оставить только абсолютные значения
// ?Сохранение всего, что есть в QCustomPlot в .dat файл с помощью встроенной функции.
// Доделать непрерывные измерения (Почему так медленно рисует?)
// Добавить в QFileTree
// meas param
// +Доделать команду "Сделать корневой"
// Разность между двумя графиками на одной картинке
// Все ошибки в отдельную вкладку снизу
// При добавлении маркера можно менять его положение -- двигать, устанавливать в точку итд. Посчитать разность между маркерами на разных графиках.
// При сохранении графика как картинки остаётся label  с подписью координат курсора. Их необходимо убрать (Удалить и снова добавить? Выделить в отдельный слой графика?)
// Предпросмотр сохраняемого изображения
// Разность между маркерами на двух графиках
// Какие правильные диапазоны
// Починить координаты у маркеров и добавить таблицу с координатами маркеров
// Как маркеры отображать в таблице? Нумеровка маркеров.
// Доделать QTableView

/*
+Придумать способ доказать что графическое отображение соответствует табличным данным -- не съезжает, правильно интерполируется

(Взять данные)

Подводные камни? Скачки, какие ещё проблемы, поискать литературу по проблемам с построением графиков.
Убедиться, что qcustomplot правильно строит, какая там интерполяция, ничего ли он не пропускает.
*/

// Background не отображать

// В measure должны быть параметры для измерения background, calibration, response.
// Измерение только для одного угла
// background и response только для одного угла

// response calibration -- поставьте цилиндр. выводится дальностный портрет и на background И на response

// Azimuth elevation

// Убрать кнопку установить параметры -- вместо этого считать параметры из интерфейса в момент запуска measure
// response -- sweep цилиндра. calibration -- сам процесс калибровки
// Добавить окно, где видна частота для зависимости от угла, и чтобы мгновенно менялся график (Все)
// +Массив комплексных чисел -- добавить функцию, которая осуществляет пересчёт массива double в массив комплексных чисел.
// +Назвать адекватно -- Vector и слова, связанные с его функционалом.
// Параметры как передавать от интерфейса в функцию, и как сделать, чтобы они были едины для всех. Нужно сделать единую структуру для параметров.
// struct для параметров, которые передаются на установку?
// postprocess - ?
// Древо классов сделать. Таблица + список + сигналы/слоты + не заострять внимание на графиках.
// ... Во время изм на кажд угле изм зав от част. Вывод дальн портр -> выв диагр, с калибр.
// +Спросить Алексея про класс обработки


// Добавить проверку непустоты графика при установке маркера.


// Две средние колонки меняются разом!!! При движении маркера влево-вправо










