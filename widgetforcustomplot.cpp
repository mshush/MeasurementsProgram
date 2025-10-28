 #include "widgetforcustomplot.h"

WidgetForCustomPlot::WidgetForCustomPlot(QWidget *parent)
    : QWidget{parent}
{
    SetUpGeneralStyle(); // Устанавливает основной стиль виджета

    SetUpPlot();         // Создаёт и настраивает график из PlotClass

    FillControlsWidget();// Заполняет панель управления

    FillLayouts();       // Заполняет основную компоновку (Добавить ли слайдер? Или хватит того, что правой кнопкой мыши можно скрыть панель?)

    SetUpContextMenu();  // Заполняет контекстное меню

    SetUpConnections();  // Соединяет сигналы со слотами
}




void WidgetForCustomPlot::SetUpGeneralStyle()
{
    // Перенести сюда стиль кнопок
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
}

void WidgetForCustomPlot::SetUpPlot()
{
    customPlot = new PlotClass();
    customPlot->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
}

void WidgetForCustomPlot::FillControlsWidget()
{
    VerticalControlsLayout = new QVBoxLayout;
    ControlsWidget = new QWidget(this);
    ControlsWidget->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    ControlsWidget ->setLayout(VerticalControlsLayout);
    ControlsWidget->setMaximumWidth(280);

    InitiateButtons(); // Инициирует кнопки, которые встречаются в двух следующих функциях

    FillYAxisControl(); // Заполняет часть, управляющую масштабом оси Y

    FillXAxisAndMarkerControl(); // Заполняет часть, управляющую масштабом оси X И МАРКЕРАМИ!

    FillMarkerTable(); // Заполняет таблицу маркеров

}

void WidgetForCustomPlot::FillLayouts()
{
    HorizontalPlotLayout = new QHBoxLayout(this);
    HorizontalPlotLayout->addWidget(customPlot);
    HorizontalPlotLayout->addWidget(ControlsWidget);
}

void WidgetForCustomPlot::SetUpConnections()
{

    //FromPlotToPanel //Нужно соединять-разъединять???
    //connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(XAxisRangeChanged(QCPRange)));
    //connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(YAxisRangeChanged(QCPRange)));

    connect(customPlot, &PlotClass::MarkerAddedSignal, this, &WidgetForCustomPlot::AddMarkerToTable);
    connect(customPlot, &PlotClass::AllMarkersDeletedSignal, this, &WidgetForCustomPlot::ClearTable);

    connect(customPlot, &PlotClass::MarkerDeletedSignal, this, &WidgetForCustomPlot::RemoveMarkerFromTable);

    connect(customPlot, &PlotClass::MarkerSelectedSignal, this, &WidgetForCustomPlot::HighlightMarkerInTable);
    connect(customPlot, &PlotClass::MarkerUnSelectedSignal, this, &WidgetForCustomPlot::UnHighlightMarkerInTable);

    connect(this, &QWidget::customContextMenuRequested, this, &WidgetForCustomPlot::ShowContextMenu);
    connect(customPlot, &QWidget::customContextMenuRequested, this, &WidgetForCustomPlot::ShowContextMenu);



    //ContextMenu
    connect(DisableScalePanelAction,&QAction::triggered, this, &WidgetForCustomPlot::OnDisableScalePanel);
    connect(PolarFormatAction,      &QAction::changed, this, &WidgetForCustomPlot::OnPolarFormat);
    connect(AmplitudeAction,        &QAction::triggered, this, &WidgetForCustomPlot::OnAmplitude);
    connect(PhaseAction,            &QAction::triggered, this, &WidgetForCustomPlot::OnPhase);
    connect(RealPartAction,         &QAction::triggered, this, &WidgetForCustomPlot::OnRealPart);
    connect(ImagPartAction,         &QAction::triggered, this, &WidgetForCustomPlot::OnImagPart);
    connect(LegendInsideAction,     &QAction::triggered, this, &WidgetForCustomPlot::OnLegendInside);
    connect(DisableLegendAction,    &QAction::triggered, this, &WidgetForCustomPlot::OnDisableLegend);


    // Buttons
    connect(YLinScaleButton,        &QPushButton::clicked, this, &WidgetForCustomPlot::OnYLinScaleClicked);
    connect(YLogScaleButton,        &QPushButton::clicked, this, &WidgetForCustomPlot::OnYLogScaleClicked);
    connect(YFitMaxSpanButton,      &QPushButton::clicked, this, &WidgetForCustomPlot::OnYFitMaxSpanClicked);
    connect(YFitMaxButton,          &QPushButton::clicked, this, &WidgetForCustomPlot::OnYFitMaxClicked);
    connect(YManualScaleButton,     &QPushButton::clicked, this, &WidgetForCustomPlot::OnYManualScaleClicked);
    connect(XScaleRectButton,       &QPushButton::clicked, this, &WidgetForCustomPlot::OnXScaleRectClicked);
    connect(XFitScaleButton,        &QPushButton::clicked, this, &WidgetForCustomPlot::OnXFitScaleClicked);
    connect(XUserScaleButton,       &QPushButton::clicked, this, &WidgetForCustomPlot::OnXUserScaleClicked);
    connect(XHighlightButton,       &QPushButton::clicked, this, &WidgetForCustomPlot::OnXHighlightClicked);
    connect(MarkerMoveLeftButton,   &QPushButton::clicked, this, &WidgetForCustomPlot::OnMarkerMoveLeftClicked);
    connect(MarkerMoveRightButton,  &QPushButton::clicked, this, &WidgetForCustomPlot::OnMarkerMoveRightClicked);
    connect(MarkerRightMaxButton,   &QPushButton::clicked, this, &WidgetForCustomPlot::OnMarkerRightMaxClicked);
    connect(MarkerLeftMaxButton,    &QPushButton::clicked, this, &WidgetForCustomPlot::OnMarkerLeftMaxClicked);
    connect(MarkerRightMinButton,   &QPushButton::clicked, this, &WidgetForCustomPlot::OnMarkerRightMinClicked);
    connect(MarkerLeftMinButton,    &QPushButton::clicked, this, &WidgetForCustomPlot::OnMarkerLeftMinClicked);
    connect(MarkerLocalMaxButton,   &QPushButton::clicked, this, &WidgetForCustomPlot::OnMarkerLocalMaxClicked);
    connect(MinusRightButton,       &QPushButton::clicked, this, &WidgetForCustomPlot::OnMinusRightClicked);
    connect(MinusLeftButton,        &QPushButton::clicked, this, &WidgetForCustomPlot::OnMinusLeftClicked);
    connect(MarkerAddButton,        &QPushButton::clicked, this, &WidgetForCustomPlot::OnMarkerAddClicked);
    connect(MarkerGraphButton,      &QPushButton::clicked, this, &WidgetForCustomPlot::OnMarkerGraphClicked);
    connect(MarkerIncreaseNButton,  &QPushButton::clicked, this, &WidgetForCustomPlot::OnMarkerIncreaseNClicked);
    connect(MarkerPrintButton,      &QPushButton::clicked, this, &WidgetForCustomPlot::OnMarkerPrintClicked);
    connect(MarkerIncreaseButton,   &QPushButton::clicked, this, &WidgetForCustomPlot::OnMarkerIncreaseClicked);
    connect(MarkerUnlockYButton,    &QPushButton::clicked, this, &WidgetForCustomPlot::OnMarkerUnlockYClicked);
    connect(MarkerUnlockXButton,    &QPushButton::clicked, this, &WidgetForCustomPlot::OnMarkerUnlockXClicked);
    connect(MarkerDeleteButton,     &QPushButton::clicked, this, &WidgetForCustomPlot::OnMarkerDeleteClicked);
    connect(MarkerUpButton,         &QPushButton::clicked, this, &WidgetForCustomPlot::OnMarkerUpClicked);
    connect(MarkerDownButton,       &QPushButton::clicked, this, &WidgetForCustomPlot::OnMarkerDownClicked);

    ConnectControlsWidget();

}

void WidgetForCustomPlot::SetUpContextMenu()
{
    contextMenu = new QMenu(tr("Context Menu"), this);

    DisableScalePanelAction   = new QAction(tr("Disable Scale Panel"),    this);
    PolarFormatAction         = new QAction(tr("Polar Format"),           this);

    AmplitudeAction           = new QAction(tr("Amplitude"),              this);
    PhaseAction               = new QAction(tr("Phase"),                  this);
    RealPartAction            = new QAction(tr("RealPart"),               this);
    ImagPartAction            = new QAction(tr("ImagPart"),               this);

    LegendInsideAction        = new QAction(tr("Legend Inside"),          this);
    DisableLegendAction       = new QAction(tr("Disable Legend"),         this);

    QAction * EmptyAction1 = new QAction("", this);
    QAction * EmptyAction2 = new QAction("", this);

    QActionGroup * APRIActionGroup = new QActionGroup(this);
    APRIActionGroup->addAction(AmplitudeAction);
    APRIActionGroup->addAction(PhaseAction);
    APRIActionGroup->addAction(RealPartAction);
    APRIActionGroup->addAction(ImagPartAction);
    APRIActionGroup->setExclusive(true);


    DisableScalePanelAction->setCheckable(true);
    PolarFormatAction->setCheckable(true);
    AmplitudeAction->setCheckable(true);
    PhaseAction->setCheckable(true);
    RealPartAction->setCheckable(true);
    ImagPartAction->setCheckable(true);
    LegendInsideAction->setCheckable(true);
    DisableLegendAction->setCheckable(true);



    contextMenu->addAction(DisableScalePanelAction);
    contextMenu->addAction(PolarFormatAction);
    contextMenu->addAction(EmptyAction1);
    contextMenu->addAction(AmplitudeAction);
    contextMenu->addAction(PhaseAction);
    contextMenu->addAction(RealPartAction);
    contextMenu->addAction(ImagPartAction);
    contextMenu->addAction(EmptyAction2);
    contextMenu->addAction(LegendInsideAction);
    contextMenu->addAction(DisableLegendAction);

    setContextMenuPolicy(Qt::CustomContextMenu);

}






void WidgetForCustomPlot::InitiateButtons()
{
    YLinScaleButton     = new QPushButton(this);
    YLogScaleButton     = new QPushButton(this);
    YFitMaxSpanButton   = new QPushButton(this);
    YFitMaxButton       = new QPushButton(this);
    YManualScaleButton  = new QPushButton(this);
    XScaleRectButton    = new QPushButton(this);
    XFitScaleButton     = new QPushButton(this);
    XUserScaleButton    = new QPushButton(this);
    XHighlightButton    = new QPushButton(this);
    MarkerMoveLeftButton    = new QPushButton(this);
    MarkerMoveRightButton   = new QPushButton(this);
    MarkerRightMaxButton    = new QPushButton(this);
    MarkerLeftMaxButton     = new QPushButton(this);
    MarkerRightMinButton    = new QPushButton(this);
    MarkerLeftMinButton     = new QPushButton(this);
    MarkerLocalMaxButton    = new QPushButton(this);
    MinusRightButton        = new QPushButton(this);
    MinusLeftButton         = new QPushButton(this);
    MarkerAddButton         = new QPushButton(this);
    MarkerGraphButton       = new QPushButton(this);
    MarkerIncreaseNButton   = new QPushButton(this);
    MarkerPrintButton       = new QPushButton(this);
    MarkerIncreaseButton    = new QPushButton(this);
    MarkerUnlockYButton     = new QPushButton(this);
    MarkerUnlockXButton     = new QPushButton(this);
    MarkerDeleteButton      = new QPushButton(this);
    MarkerUpButton          = new QPushButton(this);
    MarkerDownButton        = new QPushButton(this);


    YLinScaleButton     ->setIcon(QIcon(QPixmap(iconPaths[0])));
    YLogScaleButton     ->setIcon(QIcon(QPixmap(iconPaths[1])));
    YFitMaxSpanButton   ->setIcon(QIcon(QPixmap(iconPaths[2])));
    YFitMaxButton       ->setIcon(QIcon(QPixmap(iconPaths[3])));
    YManualScaleButton  ->setIcon(QIcon(QPixmap(iconPaths[4])));
    XScaleRectButton    ->setIcon(QIcon(QPixmap(iconPaths[5])));
    XFitScaleButton     ->setIcon(QIcon(QPixmap(iconPaths[6])));
    XUserScaleButton    ->setIcon(QIcon(QPixmap(iconPaths[7])));
    XHighlightButton    ->setIcon(QIcon(QPixmap(iconPaths[8])));
    MarkerMoveLeftButton    ->setIcon(QIcon(QPixmap(iconPaths[9])));
    MarkerMoveRightButton   ->setIcon(QIcon(QPixmap(iconPaths[10])));
    MarkerRightMaxButton    ->setIcon(QIcon(QPixmap(iconPaths[11])));
    MarkerLeftMaxButton     ->setIcon(QIcon(QPixmap(iconPaths[12])));
    MarkerRightMinButton    ->setIcon(QIcon(QPixmap(iconPaths[13])));
    MarkerLeftMinButton     ->setIcon(QIcon(QPixmap(iconPaths[14])));
    MarkerLocalMaxButton    ->setIcon(QIcon(QPixmap(iconPaths[15])));
    MinusRightButton        ->setIcon(QIcon(QPixmap(iconPaths[16])));
    MinusLeftButton         ->setIcon(QIcon(QPixmap(iconPaths[17])));
    MarkerAddButton         ->setIcon(QIcon(QPixmap(iconPaths[18])));
    MarkerGraphButton       ->setIcon(QIcon(QPixmap(iconPaths[19])));
    MarkerIncreaseNButton   ->setIcon(QIcon(QPixmap(iconPaths[20])));
    MarkerPrintButton       ->setIcon(QIcon(QPixmap(iconPaths[21])));
    MarkerIncreaseButton    ->setIcon(QIcon(QPixmap(iconPaths[22])));
    MarkerUnlockYButton     ->setIcon(QIcon(QPixmap(iconPaths[23])));
    MarkerUnlockXButton     ->setIcon(QIcon(QPixmap(iconPaths[24])));
    MarkerDeleteButton      ->setIcon(QIcon(QPixmap(iconPaths[25])));
    MarkerUpButton          ->setIcon(QIcon(QPixmap(iconPaths[26])));
    MarkerDownButton        ->setIcon(QIcon(QPixmap(iconPaths[27])));


    YLinScaleButton->setCheckable(true);
    YLogScaleButton->setCheckable(true);

    YLogScaleButton->setChecked(true);

    YLinLogScaleButtonGroup = new QButtonGroup(this);
    YLinLogScaleButtonGroup->addButton(YLinScaleButton);
    YLinLogScaleButtonGroup->addButton(YLogScaleButton);
    YLinLogScaleButtonGroup->setExclusive(true);

    YFitMaxSpanButton   ->setCheckable(true);
    YFitMaxButton       ->setCheckable(true);
    YManualScaleButton  ->setCheckable(true);

    YManualScaleButton  ->setChecked(true);

    YFitMaxSpanOrManualButtonGroup = new QButtonGroup(this);
    YFitMaxSpanOrManualButtonGroup->addButton(YFitMaxSpanButton);
    YFitMaxSpanOrManualButtonGroup->addButton(YFitMaxButton);
    YFitMaxSpanOrManualButtonGroup->addButton(YManualScaleButton);
    YFitMaxSpanOrManualButtonGroup->setExclusive(true);

    MarkerLocalMaxButton->setCheckable(true);


    XScaleRectButton->setCheckable(true);

    MarkerAddButton->setCheckable(true);
    MarkerDeleteButton->setCheckable(true);

    MarkerGraphButton->setCheckable(true);



    PlotButtonVector.append(YLinScaleButton);
    PlotButtonVector.append(YLogScaleButton);
    PlotButtonVector.append(YFitMaxSpanButton);
    PlotButtonVector.append(YFitMaxButton);
    PlotButtonVector.append(YManualScaleButton);
    PlotButtonVector.append(XScaleRectButton);
    PlotButtonVector.append(XFitScaleButton);
    PlotButtonVector.append(XUserScaleButton);
    PlotButtonVector.append(XHighlightButton);
    PlotButtonVector.append(MarkerMoveLeftButton);
    PlotButtonVector.append(MarkerMoveRightButton);
    PlotButtonVector.append(MarkerRightMaxButton);
    PlotButtonVector.append(MarkerLeftMaxButton);
    PlotButtonVector.append(MarkerRightMinButton);
    PlotButtonVector.append(MarkerLeftMinButton);
    PlotButtonVector.append(MarkerLocalMaxButton);
    PlotButtonVector.append(MinusRightButton);
    PlotButtonVector.append(MinusLeftButton);
    PlotButtonVector.append(MarkerAddButton);
    PlotButtonVector.append(MarkerGraphButton);
    PlotButtonVector.append(MarkerIncreaseNButton);
    PlotButtonVector.append(MarkerPrintButton);
    PlotButtonVector.append(MarkerIncreaseButton);
    PlotButtonVector.append(MarkerUnlockYButton);
    PlotButtonVector.append(MarkerUnlockXButton);
    PlotButtonVector.append(MarkerDeleteButton);
    PlotButtonVector.append(MarkerUpButton);
    PlotButtonVector.append(MarkerDownButton);

    for (int i=0;i<28;i++) // Перенести в SetUpGeneralStyle
    {
        PlotButtonVector[i]->setFixedSize(20,20);
        PlotButtonVector[i]->setContentsMargins(0,0,0,0);
        PlotButtonVector[i]->setStyleSheet("QPushButton {"
                                           "border-style: outset;"
                                           "border-width: 1px;"
                                           "border-color: gray;"
                                           "padding: 0px;"
                                           "}"
                                           "QPushButton:pressed {"
                                           "border-color: blue;"
                                           "background-color: lightblue;"
                                           "}"
                                           "QPushButton:checked {"
                                           "border-color: blue;"
                                           "background-color: lightgray;"
                                           "}");
    }

}

void WidgetForCustomPlot::FillYAxisControl()
{
    QWidget * YAxisWidget = new QWidget(ControlsWidget);
    YAxisWidget->setContentsMargins(QMargins(0,0,0,0));
    QVBoxLayout * YAxisVertLayout = new QVBoxLayout(YAxisWidget);

    YAxisTitleLabel = new QLabel(tr("Y-axis"));
    YAxisVertLayout->addWidget(YAxisTitleLabel);

    QGridLayout * YAxisGridLayout = new QGridLayout();

    YAxisMaxLabel   = new QLabel(tr("Max (dB)"));
    YAxisSpanLabel  = new QLabel(tr("Span (dB)"));
    YAxisMaxBox     = new QComboBox();
    YAxisSpanBox    = new QComboBox();
    YAxisMaxBox ->setEditable(true);
    YAxisSpanBox->setEditable(true);
    YAxisMaxBox ->addItem("10");
    YAxisSpanBox->addItem("10");
    YAxisMaxBox ->addItem("20");
    YAxisSpanBox->addItem("20");


    YAxisGridLayout->addWidget(YAxisMaxLabel, 0, 0);
    YAxisGridLayout->addWidget(YAxisSpanLabel, 0, 1);
    YAxisGridLayout->addWidget(YAxisMaxBox, 1, 0);
    YAxisGridLayout->addWidget(YAxisSpanBox, 1, 1);


    QWidget * YAxisScaleTypeWidget = new QWidget(YAxisWidget);
    QHBoxLayout * YAxisScaleTypeWidgetHorLayout = new QHBoxLayout();

    YAxisScaleTypeWidgetHorLayout->addWidget(PlotButtonVector[0]);
    YAxisScaleTypeWidgetHorLayout->addWidget(PlotButtonVector[1]);
    YAxisScaleTypeWidget->setLayout(YAxisScaleTypeWidgetHorLayout);
    YAxisGridLayout->addWidget(YAxisScaleTypeWidget, 2, 0);


    QWidget * YAxisScaleWidget = new QWidget(YAxisWidget);
    QHBoxLayout * YAxisScaleWidgetHorLayout = new QHBoxLayout();
    YAxisScaleWidgetHorLayout->addWidget(PlotButtonVector[2]);
    YAxisScaleWidgetHorLayout->addWidget(PlotButtonVector[3]);
    YAxisScaleWidgetHorLayout->addWidget(PlotButtonVector[4]);
    YAxisScaleWidget->setLayout(YAxisScaleWidgetHorLayout);
    YAxisGridLayout->addWidget(YAxisScaleWidget, 2, 1);

    YAxisVertLayout->addWidget(YAxisTitleLabel);
    YAxisVertLayout->addLayout(YAxisGridLayout);

    YAxisWidget->setLayout(YAxisVertLayout);

    VerticalControlsLayout->addWidget(YAxisWidget);

    YAxisMaxBox         ->setFixedWidth(80);
    YAxisSpanBox        ->setFixedWidth(80);
    YAxisScaleTypeWidget->setFixedWidth(80);
    YAxisScaleWidget    ->setFixedWidth(80);
}

void WidgetForCustomPlot::FillXAxisAndMarkerControl()
{
    QWidget * XAxisWidget = new QWidget(ControlsWidget);
    QGridLayout * XAxisGridLayout = new QGridLayout(XAxisWidget);
    XAxisWidget->setLayout(XAxisGridLayout);

    XAxisTitleLabel = new QLabel(tr("X-Axis"));
    XAxisGridLayout->addWidget(XAxisTitleLabel, 0, 0, 1, 2);


    XAxisGridLayout->addWidget(PlotButtonVector[5], 0,2);
    XAxisGridLayout->addWidget(PlotButtonVector[6], 0,3);
    XAxisGridLayout->addWidget(PlotButtonVector[7], 0,4);
    XAxisGridLayout->addWidget(PlotButtonVector[8], 0,5);


    XAxisGridLayout->addWidget(PlotButtonVector[9], 1,0);
    XAxisGridLayout->addWidget(PlotButtonVector[10], 1,1);
    XAxisGridLayout->addWidget(PlotButtonVector[11], 1,2);
    XAxisGridLayout->addWidget(PlotButtonVector[12], 1,3);
    XAxisGridLayout->addWidget(PlotButtonVector[13], 1,4);
    XAxisGridLayout->addWidget(PlotButtonVector[14], 1,5);


    XAxisGridLayout->addWidget(PlotButtonVector[15], 2,0);
    XAxisGridLayout->addWidget(new QComboBox(),      2,1,1,3);
    XAxisGridLayout->addWidget(PlotButtonVector[16], 2,4);
    XAxisGridLayout->addWidget(PlotButtonVector[17], 2,5);



    VerticalControlsLayout->addWidget(XAxisWidget);

}

void WidgetForCustomPlot::FillMarkerTable()
{

    QFrame * MarkerFrame = new QFrame(ControlsWidget); // Попробовать иначе
    QGridLayout * MarkerFrameLayout = new QGridLayout(MarkerFrame);
    MarkerFrame->setLayout(MarkerFrameLayout);

    MarkerTitleLabel = new QLabel(tr("Marker"));
    MarkerFrameLayout->addWidget(MarkerTitleLabel,0,0,1,2);

    MarkerFrameLayout->addWidget(PlotButtonVector[18], 0,2);
    MarkerFrameLayout->addWidget(PlotButtonVector[19], 0,3);
    MarkerFrameLayout->addWidget(PlotButtonVector[20], 0,4);
    MarkerFrameLayout->addWidget(PlotButtonVector[21], 0,5);


    MarkerFrameLayout->addWidget(PlotButtonVector[22], 1,0);
    MarkerFrameLayout->addWidget(PlotButtonVector[23], 1,1);
    MarkerFrameLayout->addWidget(PlotButtonVector[24], 1,2);
    MarkerFrameLayout->addWidget(PlotButtonVector[25], 1,3);
    MarkerFrameLayout->addWidget(PlotButtonVector[26], 1,4);
    MarkerFrameLayout->addWidget(PlotButtonVector[27], 1,5);


    QTableWidget * MarkerTable = new QTableWidget(MarkerFrame);
    MarkerTable->setColumnCount(2);
    //MarkerTable->setCellWidget(0,0, new QPushButton("m"));
    //MarkerTable->setCellWidget(0,1, new QPushButton("Val"));
    MarkerTable->setHorizontalHeaderLabels({tr("m"),tr("Val")});
    MarkerFrameLayout->addWidget(MarkerTable,2,0,5,6);
    MarkerTable->setColumnWidth(0,50);
    MarkerTable->setColumnWidth(1,50);
    VerticalControlsLayout->addWidget(MarkerFrame);

    MarkerTable->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
}


























































void WidgetForCustomPlot::OpenMarkerColourDialogue()
{
    QColor ChosenColour = QColorDialog::getColor(customPlot->MarkerColour, this, "Выберите цвет");
    if (ChosenColour.isValid())
    {
        customPlot->MarkerColour = ChosenColour;
        /*
        //Графика для предпросмотра текущего вида маркеров больше нет
        PreviewMarker->setPen(ChosenColour);
        PreviewMarker->setBrush(ChosenColour);
        MarkerPreviewPlot->replot();
        */
    }
}



void WidgetForCustomPlot::ChangeMarkerStyle(int ComboIndex)
{
    customPlot->MarkerStyle = ComboIndex+1;

    /*
    //Графика для предпросмотра текущего вида маркеров больше нет
    PreviewMarker->setStyle(QCPItemTracer::TracerStyle(ComboIndex+1));
    MarkerPreviewPlot->replot();
    */
}




void WidgetForCustomPlot::XAxisRangeChanged(const QCPRange &range)
{
    //double XMin = customPlot->xAxis->range().lower;
    //double XMax = customPlot->xAxis->range().upper;

    //XRangeEditFrom->setText(QString::number(range.lower));
    //XRangeEditTo  ->setText(QString::number(range.upper));
}




void WidgetForCustomPlot::YAxisRangeChanged(const QCPRange &range)
{
    this->YAxisMaxBox   ->setEditable(true);
    this->YAxisSpanBox  ->setEditable(true);
    this->YAxisMaxBox   ->setEnabled(true);
    this->YAxisSpanBox  ->setEnabled(true);

    YAxisMaxBox ->setEditText(QString::number(range.upper));
    YAxisSpanBox->setEditText(QString::number(range.upper-range.lower));
}


void WidgetForCustomPlot::EnterSelectLocalMaxMode()
{
    int GraphID = 0;
    if (MarkerLocalMaxButton->isChecked())
    {
        if (!customPlot->graph(GraphID)->data()->isEmpty())
        {
            //this->RubberBandButton->setChecked(false);
            //this->SelectLocalMinButton->setChecked(false);
            customPlot->setInteractions(QCP::iSelectPlottables| QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectItems);
            customPlot->setSelectionRectMode(QCP::srmSelect);
            customPlot->graph(GraphID)->setSelectable(QCP::stDataRange);


            connect(customPlot, SIGNAL(selectionChangedByUser()), this, SLOT(PutMarkerAtLocalMax()));// Почему так работает, а как обычно -- нет?
         disconnect(customPlot, SIGNAL(selectionChangedByUser()), this, SLOT(PutMarkerAtLocalMin()));
        }
        else
        {
            this->MarkerLocalMaxButton->setChecked(false);
        }
    }
    else
    {
        customPlot->setSelectionRectMode(QCP::srmNone);
        customPlot->setInteractions(QCP::iRangeZoom | QCP::iRangeDrag | QCP::iSelectItems);
        disconnect(customPlot, SIGNAL(selectionChangedByUser()), this, SLOT(PutMarkerAtLocalMax()));
    }

}

void WidgetForCustomPlot::PutMarkerAtLocalMax()
{
    //int GraphID = GraphChoiceComboBox->currentIndex(); // Брать из легенды!!!!!!
    int GraphID = 0;
    if (customPlot->graph(GraphID)->selection().isEmpty())
    {
        qDebug()<<"No data selected";
        for (int i=0;i<customPlot->graphCount();i++)
        {
            customPlot->graph(i)->setSelection(QCPDataSelection());
        }
        return;
    }
    else
    {
        QCPDataSelection SelectedData = customPlot->graph(GraphID)->selection();
        SelectedData.enforceType(QCP::stDataRange);
        QCPDataRange DataRange = SelectedData.dataRange();
        if (DataRange.size() > 0)
        {
            double MaxValue = customPlot->graph(GraphID)->data()->at(DataRange.begin())->value;
            double MaxKey   = customPlot->graph(GraphID)->data()->at(DataRange.begin())->key;;
            for (int i = DataRange.begin(); i < DataRange.end(); i++)
            {
                double CurrentValue = this->customPlot->graph(GraphID)->data()->at(i)->value;
                if (MaxValue < CurrentValue)
                {
                    MaxKey = this->customPlot->graph(GraphID)->data()->at(i)->key;
                    MaxValue = CurrentValue;
                }
            }
            customPlot->AddNewMarker(MaxKey,customPlot->MarkerStyle, customPlot->MarkerColour, customPlot->SelectedGraph);
        }
        else if (DataRange.size() == 0)
        {
            return;
        }
        customPlot->graph(GraphID)->setSelection(QCPDataSelection());
    }

}






void WidgetForCustomPlot::ToNextMax() // Нужно ли рассмотреть случай маркера на первой координате?
{
    if (this->customPlot->selectedItems().size() == 1)
    {
        //Как переделать лучше?
        QCPItemTracer * SelectedMarker = qobject_cast <QCPItemTracer*> (this->customPlot->selectedItems().last());

        double CurrentX = SelectedMarker->position->key();
        double CurrentY = SelectedMarker->position->value(); // В этой строке даёт неправильное значение -- дальше меняется

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



        double MaxY = 0;

        QCPGraph * MarkerGraph = SelectedMarker->graph();

        for (int i=0; i < MarkerGraph->data()->size(); i++) // Можно сделать поиск быстрее, учитывая вид x
        {
            if (MarkerGraph->data()->at(i)->key == MaxX)
            {
                MaxY = MarkerGraph->data()->at(i)->value;
            }
        }

        //MaxY = MarkerGraph->data()->at(MarkerIndex)->value;

        //MarkerPositionsTable->item(2,1)->setText(QString::number(MaxX));
        //MarkerPositionsTable->item(2,2)->setText(QString::number(MaxY));

        int SelectedMarkerRow = -1;

        /*
        for (int row = 0; row < this->MarkerPositionsTable->rowCount(); row++)
        {
            if (this->MarkerPositionsTable->item(row, 0)->background().color() == HighlightColor)
            {
                SelectedMarkerRow = row;
                break;
            }
        }
        */

        QTableWidgetItem * MaxXItem = new QTableWidgetItem(QString::number(MaxX));
        QTableWidgetItem * MaxYItem = new QTableWidgetItem(QString::number(MaxY));

        MaxXItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        MaxYItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

        //MarkerPositionsTable->setItem(SelectedMarkerRow, 2, MaxXItem);
        //MarkerPositionsTable->setItem(SelectedMarkerRow, 3, MaxYItem);

        //MarkerPositionsTable->item(SelectedMarkerRow,2)->setBackground(HighlightColor);
        //MarkerPositionsTable->item(SelectedMarkerRow,3)->setBackground(HighlightColor);

        customPlot->replot();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Предупреждение!");
        msgBox.setText("Число выделенных маркеров не равно одному");
        msgBox.setInformativeText("Убедитесь, что вы выделили маркер");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
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

        int SelectedMarkerRow = -1;
        /*
        for (int row = 0; row < this->MarkerPositionsTable->rowCount(); row++)
        {
            if (MarkerPositionsTable->item(row, 0)->background().color() == HighlightColor)
            {
                SelectedMarkerRow = row;
                break;
            }
        }
        */
        double MaxY = 0;

        qDebug()<<"Меняется строка: "<< SelectedMarkerRow;
        QCPGraph * MarkerGraph = SelectedMarker->graph();

        for (int i=0; i < MarkerGraph->data()->size(); i++) // Можно сделать поиск быстрее, учитывая вид x
        {
            if (MarkerGraph->data()->at(i)->key == MaxX)
            {
                MaxY = MarkerGraph->data()->at(i)->value;
            }
        }

        //MaxY = MarkerGraph->data()->at(MarkerIndex)->value;

        //MarkerPositionsTable->item(2,1)->setText(QString::number(MaxX));
        //MarkerPositionsTable->item(2,2)->setText(QString::number(MaxY));

        QTableWidgetItem * MaxXItem = new QTableWidgetItem(QString::number(MaxX));
        QTableWidgetItem * MaxYItem = new QTableWidgetItem(QString::number(MaxY));

        MaxXItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        MaxYItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

        //MarkerPositionsTable->setItem(SelectedMarkerRow, 2, MaxXItem);
        //MarkerPositionsTable->setItem(SelectedMarkerRow, 3, MaxYItem);

        //qDebug()<<MarkerPositionsTable->item(0,0)->background();

        //MarkerPositionsTable->item(SelectedMarkerRow,2)->setBackground(HighlightColor);
        //MarkerPositionsTable->item(SelectedMarkerRow,3)->setBackground(HighlightColor);
        //QTableWidgetItem* item2 = MarkerPositionsTable->item(SelectedMarkerRow, 2);
        //QTableWidgetItem* item3 = MarkerPositionsTable->item(SelectedMarkerRow, 3);
        /*
        if (item2) {
            item2->setBackground(HighlightColor);
        } else {
            qDebug() << "Item at (SelectedMarkerRow, 2) is null.";
        }

        if (item3) {
            item3->setBackground(HighlightColor);
        } else {
            qDebug() << "Item at (SelectedMarkerRow, 3) is null.";
        }
        */


        customPlot->replot();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Предупреждение!");
        msgBox.setText("Число выделенных маркеров не равно одному");
        msgBox.setInformativeText("Убедитесь, что вы выделили маркер");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
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
    /*
    // Добавляется без графика -- сделать проверку, не пустой ли график
    int NumberOfRows = MarkerPositionsTable->rowCount();
    MarkerPositionsTable->insertRow(MarkerPositionsTable->rowCount());
    //MarkerPositionsTable->insertRow(MarkerPositionsTable->rowCount()+2);
    //MarkerPositionsTable->setItem(NumberOfRows-1, 0, new QTableWidgetItem(QString::number(MarkerPositionsTable->rowCount())));

    QTableWidgetItem * MarkerIndexItem  = new QTableWidgetItem(QString::number(CurrentMarkerIndex));
    MarkerIndexItem ->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    MarkerPositionsTable->setItem(NumberOfRows, 1, MarkerIndexItem);
    CurrentMarkerIndex++;


    double MarkerX = MarkerPtr->graphKey();
    double MarkerY;
    QCPGraph * MarkerGraph = MarkerPtr->graph();

    double X0 = MarkerGraph->data()->at(0)->key;
    double X1 = MarkerGraph->data()->at(1)->key;
    qDebug()<< X0 << X1;


    int MarkerIndex = int((MarkerX - X0)/(X1-X0));

    qDebug()<< MarkerIndex << (MarkerX - X0)/(X1-X0); // Почему не получается проще?

    qDebug()<< "Index1 = " << MarkerIndex;

    for (int i=0; i < MarkerGraph->data()->size(); i++) // Можно сделать поиск быстрее, учитывая вид x.
    {
        if (MarkerGraph->data()->at(i)->key == MarkerX)
        {
            MarkerX = MarkerGraph->data()->at(i)->key;
            MarkerY = MarkerGraph->data()->at(i)->value;
            qDebug()<< "Index2 = " << i;
        }
    }

    MarkerY = MarkerGraph->data()->at(MarkerIndex)->value;



    QTableWidgetItem * MarkerXItem  = new QTableWidgetItem(QString::number(MarkerX));
    QTableWidgetItem * MarkerYItem  = new QTableWidgetItem(QString::number(MarkerY));
    QTableWidgetItem * GraphIdItem  = new QTableWidgetItem(QString::number(customPlot->SelectedGraph+1));

    MarkerXItem ->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    MarkerYItem ->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    GraphIdItem ->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);


    MarkerPositionsTable->setItem(NumberOfRows, 0, GraphIdItem);
    //MarkerPositionsTable->setItem(NumberOfRows, 1, MarkerIndexItem);//Добавлено ранее
    MarkerPositionsTable->setItem(NumberOfRows, 2, MarkerXItem);
    MarkerPositionsTable->setItem(NumberOfRows, 3, MarkerYItem);

    //MarkerPositionsTable->resizeColumnToContents(3);
    //MarkerPositionsTable->resizeColumnToContents(2);
    //MarkerPositionsTable->resizeColumnToContents(1);
    //MarkerPositionsTable->resizeColumnToContents(0);
    */
}


void WidgetForCustomPlot::RemoveMarkerFromTable(int RowNumberOfMarker)
{
    //MarkerPositionsTable->removeRow(RowNumberOfMarker);
}

void WidgetForCustomPlot::HighlightMarkerInTable(int RowNumberOfMarker)
{
    /*
    qDebug()<<"HighLighting!";

    for (int column = 0; column < MarkerPositionsTable->columnCount(); column++)
    {
        QTableWidgetItem *item = MarkerPositionsTable->item(RowNumberOfMarker, column);
        if (item)
        {
            item->setBackground(HighlightColor);
        }
    }
    */
}




void WidgetForCustomPlot::UnHighlightMarkerInTable(int RowNumberOfMarker)
{
    /*
    //qDebug()<<"Regularizing!";
    for (int column = 0; column < MarkerPositionsTable->columnCount(); column++)
    {
        QTableWidgetItem *item = MarkerPositionsTable->item(RowNumberOfMarker, column);
        if (item)
        {
            item->setBackground(Qt::white);
        }
    }
    */
}



void WidgetForCustomPlot::ClearTable()
{
    /*
    MarkerPositionsTable->setRowCount(0);
    CurrentMarkerIndex = 0;
    */
}

/*
void WidgetForCustomPlot::SetRange() // Теперь задаётся только y, а x выбирается выделением (Может всё-таки вернуть точное задание x?)
{
    this->customPlot->xAxis->setRange(XRangeEditFrom->text().toDouble(),XRangeEditTo->text().toDouble());
    this->customPlot->yAxis->setRange(YRangeEditFrom->text().toDouble(),YRangeEditTo->text().toDouble());
    this->customPlot->replot();
}
*/


void WidgetForCustomPlot::AddMarkerSlot()
{
    if (!this->customPlot->graph(this->customPlot->SelectedGraph)->data()->isEmpty())
    {
        customPlot->markeraddbuttonactive = MarkerAddButton->isChecked();
        customPlot->markerdeletebuttonactive = false;

        MarkerDeleteButton->setChecked(false);
        customPlot->MouseMoveMarker->setVisible(customPlot->markeraddbuttonactive);
        customPlot->MouseMoveLabel->setVisible(customPlot->markeraddbuttonactive);
        customPlot->replot();
    }
    else
    {
        MarkerAddButton->setChecked(false);
        MarkerDeleteButton->setChecked(false);

        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Предупреждение!");
        msgBox.setText("График не найден");
        msgBox.setInformativeText("Прежде чем ставить маркер добавьте график");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
}


void WidgetForCustomPlot::DeleteMarkerSlot()
{
    if (!this->customPlot->graph(this->customPlot->SelectedGraph)->data()->isEmpty())
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
    else
    {
        MarkerAddButton->setChecked(false);
        MarkerDeleteButton->setChecked(false);

        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Предупреждение!");
        msgBox.setText("График не найден");
        msgBox.setInformativeText("Прежде чем ставить маркер добавьте график");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }

}




void WidgetForCustomPlot::ConnectControlsWidget()
{

    connect(YAxisMaxBox,  &QComboBox::currentTextChanged, customPlot, &PlotClass::ChangeYAxisMax);
    connect(YAxisSpanBox, &QComboBox::currentTextChanged, customPlot, &PlotClass::ChangeYAxisSpan);
}





void WidgetForCustomPlot::ToNextKey()
{
    if (this->customPlot->selectedItems().size() == 1)
    {

        QCPItemTracer * SelectedMarker = qobject_cast <QCPItemTracer*> (this->customPlot->selectedItems().last());

        double CurrentX = SelectedMarker->graphKey();
        qDebug()<<CurrentX;


        /*

        QTableWidgetItem * MaxXItem = new QTableWidgetItem(QString::number(MaxX));
        QTableWidgetItem * MaxYItem = new QTableWidgetItem(QString::number(MaxY));

        MaxXItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        MaxYItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

        MarkerPositionsTable->setItem(SelectedMarkerRow, 2, MaxXItem);
        MarkerPositionsTable->setItem(SelectedMarkerRow, 3, MaxYItem);

        //MarkerPositionsTable->item(SelectedMarkerRow,2)->setBackground(HighlightColor);
        //MarkerPositionsTable->item(SelectedMarkerRow,3)->setBackground(HighlightColor);

        customPlot->replot();
        */
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Предупреждение!");
        msgBox.setText("Число выделенных маркеров не равно одному");
        msgBox.setInformativeText("Убедитесь, что вы выделили маркер");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
}



void WidgetForCustomPlot::ToPrevKey()
{

}








void WidgetForCustomPlot::OnYLinScaleClicked()
{
    customPlot->yAxis->setScaleType(QCPAxis::ScaleType::stLinear);
}

void WidgetForCustomPlot::OnYLogScaleClicked()
{
    customPlot->yAxis->setScaleType(QCPAxis::ScaleType::stLogarithmic);
}

void WidgetForCustomPlot::OnYFitMaxSpanClicked()
{
    YAxisMaxBox ->setEditable(false);
    YAxisSpanBox->setEditable(false);
    YAxisMaxBox  ->setEnabled(false);
    YAxisSpanBox ->setEnabled(false);

    customPlot->yAxis->rescale();
    customPlot->replot();
}

void WidgetForCustomPlot::OnYFitMaxClicked()
{
    YAxisMaxBox    ->setEditable(false);
    YAxisSpanBox   ->setEditable(true);
    YAxisMaxBox     ->setEnabled(false);
    YAxisSpanBox    ->setEnabled(true);

    QVector <QCPGraph*> GV = customPlot->yAxis->graphs();
    if (GV.size()>0)
    {
        if (GV[0]->data()->size()>0)
        {
        double MaxValue = GV[0]->data()->at(0)->value;
        for (int i=0; i<GV.size(); i++)
        {
            for (int j = 0; j < GV[i]->data()->size(); j++)
            {
                double yValue = GV[i]->data()->at(j)->value;
                if (yValue > MaxValue)
                {
                    MaxValue = yValue;
                }
            }
        }
        customPlot->ChangeYAxisMax(QString::number(MaxValue));
        }
    }
}

void WidgetForCustomPlot::OnYManualScaleClicked()
{
    YAxisMaxBox->setEditable(true);
    YAxisSpanBox->setEditable(true);
    YAxisMaxBox     ->setEnabled(true);
    YAxisSpanBox    ->setEnabled(true);
}

void WidgetForCustomPlot::OnXScaleRectClicked()
{
    if (XScaleRectButton->isChecked())
    {
        customPlot->axisRect()->setRangeZoom(Qt::Horizontal);
        QList <QCPAxis * > ZoomableAxesList = {customPlot->xAxis};
        customPlot->axisRect()->setRangeZoomAxes(ZoomableAxesList);
        //this->LockXAxisButton->setChecked(false);
        qobject_cast<SelectionRectClass*>(customPlot->selectionRect())->YAxisLocked = true;
        qobject_cast<SelectionRectClass*>(customPlot->selectionRect())->XAxisLocked = false;
        MarkerLocalMaxButton->setChecked(false);
        customPlot->setInteractions(QCP::iRangeZoom | QCP::iRangeDrag | QCP::iSelectItems);
        customPlot->setSelectionRectMode(QCP::srmZoom);
    }
    else
    {
        customPlot->axisRect()->setRangeZoom(Qt::Horizontal | Qt::Vertical);
        customPlot->axisRect()->setRangeZoomAxes(customPlot->xAxis, customPlot->yAxis);
        qobject_cast<SelectionRectClass*>(customPlot->selectionRect())->XAxisLocked = false;
        qobject_cast<SelectionRectClass*>(customPlot->selectionRect())->YAxisLocked = false;
        customPlot->setSelectionRectMode(QCP::srmNone);
    }


}

void WidgetForCustomPlot::OnXFitScaleClicked()
{
    XScaleRectButton->setChecked(false);
    SelectedRangeXMax = customPlot->xAxis->range().upper;   // Или лучше сохранять диапазон, выбранный пользователем, а не перед автоматическим масштабированием?
    SelectedRangeXMin = customPlot->xAxis->range().lower;
    customPlot->xAxis->rescale();
    customPlot->replot();
}


void WidgetForCustomPlot::OnXUserScaleClicked()
{
    XScaleRectButton->setChecked(false);
    if (SelectedRangeXMax - SelectedRangeXMin >0)
    {
        customPlot->xAxis->setRange(SelectedRangeXMin, SelectedRangeXMax);
        customPlot->replot();
    }
    else
    {
        qDebug()<<"Выберите область";
    }
}

void WidgetForCustomPlot::OnXHighlightClicked()
{

}

void WidgetForCustomPlot::OnMarkerMoveLeftClicked()
{

    if (this->customPlot->selectedItems().size() == 1)
    {
        QCPItemTracer * SelectedMarker = qobject_cast <QCPItemTracer*> (this->customPlot->selectedItems().last());

        double CurrentX = SelectedMarker->position->key();
        double XValue = CurrentX;
        QCPGraph * SelectedGraph = SelectedMarker->graph();

        for (int i = SelectedGraph->data()->size()-1; i >-1 ; i--)
        {
            double x = SelectedGraph->data()->at(i)->key;
            if (x < CurrentX)
            {
                qDebug()<< "x = " << x << ", CurrentX =" << CurrentX;
                XValue = x;
                break;
            }
            else
            {
                if (x==CurrentX and i==(SelectedGraph->data()->size()-1))
                {qDebug()<<"Right side reached!";}
            }
        }

        SelectedMarker->setGraphKey(XValue);
        SelectedMarker->updatePosition();


        double YValue = 0;

        QCPGraph * MarkerGraph = SelectedMarker->graph();

        for (int i=0; i < MarkerGraph->data()->size(); i++)
        {
            if (MarkerGraph->data()->at(i)->key == XValue)
            {
                YValue = MarkerGraph->data()->at(i)->value;
            }
        }


        int SelectedMarkerRow = -1;
        /*
        for (int row = 0; row < this->MarkerPositionsTable->rowCount(); row++)
        {
            if (this->MarkerPositionsTable->item(row, 0)->background().color() == HighlightColor)
            {
                SelectedMarkerRow = row;
                break;
            }
        }
        */

        QTableWidgetItem * PrevXItem = new QTableWidgetItem(QString::number(XValue));
        QTableWidgetItem * PrevYItem = new QTableWidgetItem(QString::number(YValue));

        PrevXItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        PrevYItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

        //MarkerPositionsTable->setItem(SelectedMarkerRow, 2, PrevXItem);
        //MarkerPositionsTable->setItem(SelectedMarkerRow, 3, PrevYItem);

        customPlot->replot();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Предупреждение!");
        msgBox.setText("Число выделенных маркеров не равно одному");
        msgBox.setInformativeText("Убедитесь, что вы выделили маркер");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
}




void WidgetForCustomPlot::OnMarkerMoveRightClicked()
{

    if (this->customPlot->selectedItems().size() == 1)
    {
        QCPItemTracer * SelectedMarker = qobject_cast <QCPItemTracer*> (this->customPlot->selectedItems().last());

        double CurrentX = SelectedMarker->position->key();
        double XValue = CurrentX;
        QCPGraph * SelectedGraph = SelectedMarker->graph();

        for (int i = 0; i < SelectedGraph->data()->size(); i++)
        {
            double x = SelectedGraph->data()->at(i)->key;
            if (x > CurrentX)
            {
                //qDebug()<< "x = " << x << ", CurrentX =" << CurrentX;
                XValue = x;
                break;
            }
            else
            {
                if (x==CurrentX and i==(SelectedGraph->data()->size()-1))
                {qDebug()<<"Right side reached!";}
            }
        }

        SelectedMarker->setGraphKey(XValue);
        SelectedMarker->updatePosition();


        double YValue = 0;

        QCPGraph * MarkerGraph = SelectedMarker->graph();

        for (int i=0; i < MarkerGraph->data()->size(); i++)
        {
            if (MarkerGraph->data()->at(i)->key == XValue)
            {
                YValue = MarkerGraph->data()->at(i)->value;
            }
        }


        int SelectedMarkerRow = -1;
        /*
        for (int row = 0; row < this->MarkerPositionsTable->rowCount(); row++)
        {
            if (this->MarkerPositionsTable->item(row, 0)->background().color() == HighlightColor)
            {
                SelectedMarkerRow = row;
                break;
            }
        }
        */

        QTableWidgetItem * NextXItem = new QTableWidgetItem(QString::number(XValue));
        QTableWidgetItem * NextYItem = new QTableWidgetItem(QString::number(YValue));

        NextXItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        NextYItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

        //MarkerPositionsTable->setItem(SelectedMarkerRow, 2, NextXItem);
        //MarkerPositionsTable->setItem(SelectedMarkerRow, 3, NextYItem);

        //MarkerPositionsTable->item(SelectedMarkerRow,2)->setBackground(HighlightColor);
        //MarkerPositionsTable->item(SelectedMarkerRow,3)->setBackground(HighlightColor);

        customPlot->replot();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Предупреждение!");
        msgBox.setText("Число выделенных маркеров не равно одному");
        msgBox.setInformativeText("Убедитесь, что вы выделили маркер");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
}

void WidgetForCustomPlot::OnMarkerRightMaxClicked()
{
    ToNextMax();
}

void WidgetForCustomPlot::OnMarkerLeftMaxClicked()
{
    ToPrevMax();
}

void WidgetForCustomPlot::OnMarkerRightMinClicked()
{
    if (this->customPlot->selectedItems().size() == 1)
    {
        QCPItemTracer * SelectedMarker = qobject_cast <QCPItemTracer*> (this->customPlot->selectedItems().last());

        double CurrentX = SelectedMarker->position->key();
        double CurrentY = SelectedMarker->position->value(); // В этой строке даёт неправильное значение -- дальше меняется

        //double PrevX;
        double PrevY;

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
                    PrevY = SelectedGraph->data()->at(i-1)->value;

                    NextY = SelectedGraph->data()->at(i+1)->value;

                    if (NextY>=CurrentY && PrevY>=CurrentY)
                    {
                        MaxX = CurrentX;
                        break;
                    }
                }
                else
                {
                    if (SelectedMarker->position->value()>=CurrentY)
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



        double MaxY = 0;

        QCPGraph * MarkerGraph = SelectedMarker->graph();

        for (int i=0; i < MarkerGraph->data()->size(); i++)
        {
            if (MarkerGraph->data()->at(i)->key == MaxX)
            {
                MaxY = MarkerGraph->data()->at(i)->value;
            }
        }

        //MaxY = MarkerGraph->data()->at(MarkerIndex)->value;

        //MarkerPositionsTable->item(2,1)->setText(QString::number(MaxX));
        //MarkerPositionsTable->item(2,2)->setText(QString::number(MaxY));
        /*
        int SelectedMarkerRow = -1;
        for (int row = 0; row < this->MarkerPositionsTable->rowCount(); row++)
        {
            if (this->MarkerPositionsTable->item(row, 0)->background().color() == HighlightColor)
            {
                SelectedMarkerRow = row;
                break;
            }
        }
        */

        QTableWidgetItem * MaxXItem = new QTableWidgetItem(QString::number(MaxX));
        QTableWidgetItem * MaxYItem = new QTableWidgetItem(QString::number(MaxY));

        MaxXItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        MaxYItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

        //MarkerPositionsTable->setItem(SelectedMarkerRow, 2, MaxXItem);
        //MarkerPositionsTable->setItem(SelectedMarkerRow, 3, MaxYItem);

        //MarkerPositionsTable->item(SelectedMarkerRow,2)->setBackground(HighlightColor);
        //MarkerPositionsTable->item(SelectedMarkerRow,3)->setBackground(HighlightColor);

        customPlot->replot();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Предупреждение!");
        msgBox.setText("Число выделенных маркеров не равно одному");
        msgBox.setInformativeText("Убедитесь, что вы выделили маркер");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
}

void WidgetForCustomPlot::OnMarkerLeftMinClicked()
{
    if (this->customPlot->selectedItems().size() == 1)
    {
        QCPItemTracer * SelectedMarker = qobject_cast <QCPItemTracer*> (this->customPlot->selectedItems().last());


        double CurrentX = SelectedMarker->position->key();
        double CurrentY = SelectedMarker->position->value();

        double PrevY;

        double NextY;

        double MaxX = CurrentX;

        QCPGraph * SelectedGraph = SelectedMarker->graph();

        for (int i = SelectedGraph->data()->size()-1; i >= 0 ; i--)
        {
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

                    if (NextY>=CurrentY && PrevY>=CurrentY)
                    {

                        MaxX = CurrentX;
                        break;
                    }
                }
                else
                {
                    if (SelectedMarker->position->value()>=CurrentY)
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

        int SelectedMarkerRow = -1;

        /*
        for (int row = 0; row < this->MarkerPositionsTable->rowCount(); row++)
        {
            if (MarkerPositionsTable->item(row, 0)->background().color() == HighlightColor)
            {
                SelectedMarkerRow = row;
                break;
            }
        }
        */

        double MaxY = 0;

        qDebug()<<"Меняется строка: "<< SelectedMarkerRow;
        QCPGraph * MarkerGraph = SelectedMarker->graph();

        for (int i=0; i < MarkerGraph->data()->size(); i++) // Можно сделать поиск быстрее, учитывая вид x
        {
            if (MarkerGraph->data()->at(i)->key == MaxX)
            {
                MaxY = MarkerGraph->data()->at(i)->value;
            }
        }

        //MaxY = MarkerGraph->data()->at(MarkerIndex)->value;

        //MarkerPositionsTable->item(2,1)->setText(QString::number(MaxX));
        //MarkerPositionsTable->item(2,2)->setText(QString::number(MaxY));

        QTableWidgetItem * MaxXItem = new QTableWidgetItem(QString::number(MaxX));
        QTableWidgetItem * MaxYItem = new QTableWidgetItem(QString::number(MaxY));

        MaxXItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        MaxYItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

        //MarkerPositionsTable->setItem(SelectedMarkerRow, 2, MaxXItem);
        //MarkerPositionsTable->setItem(SelectedMarkerRow, 3, MaxYItem);

        //qDebug()<<MarkerPositionsTable->item(0,0)->background();

        //MarkerPositionsTable->item(SelectedMarkerRow,2)->setBackground(HighlightColor);
        //MarkerPositionsTable->item(SelectedMarkerRow,3)->setBackground(HighlightColor);
        //QTableWidgetItem* item2 = MarkerPositionsTable->item(SelectedMarkerRow, 2);
        //QTableWidgetItem* item3 = MarkerPositionsTable->item(SelectedMarkerRow, 3);

        /*
        if (item2) {
            item2->setBackground(HighlightColor);
        } else {
            qDebug() << "Item at (SelectedMarkerRow, 2) is null.";
        }

        if (item3) {
            item3->setBackground(HighlightColor);
        } else {
            qDebug() << "Item at (SelectedMarkerRow, 3) is null.";
        }
        */


        customPlot->replot();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Предупреждение!");
        msgBox.setText("Число выделенных маркеров не равно одному");
        msgBox.setInformativeText("Убедитесь, что вы выделили маркер");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
}

void WidgetForCustomPlot::OnMarkerLocalMaxClicked()
{
    EnterSelectLocalMaxMode();
}

void WidgetForCustomPlot::OnMinusRightClicked()
{
    //???
}

void WidgetForCustomPlot::OnMinusLeftClicked()
{
    //???
}

void WidgetForCustomPlot::OnMarkerAddClicked()
{

    if (!this->customPlot->graph(0)->data()->isEmpty())
    {
        customPlot->markeraddbuttonactive = MarkerAddButton->isChecked();
        customPlot->markerdeletebuttonactive = false;
        MarkerDeleteButton->setChecked(false);
        customPlot->MouseMoveMarker->setVisible(customPlot->markeraddbuttonactive);
        customPlot->MouseMoveLabel->setVisible(customPlot->markeraddbuttonactive);
        customPlot->replot();
    }
    else
    {
        MarkerAddButton->setChecked(false);
        MarkerDeleteButton->setChecked(false);

        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Предупреждение!");
        msgBox.setText("График не найден");
        msgBox.setInformativeText("Прежде чем ставить маркер добавьте график");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
}

void WidgetForCustomPlot::OnMarkerGraphClicked()
{
    if (MarkerGraphButton->isChecked())
    {

        customPlot->setInteractions(QCP::iRangeZoom | QCP::iRangeDrag | QCP::iSelectPlottables);

        QCPDataSelection selection;
        selection.addDataRange(customPlot->graph(customPlot->SelectedGraph)->data()->dataRange());
        customPlot->graph(customPlot->SelectedGraph)->setSelection(selection);
        customPlot->replot();
        QVector <QCPGraph*> GV = customPlot->yAxis->graphs();
        if (GV.size()>0)
        {
            for (int i=0; i<GV.size(); i++)
            {
                GV[i]->setSelectable(QCP::SelectionType::stWhole);
            }
        }
    }
    else
    {
        customPlot->setInteractions(QCP::iRangeZoom | QCP::iRangeDrag | QCP::iSelectItems);
        for (int i = 0; i < customPlot->graphCount(); ++i)
        {
            customPlot->graph(i)->setSelection(QCPDataSelection());
        }
        customPlot->replot();
    }

    //qDebug()<<"SG = " << customPlot->SelectedGraph;
}

void WidgetForCustomPlot::OnMarkerIncreaseNClicked()
{

}

void WidgetForCustomPlot::OnMarkerPrintClicked()
{

}

void WidgetForCustomPlot::OnMarkerIncreaseClicked()
{

}

void WidgetForCustomPlot::OnMarkerUnlockYClicked()
{
//??
}

void WidgetForCustomPlot::OnMarkerUnlockXClicked()
{
//??
}

void WidgetForCustomPlot::OnMarkerDeleteClicked()
{
    DeleteMarkerSlot();
}

void WidgetForCustomPlot::OnMarkerUpClicked()
{
   //??
}

void WidgetForCustomPlot::OnMarkerDownClicked()
{
//??
}





void WidgetForCustomPlot::ShowContextMenu(const QPoint &pos)
{
    contextMenu->exec(mapToGlobal(pos));
}



void WidgetForCustomPlot::OnDisableScalePanel()
{
    if (DisableScalePanelAction->isChecked())
    {
        ControlsWidget->hide();
    }
    else
    {
        ControlsWidget->show();
    }
}

void WidgetForCustomPlot::OnPolarFormat()
{
    if (PolarFormatAction->isChecked())
    {
        customPlot->ChangeToPolarFormat();
        qDebug()<< "Polar format initiated";

        //customPlot->PolarGraph->setVisible(true);
        //customPlot->PolarGraph->setData(customPlot->graph(0)->data());
        //customPlot->addLayer("Polar");

    }
    else
    {
        customPlot->ChangeToDescartesFormat();
        qDebug()<< "Polar format disabled";


        //customPlot->PolarGraph->setVisible(false);
        //customPlot->PolarFormat(false);
    }
}



void WidgetForCustomPlot::OnAmplitude()
{

}

void WidgetForCustomPlot::OnPhase()
{

}

void WidgetForCustomPlot::OnRealPart()
{

}

void WidgetForCustomPlot::OnImagPart()
{

}

void WidgetForCustomPlot::OnLegendInside()
{

}

void WidgetForCustomPlot::OnDisableLegend()
{

}




void WidgetForCustomPlot::UpdateText()
{

}































































































// Устаревшие функции

/*
void WidgetForCustomPlot::InitiateMovementGroupBox()
{
    MovementGroupBox = new QGroupBox("Положение графика");
    MovementGroupBox->setFixedWidth(260);
    MovementGroupBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    MovementGroupBoxLayout = new QVBoxLayout(MovementGroupBox);
    LockAxesLayout = new QHBoxLayout;

    RubberBandButton = new QPushButton("⬚");
    RubberBandButton->setCheckable(true);
    connect(RubberBandButton, &QPushButton::clicked,this,&WidgetForCustomPlot::ActivateRubberBand);
    RubberBandButton->setToolTip("Масштабирование выделением области");

    LockXAxisButton = new QPushButton("⇕");
    LockXAxisButton->setToolTip("Зафиксировать масштаб по оси X");
    connect(LockXAxisButton, &QPushButton::clicked,this,&WidgetForCustomPlot::LockXAxis);
    LockXAxisButton->setCheckable(true);

    LockYAxisButton = new QPushButton("⇔");
    LockXAxisButton->setToolTip("Зафиксировать масштаб по оси Y");
    connect(LockYAxisButton, &QPushButton::clicked,this,&WidgetForCustomPlot::LockYAxis);
    LockYAxisButton->setCheckable(true);

    ResetButton = new QPushButton("↻");
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
*/



/*
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
*/
/*
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
    connect(MarkerAddButton, &QPushButton::clicked, this, &WidgetForCustomPlot::AddMarkerSlot);
    MarkerAddButton->setToolTip("Добавить маркеры на выбранный график");


    MarkerDeleteButton = new QPushButton("-");
    MarkerDeleteButton->setCheckable(true);

    connect(MarkerDeleteButton, &QPushButton::clicked, this, &WidgetForCustomPlot::DeleteMarkerSlot);
    MarkerDeleteButton->setToolTip("Удалить маркер");


    SelectLocalMarkerLayout = new QHBoxLayout();

    SelectLocalMaxButton = new QPushButton("max", this); // Установка маркера в случае если в выделенной области нет точек?
    SelectLocalMaxButton->setCheckable(true);
    connect(SelectLocalMaxButton,&QPushButton::clicked, this, &WidgetForCustomPlot::EnterSelectLocalMaxMode);
    SelectLocalMaxButton->setToolTip("Установить маркер в максимум на выделенной области");

    SelectLocalMinButton = new QPushButton("min", this);
    SelectLocalMinButton->setCheckable(true);
    connect(SelectLocalMinButton,&QPushButton::clicked, this, &WidgetForCustomPlot::EnterSelectLocalMinMode);
    SelectLocalMinButton->setToolTip("Установить маркер в минимум на выделенной области");


    DeleteAllMarkersButton = new QPushButton("✖");
    connect(DeleteAllMarkersButton, &QPushButton::clicked, customPlot, &PlotClass::DeleteAllMarkers);
    DeleteAllMarkersButton->setToolTip("Удалить все маркеры");


    QPushButton * MoveSelectedMarkerToNextMaxButton = new QPushButton("🡆∧",this);         //("➡🡆∧",this)
    connect(MoveSelectedMarkerToNextMaxButton, &QPushButton::clicked, this, &WidgetForCustomPlot::ToNextMax);
    MoveSelectedMarkerToNextMaxButton->setToolTip("Переместить маркер на следующий максимум");

    QPushButton * MoveSelectedMarkerToPrevMaxButton = new QPushButton("∧🡄",this);         //("∧🡄⬅",this);
    connect(MoveSelectedMarkerToPrevMaxButton, &QPushButton::clicked, this, &WidgetForCustomPlot::ToPrevMax);
    MoveSelectedMarkerToPrevMaxButton->setToolTip("Переместить маркер на предыдущий максимум");

    VerticalMarkerStyleConfigurationLayout = new QVBoxLayout();

    GraphChoiceComboBox = new QComboBox(MarkerGroupBox);

    GraphChoiceComboBox->addItem("График 1");
    //GraphChoiceComboBox->addItem("График 2"); // Нужно добавление неограниченного числа графиков

    connect(GraphChoiceComboBox, &QComboBox::currentIndexChanged,customPlot,&PlotClass::ChangeSelectedGraph);

    MarkerStyleLayout->addWidget(MarkerPreviewPlot);
    MarkerStyleLayout->addLayout(VerticalMarkerStyleConfigurationLayout);
    VerticalMarkerStyleConfigurationLayout->addWidget(MarkerColourButton);
    VerticalMarkerStyleConfigurationLayout->addWidget(MarkerStyleComboBox);


    QVBoxLayout * VerticalPMLayout = new QVBoxLayout();
    QHBoxLayout * HorizontalPMLayout = new QHBoxLayout();

    VerticalPMLayout->addWidget(GraphChoiceComboBox);

    MarkerStyleLayout->addLayout(VerticalPMLayout);

    HorizontalPMLayout->addWidget(MarkerAddButton);
    HorizontalPMLayout->addWidget(MarkerDeleteButton);

    VerticalPMLayout->addLayout(HorizontalPMLayout);



    MarkerGroupBoxLayout->addLayout(MarkerStyleLayout);

    MarkerAddDeleteLayout->addWidget(SelectLocalMaxButton);
    MarkerAddDeleteLayout->addWidget(SelectLocalMinButton);
    MarkerAddDeleteLayout->addWidget(DeleteAllMarkersButton);



    //SelectLocalMarkerLayout->addWidget(SelectLocalMaxButton);
    //SelectLocalMarkerLayout->addWidget(SelectLocalMinButton);
    //MarkerGroupBoxLayout->addLayout(SelectLocalMarkerLayout);

    //MarkerGroupBoxLayout->addWidget(DeleteAllMarkersButton);

    //QHBoxLayout * MoveMarkerLeftOrRightHorizontalLayout = new QHBoxLayout();
    //MarkerGroupBoxLayout->addLayout(MoveMarkerLeftOrRightHorizontalLayout);
    MarkerAddDeleteLayout->addWidget(MoveSelectedMarkerToPrevMaxButton);
    MarkerAddDeleteLayout->addWidget(MoveSelectedMarkerToNextMaxButton);



    MarkerGroupBoxLayout->addLayout(MarkerAddDeleteLayout);

    MarkerPositionsTable = new QTableWidget(MarkerGroupBox);
    MarkerPositionsTable->setFixedHeight(100);
    MarkerPositionsTable->setStyleSheet("QTableWidget { background-color: white; }");
    //qDebug()<<MarkerPositionsTable->item(0,0)->background();

    MarkerPositionsTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    MarkerPositionsTable->setColumnCount(4);
    MarkerPositionsTable->setHorizontalHeaderLabels({"Gr", "N", "x", "y"});
    //MarkerPositionsTable->horizontalHeader()->setStretchLastSection(true);

    //int ColumnWidth = 60; //(this->MarkerGroupBox->width()-20)/4;
    //qDebug()<< MarkerPositionsTable->viewport()->width() << "-- Ширина окна таблицы" << this->MarkerGroupBox->width()<<" --Ширина всего окна";

    MarkerPositionsTable->setColumnWidth(0, 40);
    MarkerPositionsTable->setColumnWidth(1, 40);
    MarkerPositionsTable->setColumnWidth(2, 80);
    MarkerPositionsTable->setColumnWidth(3, 80);


    MarkerPositionsTable->verticalHeader()->setVisible(false);

    //for (int i = 0; i < 3; i++)    {MarkerPositionsTable->resizeColumnToContents(i);}

    MarkerGroupBoxLayout->addWidget(MarkerPositionsTable);

    connect(MarkerPositionsTable, &QTableWidget::cellChanged, this, &WidgetForCustomPlot::AdjustContentsOfTableOfDifference);



    MarkerDifferenceTable = new QTableWidget(this);

    MarkerDifferenceTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    MarkerDifferenceTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    MarkerDifferenceTable->setFixedHeight(60);
    MarkerDifferenceTable->setColumnCount(4);
    MarkerDifferenceTable->setRowCount(2);
    MarkerDifferenceTable->setHorizontalHeaderLabels({ "ΔGr", "ΔN", "Δx", "Δy"});
    MarkerDifferenceTable->resizeColumnsToContents();
    //int ColumnWidth2 = MarkerDifferenceTable->width()/3;

    MarkerDifferenceTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    MarkerDifferenceTable->setColumnWidth(0, 40);
    MarkerDifferenceTable->setColumnWidth(1, 40);
    MarkerDifferenceTable->setColumnWidth(2, 80);
    MarkerDifferenceTable->setColumnWidth(3, 80);

    MarkerDifferenceTable->verticalHeader()->setVisible(false);
    MarkerGroupBoxLayout->addWidget(MarkerDifferenceTable);
}
*/
/*
void WidgetForCustomPlot::InitiateSaveLayout()
{
    HorizontalSaveLayout = new QHBoxLayout;

    //SaveButton = new QPushButton("Сохранить",this);
    //connect(SaveButton, &QPushButton::clicked, customPlot, &PlotClass::SaveAs);

    //QPushButton * SaveAsDatButton = new QPushButton(".dat", this);
    ////connect(SaveAsDatButton, &QPushButton::clicked, this, &WidgetForCustomPlot::SavePlotAsDat);


    //CopyButton = new QPushButton("Копировать");
    //connect(CopyButton, &QPushButton::clicked, customPlot, &PlotClass::CopyPlot);

    //HorizontalSaveLayout->addWidget(SaveButton);
    //HorizontalSaveLayout->addWidget(CopyButton);
    //HorizontalSaveLayout->addWidget(SaveAsDatButton);
}
*/
/*
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
*/
/*
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
    SetRangeGroupBox->setFixedSize(240, 90);
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
    YRangeUnitsLabel = new QLabel("dB",this);

    XRangeEditFrom->setValidator(DoubleValidator);
    XRangeEditTo->setValidator(DoubleValidator);
    YRangeEditFrom->setValidator(DoubleValidator);
    YRangeEditTo->setValidator(DoubleValidator);


    connect(XRangeEditFrom, &QLineEdit::editingFinished,this, &WidgetForCustomPlot::SetRange);
    connect(XRangeEditTo  , &QLineEdit::editingFinished,this, &WidgetForCustomPlot::SetRange);
    connect(YRangeEditFrom, &QLineEdit::editingFinished,this, &WidgetForCustomPlot::SetRange);
    connect(YRangeEditTo  , &QLineEdit::editingFinished,this, &WidgetForCustomPlot::SetRange);



    SetRangeButton = new QPushButton("Установить");
    //connect(SetRangeButton, &QPushButton::clicked, this,[this]()
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
    //SetRangeVerticalLayout->addWidget(SetRangeButton);

    SetRangeGroupBox->setLayout(SetRangeVerticalLayout);
}
*/




/*
void WidgetForCustomPlot::EnterSelectLocalMinMode()
{
    int GraphID = GraphChoiceComboBox->currentIndex();
    if (SelectLocalMinButton->isChecked())
    {
        if (!customPlot->graph(GraphID)->data()->isEmpty())
        {
            this->RubberBandButton->setChecked(false);
            this->SelectLocalMaxButton->setChecked(false);
            customPlot->setInteractions(QCP::iSelectPlottables| QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectItems);
            customPlot->setSelectionRectMode(QCP::srmSelect);
            customPlot->graph(GraphID)->setSelectable(QCP::stDataRange);
               connect(customPlot, SIGNAL(selectionChangedByUser()), this, SLOT(PutMarkerAtLocalMin()));
            disconnect(customPlot, SIGNAL(selectionChangedByUser()), this, SLOT(PutMarkerAtLocalMax()));
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
        disconnect(customPlot, SIGNAL(selectionChangedByUser()), this, SLOT(PutMarkerAtLocalMin()));
    }
}
*/

/*
void WidgetForCustomPlot::PutMarkerAtLocalMin()
{
    //int GraphID = GraphChoiceComboBox->currentIndex(); // Из легенды!!!
    int GraphID = 0;
    if (customPlot->graph(GraphID)->selection().isEmpty())
    {
        qDebug()<<"No data selected";
        for (int i=0;i<customPlot->graphCount();i++)
        {
            customPlot->graph(i)->setSelection(QCPDataSelection());
        }
        return;
    }
    else
    {
        QCPDataSelection SelectedData = customPlot->graph(GraphID)->selection();
        SelectedData.enforceType(QCP::stDataRange);
        QCPDataRange DataRange = SelectedData.dataRange();
        if (DataRange.size() > 0)
        {
            double MinValue = this->customPlot->graph(GraphID)->data()->at(DataRange.begin())->value;
            double MinKey   = this->customPlot->graph(GraphID)->data()->at(DataRange.begin())->key;
            for (int i = DataRange.begin(); i < DataRange.end(); i++)
            {
                double CurrentValue = this->customPlot->graph(GraphID)->data()->at(i)->value;
                if (MinValue > CurrentValue)
                {
                    MinKey = this->customPlot->graph(GraphID)->data()->at(i)->key;
                    MinValue = CurrentValue;
                }
            }
            customPlot->AddNewMarker(MinKey,customPlot->MarkerStyle, customPlot->MarkerColour, customPlot->SelectedGraph);
        }
        else if (DataRange.size() == 0)
        {
            return;
        }

        customPlot->graph(GraphID)->setSelection(QCPDataSelection());
    }
}
*/




/*
void WidgetForCustomPlot::AdjustContentsOfTableOfDifference(int row, int column)
{

    if (this->MarkerPositionsTable->item(1,3))
    {
        //qDebug()<<"Start";

        //qDebug()<<"rowcount()>=2" << MarkerPositionsTable->rowCount();

        QString G0   = MarkerPositionsTable->item(0,0)->text();
        QString G1   = MarkerPositionsTable->item(1,0)->text();
        //qDebug()<<"1" << "G0";
        QString Num0 = MarkerPositionsTable->item(0,1)->text();
        //qDebug()<<"1.5";
        QString Num1 = MarkerPositionsTable->item(1,1)->text();
        //qDebug()<<"2";
        QString x0   = MarkerPositionsTable->item(0,2)->text();
        QString x1   = MarkerPositionsTable->item(1,2)->text();
        //qDebug()<<"3";
        QString y0   = MarkerPositionsTable->item(0,3)->text();
        QString y1   = MarkerPositionsTable->item(1,3)->text();

        //qDebug()<< "ok1" << G0 << G1 << Num0 << Num1 << x0 << x1 << y0 << y1;

        QString DeltaG = G1 + "-" + G0;
        QString DeltaN = Num1 + "-" + Num0;
        QString DeltaX = QString::number ( x1.toDouble() - x0.toDouble() );
        QString DeltaY = QString::number ( y1.toDouble() - y0.toDouble() );

        //qDebug()<< "ok2" <<DeltaG<<DeltaN<<DeltaX<<DeltaY;

        QTableWidgetItem * DeltaGItem  = new QTableWidgetItem(DeltaG);
        QTableWidgetItem * DeltaNItem  = new QTableWidgetItem(DeltaN);
        QTableWidgetItem * DeltaXItem  = new QTableWidgetItem(DeltaX);
        QTableWidgetItem * DeltaYItem  = new QTableWidgetItem(DeltaY);

        DeltaGItem ->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        DeltaNItem ->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        DeltaXItem ->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        DeltaYItem ->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

        MarkerDifferenceTable->setItem(0, 0, DeltaGItem );
        MarkerDifferenceTable->setItem(0, 1, DeltaNItem );
        MarkerDifferenceTable->setItem(0, 2, DeltaXItem );
        MarkerDifferenceTable->setItem(0, 3, DeltaYItem );

        //qDebug()<<"Success";


    }
    else
    {
        //qDebug()<<"ok6";


        qDebug()<<"ok6";
        MarkerDifferenceTable->setItem(0, 0, new QTableWidgetItem(""));
        MarkerDifferenceTable->setItem(0, 1, new QTableWidgetItem(""));
        MarkerDifferenceTable->setItem(0, 2, new QTableWidgetItem(""));
        MarkerDifferenceTable->setItem(0, 3, new QTableWidgetItem(""));
        qDebug()<<"ok7";

    }
}
*/

// Из старого конструктора
// Не используется больше (теперь как в старой программе)
//InitiateMovementGroupBox();
//VerticalControlsLayout->addWidget(MovementGroupBox);
//InitiateMarkerGroupBox();
//VerticalControlsLayout->addWidget(MarkerGroupBox);
//InitiateSaveLayout();
//VerticalControlsLayout->addLayout(HorizontalSaveLayout);
//------------------------------------------------------

