#include "measurementsparameterswidget.h"
#include "qlineedit.h"

MeasurementsParametersWidget::MeasurementsParametersWidget(QWidget *parent)
    : QWidget{parent}
{

    resize(200,500);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    QVBoxLayout *VerticalLayoutOfParameters = new QVBoxLayout(this);


    QGroupBox * FrequencyGroup = new QGroupBox("Частотный диапазон");
    QVBoxLayout * FrequencyGroupMainLayout = new QVBoxLayout;

    /*
    QLabel * ExplanationLabel2 = new QLabel("Переключение кнопки меняет поля ввода. Единицы измерений через QComboBox возможно слишком громоздко");
    ExplanationLabel2->setWordWrap(true);
    FrequencyGroupMainLayout->addWidget(ExplanationLabel2);
    */

    QHBoxLayout * FrequencyButtonLayout = new QHBoxLayout;
    QRadioButton * StartStopButton = new QRadioButton("Начало-Конец");
    QRadioButton * CenterSpanButton = new QRadioButton("Центр-Диапазон");
    FrequencyButtonLayout->addWidget(StartStopButton);
    FrequencyButtonLayout->addWidget(CenterSpanButton);

    QHBoxLayout * FrequencyStartLayout = new QHBoxLayout;
    QLabel * FrequencyStartLabel = new QLabel("Начало");
    QLineEdit * FrequencyStartEdit = new QLineEdit;
    QComboBox * FrequencyStartComboBox = new QComboBox;
    FrequencyStartComboBox->addItem("ГГц");
    FrequencyStartLayout->addWidget(FrequencyStartLabel);
    FrequencyStartLayout->addWidget(FrequencyStartEdit);
    FrequencyStartLayout->addWidget(FrequencyStartComboBox);


    QHBoxLayout * FrequencyStopLayout = new QHBoxLayout;
    QLabel * FrequencyStopLabel = new QLabel("Конец");
    QLineEdit * FrequencyStopEdit = new QLineEdit;
    QComboBox * FrequencyStopComboBox = new QComboBox;
    FrequencyStopComboBox->addItem("ГГц");
    FrequencyStopLayout->addWidget(FrequencyStopLabel);
    FrequencyStopLayout->addWidget(FrequencyStopEdit);
    FrequencyStopLayout->addWidget(FrequencyStopComboBox);

    QHBoxLayout * FrequencyNumberOfPointsLayout = new QHBoxLayout;
    QLabel * FrequencyNumberOfPointsLabel = new QLabel("Число точек");
    QLineEdit * FrequencyNumberOfPointsEdit = new QLineEdit;
    FrequencyNumberOfPointsLayout->addWidget(FrequencyNumberOfPointsLabel);
    FrequencyNumberOfPointsLayout->addWidget(FrequencyNumberOfPointsEdit);



    FrequencyGroupMainLayout->addLayout(FrequencyButtonLayout);
    FrequencyGroupMainLayout->addLayout(FrequencyStartLayout);
    FrequencyGroupMainLayout->addLayout(FrequencyStopLayout);
    FrequencyGroupMainLayout->addLayout(FrequencyNumberOfPointsLayout);

    FrequencyGroup->setLayout(FrequencyGroupMainLayout);

    QGroupBox * AngleGroup = new QGroupBox("Диапазон углов");
    QGridLayout * AngleLayout = new QGridLayout(AngleGroup);
    AngleLayout->addWidget(new QLabel("От"),0,0);
    AngleLayout->addWidget(new QLineEdit("Введите начальный угол"),0,1);
    AngleLayout->addWidget(new QLabel("До"),1,0);
    AngleLayout->addWidget(new QLineEdit("Введите конечный угол"),1,1);

    AngleGroup->setLayout(AngleLayout);


    QGroupBox * CalibrationSampleGroup = new QGroupBox("Калибровочный образец");



    QVBoxLayout * CalibrationSampleMainLayout = new QVBoxLayout;
    /*
    QLabel * ExplanationLabel4 = new QLabel("Здесь QComboBox образцов и набор параметров \nобразца, определяемый QComboBox-ом");
    CalibrationSampleGroupMainLayout->addWidget(ExplanationLabel4);
    */
    QHBoxLayout * CalibrationSampleTypeLayout = new QHBoxLayout();
    CalibrationSampleTypeLayout->addWidget(new QLabel("Вид образца"));
    QComboBox * CalibrationSampleComboBox = new QComboBox;
    CalibrationSampleComboBox->addItem("Цилиндр");
    CalibrationSampleTypeLayout->addWidget(CalibrationSampleComboBox);
    CalibrationSampleMainLayout->addLayout(CalibrationSampleTypeLayout);

    QHBoxLayout * CalibrationSampleParametersLayout = new QHBoxLayout();
    CalibrationSampleParametersLayout->addWidget(new QLabel("Параметры"));
    CalibrationSampleParametersLayout->addWidget(new QLineEdit("Введите параметр"));

    CalibrationSampleMainLayout->addLayout(CalibrationSampleParametersLayout);


    CalibrationSampleGroup->setLayout(CalibrationSampleMainLayout);
    //QPushButton * button1 = new QPushButton("Press!!!");

    /*
    QLabel * ExplanationLabel = new QLabel("Здесь меняются параметры измерений \n(В другой вкладке будут параметры для работы с полученными данными)");
    ExplanationLabel->setWordWrap(true);
    VerticalLayoutOfParameters->addWidget(ExplanationLabel);
    */

    VerticalLayoutOfParameters->addWidget(FrequencyGroup);
    VerticalLayoutOfParameters->addWidget(AngleGroup);
    VerticalLayoutOfParameters->addWidget(CalibrationSampleGroup);

    /*
    QLabel * ExplanationLabel1 = new QLabel("Справа, также как в старой программе,\nчтобы было привычнее. Последовательность,\nв которой расположены параметры если менять,\nто перераспределить в порядке частоты\nиспользования, чтобы далеко мышку не вести");
    ExplanationLabel1->setWordWrap(true);
    ExplanationLabel->resize(160,50);
    ExplanationLabel1->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    VerticalLayoutOfParameters->addWidget(ExplanationLabel1);
    */
    setLayout(VerticalLayoutOfParameters);

    //qDebug()<<this->size();

}
