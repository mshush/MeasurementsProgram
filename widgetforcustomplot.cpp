#include "widgetforcustomplot.h"

WidgetForCustomPlot::WidgetForCustomPlot(QWidget *parent)
    : QWidget{parent}
{

    this->resize(600,200);
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    HorizontalPlotLayout = new QHBoxLayout(this);

    VerticalControlsLayout = new QVBoxLayout;
    //VerticalControlsLayout->setAlignment(Qt::AlignLeft);

    customPlot = new PlotClass(this);
    customPlot->resize(600,400);
    customPlot->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    ControlsWidget = new QWidget(this);
    //ControlsWidget->setFixedSize(260,500);
    //ControlsWidget->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    ControlsWidget->setLayout(VerticalControlsLayout);
    //qDebug()<<"Размер="<<ControlsWidget->size();


    InitiateMovementGroupBox();
    VerticalControlsLayout->addWidget(MovementGroupBox);

    InitiateMarkerGroupBox();
    VerticalControlsLayout->addWidget(MarkerGroupBox);

    InitiateSaveLayout();
    VerticalControlsLayout->addLayout(HorizontalSaveLayout);

    QPushButton * FourierButton = new QPushButton("F");
    connect(FourierButton, &QPushButton::clicked, this->customPlot, &PlotClass::FourierTransform);
    VerticalControlsLayout->addWidget(FourierButton);

    QPushButton * InverseFourierButton = new QPushButton("InvF");
    connect(InverseFourierButton, &QPushButton::clicked, this->customPlot, &PlotClass::InverseFourierTransform);
    VerticalControlsLayout->addWidget(InverseFourierButton);

    HorizontalPlotLayout->addWidget(customPlot);
    HorizontalPlotLayout->addWidget(ControlsWidget);



    //connect(customPlot->xAxis, &QCPAxis::rangeChanged, this, &WidgetForCustomPlot::XAxisRangeChanged);
    //connect(customPlot->yAxis, &QCPAxis::rangeChanged, this, &WidgetForCustomPlot::YAxisRangeChanged);

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




void WidgetForCustomPlot::ChangeMarkerStyle(int ComboIndex) // Почему выдаёт не то до первого изменения
{
    this->customPlot->MarkerStyle = ComboIndex+1;
    this->PreviewMarker->setStyle(QCPItemTracer::TracerStyle(ComboIndex+1));
    this->MarkerPreviewPlot->replot();
}

void WidgetForCustomPlot::ActivateRubberBand()
{
    if (this->RubberBandButton->isChecked())
    {
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
    }
    else
    {
        customPlot->axisRect()->setRangeZoom(Qt::Horizontal | Qt::Vertical);
        customPlot->axisRect()->setRangeZoomAxes(customPlot->xAxis, customPlot->yAxis);
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
    }
    else
    {
        customPlot->axisRect()->setRangeZoom(Qt::Horizontal | Qt::Vertical);
        customPlot->axisRect()->setRangeZoomAxes(customPlot->xAxis, customPlot->yAxis);
    }
}


void WidgetForCustomPlot::InitiateMovementGroupBox()
{


    MovementGroupBox = new QGroupBox("Движение");
    MovementGroupBox->setFixedSize(250,250);
    MovementGroupBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    MovementGroupBoxLayout = new QVBoxLayout(MovementGroupBox);
    LockAxesLayout = new QHBoxLayout;

    RubberBandButton = new QPushButton("Выделить");
    RubberBandButton->setCheckable(true);
    connect(RubberBandButton, &QPushButton::clicked,this,&WidgetForCustomPlot::ActivateRubberBand);

    LockXAxisButton = new QPushButton("Блок X");
    connect(LockXAxisButton, &QPushButton::clicked,this,&WidgetForCustomPlot::LockXAxis);
    LockXAxisButton->setCheckable(true);

    LockYAxisButton = new QPushButton("Блок Y");
    connect(LockYAxisButton, &QPushButton::clicked,this,&WidgetForCustomPlot::LockYAxis);
    LockYAxisButton->setCheckable(true);

    ResetButton = new QPushButton("Вернуть");
    connect(ResetButton, &QPushButton::clicked, customPlot, &PlotClass::ResetPlot);

    InitiateSetRangeGroupBox();

    MovementGroupBoxLayout->addWidget(RubberBandButton);

    LockAxesLayout->addWidget(LockXAxisButton);
    LockAxesLayout->addWidget(LockYAxisButton);
    MovementGroupBoxLayout->addLayout(LockAxesLayout);

    MovementGroupBoxLayout->addWidget(ResetButton);


    MovementGroupBoxLayout->addWidget(SetRangeGroupBox);
}




void WidgetForCustomPlot::InitiateMarkerGroupBox()
{

    MarkerGroupBox = new QGroupBox("Маркеры");
    MarkerGroupBox->setFixedSize(250,200);
    MarkerGroupBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
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

    InitiateMarkerPreviewPlot();

    MarkerAddButton = new QPushButton("Добавить");
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
                customPlot->MouseMoveMarker->setVisible(customPlot->markeraddbuttonactive);
                customPlot->MouseMoveLabel->setVisible(customPlot->markeraddbuttonactive);
                customPlot->replot();
            }
            );

    DeleteAllMarkersButton = new QPushButton("Убрать все");
    connect(DeleteAllMarkersButton, &QPushButton::clicked, customPlot, &PlotClass::DeleteAllMarkers);


    MarkerStyleLayout->addWidget(MarkerPreviewPlot);
    MarkerStyleLayout->addWidget(MarkerColourButton);
    MarkerStyleLayout->addWidget(MarkerStyleComboBox);
    MarkerGroupBoxLayout->addLayout(MarkerStyleLayout);

    MarkerAddDeleteLayout->addWidget(MarkerAddButton);
    MarkerAddDeleteLayout->addWidget(MarkerDeleteButton);
    MarkerGroupBoxLayout->addLayout(MarkerAddDeleteLayout);

    MarkerGroupBoxLayout->addWidget(DeleteAllMarkersButton);

}


void WidgetForCustomPlot::InitiateSaveLayout()
{
    HorizontalSaveLayout = new QHBoxLayout;

    SaveButton = new QPushButton("Сохранить");
    connect(SaveButton, &QPushButton::clicked, customPlot, &PlotClass::SavePlot);

    CopyButton = new QPushButton("Копировать");
    connect(CopyButton, &QPushButton::clicked, customPlot, &PlotClass::CopyPlot);

    HorizontalSaveLayout->addWidget(SaveButton);
    HorizontalSaveLayout->addWidget(CopyButton);
}



void WidgetForCustomPlot::InitiateMarkerPreviewPlot()
{
    MarkerPreviewPlot = new QCustomPlot;

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

    SetRangeGroupBox = new QGroupBox("Установка вручную");
    SetRangeGroupBox->setFixedSize(230,120);
    SetRangeGroupBox->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    SetRangeVerticalLayout = new QVBoxLayout;
    SetRangeLayout = new QGridLayout;
    XRangeLabel1 = new QLabel("X от");
    XRangeEditFrom = new QLineEdit(XLower);
    XRangeLabel2 = new QLabel("до");
    XRangeEditTo = new QLineEdit(XUpper);
    XRangeComboBox = new QComboBox;
    XRangeComboBox->addItem("ГГц");

    YRangeLabel1 = new QLabel("Y от");
    YRangeEditFrom = new QLineEdit(YLower);
    YRangeLabel2 = new QLabel("до");
    YRangeEditTo = new QLineEdit(YUpper);
    YRangeComboBox = new QComboBox;
    YRangeComboBox->addItem("Вт");

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




    SetRangeLayout->addWidget(XRangeLabel1,  0,0);
    SetRangeLayout->addWidget(XRangeEditFrom,0,1);
    SetRangeLayout->addWidget(XRangeLabel2,  0,2);
    SetRangeLayout->addWidget(XRangeEditTo,  0,3);
    SetRangeLayout->addWidget(XRangeComboBox,0,4);

    SetRangeLayout->addWidget(YRangeLabel1,  1,0);
    SetRangeLayout->addWidget(YRangeEditFrom,1,1);
    SetRangeLayout->addWidget(YRangeLabel2,  1,2);
    SetRangeLayout->addWidget(YRangeEditTo,  1,3);
    SetRangeLayout->addWidget(YRangeComboBox,1,4);


    SetRangeVerticalLayout->addLayout(SetRangeLayout);
    SetRangeVerticalLayout->addWidget(SetRangeButton);

    SetRangeGroupBox->setLayout(SetRangeVerticalLayout);
}




void WidgetForCustomPlot::XAxisRangeChanged(QCPRange range)
{
    //double XMin = customPlot->xAxis->range().lower;
    //double XMax = customPlot->xAxis->range().upper;


    this->XRangeEditFrom->setText(QString::number(range.lower));
    this->XRangeEditTo  ->setText(QString::number(range.upper));

}

void WidgetForCustomPlot::YAxisRangeChanged(QCPRange range)
{
    //double YMin = customPlot->xAxis->range().lower;
    //double YMax = customPlot->xAxis->range().upper;

    this->YRangeEditFrom->setText(QString::number(range.lower));
    this->YRangeEditTo  ->setText(QString::number(range.upper));
}




WidgetForCustomPlot::~WidgetForCustomPlot()
{
    /*
    delete customPlot;
    delete ControlsWidget;
    delete HorizontalPlotLayout;
    delete VerticalControlsLayout;
    delete HorizontalSaveLayout;
    delete SaveButton;
    delete CopyButton;
    delete MovementGroupBox;
    delete MovementGroupBoxLayout;
    delete LockAxesLayout;
    delete ResetButton;
    delete RubberBandButton;
    delete LockXAxisButton;
    delete LockYAxisButton;
    delete SetRangeGroupBox;
    delete SetRangeLayout;
    delete XRangeLabel1;
    delete XRangeEditFrom;
    delete XRangeLabel2;
    delete XRangeEditTo;
    delete YRangeLabel1;
    delete YRangeEditFrom;
    delete YRangeLabel2;
    delete YRangeEditTo;
    delete MarkerGroupBox;
    delete MarkerGroupBoxLayout;
    delete MarkerStyleLayout;
    delete MarkerAddDeleteLayout;
    delete MarkerAddButton;
    delete MarkerDeleteButton;
    delete DeleteAllMarkersButton;
    delete MarkerSettingsButton;
    delete MarkerStyleComboBox;
    delete MarkerColourButton;
    delete ColourDialogue;
    delete MarkerPreviewPlot;
    delete PreviewMarker;
    delete XRangeComboBox;
    delete YRangeComboBox;
    */
}


/*
Придумать способ доказать что графическое отображение соответствует табличным данным -- не съезжает, правильно интерполируется

(Взять данные)

Подводные камни? Скачки, какие ещё проблемы, поискать литературу по проблемам с построением графиков.
Убедиться, что qcustomplot правильно строит, какая там интерполяция, ничего ли он не пропускает.
*/

