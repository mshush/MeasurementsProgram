#include "widgetforcustomplot.h"

WidgetForCustomPlot::WidgetForCustomPlot(QWidget *parent)
    : QWidget{parent}
{
    //this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    HorizontalPlotLayout = new QHBoxLayout(this);

    VerticalControlsLayout = new QVBoxLayout;
    //VerticalControlsLayout->setAlignment(Qt::AlignLeft);

    //PlotThread = new QThread(this);
    customPlot = new PlotClass();
    //customPlot->moveToThread(PlotThread);
    //PlotThread->start();




    //customPlot->resize(600,400);
    //customPlot->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    ControlsWidget = new QWidget(this);
    //ControlsWidget->setFixedSize(260,500);
    //ControlsWidget->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    ControlsWidget ->setLayout(VerticalControlsLayout);
    //qDebug()<<"Размер="<<ControlsWidget->size();


    InitiateMovementGroupBox();
    VerticalControlsLayout->addWidget(MovementGroupBox);

    InitiateMarkerGroupBox();
    VerticalControlsLayout->addWidget(MarkerGroupBox);

    InitiateSaveLayout();
    VerticalControlsLayout->addLayout(HorizontalSaveLayout);

    //VerticalControlsLayout->addWidget(MarkerTableView);
    /*
    QPushButton * FourierButton = new QPushButton("F");
    connect(FourierButton, &QPushButton::clicked, this->customPlot, &PlotClass::FourierTransform);
    VerticalControlsLayout->addWidget(FourierButton);

    QPushButton * InverseFourierButton = new QPushButton("InvF");
    connect(InverseFourierButton, &QPushButton::clicked, this->customPlot, &PlotClass::InverseFourierTransform);
    VerticalControlsLayout->addWidget(InverseFourierButton);
    */



    HorizontalPlotLayout->addWidget(customPlot);
    HorizontalPlotLayout->addWidget(ControlsWidget);


    //connect(customPlot->xAxis, &QCPAxis::rangeChanged, this, &WidgetForCustomPlot::XAxisRangeChanged);
    //connect(customPlot->yAxis, &QCPAxis::rangeChanged, this, &WidgetForCustomPlot::YAxisRangeChanged);

    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(XAxisRangeChanged(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(YAxisRangeChanged(QCPRange)));

    connect(customPlot, &PlotClass::MarkerAddedSignal, this, &WidgetForCustomPlot::AddMarkerToTable);
    connect(customPlot, &PlotClass::AllMarkersDeletedSignal, this, &WidgetForCustomPlot::ClearTable);


    connect(customPlot, &PlotClass::MarkerDeletedSignal, this, &WidgetForCustomPlot::RemoveMarkerFromTable);

    connect(customPlot, &PlotClass::MarkerSelectedSignal, this, &WidgetForCustomPlot::HighlightMarkerInTable);
    connect(customPlot, &PlotClass::MarkerUnSelectedSignal, this, &WidgetForCustomPlot::UnHighlightMarkerInTable);


    MarkerPositionsTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}





void WidgetForCustomPlot::OpenMarkerColourDialogue() // Почему не меняется сразу???
{

    /*
    QColorDialog *colorDialog = new QColorDialog();

    //colorDialog->setCurrentColor(Qt::black);
    //colorDialog->setCustomColor(0,QColor(1,1,1));
    colorDialog->setCurrentColor(Qt::red);
    //colorDialog->setCurrentColor(Qt::black);

    colorDialog->setWindowTitle("Выберите цвет");


    connect(colorDialog, &QColorDialog::accepted, this,  [this, colorDialog]()
            {
                QColor chosenColor = colorDialog->currentColor();
                customPlot->MarkerColour = chosenColor;
                delete colorDialog;
            }
            );

    connect(colorDialog, &QColorDialog::rejected, [colorDialog]() {
        delete colorDialog;
    });

    colorDialog->open();
    */

    QColor ChosenColour = QColorDialog::getColor(customPlot->MarkerColour, this, "Выберите цвет");
    if (ChosenColour.isValid())
    {
        customPlot->MarkerColour = ChosenColour;
        PreviewMarker->setPen(ChosenColour);
        PreviewMarker->setBrush(ChosenColour);
        MarkerPreviewPlot->replot();
    }
}




void WidgetForCustomPlot::ChangeMarkerStyle(int ComboIndex)
{
    this->customPlot->MarkerStyle = ComboIndex+1;
    this->PreviewMarker->setStyle(QCPItemTracer::TracerStyle(ComboIndex+1));
    this->MarkerPreviewPlot->replot();
}



void WidgetForCustomPlot::ActivateRubberBand()
{
    if (this->RubberBandButton->isChecked())
    {
        SelectLocalMaxButton->setChecked(false);
        SelectLocalMinButton->setChecked(false);
        customPlot->setInteractions(QCP::iRangeZoom | QCP::iRangeDrag | QCP::iSelectItems);
        customPlot->setSelectionRectMode(QCP::srmZoom);
    }
    else
    {
        customPlot->setSelectionRectMode(QCP::srmNone);
    }
}

void WidgetForCustomPlot::LockXAxis()
{
    if (this->LockXAxisButton->isChecked())
    {
        customPlot->axisRect()->setRangeZoom(Qt::Vertical);
        QList <QCPAxis * > ZoomableAxesList = {customPlot->yAxis};
        customPlot->axisRect()->setRangeZoomAxes(ZoomableAxesList);
        this->LockYAxisButton->setChecked(false);
        qobject_cast<SelectionRectClass*>(customPlot->selectionRect())->XAxisLocked = true;
        qobject_cast<SelectionRectClass*>(customPlot->selectionRect())->YAxisLocked = false;
    }
    else
    {
        customPlot->axisRect()->setRangeZoom(Qt::Horizontal | Qt::Vertical);
        customPlot->axisRect()->setRangeZoomAxes(customPlot->xAxis, customPlot->yAxis);
        qobject_cast<SelectionRectClass*>(customPlot->selectionRect())->XAxisLocked = false;
        qobject_cast<SelectionRectClass*>(customPlot->selectionRect())->YAxisLocked = false;
    }
}

void WidgetForCustomPlot::LockYAxis()
{
    if (this->LockYAxisButton->isChecked())
    {
        customPlot->axisRect()->setRangeZoom(Qt::Horizontal);
        QList <QCPAxis * > ZoomableAxesList = {customPlot->xAxis};
        customPlot->axisRect()->setRangeZoomAxes(ZoomableAxesList);
        this->LockXAxisButton->setChecked(false);
        qobject_cast<SelectionRectClass*>(customPlot->selectionRect())->YAxisLocked = true;
        qobject_cast<SelectionRectClass*>(customPlot->selectionRect())->XAxisLocked = false;
    }
    else
    {
        customPlot->axisRect()->setRangeZoom(Qt::Horizontal | Qt::Vertical);
        customPlot->axisRect()->setRangeZoomAxes(customPlot->xAxis, customPlot->yAxis);
        qobject_cast<SelectionRectClass*>(customPlot->selectionRect())->XAxisLocked = false;
        qobject_cast<SelectionRectClass*>(customPlot->selectionRect())->YAxisLocked = false;
    }
}


void WidgetForCustomPlot::InitiateMovementGroupBox()
{
    MovementGroupBox = new QGroupBox("Положение графика");
    MovementGroupBox->setFixedWidth(260);
    MovementGroupBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    MovementGroupBoxLayout = new QVBoxLayout(MovementGroupBox);
    LockAxesLayout = new QHBoxLayout;

    RubberBandButton = new QPushButton("В");
    RubberBandButton->setCheckable(true);
    connect(RubberBandButton, &QPushButton::clicked,this,&WidgetForCustomPlot::ActivateRubberBand);
    RubberBandButton->setToolTip("Масштабирование выделением области");

    LockXAxisButton = new QPushButton("Бx");
    LockXAxisButton->setToolTip("Зафиксировать масштаб по оси X");
    connect(LockXAxisButton, &QPushButton::clicked,this,&WidgetForCustomPlot::LockXAxis);
    LockXAxisButton->setCheckable(true);

    LockYAxisButton = new QPushButton("Бy");
    LockXAxisButton->setToolTip("Зафиксировать масштаб по оси Y");
    connect(LockYAxisButton, &QPushButton::clicked,this,&WidgetForCustomPlot::LockYAxis);
    LockYAxisButton->setCheckable(true);

    ResetButton = new QPushButton("М");
    connect(ResetButton, &QPushButton::clicked, customPlot, &PlotClass::ResetPlot);
    ResetButton->setToolTip("Подгоняет масштаб под график");

    InitiateSetRangeGroupBox();

    //MovementGroupBoxLayout->addWidget(RubberBandButton);

    LockAxesLayout->addWidget(RubberBandButton);
    LockAxesLayout->addWidget(LockXAxisButton);
    LockAxesLayout->addWidget(LockYAxisButton);
    LockAxesLayout->addWidget(ResetButton);
    MovementGroupBoxLayout->addLayout(LockAxesLayout);

    //MovementGroupBoxLayout->addWidget(ResetButton);

    MovementGroupBoxLayout->addWidget(SetRangeGroupBox);
}




void WidgetForCustomPlot::InitiateMarkerGroupBox()
{

    MarkerGroupBox = new QGroupBox("Маркеры");
    MarkerGroupBox->setFixedWidth(260);
    //MarkerGroupBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    MarkerGroupBoxLayout = new QVBoxLayout(MarkerGroupBox);
    MarkerGroupBox->setLayout(MarkerGroupBoxLayout);
    MarkerStyleLayout = new QHBoxLayout;
    MarkerAddDeleteLayout = new QHBoxLayout;

    MarkerColourButton = new QPushButton("Цвет");
    //qDebug()<< "Размер кнопки" <<MarkerColourButton->size();
    connect(MarkerColourButton, &QPushButton::clicked, this, &WidgetForCustomPlot::OpenMarkerColourDialogue);

    MarkerStyleComboBox = new QComboBox(this);
    MarkerStyleComboBox->addItem("Плюс");
    MarkerStyleComboBox->addItem("Прицел");
    MarkerStyleComboBox->addItem("Круг");
    MarkerStyleComboBox->addItem("Квадрат");
    MarkerStyleComboBox->setCurrentIndex(0);
    connect(MarkerStyleComboBox, &QComboBox::currentIndexChanged,this,&WidgetForCustomPlot::ChangeMarkerStyle);
    MarkerStyleComboBox->setToolTip("Геометрическая форма маркера");

    InitiateMarkerPreviewPlot();

    MarkerAddButton = new QPushButton("+");
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
    MarkerAddButton->setToolTip("Добавить маркеры на выбранный график");


    MarkerDeleteButton = new QPushButton("-");
    MarkerDeleteButton->setCheckable(true);

    connect(MarkerDeleteButton, &QPushButton::clicked, this, [this]() // Вынести в отдельную функцию, чтобы не искать
            {
                for (QCPAbstractItem* item : customPlot->selectedItems()) //Как сделать без dynamic cast-ов?
                {
                    if (dynamic_cast<QCPItemTracer*>(item))
                    {
                        dynamic_cast<QCPItemTracer*>(item)->setSelected(false);
                    }
                }
                customPlot->markeraddbuttonactive = false;
                customPlot->markerdeletebuttonactive = MarkerDeleteButton->isChecked();
                MarkerAddButton->setChecked(false);
                customPlot->MouseMoveMarker->setVisible(customPlot->markeraddbuttonactive);
                customPlot->MouseMoveLabel->setVisible(customPlot->markeraddbuttonactive);
                customPlot->replot();

                }
            );
    MarkerDeleteButton->setToolTip("Удалить маркеры");


    SelectLocalMarkerLayout = new QHBoxLayout();

    SelectLocalMaxButton = new QPushButton("max", this); // Установка маркера в случае если в выделенной области нет точек?
    SelectLocalMaxButton->setCheckable(true);
    connect(SelectLocalMaxButton,&QPushButton::clicked, this, &WidgetForCustomPlot::EnterSelectLocalMaxMode);
    SelectLocalMaxButton->setToolTip("Установить маркер в максимум на выделенной области");

    SelectLocalMinButton = new QPushButton("min", this);
    SelectLocalMinButton->setCheckable(true);
    connect(SelectLocalMinButton,&QPushButton::clicked, this, &WidgetForCustomPlot::EnterSelectLocalMinMode);
    SelectLocalMinButton->setToolTip("Установить маркер в минимум на выделенной области");


    DeleteAllMarkersButton = new QPushButton("0");
    connect(DeleteAllMarkersButton, &QPushButton::clicked, customPlot, &PlotClass::DeleteAllMarkers);
    DeleteAllMarkersButton->setToolTip("Удалить все маркеры");


    QPushButton * MoveSelectedMarkerToNextMaxButton = new QPushButton("→",this);
    connect(MoveSelectedMarkerToNextMaxButton, &QPushButton::clicked, this, &WidgetForCustomPlot::ToNextMax);

    QPushButton * MoveSelectedMarkerToPrevMaxButton = new QPushButton("←",this);
    connect(MoveSelectedMarkerToPrevMaxButton, &QPushButton::clicked, this, &WidgetForCustomPlot::ToPrevMax);


    VerticalMarkerStyleConfigurationLayout = new QVBoxLayout();

    GraphChoiceComboBox = new QComboBox(MarkerGroupBox);

    GraphChoiceComboBox->addItem("График 1");
    GraphChoiceComboBox->addItem("График 2"); // Нужно добавление неограниченного числа графиков

    connect(GraphChoiceComboBox, &QComboBox::currentIndexChanged,customPlot,&PlotClass::ChangeSelectedGraph);

    MarkerStyleLayout->addWidget(MarkerPreviewPlot);
    MarkerStyleLayout->addLayout(VerticalMarkerStyleConfigurationLayout);
    VerticalMarkerStyleConfigurationLayout->addWidget(MarkerColourButton);
    VerticalMarkerStyleConfigurationLayout->addWidget(MarkerStyleComboBox);
    MarkerStyleLayout->addWidget(GraphChoiceComboBox);

    MarkerGroupBoxLayout->addLayout(MarkerStyleLayout);

    MarkerAddDeleteLayout->addWidget(MarkerAddButton);
    MarkerAddDeleteLayout->addWidget(MarkerDeleteButton);

    MarkerAddDeleteLayout->addWidget(SelectLocalMaxButton);
    MarkerAddDeleteLayout->addWidget(SelectLocalMinButton);
    MarkerAddDeleteLayout->addWidget(DeleteAllMarkersButton);



    MarkerGroupBoxLayout->addLayout(MarkerAddDeleteLayout);

    //SelectLocalMarkerLayout->addWidget(SelectLocalMaxButton);
    //SelectLocalMarkerLayout->addWidget(SelectLocalMinButton);
    //MarkerGroupBoxLayout->addLayout(SelectLocalMarkerLayout);

    //MarkerGroupBoxLayout->addWidget(DeleteAllMarkersButton);

    QHBoxLayout * MoveMarkerLeftOrRightHorizontalLayout = new QHBoxLayout();
    MarkerGroupBoxLayout->addLayout(MoveMarkerLeftOrRightHorizontalLayout);
    MoveMarkerLeftOrRightHorizontalLayout->addWidget(MoveSelectedMarkerToNextMaxButton);
    MoveMarkerLeftOrRightHorizontalLayout->addWidget(MoveSelectedMarkerToPrevMaxButton);

    MarkerPositionsTable = new QTableWidget(MarkerGroupBox);

    MarkerPositionsTable->setColumnCount(3);
    MarkerPositionsTable->setHorizontalHeaderLabels({"Gr", "x", "y"});
    //MarkerPositionsTable->horizontalHeader()->setStretchLastSection(true);
    MarkerPositionsTable->resizeColumnToContents(0);

    /*
    for (int i = 0; i < 3; i++)
    {
        MarkerPositionsTable->resizeColumnToContents(i);
    }
    */
    MarkerGroupBoxLayout->addWidget(MarkerPositionsTable);






}


void WidgetForCustomPlot::InitiateSaveLayout()
{
    HorizontalSaveLayout = new QHBoxLayout;

    SaveButton = new QPushButton("Сохранить",this);
    connect(SaveButton, &QPushButton::clicked, customPlot, &PlotClass::SaveAs);

    //QPushButton * SaveAsDatButton = new QPushButton(".dat", this);
    //connect(SaveAsDatButton, &QPushButton::clicked, this, &WidgetForCustomPlot::SavePlotAsDat);


    CopyButton = new QPushButton("Копировать");
    connect(CopyButton, &QPushButton::clicked, customPlot, &PlotClass::CopyPlot);

    HorizontalSaveLayout->addWidget(SaveButton);
    HorizontalSaveLayout->addWidget(CopyButton);
    //HorizontalSaveLayout->addWidget(SaveAsDatButton);
}



void WidgetForCustomPlot::InitiateMarkerPreviewPlot()
{
    MarkerPreviewPlot = new QCustomPlot;
    MarkerPreviewPlot->setBackground(QBrush(Qt::black));
    MarkerPreviewPlot->setFixedSize(50,50);
    MarkerPreviewPlot->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    //MarkerPreviewPlot->setMaximumSize(30,30);
    MarkerPreviewPlot->addGraph();
    MarkerPreviewPlot->graph(0)->setData({0}, {0});
    //MarkerPreviewPlot->graph(0)->setVisible(false);
    MarkerPreviewPlot->xAxis->setVisible(false);
    MarkerPreviewPlot->yAxis->setVisible(false);
    MarkerPreviewPlot->xAxis->setTickLabels(false);
    MarkerPreviewPlot->yAxis->setTickLabels(false);
    MarkerPreviewPlot->xAxis->setRange(-1, 1);
    MarkerPreviewPlot->yAxis->setRange(-1, 1);
    //MarkerPreviewPlot->rescaleAxes();

    //MarkerPreviewPlot->setStyleSheet("QCustomPlot { border: 2px solid black; }");
    PreviewMarker = new QCPItemTracer(MarkerPreviewPlot);
    PreviewMarker->setStyle(QCPItemTracer::TracerStyle(customPlot->MarkerStyle));
    PreviewMarker->setPen(QPen(customPlot->MarkerColour));
    PreviewMarker->setBrush(QBrush(customPlot->MarkerColour));
    PreviewMarker->setSize(14);
    PreviewMarker->setGraph(MarkerPreviewPlot->graph(0));
    PreviewMarker->setGraphKey(0);
    PreviewMarker->setVisible(true);

    MarkerPreviewPlot->setContentsMargins(0,0,0,0);
    MarkerPreviewPlot->axisRect()->setMargins(QMargins(0,0,0,0));

}

void WidgetForCustomPlot::InitiateSetRangeGroupBox()
{

    DoubleValidator = new QDoubleValidator(this);
    DoubleValidator->setNotation(QDoubleValidator::ScientificNotation);
    DoubleValidator->setLocale(QLocale("en_US"));

    //DoubleValidator->setRange(-1e6, 1e6);

    QString XLower = QString::number(this->customPlot->xAxis->range().lower);
    QString XUpper = QString::number(this->customPlot->xAxis->range().upper);
    QString YLower = QString::number(this->customPlot->yAxis->range().lower);
    QString YUpper = QString::number(this->customPlot->yAxis->range().upper);

    SetRangeGroupBox = new QGroupBox("Установить вручную");
    //SetRangeGroupBox->setFixedWidth(240);
    //SetRangeGroupBox->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    SetRangeVerticalLayout = new QVBoxLayout;
    SetRangeLayout = new QGridLayout;
    XRangeLabel1 = new QLabel("X:");
    XRangeEditFrom = new QLineEdit(XLower);
    XRangeEditFrom->setAlignment(Qt::AlignLeft);
    XRangeLabel2 = new QLabel("-");
    XRangeEditTo = new QLineEdit(XUpper);
    XRangeEditTo->setAlignment(Qt::AlignLeft);
    XRangeUnitsLabel = new QLabel("ГГц",this);

    YRangeLabel1 = new QLabel("Y:",this);
    YRangeEditFrom = new QLineEdit(YLower,this);
    YRangeEditFrom->setAlignment(Qt::AlignLeft);
    YRangeLabel2 = new QLabel("-",this);
    YRangeEditTo = new QLineEdit(YUpper,this);
    YRangeEditTo->setAlignment(Qt::AlignLeft);
    YRangeUnitsLabel = new QLabel("Дб",this);

    XRangeEditFrom->setValidator(DoubleValidator);
    XRangeEditTo->setValidator(DoubleValidator);
    YRangeEditFrom->setValidator(DoubleValidator);
    YRangeEditTo->setValidator(DoubleValidator);

    SetRangeButton = new QPushButton("Установить");
    connect(SetRangeButton, &QPushButton::clicked, this,[this]()
            {
                this->customPlot->xAxis->setRange(XRangeEditFrom->text().toDouble(),XRangeEditTo->text().toDouble());
                this->customPlot->yAxis->setRange(YRangeEditFrom->text().toDouble(),YRangeEditTo->text().toDouble());
                this->customPlot->replot();
             }
            );




    SetRangeLayout->addWidget(XRangeLabel1,    0,0);
    SetRangeLayout->addWidget(XRangeEditFrom,  0,1);
    SetRangeLayout->addWidget(XRangeLabel2,    0,2);
    SetRangeLayout->addWidget(XRangeEditTo,    0,3);
    SetRangeLayout->addWidget(XRangeUnitsLabel,0,4);

    SetRangeLayout->addWidget(YRangeLabel1,    1,0);
    SetRangeLayout->addWidget(YRangeEditFrom,  1,1);
    SetRangeLayout->addWidget(YRangeLabel2,    1,2);
    SetRangeLayout->addWidget(YRangeEditTo,    1,3);
    SetRangeLayout->addWidget(YRangeUnitsLabel,1,4);


    SetRangeVerticalLayout->addLayout(SetRangeLayout);
    SetRangeVerticalLayout->addWidget(SetRangeButton);

    SetRangeGroupBox->setLayout(SetRangeVerticalLayout);
}




void WidgetForCustomPlot::XAxisRangeChanged(const QCPRange &range)
{
    //double XMin = customPlot->xAxis->range().lower;
    //double XMax = customPlot->xAxis->range().upper;


    this->XRangeEditFrom->setText(QString::number(range.lower));
    this->XRangeEditTo  ->setText(QString::number(range.upper));

}

void WidgetForCustomPlot::YAxisRangeChanged(const QCPRange &range)
{
    //double YMin = customPlot->xAxis->range().lower;
    //double YMax = customPlot->xAxis->range().upper;

    this->YRangeEditFrom->setText(QString::number(range.lower));
    this->YRangeEditTo  ->setText(QString::number(range.upper));
}


void WidgetForCustomPlot::EnterSelectLocalMaxMode()
{
    if (SelectLocalMaxButton->isChecked())
    {
        if (!customPlot->graph(0)->data()->isEmpty())
        {
            this->RubberBandButton->setChecked(false);
            this->SelectLocalMinButton->setChecked(false);
            customPlot->setInteractions(QCP::iSelectPlottables| QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectItems);
            customPlot->setSelectionRectMode(QCP::srmSelect);
            customPlot->graph(0)->setSelectable(QCP::stDataRange);
            connect(customPlot, &QCustomPlot::selectionChangedByUser, this, &WidgetForCustomPlot::PutMarkerAtLocalMax);
            disconnect(customPlot, &QCustomPlot::selectionChangedByUser, this, &WidgetForCustomPlot::PutMarkerAtLocalMin);
        }
        else
        {
            this->SelectLocalMaxButton->setChecked(false);
        }
    }
    else
    {
        customPlot->setSelectionRectMode(QCP::srmNone);
        customPlot->setInteractions(QCP::iRangeZoom | QCP::iRangeDrag | QCP::iSelectItems);
        disconnect(customPlot, &QCustomPlot::selectionChangedByUser, this, &WidgetForCustomPlot::PutMarkerAtLocalMax);
    }
}

void WidgetForCustomPlot::PutMarkerAtLocalMax()
{
    QCPDataSelection SelectedData = this->customPlot->graph(0)->selection();
    SelectedData.enforceType(QCP::stDataRange);
    QCPDataRange DataRange = SelectedData.dataRange();
    if (DataRange.size() > 0) {
        double MaxValue = this->customPlot->graph(0)->data()->at(DataRange.begin())->value;
        double MaxKey   = this->customPlot->graph(0)->data()->at(DataRange.begin())->key;;
        for (int i = DataRange.begin(); i < DataRange.end(); i++)
        {
            double CurrentValue = this->customPlot->graph(0)->data()->at(i)->value;
            if (MaxValue < CurrentValue)
            {
                MaxKey = this->customPlot->graph(0)->data()->at(i)->key;
                MaxValue = CurrentValue;
            }
        }
        customPlot->AddNewMarker(MaxKey,customPlot->MarkerStyle, customPlot->MarkerColour, customPlot->SelectedGraph);
    }
     customPlot->graph(0)->setSelection(QCPDataSelection());
}





void WidgetForCustomPlot::EnterSelectLocalMinMode()
{
    if (SelectLocalMinButton->isChecked())
    {
        if (!customPlot->graph(0)->data()->isEmpty())
        {
            this->RubberBandButton->setChecked(false);
            this->SelectLocalMaxButton->setChecked(false);
            customPlot->setInteractions(QCP::iSelectPlottables| QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectItems);
            customPlot->setSelectionRectMode(QCP::srmSelect);
            customPlot->graph(0)->setSelectable(QCP::stDataRange);
            connect(customPlot, &QCustomPlot::selectionChangedByUser, this, &WidgetForCustomPlot::PutMarkerAtLocalMin);
            disconnect(customPlot, &QCustomPlot::selectionChangedByUser, this, &WidgetForCustomPlot::PutMarkerAtLocalMax);
        }
        else
        {
            this->SelectLocalMinButton->setChecked(false);
        }
    }
    else
    {
        customPlot->setSelectionRectMode(QCP::srmNone);
        customPlot->setInteractions(QCP::iRangeZoom | QCP::iRangeDrag | QCP::iSelectItems);
        disconnect(customPlot, &QCustomPlot::selectionChangedByUser, this, &WidgetForCustomPlot::PutMarkerAtLocalMin);
    }
}

void WidgetForCustomPlot::PutMarkerAtLocalMin()
{
    QCPDataSelection SelectedData = this->customPlot->graph(0)->selection();
    SelectedData.enforceType(QCP::stDataRange);
    QCPDataRange DataRange = SelectedData.dataRange();
    if (DataRange.size() > 0)
    {
        double MinValue = this->customPlot->graph(0)->data()->at(DataRange.begin())->value;
        double MinKey   = this->customPlot->graph(0)->data()->at(DataRange.begin())->key;
        for (int i = DataRange.begin(); i < DataRange.end(); i++)
        {
            double CurrentValue = this->customPlot->graph(0)->data()->at(i)->value;
            if (MinValue > CurrentValue)
            {
                MinKey = this->customPlot->graph(0)->data()->at(i)->key;
                MinValue = CurrentValue;
            }
        }
        customPlot->AddNewMarker(MinKey,customPlot->MarkerStyle, customPlot->MarkerColour, customPlot->SelectedGraph);
    }
    customPlot->graph(0)->setSelection(QCPDataSelection());
}



void WidgetForCustomPlot::ToNextMax() // Нужно ли рассмотреть случай маркера на первой координате?
{
    if (this->customPlot->selectedItems().size() == 1)
    {
        //Переделать получше
        QCPItemTracer * SelectedMarker = qobject_cast <QCPItemTracer*> (this->customPlot->selectedItems().last());


        double CurrentX = SelectedMarker->position->key();
        double CurrentY = SelectedMarker->position->value();

        //double PrevX;
        double PrevY;

        //double NextX;
        double NextY;

        double MaxX = CurrentX;

        QCPGraph * SelectedGraph = SelectedMarker->graph();
        for (int i = 0; i < SelectedGraph->data()->size(); i++)
        {
            double x = SelectedGraph->data()->at(i)->key;
            if (x > CurrentX)
            {
                CurrentX = x;
                CurrentY = SelectedGraph->data()->at(i)->value;

                if (i<SelectedGraph->data()->size()-1)
                {
                    //PrevX = SelectedGraph->data()->at(i-1)->key;
                    PrevY = SelectedGraph->data()->at(i-1)->value;

                    //NextX = SelectedGraph->data()->at(i+1)->key;
                    NextY = SelectedGraph->data()->at(i+1)->value;

                    if (NextY<=CurrentY && PrevY<=CurrentY)
                    {
                        MaxX = CurrentX;
                        break;
                    }
                }
                else
                {
                    if (SelectedMarker->position->value()<=CurrentY)
                    {
                        MaxX = CurrentX;
                    }
                    else
                    {
                        MaxX = SelectedMarker->position->key();
                        qDebug()<< "Справа не найдено маркеров";
                    }
                }

            }
        }
        SelectedMarker->setGraphKey(MaxX);
        SelectedMarker->updatePosition();
        customPlot->replot();
    }
    else
    {
        qDebug()<< "Inappropriate number of markers";
    }
}

void WidgetForCustomPlot::ToPrevMax()
{
    if (this->customPlot->selectedItems().size() == 1)
    {
        // Как сделать более аккуратно?
        QCPItemTracer * SelectedMarker = qobject_cast <QCPItemTracer*> (this->customPlot->selectedItems().last());


        double CurrentX = SelectedMarker->position->key();
        double CurrentY = SelectedMarker->position->value();

        //double PrevX;
        double PrevY;

        //double NextX;
        double NextY;

        double MaxX = CurrentX;

        QCPGraph * SelectedGraph = SelectedMarker->graph();

        for (int i = SelectedGraph->data()->size()-1; i >= 0 ; i--)
        {
            //qDebug()<<i;
            double x = SelectedGraph->data()->at(i)->key;
            if (x < SelectedMarker->position->key())
            {
                CurrentX = x;
                CurrentY = SelectedGraph->data()->at(i)->value;

                if (i>0)
                {
                    //PrevX = SelectedGraph->data()->at(i-1)->key;
                    PrevY = SelectedGraph->data()->at(i-1)->value;

                    //NextX = SelectedGraph->data()->at(i+1)->key;
                    NextY = SelectedGraph->data()->at(i+1)->value;

                    if (NextY<=CurrentY && PrevY<=CurrentY)
                    {
                        //qDebug()<<"Was Here!!!";
                        MaxX = CurrentX;
                        break;
                    }
                }
                else
                {
                    if (SelectedMarker->position->value()<=CurrentY)
                    {
                        MaxX = CurrentX;
                    }
                    else
                    {
                        MaxX = SelectedMarker->position->key();
                        qDebug()<< "Слева не найдено маркеров";
                    }
                }

            }
        }

        SelectedMarker->setGraphKey(MaxX);
        SelectedMarker->updatePosition();
        customPlot->replot();
    }
    else
    {
        qDebug()<< "Inappropriate number of markers";
    }
}








//Перенесено в PlotClass
/*
void WidgetForCustomPlot::SavePlotAsDat()
{
    QString Path = QDir::homePath() + "/" + "PlotData" + ".dat";
    QString FilePath = QFileDialog::getSaveFileName(this, "Save File", Path, "Data Files (*.dat);;All Files (*)");

    QFile File(FilePath);
    if (!File.open(QIODevice::WriteOnly))
    {
        //ShowErrorMessage("Не удалось открыть файл для записи!",File.errorString());
        qDebug()<< "Не получилось записать";
        return;
    }


    QDataStream out(&File);
    //QCustomPlot Plot;
    //out << Plot;
    File.close();

    customPlot->saveGeometry();
    //customPlot->saveRastered(FilePath,);
}
*/




WidgetForCustomPlot::~WidgetForCustomPlot()
{
    //PlotThread->quit();
    //PlotThread->wait();
    //PlotThread->deleteLater();
    customPlot->deleteLater();

}







void WidgetForCustomPlot::AddMarkerToTable(QCPItemTracer * MarkerPtr) // Наладить сдвиг координат при скачках по максимумам
{
    // Добавляется без графика -- сделать проверку, не пустой ли график

    NumberOfRows = MarkerPositionsTable->rowCount();
    MarkerPositionsTable->insertRow(MarkerPositionsTable->rowCount());
    //MarkerPositionsTable->insertRow(MarkerPositionsTable->rowCount()+2);
    //MarkerPositionsTable->setItem(NumberOfRows-1, 0, new QTableWidgetItem(QString::number(MarkerPositionsTable->rowCount())));
    MarkerPositionsTable->setItem(NumberOfRows, 0, new QTableWidgetItem(QString::number(customPlot->SelectedGraph)));
    MarkerPositionsTable->setItem(NumberOfRows, 1, new QTableWidgetItem(QString::number(MarkerPtr->graphKey())));
    MarkerPositionsTable->setItem(NumberOfRows, 2, new QTableWidgetItem(QString::number((MarkerPtr->positions())[0]->value())));

    MarkerPositionsTable->resizeColumnToContents(2);
    MarkerPositionsTable->resizeColumnToContents(1);
    MarkerPositionsTable->resizeColumnToContents(0);
    //qDebug()<<"Was Here" << MarkerPositionsTable->rowCount() << customPlot->SelectedGraph << MarkerPtr->position->key() << MarkerPtr->position->value();
}


void WidgetForCustomPlot::RemoveMarkerFromTable(int RowNumberOfMarker)
{
    MarkerPositionsTable->removeRow(RowNumberOfMarker);
}

void WidgetForCustomPlot::HighlightMarkerInTable(int RowNumberOfMarker)
{
    //qDebug()<<"HighLighting!";
    QColor HighlightColor(200, 200, 255);

    for (int column = 0; column < MarkerPositionsTable->columnCount(); column++)
    {
        QTableWidgetItem *item = MarkerPositionsTable->item(RowNumberOfMarker, column);
        if (item)
        {
            item->setBackground(HighlightColor);
        }
    }
}




void WidgetForCustomPlot::UnHighlightMarkerInTable(int RowNumberOfMarker)
{
    //qDebug()<<"Regularizing!";
    for (int column = 0; column < MarkerPositionsTable->columnCount(); column++)
    {
        QTableWidgetItem *item = MarkerPositionsTable->item(RowNumberOfMarker, column);
        if (item)
        {
            item->setBackground(Qt::white);
        }
    }
}



void WidgetForCustomPlot::ClearTable()
{
    MarkerPositionsTable->setRowCount(0);
}










