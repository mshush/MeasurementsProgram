#include "widgetforcustomplot.h"

WidgetForCustomPlot::WidgetForCustomPlot(QWidget *parent)
    : QWidget{parent}
{


    this->resize(600,200);
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    VerticalPlotLayout = new QVBoxLayout(this);
    HorizontalControlsLayout = new QHBoxLayout;
    HorizontalControlsLayout->setAlignment(Qt::AlignLeft);

    customPlot = new PlotClass(this);
    customPlot->resize(600,200);
    customPlot->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);


    ControlsWidget = new QWidget(this);
    ControlsWidget->resize(200,200);
    ControlsWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ControlsWidget->setLayout(HorizontalControlsLayout);
    ControlsWidget->resize(50,30);
    ControlsWidget->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);


    ResetButton = new QPushButton("Вернуть");
    connect(ResetButton, &QPushButton::clicked, customPlot, &PlotClass::ResetPlot);


    MarkerAddButton = new QPushButton("+"); //Добавить смену значка и цвета где-нибудь в продвинутых опциях. Переместить лямбда-функцию в PlotClass?
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


    MarkerDeleteButton = new QPushButton("-");
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


    DeleteAllMarkersButton = new QPushButton("0");
    connect(DeleteAllMarkersButton, &QPushButton::clicked, customPlot, &PlotClass::DeleteAllMarkers);


    MarkerSettingsButton = new QPushButton("Вид");
    connect(MarkerSettingsButton, &QPushButton::clicked, this, &WidgetForCustomPlot::OpenMarkerSettings);



    SaveButton = new QPushButton("Сохранить");
    connect(SaveButton, &QPushButton::clicked, customPlot, &PlotClass::SavePlot);

    CopyButton = new QPushButton("Копировать");
    connect(CopyButton, &QPushButton::clicked, customPlot, &PlotClass::CopyPlot);


    HorizontalControlsLayout->addWidget(ResetButton);

    MarkerManipulationGroupBox = new QGroupBox("Маркеры");
    MarkerManipulationLayout = new QVBoxLayout(MarkerManipulationGroupBox);
    MarkerManipulationGroupBox->setLayout(MarkerManipulationLayout);
    MarkerStyleLayout = new QHBoxLayout;
    MarkerAddDeleteLayout = new QHBoxLayout;

    MarkerStyleLayout->addWidget(MarkerSettingsButton);

    MarkerAddDeleteLayout->addWidget(MarkerAddButton);
    MarkerAddDeleteLayout->addWidget(MarkerDeleteButton);

    MarkerManipulationLayout->addLayout(MarkerStyleLayout);
    MarkerManipulationLayout->addLayout(MarkerAddDeleteLayout);

    MarkerManipulationLayout->addWidget(DeleteAllMarkersButton);

    HorizontalControlsLayout->addWidget(MarkerManipulationGroupBox);
    HorizontalControlsLayout->addWidget(SaveButton);
    HorizontalControlsLayout->addWidget(CopyButton);


    VerticalPlotLayout->addWidget(ControlsWidget);
    VerticalPlotLayout->addWidget(customPlot);


    RubberBandButton = new QPushButton("Выделить");
    RubberBandButton->setCheckable(true);
    connect(RubberBandButton, &QPushButton::clicked,this,&WidgetForCustomPlot::ActivateRubberBand);

    HorizontalControlsLayout->addWidget(RubberBandButton);


    LockXAxisButton = new QPushButton("Блок X");
    connect(LockXAxisButton, &QPushButton::clicked,this,&WidgetForCustomPlot::LockXAxis);
    LockXAxisButton->setCheckable(true);
    LockYAxisButton = new QPushButton("Блок Y");
    connect(LockYAxisButton, &QPushButton::clicked,this,&WidgetForCustomPlot::LockYAxis);
    LockYAxisButton->setCheckable(true);

    HorizontalControlsLayout->addWidget(LockXAxisButton);
    HorizontalControlsLayout->addWidget(LockYAxisButton);



    MarkerSettingsDialogue = new QDialog;
    //MarkerSettingsDialogueButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, MarkerSettingsDialogue);

    QPushButton * OKDialogueButton = new QPushButton("OK");
    connect(OKDialogueButton, &QPushButton::clicked, this, &WidgetForCustomPlot::DialogueResultAccepted);


    //connect(MarkerSettingsDialogueButtonBox, &QDialogButtonBox::rejected, MarkerSettingsDialogue, &QDialog::reject);




    MarkerSettingsDialogueLayout = new QVBoxLayout(MarkerSettingsDialogue);

    MarkerColourButton = new QPushButton("Цвет");
    connect(MarkerColourButton, &QPushButton::clicked, this, &WidgetForCustomPlot::OpenMarkerColourDialogue);

    MarkerSettingsDialogueLayout->addWidget(MarkerColourButton);
/*
    IndexToMarkerStyle =
        {
        {0, QCPItemTracer::TracerStyle::tsSquare},
        {1, QCPItemTracer::TracerStyle::tsCrosshair},
        {2, QCPItemTracer::TracerStyle::tsPlus},
        {3,QCPItemTracer::TracerStyle::tsCircle},
        };
*/
    MarkerStyleComboBox = new QComboBox(this);
    MarkerStyleComboBox->addItem("Плюс");
    MarkerStyleComboBox->addItem("Прицел");
    MarkerStyleComboBox->addItem("Круг");
    MarkerStyleComboBox->addItem("Квадрат");
    //MarkerStyleComboBox->addItem("Проверка");
    MarkerStyleComboBox->setCurrentIndex(0);
    MarkerStyleChoice = 1;

    connect(MarkerStyleComboBox, &QComboBox::currentIndexChanged,this,&WidgetForCustomPlot::ChangeMarkerStyle);

    MarkerSettingsDialogueLayout->addWidget(MarkerColourButton);
    MarkerSettingsDialogueLayout->addWidget(MarkerStyleComboBox);
    MarkerSettingsDialogueLayout->addWidget(OKDialogueButton);
    //MarkerSettingsDialogueLayout->addWidget(MarkerSettingsDialogueButtonBox);

    //qDebug()<< customPlot->size();


    /*
    ColourDialogue = new QColorDialog;
    ColourDialogue->setModal(true);
    ColourDialogue->setFocus();
    */
}







void WidgetForCustomPlot::OpenMarkerColourDialogue() // Почему не сразу меняется сразу???
{
    MarkerColourChoise = QColorDialog::getColor(Qt::black, this, "Выберите цвет");
    //MarkerColourChoise = ColourDialogue->getColor(Qt::black, this, "Выберите цвет");

    if (!MarkerColourChoise.isValid())
    {
        return;
    }
}

void WidgetForCustomPlot::OpenMarkerSettings() // Лучше наверное вообще без диалога.
{
/*
    if (MarkerSettingsDialogue->exec() == QDialog::Accepted)
    {
        customPlot->MarkerColour = MarkerColourChoise;
        customPlot->MarkerStyle = MarkerStyleChoise + 1;
        qDebug()<< "Стиль маркера = " << customPlot->MarkerStyle;
    }
    else
    {
        MarkerColourChoise = customPlot->MarkerColour;
        MarkerStyleChoise = customPlot->MarkerStyle -1;
        this->MarkerStyleComboBox->setCurrentIndex(MarkerStyleChoise);
    }
*/
    MarkerSettingsDialogue->show();
}



void WidgetForCustomPlot::ChangeMarkerStyle(int ComboIndex) // Почему выдаёт не то до первого изменения
{
    MarkerStyleChoise = ComboIndex;
    //qDebug()<< "Стиль Маркера (КомбоБокс) = " << MarkerStyleChoice + 1;
    //MarkerStyleChoise = QCPItemTracer::TracerStyle(index);
    //if ()
    //MarkerStyleChoise =IndexToMarkerStyle[MarkerStyleComboBox->currentIndex()];
    //qDebug()<< MarkerStyleChoise;
}

void WidgetForCustomPlot::DialogueResultAccepted()
{

    customPlot->MarkerColour = MarkerColourChoise;
    customPlot->MarkerStyle = MarkerStyleChoise + 1;
    //qDebug()<< "Стиль маркера (График) = " << customPlot->MarkerStyle;
    //qDebug()<< "Стиль маркера (График Выбор) = " << MarkerStyleChoice + 1;
    MarkerSettingsDialogue->close();
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



/*
Придумать способ доказать что графическое отображение соответствует табличным данным -- не съезжает, правильно интерполируется

(Взять данные)

Подводные камни? Скачки, какие ещё проблемы, поискать литературу по проблемам с построением графиков.
Убедиться, что qcustomplot правильно строит, какая там интерполяция, ничего ли он не пропускает.
*/
