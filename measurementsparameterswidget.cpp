#include "measurementsparameterswidget.h"

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

    FrequencyButtonLayout = new QVBoxLayout;
    StartStopButton = new QRadioButton("Начало-Конец");
    connect(StartStopButton,&QRadioButton::clicked,this,&MeasurementsParametersWidget::SetStartStopMode);
    CenterSpanButton = new QRadioButton("Центр-Диапазон");
    connect(CenterSpanButton,&QRadioButton::clicked,this,&MeasurementsParametersWidget::SetCenterSpanMode);
    FrequencyButtonLayout->addWidget(StartStopButton);
    StartStopButton->setChecked(true);
    FrequencyButtonLayout->addWidget(CenterSpanButton);

    FrequencyStartCenterLayout = new QHBoxLayout;
    FrequencyStartCenterLabel = new QLabel("Начало");
    FrequencyStartCenterEdit = new QLineEdit("-800");
    //QDoubleValidator * StartCenterDoubleValidator = new QDoubleValidator(FrequencyStopSpanEdit);
    //FrequencyStopSpanEdit->setValidator(StartCenterDoubleValidator);
    connect(FrequencyStartCenterEdit, &QLineEdit::textEdited,this, &MeasurementsParametersWidget::ProcessChangedStartSpanEdit);
    FrequencyStartCenterComboBox = new QComboBox;
    FrequencyStartCenterComboBox->addItem("ГГц");
    FrequencyStartCenterLayout->addWidget(FrequencyStartCenterLabel);
    FrequencyStartCenterLayout->addWidget(FrequencyStartCenterEdit);
    FrequencyStartCenterLayout->addWidget(FrequencyStartCenterComboBox);


    FrequencyStopSpanLayout = new QHBoxLayout;
    FrequencyStopSpanLabel = new QLabel("Конец");
    FrequencyStopSpanEdit = new QLineEdit("800");
    //QDoubleValidator * StopSpanDoubleValidator = new QDoubleValidator(FrequencyStopSpanEdit);
    //FrequencyStopSpanEdit->setValidator(StopSpanDoubleValidator);
    connect(FrequencyStartCenterEdit, &QLineEdit::textEdited,this, &MeasurementsParametersWidget::ProcessChangedStopCenterEdit);
    FrequencyStopSpanComboBox = new QComboBox;
    FrequencyStopSpanComboBox->addItem("ГГц");
    FrequencyStopSpanLayout->addWidget(FrequencyStopSpanLabel);
    FrequencyStopSpanLayout->addWidget(FrequencyStopSpanEdit);
    FrequencyStopSpanLayout->addWidget(FrequencyStopSpanComboBox);











    QHBoxLayout * FrequencyNumberOfPointsLayout = new QHBoxLayout;
    QLabel * FrequencyNumberOfPointsLabel = new QLabel("Число точек");
    QLineEdit * FrequencyNumberOfPointsEdit = new QLineEdit ("1601");
    FrequencyNumberOfPointsLayout->addWidget(FrequencyNumberOfPointsLabel);
    FrequencyNumberOfPointsLayout->addWidget(FrequencyNumberOfPointsEdit);



    FrequencyGroupMainLayout->addLayout(FrequencyButtonLayout);
    FrequencyGroupMainLayout->addLayout(FrequencyStartCenterLayout);
    FrequencyGroupMainLayout->addLayout(FrequencyStopSpanLayout);
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





void MeasurementsParametersWidget::SetStartStopMode (bool StartStopButtonCheckStatus )
{
    if (StartStopButtonCheckStatus)
    {
        FrequencyStartCenterLabel->setText("Начало");
        FrequencyStopSpanLabel->setText("Конец");
        ProcessChangedStartSpanEdit();
    }
}



void MeasurementsParametersWidget::SetCenterSpanMode(bool CenterSpanButtonCheckStatus)
{
    if (CenterSpanButtonCheckStatus)
    {
        FrequencyStartCenterLabel->setText("Центр");
        FrequencyStopSpanLabel->setText("Диапазон");
        ProcessChangedStartSpanEdit();
    }
}





void MeasurementsParametersWidget::ProcessChangedStartSpanEdit()
{

    if (StartStopButton->isChecked())
    {
        StartFrequency = FrequencyStartCenterEdit->text().toDouble();
        StopFrequency = FrequencyStopSpanEdit->text().toDouble();
    }
    else
    {
        double center = FrequencyStartCenterEdit->text().toDouble();
        double span = FrequencyStopSpanEdit->text().toDouble();
        StartFrequency = center-span/2;
        StopFrequency = center+span/2;
        qDebug()<< "From" << StartFrequency << " to " << StopFrequency;
    }
    emit StartStopFrequenciesChanged(StartFrequency,StopFrequency);
}
void MeasurementsParametersWidget::ProcessChangedStopCenterEdit()
{

    if (StartStopButton->isChecked())
    {
        StartFrequency = FrequencyStartCenterEdit->text().toDouble();
        StopFrequency = FrequencyStopSpanEdit->text().toDouble();
    }
    else
    {
        double center = FrequencyStartCenterEdit->text().toDouble();
        double span = FrequencyStopSpanEdit->text().toDouble();
        StartFrequency = center-span/2;
        StopFrequency = center+span/2;
    }
    emit StartStopFrequenciesChanged(StartFrequency,StopFrequency);
}








MeasurementsParametersWidget::~MeasurementsParametersWidget()
{
    delete FrequencyButtonLayout;
    delete StartStopButton;
    delete CenterSpanButton;

    delete FrequencyStartCenterLayout;
    delete FrequencyStartCenterLabel;
    delete FrequencyStartCenterEdit;
    delete FrequencyStartCenterComboBox;

    delete FrequencyStopSpanLayout;
    delete FrequencyStopSpanLabel;
    delete FrequencyStopSpanEdit;
    delete FrequencyStopSpanComboBox;
}






