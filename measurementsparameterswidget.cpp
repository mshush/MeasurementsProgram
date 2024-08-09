#include "measurementsparameterswidget.h"

MeasurementsParametersWidget::MeasurementsParametersWidget(QWidget *parent)
    : QWidget{parent}
{

    //resize(300,900);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    //qDebug()<<size();


    VerticalLayoutOfParameters = new QVBoxLayout(this);
    FrequencyGroupBox = new QGroupBox("Диапазон частот измерения",this);
    //FrequencyGroupBox->setFixedSize(280,250);
    FrequencyGroupBox->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    FrequencyGroupBoxLayout = new QVBoxLayout;
    StartStopButton = new QRadioButton("Начало-Конец");
    connect(StartStopButton,&QRadioButton::clicked,this,&MeasurementsParametersWidget::StartStopButtonClicked);
    CenterSpanButton = new QRadioButton("Центр-Диапазон");
    connect(CenterSpanButton,&QRadioButton::clicked,this,&MeasurementsParametersWidget::CenterSpanButtonClicked);
    FrequencyGroupBoxLayout->addWidget(StartStopButton);
    StartStopButton->setChecked(true);
    FrequencyGroupBoxLayout->addWidget(CenterSpanButton);

    FrequencyRangeLayout = new QGridLayout(this);
    FrequencyStartCenterLabel = new QLabel("Начало");
    FrequencyStartCenterEdit = new QLineEdit("0");
    //QDoubleValidator * StartCenterDoubleValidator = new QDoubleValidator(FrequencyStopSpanEdit);
    //FrequencyStopSpanEdit->setValidator(StartCenterDoubleValidator);

    FrequencyStartCenterUnitsLabel = new QLabel("ГГц", this);
    //FrequencyStartCenterComboBox = new QComboBox(this);
    //FrequencyStartCenterComboBox->addItem("ГГц");

    FrequencyStopSpanLabel = new QLabel("Конец");
    FrequencyStopSpanEdit = new QLineEdit("1600");
    //QDoubleValidator * StopSpanDoubleValidator = new QDoubleValidator(FrequencyStopSpanEdit);
    //FrequencyStopSpanEdit->setValidator(StopSpanDoubleValidator);
    //connect(FrequencyStartCenterEdit, &QLineEdit::textEdited,this, &MeasurementsParametersWidget::ProcessChangedStopCenterEdit);

    FrequencyStopSpanUnitsLabel = new QLabel("ГГц", this);
    //FrequencyStopSpanComboBox = new QComboBox(this);
    //FrequencyStopSpanComboBox->addItem("ГГц");

    FrequencyStartCenterEdit->setFixedWidth(60);
    FrequencyStopSpanEdit   ->setFixedWidth(60);
    FrequencyRangeLayout->addWidget(FrequencyStartCenterLabel      ,0,0);
    FrequencyRangeLayout->addWidget(FrequencyStartCenterEdit       ,0,1);
    FrequencyRangeLayout->addWidget(FrequencyStartCenterUnitsLabel ,0,2);

    FrequencyRangeLayout->addWidget(FrequencyStopSpanLabel         ,1,0);
    FrequencyRangeLayout->addWidget(FrequencyStopSpanEdit          ,1,1);
    FrequencyRangeLayout->addWidget(FrequencyStopSpanUnitsLabel    ,1,2);

    FrequencyGroupBoxLayout->addLayout(FrequencyRangeLayout);

    FrequencyNumberOfPointsLayout = new QHBoxLayout(this);
    FrequencyNumberOfPointsLabel = new QLabel("Число точек",this);
    FrequencyNumberOfPointsEdit = new QLineEdit ("1601",this);
    FrequencyNumberOfPointsLayout->addWidget(FrequencyNumberOfPointsLabel);
    FrequencyNumberOfPointsLayout->addWidget(FrequencyNumberOfPointsEdit);

    SetFrequencyParametersButton = new QPushButton("Установить", this);
    connect(SetFrequencyParametersButton,&QPushButton::clicked,this,&MeasurementsParametersWidget::OnSetFrequencyParametersButtonClicked);


    FrequencyGroupBoxLayout->addLayout(FrequencyRangeLayout);
    FrequencyGroupBoxLayout->addLayout(FrequencyNumberOfPointsLayout);
    FrequencyGroupBoxLayout->addWidget(SetFrequencyParametersButton);
    FrequencyGroupBox->setLayout(FrequencyGroupBoxLayout);

    QGroupBox * AngleGroup = new QGroupBox("Диапазон углов");
    QGridLayout * AngleLayout = new QGridLayout(AngleGroup);
    AngleLayout->addWidget(new QLabel("От"),0,0);
    AngleLayout->addWidget(new QLineEdit("Введите начальный угол"),0,1);
    AngleLayout->addWidget(new QLabel("До"),1,0);
    AngleLayout->addWidget(new QLineEdit("Введите конечный угол"),1,1);

    AngleGroup->setLayout(AngleLayout);


    CalibrationSampleGroup = new QGroupBox("Калибровочный образец");



    CalibrationSampleMainLayout = new QVBoxLayout;

    CalibrationSampleTypeLayout = new QHBoxLayout();
    CalibrationSampleTypeLayout->addWidget(new QLabel("Вид образца"));
    CalibrationSampleComboBox = new QComboBox;
    CalibrationSampleComboBox->addItem("Цилиндр");
    CalibrationSampleTypeLayout->addWidget(CalibrationSampleComboBox);
    CalibrationSampleMainLayout->addLayout(CalibrationSampleTypeLayout);

    CalibrationSampleParametersLayout = new QHBoxLayout();
    CalibrationSampleParametersLayout->addWidget(new QLabel("Параметры"));
    CalibrationSampleParametersLayout->addWidget(new QLineEdit("Введите параметр"));

    CalibrationSampleMainLayout->addLayout(CalibrationSampleParametersLayout);

    CalibrationSampleGroup->setLayout(CalibrationSampleMainLayout);

    VerticalLayoutOfParameters->addWidget(FrequencyGroupBox);
    VerticalLayoutOfParameters->addWidget(AngleGroup);
    VerticalLayoutOfParameters->addWidget(CalibrationSampleGroup);


    setLayout(VerticalLayoutOfParameters);


}





void MeasurementsParametersWidget::StartStopButtonClicked (bool StartStopButtonCheckStatus)
{
    if (StartStopButtonCheckStatus)
    {
        double FreqCenter = FrequencyStartCenterEdit->text().toDouble();
        double FreqSpan   = FrequencyStopSpanEdit   ->text().toDouble();

        double FreqStart = FreqCenter-FreqSpan/2;
        double FreqStop  = FreqCenter+FreqSpan/2;

        FrequencyStartCenterEdit->setText(QString::number(FreqStart));
        FrequencyStopSpanEdit   ->setText(QString::number(FreqStop ));

        FrequencyStartCenterLabel->setText("Начало");
        FrequencyStopSpanLabel   ->setText("Конец" );
    }
}



void MeasurementsParametersWidget::CenterSpanButtonClicked(bool CenterSpanButtonCheckStatus)
{
    if (CenterSpanButtonCheckStatus)
    {
        double FreqStart = FrequencyStartCenterEdit->text().toDouble();
        double FreqStop  = FrequencyStopSpanEdit   ->text().toDouble();

        double FreqCenter = (FreqStart + FreqStop)/2;
        double FreqSpan   = FreqStop - FreqStart;

        FrequencyStartCenterEdit->setText(QString::number(FreqCenter));
        FrequencyStopSpanEdit   ->setText(QString::number(FreqSpan  ));

        FrequencyStartCenterLabel->setText("Центр"    );
        FrequencyStopSpanLabel   ->setText("Диапазон" );
    }
}


void MeasurementsParametersWidget::OnSetFrequencyParametersButtonClicked()
{
    if (StartStopButton->isChecked())
    {
        StartFrequency = FrequencyStartCenterEdit->text().toDouble();
        StopFrequency  = FrequencyStopSpanEdit   ->text().toDouble();
    }
    else
    {
        StartFrequency = FrequencyStartCenterEdit->text().toDouble() - FrequencyStopSpanEdit->text().toDouble()/2;
        StopFrequency  = FrequencyStartCenterEdit->text().toDouble() + FrequencyStopSpanEdit->text().toDouble()/2;
    }
    NumberOfPoints = FrequencyNumberOfPointsEdit->text().toDouble();

    emit ParametersOfMeasurementsChanged(StartFrequency, StopFrequency, NumberOfPoints);
}




MeasurementsParametersWidget::~MeasurementsParametersWidget()
{
    /*
    delete FrequencyGroupBox;
    delete FrequencyGroupBoxLayout;
    delete StartStopButton;
    delete CenterSpanButton;
    delete FrequencyRangeLayout;
    delete FrequencyStartCenterLabel;
    delete FrequencyStartCenterEdit;
    delete FrequencyStartCenterComboBox;
    delete SetFrequencyParametersButton;
    delete FrequencyStopSpanLabel;
    delete FrequencyStopSpanEdit;
    delete FrequencyStopSpanComboBox;
    */
}






