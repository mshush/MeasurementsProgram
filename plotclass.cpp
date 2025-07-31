#include "plotclass.h"


PlotClass::PlotClass(QWidget * parent) : QCustomPlot(parent)
{
    SetUpGeneralStyle(); // Устанавливает общее оформление

    SetUpItems(); // Создаёт и настраивает вспомогательные объекты: маркер прицела, прямоугольник выделения, контекстное меню

    SetUpConnections(); // Устанавливает соединения между сигналами и слотами

    //AddEmptyGraphToPlot();
}


void PlotClass::SetUpGeneralStyle()
{
    // Размер
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    setMinimumWidth(1000);

    // Цвет фона
    setBackground(QBrush(Qt::black));

        // Позволенные взаимодействия с графиком: можно менять масштаб, двигать и выбирать объекты.
    setInteractions(QCP::iRangeZoom | QCP::iRangeDrag | QCP::iSelectItems);

    // Стиль подписи легенды // Тоже переместить наверное отдельно
    legend->setVisible(false);
    legend->setBrush(QBrush(Qt::black));
    legend->setBorderPen(QPen(Qt::white));
    legend->setTextColor(Qt::white);
    //legend->clearItems();
    //legend->clear();

}

void PlotClass::SetUpItems()
{
    // Область для информации, настраиваемой через легенду (надо поменять)
    SetUpCursorPositionText();

    // Прямоугольник выбора
    SelectionRectClass * SelectionRectangle = new SelectionRectClass(this);
    setSelectionRect(SelectionRectangle);

    // Контекстное меню
    setContextMenuPolicy(Qt::CustomContextMenu);

    // Маркер прицела
    SetUpMouseMoveMarker();

    // Оси для полярного формата графика
    SetUpPolarAxes();

    // Оси декартового формата
    SetUpDescartesAxes();

}

void PlotClass::SetUpMouseMoveMarker()
{
    // МАРКЕР ПРИЦЕЛА
    // Создаём маркер прицела и подпись к нему
    MouseMoveMarker = new QCPItemTracer(this);
    MouseMoveLabel = new QCPItemText(this);
    // Может перенести маркер в отдельный QCPLayer для более быстрой работы? Затем Layer->setMode(QCPLayer::lmBuffered);

    // Устанавливаем цвет маркера, стиль и размер
    MouseMoveMarker->setBrush(QBrush(Qt::white));
    MouseMoveMarker->setPen(QPen(Qt::white));
    MouseMoveMarker->setStyle(QCPItemTracer::TracerStyle(2));
    MouseMoveMarker->setSize(0.1);

    // Подпись к маркеру устанавливаем в правом нижнем углу (можно сделать так, чтобы менялось в зависимости от близости к границе), меняем шрифт
    MouseMoveLabel->setPositionAlignment(Qt::AlignRight|Qt::AlignBottom);
    MouseMoveLabel->setTextAlignment(Qt::AlignLeft);
    MouseMoveLabel->setFont(QFont(font().family(), 9));

    // Делаем маркер и подпись невидимыми (до надобности) и невыбираемыми
    MouseMoveMarker->setVisible(false);
    MouseMoveLabel->setVisible(false);
    MouseMoveMarker->setSelectable(false);
    MouseMoveLabel->setSelectable(false);

}

void PlotClass::SetUpPolarAxes()
{
    // Инициируем полярный график
    AngularAxis = new QCPPolarAxisAngular(this);
    AngularAxis->removeRadialAxis(AngularAxis->radialAxis()); //Убираем радиальную ось по умолчанию и создаём свою (иначе она будет отрисовываться и мешать)
    RadialAxis = new CustomRadialAxis(AngularAxis);
    AngularAxis->addRadialAxis(RadialAxis);
    qDebug()<<AngularAxis->radialAxisCount();

    // Настраиваем угловую ось
    AngularAxis->grid()->setAngularSubGridPen(QPen(Qt::white));
    AngularAxis->grid()->setRadialSubGridPen(QPen(Qt::white));
    AngularAxis->grid()->setRadialAxis(RadialAxis);
    //AngularAxis->grid()->setAngularPen(QPen(Qt::white));
    AngularAxis->setTickPen(QPen(Qt::white,2));
    AngularAxis->setLabelColor(Qt::white);
    AngularAxis->setBasePen(QPen(Qt::white,2));
    AngularAxis->setSubTickPen(QPen(Qt::white));
    AngularAxis->setTickLength(10,0);
    AngularAxis->setSubTickLength(5,0);

    // Настраиваем радиальную ось
    RadialAxis->setTickPen(QPen(Qt::white,2));
    RadialAxis->setSubTickPen(QPen(Qt::white));
    RadialAxis->setLabelColor(Qt::white);
    RadialAxis->setBasePen(QPen(Qt::white,2));


    // Устанавливает радиальную ось прямо (Положение слева устанавливается через наследование)
    RadialAxis->setTickLabelMode(QCPPolarAxisRadial::LabelMode::lmUpright);
    RadialAxis->setAngle(0);

    RadialAxis->setTickLength(-10,0);
    RadialAxis->setSubTickLength(-5,0);
    //RadialAxis->setTickLabelRotation(0);
    //RadialAxis->ticklabel
    //AngularAxis->setLabelPosition(Qt::AlignmentFlag::AlignBottom);

    //RadialAxis->setAngleReference(QCPPolarAxisRadial::AngleReference::arAbsolute);

    //Шрифт полярного графика
    QFont font("Arial",10);
    AngularAxis->setTickLabelFont(font);
    RadialAxis->setTickLabelFont(font);
    AngularAxis->setTickLabelColor(Qt::white);
    RadialAxis->setTickLabelColor(Qt::white);

    // Поведение:
    AngularAxis->setRangeZoom(true);
    AngularAxis->setRangeDrag(true);

    // Подписи к осям
    AngularAxis->setLabelColor(Qt::white);
    RadialAxis->setLabelColor(Qt::white);
    AngularAxis->setLabel(XAxisLabel);
    RadialAxis ->setLabel(YAxisLabel);
    AngularAxis->setLabelFont(QFont("Arial", 12));
    RadialAxis->setLabelFont(QFont("Arial", 12));
    AngularAxis->setVisible(true);
    RadialAxis->setVisible(true);
    qDebug()<< "Label Ang" << AngularAxis->label();


    //setBackground(QBrush(Qt::white));

    // Устанавливаем поведение отметок на графика
    QSharedPointer<QCPAxisTicker> AngularTicker = QSharedPointer<QCPAxisTicker>::create();
    AngularAxis->setTicker(AngularTicker);
    QSharedPointer<QCPAxisTicker> RadialTicker = QSharedPointer<QCPAxisTicker>::create();
    RadialAxis ->setTicker(RadialTicker);
    RadialAxis->setTickLabelPadding(-20);


    //RadialAxis->moveRange(0); // Посмотреть для смены на логарифмический
    //RadialAxis->setRange ( 0,  10, Qt::AlignmentFlag::AlignLeft);
    replot();
}

void PlotClass::SetUpDescartesAxes()
{
    // Сохраняем указатель на прямоугольник с осями (чтобы мы могли его вернуть после смены на полярный режим)
    AxisRectangle = axisRect();

    // Ось x
    xAxis->setBasePen(QPen(Qt::white));
    xAxis->setTickPen(QPen(Qt::white,2));
    xAxis->setLabelColor(Qt::white);
    xAxis->setTickLabelColor(Qt::white);
    xAxis->setLabel(XAxisLabel);

    // Ось y
    yAxis->setBasePen(QPen(Qt::white));
    yAxis->setTickPen(QPen(Qt::white,2));
    yAxis->setLabelColor(Qt::white);
    yAxis->setTickLabelColor(Qt::white);
    yAxis->setLabel(YAxisLabel);

}

void PlotClass::SetUpCursorPositionText()
{
    PlotLabel = new QCPItemText(this);
    PlotLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignLeft);
    PlotLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    PlotLabel->position->setCoords(0, 0);
    PlotLabel->setText("x=0.00\ny=0.00");
    //PlotLabel->setFont(QFont());//(QFont(font().family(), 16));
    PlotLabel->setColor(Qt::white);
    PlotLabel->setPen(QPen(Qt::white));
    PlotLabel->setClipToAxisRect(false);
    PlotLabel->setSelectable(false);// Можно сделать выбираемой, чтобы удалять при необходимости
}

void PlotClass::SetUpConnections()
{
    // Соединяем сигнал клика на график и слот смены выбранного графика
    connect(this, &PlotClass::GraphClickedSignal, this, &PlotClass::ChangeSelectedGraph);

    /*
     * Никак совсем не работает. Но скорее всего это и не нужно
    // Соединяем диапазоны осей, чтобы у полярного и декартового графиков они менялись синхронно:
    //connect(xAxis,      SIGNAL(rangeChanged(QCPRange)), AngularAxis,SIGNAL(setRange(QCPRange)));
    //connect(yAxis,      SIGNAL(rangeChanged(QCPRange)), RadialAxis, SIGNAL(setRange(QCPRange)));
    //connect(AngularAxis,SIGNAL(rangeChanged(QCPRange)), xAxis,      SIGNAL(setRange(QCPRange)));
    //connect(RadialAxis, SIGNAL(rangeChanged(QCPRange)), yAxis,      SIGNAL(setRange(QCPRange)));


    connect(xAxis,
            QOverload<const QCPRange &>::of(&QCPAxis::rangeChanged),
            AngularAxis,
            QOverload<const QCPRange &>::of(&QCPPolarAxisAngular::setRange));

    connect(yAxis,
            QOverload<const QCPRange &>::of(&QCPAxis::rangeChanged),
            RadialAxis,
            QOverload<const QCPRange &>::of(&QCPPolarAxisRadial::setRange));



    connect(AngularAxis,
            QOverload<const QCPRange &>::of(&QCPPolarAxisAngular::rangeChanged),
            xAxis,
            QOverload<const QCPRange &>::of(&QCPAxis::setRange));

    connect(RadialAxis,
            QOverload<const QCPRange &>::of(&QCPPolarAxisRadial::rangeChanged),
            yAxis,
            QOverload<const QCPRange &>::of(&QCPAxis::setRange));

    //connect <QCPAxis, AngularAxis> (xAxis, &QCPAxis::rangeChanged, AngularAxis,  &QCPPolarAxisAngular::setRange);


    //connect(AxisRectangle->axis(QCPAxis::AxisType::atBottom), &QCPAxis::rangeChanged, AngularAxis, &QCPPolarAxisAngular::setRange);

    connect(
        AxisRectangle->axis(QCPAxis::AxisType::atBottom),
        QOverload<const QCPRange &>::of(&QCPAxis::rangeChanged),
        this,
        yAxis,
        QOverload<const QCPRange &>::of(&QCPAxis::setRange));
*/

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
void PlotClass::mouseReleaseEvent(QMouseEvent *event)
{
    QCustomPlot::mouseReleaseEvent(event);

    for (int i = 0; i < graphCount(); ++i)
    {
        if (graph(i)->selected())
        {
            qDebug()<<"Selected Graph "<<i;
            emit GraphClickedSignal(i);
            break;
        }
    }
}



void PlotClass::ChangeToPolarFormat()
{
    PolarFormatInUse = true;

    plotLayout()->take(plotLayout()->element(0,0)); // Убираем прямоугольник с осями
    //xAxis->setVisible(false);
    plotLayout()->addElement(0,0, AngularAxis); // Ставим на его место круг угловой оси

    //Подстраиваем диапазоны
    AngularAxis->setRange(xAxis->range());
    RadialAxis->setRange(yAxis->range());

    qDebug()<<xAxis->range()<<"=x=a="<<AngularAxis->range();


    int NumberOfGraphs = graphCount();
    for (int i=0;i<NumberOfGraphs; i++)
    {
        QCPPolarGraph * PolarGraph = new QCPPolarGraph(AngularAxis,RadialAxis);
        PolarGraph->setData(graph(i)->data());
        PolarGraph->setPen(graph(i)->pen());
    }



    AngularAxis->setVisible(true);
    AngularAxis->setLayer(this->layer(1));
    AxisRectangle->setVisible(false);
    AngularAxis->setVisible(true);

    qDebug()<< "TICKLABELMODE===" <<AngularAxis->tickLabelMode();
    replot();
}



void PlotClass::ChangeToDescartesFormat()
{
    PolarFormatInUse = false;

    plotLayout()->take(plotLayout()->element(0,0));
    xAxis->setLabel(XAxisLabel);
    yAxis->setLabel(YAxisLabel);
    plotLayout()->addElement(0,0,AxisRectangle);



    //xAxis->setRange(AngularAxis->range());
    //yAxis->setRange(RadialAxis ->range());











    AxisRectangle->setVisible(true);
    AngularAxis->setVisible(false);
    replot();
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



void PlotClass::ChangeYAxisMax(QString MaxValue)
{
    double Lower = yAxis->range().lower;
    double Upper = yAxis->range().upper;
    double Span = Upper - Lower;
    Lower = MaxValue.toDouble() - Span;
    Upper = MaxValue.toDouble();
    yAxis->setRange(Lower,Upper);
    replot();
}


void PlotClass::ChangeYAxisSpan(QString SpanValue)
{
    double Lower = yAxis->range().lower;
    double Upper = yAxis->range().upper;
    Lower = Upper-SpanValue.toDouble();
    yAxis->setRange(Lower,Upper);
    replot();
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




    connect(NewMarker, &QCPItemTracer::selectionChanged, this, [NewMarkerLabel, NewMarker,this]() // Убрать отсюда лямбду
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



    /*
    connect(NewMarker, SIGNAL(selectionChanged()), this, SLOT([=]()
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

            })
            );
    */
    //connect(NewMarker,SIGNAL(QCPItemTracer::selectionChanged(bool, QCPItemText*, QCPItemTracer*)),this,SLOT(OnSelectionChangedSlot(bool, QCPItemText*, QCPItemTracer*)));



    //connect(NewMarker,SIGNAL(selectionChanged),this, SLOT(OnMarkerSelectedSlot));


    AddedMarkersList.push_back(NewMarker);
    AddedMarkerLabelsList.push_back(NewMarkerLabel);
    emit MarkerAddedSignal(NewMarker);

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




void PlotClass::loadDat(QString FilePath) //Добавить данные полярного графика
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
        LoadedPlot->AddEmptyGraphToPlot();


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


void PlotClass::saveCsv(QString FilePath) // ПРОВЕРИТЬ!!! Что-то не то
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


void PlotClass::AddEmptyGraphToPlot()
{
    int CurrentNumberOfGraphs = GraphVector.size();
    addGraph();
    graph(CurrentNumberOfGraphs)->setPen(QPen(this->GenerateColor(CurrentNumberOfGraphs)));
}


void PlotClass::SendPlotImageForPreview()
{

}



PlotClass::CustomRadialAxis::CustomRadialAxis(QCPPolarAxisAngular *parent) : QCPPolarAxisRadial(parent)
{
    // Не меняю конструктор
}

void PlotClass::CustomRadialAxis::draw(QCPPainter *painter)
{
    // Сохраняем исходные
    QPointF originalCenter = mCenter;
    //mSubTickLengthOut;
    // Меняем на свои
    mCenter += QPointF(-1, 0) * (mRadius - 0.5); // Можно ещё немного левее сдвинуть
    // Используем исходную функцию
    QCPPolarAxisRadial::draw(painter);



    // Параллельные горизонтальные линии подсетки от отметок
    painter->setPen(QPen(Qt::white, 0, Qt::DotLine));
    if (!mTickVector.isEmpty())
    {
        // Дорисовываем горизонтальные линии
        for (int i=0; i<mTickVector.size(); ++i)
        {
            double r = coordToRadius(mTickVector.at(i));
            QPointF tickPosition = mCenter+QPointF(0,-1)*r;
            painter->drawLine(QLineF(tickPosition, QPointF(originalCenter.x(),tickPosition.y())));
        }

        // Дорисоваем подпись к последней отметке
        const QPointF MyTickNormal = QCPVector2D(QPointF(-1,0)).perpendicular().toPointF();
        const double r = coordToRadius(mTickVector.at(mTickVector.size()-1));
        const QPointF LastTickPosition = mCenter+QPointF(0,-1)*r;

        painter->setFont(getTickLabelFont());
        painter->setPen(getTickLabelColor());
        QPointF LastLabelPosition = LastTickPosition+MyTickNormal*mSubTickLengthOut + QPointF(-19.3,5); // Последнее слагаемое -- подбором. Придумать, как сделать так, чтобы адаптировалось ( Вроде изначально в коде как-то через высоту текста?)
        painter->drawText(LastLabelPosition, mTickVectorLabels.at(mTickVector.size()-1));



    }

    // Возвращаем как было
    mCenter = originalCenter;



}



/* // Функция отрисовки радиальной оси от qcustomplot (для сравнения)
void QCPPolarAxisRadial::draw(QCPPainter *painter)
{
  const double axisAngleRad = (mAngle+(mAngleReference==arAngularAxis ? mAngularAxis->angle() : 0))/180.0*M_PI;
  const QPointF axisVector(qCos(axisAngleRad), qSin(axisAngleRad)); // semantically should be QCPVector2D, but we save time in loops when we keep it as QPointF
  const QPointF tickNormal = QCPVector2D(axisVector).perpendicular().toPointF(); // semantically should be QCPVector2D, but we save time in loops when we keep it as QPointF

  // draw baseline:
  painter->setPen(getBasePen());
  painter->drawLine(QLineF(mCenter, mCenter+axisVector*(mRadius-0.5)));

  // draw subticks:
  if (!mSubTickVector.isEmpty())
  {
    painter->setPen(getSubTickPen());
    for (int i=0; i<mSubTickVector.size(); ++i)
    {
      const QPointF tickPosition = mCenter+axisVector*coordToRadius(mSubTickVector.at(i));
      painter->drawLine(QLineF(tickPosition-tickNormal*mSubTickLengthIn, tickPosition+tickNormal*mSubTickLengthOut));
    }
  }

  // draw ticks and labels:
  if (!mTickVector.isEmpty())
  {
    mLabelPainter.setAnchorReference(mCenter-axisVector); // subtract (normalized) axisVector, just to prevent degenerate tangents for tick label at exact lower axis range
    mLabelPainter.setFont(getTickLabelFont());
    mLabelPainter.setColor(getTickLabelColor());
    const QPen ticksPen = getTickPen();
    painter->setPen(ticksPen);
    for (int i=0; i<mTickVector.size(); ++i)
    {
      const double r = coordToRadius(mTickVector.at(i));
      const QPointF tickPosition = mCenter+axisVector*r;
      painter->drawLine(QLineF(tickPosition-tickNormal*mTickLengthIn, tickPosition+tickNormal*mTickLengthOut));
      // possibly draw tick labels:
      if (!mTickVectorLabels.isEmpty())
      {
        if ((!mRangeReversed && (i < mTickVectorLabels.count()-1 || mRadius-r > 10)) || (mRangeReversed && (i > 0 || mRadius-r > 10))) // skip last label if it's closer than 10 pixels to angular axis
          mLabelPainter.drawTickLabel(painter, tickPosition+tickNormal*mSubTickLengthOut, mTickVectorLabels.at(i));
      }
    }
  }
}
*/

/*
void QCPAxisPainterPrivate::drawTickLabel(QCPPainter *painter, double x, double y, const TickLabelData &labelData) const
{
    // backup painter settings that we're about to change:
    QTransform oldTransform = painter->transform();
    QFont oldFont = painter->font();

    // transform painter to position/rotation:
    painter->translate(x, y);
    if (!qFuzzyIsNull(tickLabelRotation))
        painter->rotate(tickLabelRotation);

    // draw text:
    if (!labelData.expPart.isEmpty()) // indicator that beautiful powers must be used
    {
        painter->setFont(labelData.baseFont);
        painter->drawText(0, 0, 0, 0, Qt::TextDontClip, labelData.basePart);
        if (!labelData.suffixPart.isEmpty())
            painter->drawText(labelData.baseBounds.width()+1+labelData.expBounds.width(), 0, 0, 0, Qt::TextDontClip, labelData.suffixPart);
        painter->setFont(labelData.expFont);
        painter->drawText(labelData.baseBounds.width()+1, 0, labelData.expBounds.width(), labelData.expBounds.height(), Qt::TextDontClip,  labelData.expPart);
    } else
    {
        painter->setFont(labelData.baseFont);
        painter->drawText(0, 0, labelData.totalBounds.width(), labelData.totalBounds.height(), Qt::TextDontClip | Qt::AlignHCenter, labelData.basePart);
    }

    // reset painter settings to what it was before:
    painter->setTransform(oldTransform);
    painter->setFont(oldFont);
}
*/





























































/*
void PlotClass::OnSelectionChangedSlot(bool selected, QCPItemText * NewMarkerLabel, QCPItemTracer * NewMarker)
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
        //////connect(RefreshTimer, &QTimer::timeout, this, &PlotClass::RefreshPlot);

        RefreshTimer->start(100);
    }
    else
    {
        dis//////connect(RefreshTimer, &QTimer::timeout, this, &PlotClass::RefreshPlot);
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


/*
void PlotClass::ContinuousMeasurementsModeChanged(bool ModeStatus)
{

    ContinuousMeasurementMode = ModeStatus;

    if (ModeStatus)
    {
        ////////connect(Timer, &QTimer::timeout, this, &PlotClass::ResetPlot);

        //Timer->setInterval(10);
        //Timer->start();
        //qDebug()<<"Replotted!";
    }
    else
    {
        //disconnect(Timer, &QTimer::timeout, this, &PlotClass::ResetPlot);
        //Timer->stop();
    }
}
*/




























































































// +Убедиться, что ошибается не более чем на один пиксель
// +Размер графика нельзя менять. Люди привыкают как выглядит -- привыкают, могут сказать, что ошибка. Интерфейс как прибор
// +Прорежевание -- опасно, так как острые пики может неправильно показать
// +Посмотреть, как с этим работает QCustomPlot.
// +dynamic_cast не надо использовать. Лучше хранить массив. В Qt есть автоматический сборщик мусора (определяет -- используется или нет, можно не удалять). Всё наследуется из QObject, вся память -- древовидная структура (у всех parent).
// +При удалении виджета рекурсивно удаляются дети. Если удалять вручную, то программа упадёт. Не факт, что из-за delete программа падала.
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
// Добавить график от угла!!!!!

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
// Древо классов нарисовать. Таблица + список + сигналы/слоты + не заострять внимание на графиках.
// ... Во время изм на кажд угле изм зав от част. Вывод дальн портр -> выв диагр, с калибр.
// + Спросить Алексея про класс обработки
//

// Добавить проверку непустоты графика при установке маркера.


// Две средние колонки меняются разом!!! При движении маркера влево-вправо


// Изменение диапазонов и чисел шагов азимута-подъёма-частоты в resultparameterswidget


// сайт у Арины посмотреть презентацию, фя чебышева,
// Четырёхмерный массив? Ещё есть поляризации - только две.

// В measuredfunction нужно добавить функцию:

//downsample -- выбирает каждую 4 точку из 1601 -- оставляет 400.

// WriteTo -- AddValueToPosition
// Спросить Алексея, нужно ли переделать Qt

// Отрицательные числа нельзя вводить

// Программа Арины:
// 1) Класс ошибок ErrorHandler
// AppendErrorToList -- добавляется в список ошибок, номер ошибки сопоставлен тексту ошибки
// Сохранять ошибки
// Фатальные ошибки и не фатальные -- как хранить
// bNoError -- общая для всех классов
// extern -- общее для всех классов!!!! Добавить у меня в код такое же!
//
//
// 2) mainwindow -- минимально
//
// 3) measurementcontrol start...? MeasureCurrentAspect, передаётся в виде структуры.
// Остальные устроены также : респонс, бэкграунд -- одна точка по углу,
// measureaspect -- измерение для одного угла
// измерения по углу -- в поток
// StartTargetMeasure -- measureaspect в цикле
//
//
//  StartUpdatingGraph -- после запуска измерений нужно, чтобы интерфейс обновлялся. Для этого система такая: основной поток и дополнительный
//  В доп потоке -- связь с vna, в основном, с интерфейсом, -- постоянно спрашивает готовность
//  (там таймер проверяет каждые 50ms, есть ли данные. Когда есть -- он их обработает и пошлёт на интерфейс график от частоты и поставит точку на угловой)
//  Отправляет для каждой точке зависимость от частоты.
//  Может ли прийти 3200 точек? Между измерениями ~= 500ms, так что проблем не должно быть. ТОЧНО!
//  Переделать принятие сигнала -- по 1601 точке.
//  В отдельном потоке комп ждёт данные. vna измеряет по триггеру. Триггер приходит каждые 1.2 сек на точку.
//  Вращ. непр. -- после 1601 точки даёт данные, их принимаю, добавляет к массиву (Функция добавления строку в массив),
//
//  Background и калибровка на одном угле (не отличаются -- нет зависимости от угла).
//
//  Пока калибровку не удалять на многих углах.
//
//
//  Измерение одной точки
//
//  подключение при нажатии measure
//  Класс с поворотом
//
//  Что должно происходить с данными после принятия.
//  Когда данные приходят используется класс DataProcess.
//  После прихода 1601 точки пересчёт в децибелах
//  Sweep приходит мне и отображается верный диапазон частот
//  Преобразование Фурье аккуратно и мне отдать массив значений Фурье и
//  Помимо Фурье ещё что-то. Есть какие-то приколы с Фурье. Сайты с фильтром смотреть в телеграмме
//  Импульсная характеристика
//  Чтобы выделить рабочую зону. Фильтрация -- делается с помощью свёртки.
//  Доразобраться.
//  Не только кайзер бессель, но и синк -- см видео. Рекомендует видео FIR filter design using window method
//
//  Фильтрация, свёртка,
//
//  Разговор с Алексеем:
//
//  Хранить double или float -- пока оставляем double
//
//  Сделан класс обёртки над массивом данных -- в нём и response и background, и измерение
//  сохр загр и передавать данные. -- перенести в класс массива
//
//  Кто является ответственным за response и background
//
//  Подкл библиотеку, создаю эксемпляр класса, вставляю вызовы - фукнции - заглушки в программу.
//  api предоставляет backend и добавляются к фронтенду.
//  Фурье обязательно в бэкенде. Так как ->
//  Аттестация: камера проходит переаттестацию и программа -- часть комплекса.
//  Сейчас, добавляя что-то в программу, её нужно перекомпилировать -> переаттестовываться. Ничего не поменялось, но нужно проходить снова аттестацию.
//  Метрологически значимая часть -- входит в аттестацию. Фронтенд -- не входит. Это одна из целей переписывания программы.
//  Первичная обработка = background + response. Без них данные не имеют смысла.
//  Что такое localhost и микросервисы? Много программ, которые общаются по сети. localhost -- если на одном компьютере.
//  Позволяет разбить задачи.
//
//  Про мануал
//  Спросить прибор, как его зовут, вывести на экран
//  Получить ответ -> Получить асинхронный ответ ->
//  Текущее значение угла.
//
//  Разговор с Алексеем 28-11-2024:
//  1) Подключить через dll
//  2) (Контейнер?) Чтобы можно было показать людям, кто не понимает в программировании, визуально
//
//
//
/*  след часть разговора

    В классе измерения
    Массив от частот и углов
    Операции над ними

Инвариант класса -- предположение, которое будет выполнено. (например в list нет петель. Если поменять ссылку для зацикливания, то всё сломается)
    Измерение без бэкграунда и респонса не имеет смысла совсем -> Поэтому всегда нужно хранить и бэкграунд и респонс

    Почему два бэкграунда и два респонса. -- сокращённые и полные

Когда померили -- как понять, при каких калибровках померено
А может калибровка неправильная
Вот делается калибровка потом измеряется -- узнаётся, что калибровка неправильная и потом калибровку меняют

Это к объекту measurement. И добавить объект submeasurement

Есть след проблема:
От частоты, азимута и элевэйшена есть трёхмерная картина. Есть ещё параметр: поляризация и ещё какие-то параметры.
Но все эти параметры не имеют общего
Background и Response -- это всё в классе Submeasurement
И класс Measurement -- обёртка, чтобы учитывать верт и гориз и др. параметры -- список произвольного размера

Measurement -- массив массивов, но как список (нельзя обратиться через квадратные скобки)
N-мерные становятся плохи тем, что тяжело в плане интерфейса -- много графиков

Писать очень надёжно, так как потом с этим кодом сами и будем работать



1 этап:
Задание на класс,
Интерфейс, чтобы похожий,
Подключить dll
h - файл
Заглушки заменить

2 этап:
Поворотка
Кабель
h-файл и dll
Как протокол называется?
Подключение по TCPIP номер порта, как начинается-заканчивается общение с повороткой

3 этап:
Смогу ли я до конца года сделать 1 этап? Тест planar -- подключаемся, открываем программу, измерения запускаем, смотрим результат.
Если есть вопросы -- Алексею писать сразу, чтобы не застревать надолго
(Сейчас у Алексея задача -- нужно логировать файлы, но старая функция для именования не работает как надо.)

До конца года подключение через Аринину dll, и в интерфейсе кнопки где надо.

Последнюю неделю никто не работает

До нового года скооперироваться с Сергеем Викторовичем. Сроки получаются минимальные, ведь ещё нужно исправлять

*/
//
// +Сделать так, чтобы не вылетало при нажатии на + - если нет графика.
// Изменение пути вверху file manager при смене директории
// Неограниченное количество графиков
//
//
//
//В нужных местах нужные кнопки.
//
//
//Передвинуть всё как было в старой программе.
//Необходимо использовать Аринин код
// По measuredFunction
//
// У обоих есть заглушки. Они все в виде функций или методов.
// Можем составить таблицу из двух колонок: в левой мои заглушки, а в левой -- Арины.
// Установить Вз одн соотв
// Проблемы:
// 1) Заглушки без пары
// 2) У заглушек без пары могут не совпадать сигнатуры
// Открываем программы и выписываем функции
// Обсуждаем с первого пункта по последний.
// Договорились, что мы это начнём сегодня.
// Просьба: мы договаривались, что договоримся. Можно ли попросить, найти время, обсудить.
// API -- что такое
// Выписать функции сперва. Каждый выписывает API и предположительное API коллеги.
// До следующей среды или пятницы сделать.
//
// Либо я компилирую в dll, либо Арина присылает исходники и я компилирую.
//
//
//
// Достоинства и недостатки.
// После  договорённости по API -- создать API, которые полностью совпадут: у меня и у Арины по n функций, и они полностью совпадают.
//
// Есть программа, она работает. У неё есть заглушки в отдельных классах в отдельных файлах.
// Потренироваться сделать из этих файлов заглушек .dll
//
// Чётко разработанная методика: совпадают API
//
// Что такое API:
// API разделён на Backend и Frontend
// Преврать Backend в dll.
// Стали исходники frontend и dllьный backend
//
//
// энкапсулировать?
//
// Метрологически значимая часть, которая была бы скомпилирована в dll и больше не менялась никогда.
//
// Результат измерений -- не сырые данные, а обработанные.
//
//
// Функций больше, чем мы думали: Неизолированные функции. Обернуть все функции.
//
// Прислать в телеграмме, когда мы будем обсуждать.
//
//
//
// Get и Set
//
//
// Через стрелочку или точку нельзя обращаться.

// Внутри класса можно
// Написать а в этом классе функцию GetValue и SetValue?
//
// SetValue:
// void SetValue(double value);
//
// Generate getter, generate setter -- после правой кнопки мыши. Для безопасности.
// Все переменные запихнуть в private.
// Насчёт класса измерений. Много того, что я не знаю, что нужно Арине -- она говорит, что сделает сама.
//
//
// Если класс в классе, а у него есть внутри свой класс -- и нужно, чтобы добраться до переменной внутри написать
// Класс1.Класс2.переменнаякласса2 = 1 Написать set внутри
//  в классе 1 пишешь функцию Get { return Class2.NumofPoint }
//
// Запихнуть qcustomplot в dll -- будет работать быстрее. Научиться на примере работать.
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//Разговор 23 12 2024
//
//MeasurementControl -- создать
//
// Углы меняются по ходу добавления данных
// Частота никого не интересует
// Интересует диаграмма
//
// Есть ли кнопка, которая меняет частоту, на которой пересчитывается ЭПР -- график по углам
// Он отображается на одной частоте, но если в прямом эфире попросят на друг
// Сколько времени отрисовка -- поставить chrono
//
//
// Проверить размеры отрисовываемых графиков
//
// Непрерывно спрашиваются углы. Принимает сигнал и выставляет в интерфейс -- два угла (пока азимут только).
//
/*
 * Не добавленные параметры:
 * Скорость поворота
 * Мощность
 * void SetIFFromPanelSlot(); -- IF bandwidth
 * MoveMode
 * Две кнопки -- чтобы не использовать background и response
 *
 *
 *
 *
 *
 *
 *
 *  DLL Диаграмма -- используется, чтобы описать, как устроена программа --
 *  Например, в Main создаётся класс. Какой-то включён, какоё-то наследуется. Диаграмма похожа на логическую -- с ромбами, прямоугольниками
 *
 *  Класс имеет такие-то параметры, что умеет итд
 *  Осн классы, интерф классы, соединяются, пускается через dll Аринин класс,
 *  Нужно, чтобы осталась документация, хотя бы минимальная
 *  Устройство и архитектура программы.
 *  Значимая часть?
 *  Что должно в ней быть, чтобы её не менять
 *
 *
 *  +++-----------------------------+++
 *  +++-----------------------------+++
 *  |||ТАБЛИЧКА С ЗАДАЧАМИ И СРОКАМИ|||
 *  +++-----------------------------+++
 *  +++-----------------------------+++
 *
 * + DLL Диаграмма!!
 *
 * Инициализировать массивы на графиках малыми значениями
 *
 * Освоить ветки кода в Github
 *
 * Запрашивать данные графика периодически -- чтобы обновлялся и не
 *
 *
 * Разобраться, как работает ISAR -- найти статью базовую: какие входные данные, какой алгоритм, какие выходные данные.
 * Радиоизображение
 *
 *
 *  Сделать объект для хранания ошибок
 *
 *  Всё заключаем в try, throw, catch -- не очень срочная, но обязательно нужная
 *
 *  std::terminate, std::abort
 *
 *
 *  Как хранить список ошибок?
 *
 *
 *  SaveData()?
 *
 *
 *
 *
 *
 *
 *
 *
 * (1)
 * Открывает программу, идёт триггер, жмём, запоминаем, запускаем измерения на 10 градусов. Вручную кликаем на триггер, можно перекючаться между дальностным портретом.
 * Заглушку, чтобы показывать, если нет подключения
 *
 * (2)
 * Два столбца: срочно и не срочно.
 *
 *
 * Программа лезет в область памяти, отображает и ждёт время. Не нужно QThread, что
 *
 *03042025
 *В заглушке тест подключения подкл задать число точек посчитать значение вывести в debug числа, которые пришли.
 *Можно график от модуля, можно в файл, маленькие кнопки: коннект и тест 1 измерение
 *Эта кнопка должна
 *Не нужно новый код поместить
 * Скопировать и в копию где коннект вставить коннект, параметры, генерация, не имит а TestVNA
 *
 *
 *
 *
 * Перемещение маркера в следующую точку,
 *
 *
 *
 * */
