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


    InitiateMovementGroupBox();
    HorizontalControlsLayout->addWidget(MovementGroupBox);

    InitiateMarkerGroupBox();
    HorizontalControlsLayout->addWidget(MarkerGroupBox);


    //Вынести в InitiateSaveGroupBox()---------------------------------------------------
    SaveButton = new QPushButton("Сохранить");
    connect(SaveButton, &QPushButton::clicked, customPlot, &PlotClass::SavePlot);

    CopyButton = new QPushButton("Копировать");
    connect(CopyButton, &QPushButton::clicked, customPlot, &PlotClass::CopyPlot);

    HorizontalControlsLayout->addWidget(SaveButton);
    HorizontalControlsLayout->addWidget(CopyButton);
    //Вынести в InitiateSaveGroupBox()---------------------------------------------------

    VerticalPlotLayout->addWidget(ControlsWidget);
    VerticalPlotLayout->addWidget(customPlot);


    //MarkerSettingsDialogue = new QDialog;
    //MarkerSettingsDialogueButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, MarkerSettingsDialogue);

    //QPushButton * OKDialogueButton = new QPushButton("OK");
    //connect(OKDialogueButton, &QPushButton::clicked, this, &WidgetForCustomPlot::DialogueResultAccepted);


    //connect(MarkerSettingsDialogueButtonBox, &QDialogButtonBox::rejected, MarkerSettingsDialogue, &QDialog::reject);




    //MarkerSettingsDialogueLayout = new QVBoxLayout(MarkerSettingsDialogue);

    //MarkerColourButton = new QPushButton("Цвет");
    //connect(MarkerColourButton, &QPushButton::clicked, this, &WidgetForCustomPlot::OpenMarkerColourDialogue);

    //MarkerSettingsDialogueLayout->addWidget(MarkerColourButton);


    //MarkerSettingsDialogueLayout->addWidget(MarkerColourButton);
    //MarkerSettingsDialogueLayout->addWidget(MarkerStyleComboBox);
    //MarkerSettingsDialogueLayout->addWidget(OKDialogueButton);
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
    this->customPlot->MarkerColour = QColorDialog::getColor(Qt::black, this, "Выберите цвет");
    //MarkerColourChoise = ColourDialogue->getColor(Qt::black, this, "Выберите цвет");
    /*
    if (!MarkerColourChoise.isValid())
    {
        return;
    }
    */
}




void WidgetForCustomPlot::ChangeMarkerStyle(int ComboIndex) // Почему выдаёт не то до первого изменения
{
    this->customPlot->MarkerStyle = ComboIndex+1;
}

/*
void WidgetForCustomPlot::DialogueResultAccepted()
{

    customPlot->MarkerColour = MarkerColourChoise;
    customPlot->MarkerStyle = MarkerStyleChoise + 1;
    //qDebug()<< "Стиль маркера (График) = " << customPlot->MarkerStyle;
    //qDebug()<< "Стиль маркера (График Выбор) = " << MarkerStyleChoice + 1;
    MarkerSettingsDialogue->close();
}
*/

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


    MovementGroupBoxLayout->addWidget(RubberBandButton);

    LockAxesLayout->addWidget(LockXAxisButton);
    LockAxesLayout->addWidget(LockYAxisButton);
    MovementGroupBoxLayout->addLayout(LockAxesLayout);

    MovementGroupBoxLayout->addWidget(ResetButton);
}




void WidgetForCustomPlot::InitiateMarkerGroupBox()
{

    MarkerGroupBox = new QGroupBox("Маркеры");
    MarkerGroupBoxLayout = new QVBoxLayout(MarkerGroupBox);
    MarkerGroupBox->setLayout(MarkerGroupBoxLayout);
    MarkerStyleLayout = new QHBoxLayout;
    MarkerAddDeleteLayout = new QHBoxLayout;

    //ColourDialogue = new QColorDialog;
    MarkerColourButton = new QPushButton("Цвет");
    connect(MarkerColourButton, &QPushButton::clicked, this, &WidgetForCustomPlot::OpenMarkerColourDialogue);

    MarkerStyleComboBox = new QComboBox(this);
    MarkerStyleComboBox->addItem("Плюс");
    MarkerStyleComboBox->addItem("Прицел");
    MarkerStyleComboBox->addItem("Круг");
    MarkerStyleComboBox->addItem("Квадрат");
    MarkerStyleComboBox->setCurrentIndex(0);
    connect(MarkerStyleComboBox, &QComboBox::currentIndexChanged,this,&WidgetForCustomPlot::ChangeMarkerStyle);


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


    MarkerStyleLayout->addWidget(MarkerColourButton);
    MarkerStyleLayout->addWidget(MarkerStyleComboBox);
    MarkerGroupBoxLayout->addLayout(MarkerStyleLayout);

    MarkerAddDeleteLayout->addWidget(MarkerAddButton);
    MarkerAddDeleteLayout->addWidget(MarkerDeleteButton);
    MarkerGroupBoxLayout->addLayout(MarkerAddDeleteLayout);

    MarkerGroupBoxLayout->addWidget(DeleteAllMarkersButton);

}





/*
Придумать способ доказать что графическое отображение соответствует табличным данным -- не съезжает, правильно интерполируется

(Взять данные)

Подводные камни? Скачки, какие ещё проблемы, поискать литературу по проблемам с построением графиков.
Убедиться, что qcustomplot правильно строит, какая там интерполяция, ничего ли он не пропускает.
*/
