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

    InitializeCalibrationSampleGroupBox(); // Перенести в обработку???
    VerticalLayoutOfParameters->addWidget(CalibrationSampleGroupBox);

    setLayout(VerticalLayoutOfParameters);
}





void MeasurementsParametersWidget::StartStopButtonClicked (bool StartStopButtonCheckStatus)
{
    if (StartStopButtonCheckStatus)
    {
        FrequencyStartCenterEdit->setText(QString::number(FrequencyStart));
        FrequencyStopSpanEdit   ->setText(QString::number(FrequencyStop ));

        FrequencyStartCenterLabel->setText("Начало");
        FrequencyStopSpanLabel   ->setText("Конец" );
    }
}

void MeasurementsParametersWidget::CenterSpanButtonClicked(bool CenterSpanButtonCheckStatus)
{
    if (CenterSpanButtonCheckStatus)
    {
        double FreqCenter = (FrequencyStart + FrequencyStop)/2;
        double FreqSpan   = FrequencyStop - FrequencyStart;

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
        FrequencyStart = FrequencyStartCenterEdit->text().toDouble();
        FrequencyStop  = FrequencyStopSpanEdit   ->text().toDouble();
    }
    else
    {
        FrequencyStart = FrequencyStartCenterEdit->text().toDouble() - FrequencyStopSpanEdit->text().toDouble()/2;
        FrequencyStop  = FrequencyStartCenterEdit->text().toDouble() + FrequencyStopSpanEdit->text().toDouble()/2;
    }
    FrequencyNumber = FrequencyNumberOfPointsEdit->text().toDouble();

    emit FrequencyParametersChanged(FrequencyStart, FrequencyStop, FrequencyNumber);
}


void MeasurementsParametersWidget::OnSetAngleParametersButtonClicked()
{
    RotationAngleStart  = RotationAngleStartEdit->text().toDouble();
    RotationAngleStop   = RotationAngleStopEdit->text().toDouble();
    RotationAngleNumber = RotationAngleNumberOfPointsEdit->text().toDouble();

    TiltAngleStart      = TiltAngleStartEdit->text().toDouble();
    TiltAngleStop       = TiltAngleStopEdit->text().toDouble();
    TiltAngleNumber     = TiltAngleNumberOfPointsEdit->text().toDouble();


    emit AngleParametersChanged(RotationAngleStart, RotationAngleStop, RotationAngleNumber, TiltAngleStart, TiltAngleStop, TiltAngleNumber);
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
    FrequencyStartCenterEdit = new QLineEdit(QString::number(FrequencyStart),FrequencyGroupBox);
    FrequencyStartCenterEdit->setValidator(DoubleValidator);

    FrequencyStartCenterUnitsLabel = new QLabel("ГГц", FrequencyGroupBox);

    FrequencyStopSpanLabel = new QLabel("Конец",FrequencyGroupBox);
    FrequencyStopSpanEdit = new QLineEdit(QString::number(FrequencyStop),FrequencyGroupBox);
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
            FrequencyStart = FrequencyRanges[ChosenRangeId].first;
            FrequencyStop = FrequencyRanges[ChosenRangeId].second;
            FrequencyStartCenterEdit->setText(QString::number(FrequencyStart));
            FrequencyStopSpanEdit->setText(QString::number(FrequencyStop));

        }
        else
        {
            FrequencyStart = FrequencyRanges[ChosenRangeId].first;
            FrequencyStop = FrequencyRanges[ChosenRangeId].second;
            double FreqCenter = (FrequencyStart + FrequencyStop)/2;
            double FreqSpan   = FrequencyStop - FrequencyStart;
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
        FrequencyStart = FrequencyStartCenterEdit->text().toDouble();
        FrequencyStop  = FrequencyStopSpanEdit   ->text().toDouble();
    }
    else
    {
        double Center = FrequencyStartCenterEdit->text().toDouble();
        double Span   = FrequencyStopSpanEdit   ->text().toDouble();
        FrequencyStart = Center-Span/2;
        FrequencyStop = Center+Span/2;
    }
}



void MeasurementsParametersWidget::InitializeAngleGroupBox()
{
    AngleGroupBox = new QGroupBox("Диапазон углов", this);
    AngleGroupBoxLayout = new QVBoxLayout(AngleGroupBox);

    AngleGridLayout = new QGridLayout();

    RotationAngleStartLabel = new QLabel("Поворот:", AngleGroupBox);
    RotationAngleStartEdit  = new QLineEdit(QString::number(RotationAngleStart), AngleGroupBox);
    RotationAngleStopLabel   = new QLabel("-", AngleGroupBox);
    RotationAngleStopEdit    = new QLineEdit(QString::number(RotationAngleStop), AngleGroupBox);

    TiltAngleStartLabel = new QLabel("Наклон:", AngleGroupBox);
    TiltAngleStartEdit  = new QLineEdit(QString::number(TiltAngleStart), AngleGroupBox);
    TiltAngleStopLabel   = new QLabel("-", AngleGroupBox);
    TiltAngleStopEdit    = new QLineEdit(QString::number(TiltAngleStop), AngleGroupBox);


    RotationAngleNumberOfPointsLabel = new QLabel("Число точек поворота:", AngleGroupBox);
    RotationAngleNumberOfPointsEdit = new QLineEdit(QString::number(RotationAngleNumber),this);


    TiltAngleNumberOfPointsLabel = new QLabel("Число точек наклона:", AngleGroupBox);
    TiltAngleNumberOfPointsEdit = new QLineEdit(QString::number(TiltAngleNumber),this);

    SetAngleParametersButton = new QPushButton("Установить", AngleGroupBox);
    connect(SetAngleParametersButton,&QPushButton::clicked,this, &MeasurementsParametersWidget::OnSetAngleParametersButtonClicked);

    AngleGridLayout->addWidget(RotationAngleStartLabel, 0,0); // Переименовать Labelы
    AngleGridLayout->addWidget(RotationAngleStartEdit,  0,1);
    AngleGridLayout->addWidget(RotationAngleStopLabel,   0,2);
    AngleGridLayout->addWidget(RotationAngleStopEdit,    0,3);

    AngleGridLayout->addWidget(RotationAngleNumberOfPointsLabel, 1,0,1,3);
    AngleGridLayout->addWidget(RotationAngleNumberOfPointsEdit,  1,3,1,1);

    AngleGridLayout->addWidget(TiltAngleStartLabel, 2,0);
    AngleGridLayout->addWidget(TiltAngleStartEdit,  2,1);
    AngleGridLayout->addWidget(TiltAngleStopLabel,   2,2);
    AngleGridLayout->addWidget(TiltAngleStopEdit,    2,3);

    AngleGridLayout->addWidget(TiltAngleNumberOfPointsLabel, 3,0,1,3);
    AngleGridLayout->addWidget(TiltAngleNumberOfPointsEdit,  3,3,1,1);

    AngleGridLayout->addWidget(SetAngleParametersButton,  4,0,1,4);


    AngleGroupBoxLayout->addLayout(AngleGridLayout);

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



