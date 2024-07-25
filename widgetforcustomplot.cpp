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


    VerticalPlotLayout->addWidget(ControlsWidget);
    VerticalPlotLayout->addWidget(customPlot);



    MarkerSettingsDialogue = new QDialog(this);
    MarkerSettingsDialogueButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, MarkerSettingsDialogue);

    connect(MarkerSettingsDialogueButtonBox, &QDialogButtonBox::accepted, MarkerSettingsDialogue, &QDialog::accept);
    connect(MarkerSettingsDialogueButtonBox, &QDialogButtonBox::rejected, MarkerSettingsDialogue, &QDialog::reject);



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
    MarkerStyleComboBox->addItem("Квадрат");
    MarkerStyleComboBox->addItem("Крест");
    MarkerStyleComboBox->addItem("Крестик");
    MarkerStyleComboBox->addItem("Круг");
    connect(MarkerStyleComboBox, &QComboBox::currentIndexChanged,this,&WidgetForCustomPlot::ChangeMarkerStyle);

    MarkerSettingsDialogueLayout->addWidget(MarkerColourButton);
    MarkerSettingsDialogueLayout->addWidget(MarkerStyleComboBox);
    MarkerSettingsDialogueLayout->addWidget(MarkerSettingsDialogueButtonBox);




    //qDebug()<< customPlot->size();

}







void WidgetForCustomPlot::OpenMarkerColourDialogue()
{
    MarkerColourChoise = QColorDialog::getColor(Qt::black, this, "Select Marker Color");
    if (!MarkerColourChoise.isValid())
    {
        return;
    }
}

void WidgetForCustomPlot::OpenMarkerSettings()
{

    if (MarkerSettingsDialogue->exec() == QDialog::Accepted)
    {
        customPlot->MarkerColour = MarkerColourChoise;
        customPlot->MarkerStyle = 3;//MarkerStyleChoise;
        qDebug()<< "Стиль маркера = " << customPlot->MarkerStyle;
    }

    /*
    QDialog dialog;
    QComboBox *markerTypeComboBox = new QComboBox(&dialog);
    markerTypeComboBox->addItem("Circle");
    markerTypeComboBox->addItem("Square");


    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    QVBoxLayout layout(&dialog);
    layout.addWidget(markerTypeComboBox);
    layout.addWidget(&buttonBox);

    if (dialog.exec() == QDialog::Accepted)
    {
        // Get the selected marker type
        QString selectedMarkerType = markerTypeComboBox->currentText();

        // Update the plot with the selected marker color and type
        // You can use the selectedColor and selectedMarkerType to update the plot
    }
*/
}



void WidgetForCustomPlot::ChangeMarkerStyle() //Может это из-за QDialogBox ошибки?
{
    //int MarkerStyleChoise = this->MarkerStyleComboBox->currentIndex();
    //MarkerStyleChoise = QCPItemTracer::TracerStyle(index);
    //if ()
    //MarkerStyleChoise =IndexToMarkerStyle[MarkerStyleComboBox->currentIndex()];
    //qDebug()<< MarkerStyleChoise;
}


/*
Придумать способ доказать что графическое отображение соответствует табличным данным -- не съезжает, правильно интерполируется

(Взять данные)

Подводные камни? Скачки, какие ещё проблемы, поискать литературу по проблемам с построением графиков.
Убедиться, что qcustomplot правильно строит, какая там интерполяция, ничего ли он не пропускает.



*/
