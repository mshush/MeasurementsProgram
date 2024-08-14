#include "measurementsparameterswidget.h"


MeasurementsParametersWidget::MeasurementsParametersWidget(QWidget *parent)
    : QWidget{parent}
{

    //resize(300,900);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    //qDebug()<<size();


    DoubleValidator = new QDoubleValidator(this);
    DoubleValidator->setNotation(QDoubleValidator::ScientificNotation);
    DoubleValidator->setLocale(QLocale("en_US"));


    VerticalLayoutOfParameters = new QVBoxLayout(this);

    InitializeFrequencyGroupBox();
    VerticalLayoutOfParameters->addWidget(FrequencyGroupBox);

    InitializeAngleGroupBox();
    VerticalLayoutOfParameters->addWidget(AngleGroupBox);

    InitializeCalibrationSampleGroupBox();
    VerticalLayoutOfParameters->addWidget(CalibrationSampleGroupBox);





    setLayout(VerticalLayoutOfParameters);
}





void MeasurementsParametersWidget::StartStopButtonClicked (bool StartStopButtonCheckStatus)
{
    if (StartStopButtonCheckStatus)
    {
        FrequencyStartCenterEdit->setText(QString::number(StartFrequency));
        FrequencyStopSpanEdit   ->setText(QString::number(StopFrequency ));

        FrequencyStartCenterLabel->setText("Начало");
        FrequencyStopSpanLabel   ->setText("Конец" );
    }
}

void MeasurementsParametersWidget::CenterSpanButtonClicked(bool CenterSpanButtonCheckStatus)
{
    if (CenterSpanButtonCheckStatus)
    {
        double FreqCenter = (StartFrequency + StopFrequency)/2;
        double FreqSpan   = StopFrequency - StartFrequency;

        FrequencyStartCenterEdit->setText(QString::number(FreqCenter));
        FrequencyStopSpanEdit   ->setText(QString::number(FreqSpan  ));

        FrequencyStartCenterLabel->setText("Центр" );
        FrequencyStopSpanLabel   ->setText("Ширина");
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




void MeasurementsParametersWidget::InitializeFrequencyGroupBox()
{
    FrequencyGroupBox = new QGroupBox("Диапазон частот измерения",this);
    //FrequencyGroupBox->setFixedSize(280,250);
    FrequencyGroupBox->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    FrequencyGroupBoxLayout = new QVBoxLayout(FrequencyGroupBox);

    ButtonGroupLayout = new QHBoxLayout();
    FrequencyRangesButtonGroup = new QButtonGroup(FrequencyGroupBox);

    FrequencyRangesButtonGroup->setExclusive(true);

    //NoRangeButton = new QPushButton("-", FrequencyGroupBox);
    //NoRangeButton->setToolTip("Ввести свой диапазон");
    LRangeButton  = new QPushButton("L"  ,FrequencyGroupBox);
    SRangeButton  = new QPushButton("S"  ,FrequencyGroupBox);
    CRangeButton  = new QPushButton("C"  ,FrequencyGroupBox);
    XRangeButton  = new QPushButton("X"  ,FrequencyGroupBox);
    KuRangeButton = new QPushButton("Ku" ,FrequencyGroupBox);
    KRangeButton  = new QPushButton("K"  ,FrequencyGroupBox);
    KaRangeButton = new QPushButton("Ka" ,FrequencyGroupBox);

    //NoRangeButton->setCheckable(true);
    LRangeButton ->setCheckable(true);
    SRangeButton ->setCheckable(true);
    CRangeButton ->setCheckable(true);
    XRangeButton ->setCheckable(true);
    KuRangeButton->setCheckable(true);
    KRangeButton ->setCheckable(true);
    KaRangeButton->setCheckable(true);

    //NoRangeButton->setChecked(true);

    QString StyleSheetStringForLeftButton = "QPushButton { background-color: white;"
                                            "   color: black;"
                                            "   border: 1px solid gray;"
                                            "   border-top-right-radius: 0px;"
                                            "   border-bottom-right-radius: 0px;"
                                            "   border-top-left-radius: 5px;"
                                            "   border-bottom-left-radius: 5px;"
                                            "   padding: 3px 3px;"
                                            "   font-size: 16px;"
                                            "   font-weight: bold;"
                                            "   text-align: center;"
                                            "}"
                                            "QPushButton:checked {background-color: #ADD8E6;}";

    QString StyleSheetStringForRightButton = "QPushButton { background-color: white;"
                                             "   color: black;"
                                             "   border: 1px solid gray;"
                                             "   border-top-right-radius: 5px;"
                                             "   border-bottom-right-radius: 5px;"
                                             "   border-top-left-radius: 0px;"
                                             "   border-top-left-radius: 0px;"
                                             "   padding: 3px 3px;"
                                             "   font-size: 16px;"
                                             "   font-weight: bold;"
                                             "   text-align: center;"
                                             "}"
                                             "QPushButton:checked {background-color: #ADD8E6;}";


    QString StyleSheetStringForMiddleButton = "QPushButton { background-color: white;"
                                             "   color: black;"
                                             "   border: 1px solid gray;"
                                             "   border-radius: 0px;"
                                             "   padding: 3px 3px;"
                                             "   font-size: 16px;"
                                             "   font-weight: bold;"
                                             "   text-align: center;"
                                             "}"
                                             "QPushButton:checked {background-color: #ADD8E6;}";


    //NoRangeButton->setStyleSheet(StyleSheetStringForLeftButton  );
    LRangeButton ->setStyleSheet(StyleSheetStringForLeftButton);
    SRangeButton ->setStyleSheet(StyleSheetStringForMiddleButton);
    CRangeButton ->setStyleSheet(StyleSheetStringForMiddleButton);
    XRangeButton ->setStyleSheet(StyleSheetStringForMiddleButton);
    KuRangeButton->setStyleSheet(StyleSheetStringForMiddleButton);
    KRangeButton ->setStyleSheet(StyleSheetStringForMiddleButton);
    KaRangeButton->setStyleSheet(StyleSheetStringForRightButton );




    //FrequencyRangesButtonGroup->addButton(NoRangeButton, 0);
    FrequencyRangesButtonGroup->addButton(LRangeButton , 0);
    FrequencyRangesButtonGroup->addButton(SRangeButton , 1);
    FrequencyRangesButtonGroup->addButton(CRangeButton , 2);
    FrequencyRangesButtonGroup->addButton(XRangeButton , 3);
    FrequencyRangesButtonGroup->addButton(KuRangeButton, 4);
    FrequencyRangesButtonGroup->addButton(KRangeButton , 5);
    FrequencyRangesButtonGroup->addButton(KaRangeButton, 6);

    //ButtonGroupLayout->addWidget(NoRangeButton);
    ButtonGroupLayout->addWidget(LRangeButton );
    ButtonGroupLayout->addWidget(SRangeButton );
    ButtonGroupLayout->addWidget(CRangeButton );
    ButtonGroupLayout->addWidget(XRangeButton );
    ButtonGroupLayout->addWidget(KuRangeButton);
    ButtonGroupLayout->addWidget(KRangeButton );
    ButtonGroupLayout->addWidget(KaRangeButton);
    ButtonGroupLayout->setSpacing(0);

    connect(FrequencyRangesButtonGroup, &QButtonGroup::idPressed, this, &MeasurementsParametersWidget::FrequencyRangeButtonPressed);
    connect(FrequencyRangesButtonGroup, &QButtonGroup::idClicked, this, &MeasurementsParametersWidget::FrequencyRangeButtonClicked);

    FrequencyGroupBoxLayout->addLayout(ButtonGroupLayout);



    StartStopButton = new QRadioButton("Начало-Конец",FrequencyGroupBox);
    connect(StartStopButton,&QRadioButton::clicked,this,&MeasurementsParametersWidget::StartStopButtonClicked);
    CenterSpanButton = new QRadioButton("Центр-Ширина",FrequencyGroupBox);
    connect(CenterSpanButton,&QRadioButton::clicked,this,&MeasurementsParametersWidget::CenterSpanButtonClicked);
    FrequencyGroupBoxLayout->addWidget(StartStopButton);
    StartStopButton->setChecked(true);
    FrequencyGroupBoxLayout->addWidget(CenterSpanButton);

    FrequencyRangeLayout = new QGridLayout();
    FrequencyStartCenterLabel = new QLabel("Начало",FrequencyGroupBox);
    FrequencyStartCenterEdit = new QLineEdit(QString::number(StartFrequency),FrequencyGroupBox);
    FrequencyStartCenterEdit->setValidator(DoubleValidator);

    FrequencyStartCenterUnitsLabel = new QLabel("ГГц", FrequencyGroupBox);

    FrequencyStopSpanLabel = new QLabel("Конец",FrequencyGroupBox);
    FrequencyStopSpanEdit = new QLineEdit(QString::number(StopFrequency),FrequencyGroupBox);
    FrequencyStopSpanEdit->setValidator(DoubleValidator);

    connect(FrequencyStartCenterEdit, &QLineEdit::textEdited,this, &MeasurementsParametersWidget::RenewStartStopFrequencies);
    connect(FrequencyStopSpanEdit,    &QLineEdit::textEdited,this, &MeasurementsParametersWidget::RenewStartStopFrequencies);


    FrequencyStopSpanUnitsLabel = new QLabel("ГГц", FrequencyGroupBox);

    FrequencyStartCenterEdit->setFixedWidth(60);
    FrequencyStopSpanEdit   ->setFixedWidth(60);
    FrequencyRangeLayout->addWidget(FrequencyStartCenterLabel      ,0,0);
    FrequencyRangeLayout->addWidget(FrequencyStartCenterEdit       ,0,1);
    FrequencyRangeLayout->addWidget(FrequencyStartCenterUnitsLabel ,0,2);

    FrequencyRangeLayout->addWidget(FrequencyStopSpanLabel         ,1,0);
    FrequencyRangeLayout->addWidget(FrequencyStopSpanEdit          ,1,1);
    FrequencyRangeLayout->addWidget(FrequencyStopSpanUnitsLabel    ,1,2);

    FrequencyGroupBoxLayout->addLayout(FrequencyRangeLayout);


    FrequencyNumberOfPointsLayout = new QHBoxLayout();
    FrequencyNumberOfPointsLabel = new QLabel("Число точек",FrequencyGroupBox);
    FrequencyNumberOfPointsEdit = new QLineEdit ("1601",FrequencyGroupBox);
    FrequencyNumberOfPointsLayout->addWidget(FrequencyNumberOfPointsLabel);
    FrequencyNumberOfPointsLayout->addWidget(FrequencyNumberOfPointsEdit);

    SetFrequencyParametersButton = new QPushButton("Установить", FrequencyGroupBox);
    connect(SetFrequencyParametersButton,&QPushButton::clicked,this,&MeasurementsParametersWidget::OnSetFrequencyParametersButtonClicked);


    FrequencyGroupBoxLayout->addLayout(FrequencyRangeLayout);
    FrequencyGroupBoxLayout->addLayout(FrequencyNumberOfPointsLayout);
    FrequencyGroupBoxLayout->addWidget(SetFrequencyParametersButton);
    FrequencyGroupBox->setLayout(FrequencyGroupBoxLayout);

}






void MeasurementsParametersWidget::FrequencyRangeButtonClicked(int ChosenRangeId)
{
    bool CheckStatus = FrequencyRangesButtonGroup->button(ChosenRangeId)->isChecked();
    if (CheckStatus)
    {
        if (StartStopButton->isChecked())
        {
            StartFrequency = FrequencyRanges[ChosenRangeId].first;
            StopFrequency = FrequencyRanges[ChosenRangeId].second;
            FrequencyStartCenterEdit->setText(QString::number(StartFrequency));
            FrequencyStopSpanEdit->setText(QString::number(StopFrequency));

        }
        else
        {
            StartFrequency = FrequencyRanges[ChosenRangeId].first;
            StopFrequency = FrequencyRanges[ChosenRangeId].second;
            double FreqCenter = (StartFrequency + StopFrequency)/2;
            double FreqSpan   = StopFrequency - StartFrequency;
            FrequencyStartCenterEdit->setText(QString::number(FreqCenter));
            FrequencyStopSpanEdit->setText(QString::number(FreqSpan));
        }
        FrequencyStartCenterEdit->setReadOnly(true);
        FrequencyStopSpanEdit   ->setReadOnly(true);
        QPalette Palette = FrequencyStartCenterEdit->palette();
        Palette.setColor(QPalette::Base, QColor(173, 216, 230,100));
        FrequencyStartCenterEdit->setPalette(Palette);
        FrequencyStopSpanEdit   ->setPalette(Palette);
    }
    else
    {

        FrequencyStartCenterEdit->setReadOnly(false);
        FrequencyStopSpanEdit   ->setReadOnly(false);
        QPalette Palette = FrequencyStartCenterEdit->palette();
        Palette.setColor(QPalette::Base, QColor(255,255,255));
        FrequencyStartCenterEdit->setPalette(Palette);
        FrequencyStopSpanEdit   ->setPalette(Palette);
    }
    FrequencyRangesButtonGroup->setExclusive(true);
}


void MeasurementsParametersWidget::FrequencyRangeButtonPressed(int ChosenRangeId) //Чтобы можно было выключить все кнопки диапазонов
{
    bool CheckStatus = FrequencyRangesButtonGroup->button(ChosenRangeId)->isChecked();
    FrequencyRangesButtonGroup->setExclusive(!CheckStatus);
}


void MeasurementsParametersWidget::RenewStartStopFrequencies()
{
    if (StartStopButton->isChecked())
    {
        StartFrequency = FrequencyStartCenterEdit->text().toDouble();
        StopFrequency  = FrequencyStopSpanEdit   ->text().toDouble();
    }
    else
    {
        double Center = FrequencyStartCenterEdit->text().toDouble();
        double Span   = FrequencyStopSpanEdit   ->text().toDouble();
        StartFrequency = Center-Span/2;
        StopFrequency = Center+Span/2;
    }
}



void MeasurementsParametersWidget::InitializeAngleGroupBox()
{
    AngleGroupBox = new QGroupBox("Диапазон углов", this);
    AngleGroupBoxLayout = new QVBoxLayout(AngleGroupBox);
    AngleFromToGridLayout = new QGridLayout();

    AngleFromLabel = new QLabel("От",this);
    AngleFromEdit  = new QLineEdit("",this);
    AngleToLabel   = new QLabel("До",this);
    AngleToEdit    = new QLineEdit("",this);

    AngleFromToGridLayout->addWidget(AngleFromLabel, 0,0);
    AngleFromToGridLayout->addWidget(AngleFromEdit,  0,1);
    AngleFromToGridLayout->addWidget(AngleToLabel,   1,0);
    AngleFromToGridLayout->addWidget(AngleToEdit,    1,1);

    AngleNumberOfPointsLayout = new QHBoxLayout();

    AngleNumberOfPointsLabel = new QLabel("Число точек",this);
    AngleNumberOfPointsEdit = new QLineEdit("",this);

    AngleNumberOfPointsLayout->addWidget(AngleNumberOfPointsLabel);
    AngleNumberOfPointsLayout->addWidget(AngleNumberOfPointsEdit );



    AngleGroupBoxLayout->addLayout(AngleFromToGridLayout);
    AngleGroupBoxLayout->addLayout(AngleNumberOfPointsLayout);

    AngleGroupBox->setLayout(AngleGroupBoxLayout);
}



void MeasurementsParametersWidget::InitializeCalibrationSampleGroupBox()
{
    CalibrationSampleGroupBox = new QGroupBox("Калибровочный образец");

    CalibrationSampleMainLayout = new QVBoxLayout();

    CalibrationSampleTypeLayout = new QHBoxLayout();
    CalibrationSampleTypeLayout->addWidget(new QLabel("Вид образца"));
    CalibrationSampleComboBox = new QComboBox(this);
    CalibrationSampleComboBox->addItem("Цилиндр");
    CalibrationSampleTypeLayout->addWidget(CalibrationSampleComboBox);
    CalibrationSampleMainLayout->addLayout(CalibrationSampleTypeLayout);

    CalibrationSampleParametersLayout = new QHBoxLayout();
    CalibrationSampleParametersLayout->addWidget(new QLabel("Параметры",this));
    CalibrationSampleParametersLayout->addWidget(new QLineEdit("Введите параметр",this));

    CalibrationSampleMainLayout->addLayout(CalibrationSampleParametersLayout);

    CalibrationSampleGroupBox->setLayout(CalibrationSampleMainLayout);

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



// Делать ли после нажатия на кнопку сброс наведения



