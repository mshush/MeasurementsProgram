#include "resultparameterswidget.h"

ResultParametersWidget::ResultParametersWidget(QWidget *parent)
    : QWidget{parent}
{
    //IntValidator = new QIntValidator(this);

    this->setMaximumWidth(300);
    this->setFixedSize(300,830);
    OutermostVerticalLayout = new QVBoxLayout(this);
    this->setLayout(OutermostVerticalLayout);


    // Задаём область сдвига и растяжения углов

    AzimuthScaleAndOffsetGroupBox = new QGroupBox("Azimuth Scale And Offset",this);
    QLabel * AzimuthScaleLabel      = new QLabel("Scale", AzimuthScaleAndOffsetGroupBox);
    QLineEdit * AzimuthScaleEdit    = new QLineEdit("1", AzimuthScaleAndOffsetGroupBox);
    QLabel * AzimuthOffsetLabel     = new QLabel("Offset", AzimuthScaleAndOffsetGroupBox);
    QLineEdit * AzimuthOffsetEdit   = new QLineEdit("0", AzimuthScaleAndOffsetGroupBox);

    QGridLayout * AzimuthGridLayout = new QGridLayout(AzimuthScaleAndOffsetGroupBox);
    AzimuthGridLayout->addWidget(AzimuthScaleLabel  ,0,0);
    AzimuthGridLayout->addWidget(AzimuthScaleEdit   ,0,1);
    AzimuthGridLayout->addWidget(AzimuthOffsetLabel ,1,0);
    AzimuthGridLayout->addWidget(AzimuthOffsetEdit  ,1,1);
    AzimuthScaleAndOffsetGroupBox->setLayout(AzimuthGridLayout);
    OutermostVerticalLayout->addWidget(AzimuthScaleAndOffsetGroupBox);

    // Задаём AnglesGroupBox -- область введения отображаемых углов измеренных данных
    InitiateAnglesGroupBox();
    OutermostVerticalLayout->addWidget(AnglesGroupBox);


    /* Нужно ли?
    // Задаём ResponseGroupBox -- область задания файла отклика. По умолчанию -- тот, в который было сохранено измерение
    InitiateResponseGroupBox();
    OutermostVerticalLayout->addWidget(ResponseGroupBox);
    */



    // Задаём BackgroundGroupBox -- область задания файла фона
    InitiateBackgroundGroupBox(); // Перенести весь функционал в TabOfTools
    OutermostVerticalLayout->addWidget(BackgroundGroupBox);

    // Задаём CalibrationGroupBox -- область задания файла калибровки
    //InitiateCalibrationGroupBox(); // Перенести весь функционал в TabOfTools
    //OutermostVerticalLayout->addWidget(CalibrationGroupBox);


    //CalculateDistancePortraitButton = new QPushButton( "Дальностный портрет" , this );
    //OutermostVerticalLayout->addWidget(CalculateDistancePortraitButton);


}



void ResultParametersWidget::FindBackground ()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл фона", QDir::homePath(), "All Files (*.*)");
    if (!fileName.isEmpty())
    {
        BackgroundLineEdit->setText(fileName);
        QFileInfo FileInfo(fileName);
        BackgroundLineEdit->setToolTip(FileInfo.baseName());
    }

}


/*
void ResultParametersWidget::FindCalibration()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл калибровки", QDir::homePath(), "All Files (*.*)");
    if (!fileName.isEmpty())
    {
        CalibrationLineEdit->setText(fileName);
        QFileInfo FileInfo(fileName);
        CalibrationLineEdit->setToolTip(FileInfo.baseName());
    }
}
*/




void ResultParametersWidget::HandleAzimuthSpinBoxChange() // Переделать получше. Новый класс? Округление значений при окончании ввода? Или при нажатии кнопки enter?
{
    double AzimuthValue = this->SetCurrentAzimuthDoubleSpinBox->value();
    int ClosestIndex = std::round((AzimuthValue - AzimuthStart)/(AzimuthStop-AzimuthStart)*(AzimuthNumber-1));
    double RoundedValue = AzimuthStart + double(ClosestIndex) * ((AzimuthStop-AzimuthStart))/ (AzimuthNumber-1);
    this->SetCurrentAzimuthDoubleSpinBox->setValue(RoundedValue);
    //emit AzimuthOrElevationChanged();
}


void ResultParametersWidget::HandleElevationSpinBoxChange()
{
    double ElevationValue = this->SetCurrentElevationDoubleSpinBox->value();
    int ClosestIndex = std::round((ElevationValue - ElevationStart)/(ElevationStop-ElevationStart)*(ElevationNumber-1));
    double RoundedValue = ElevationStart + double(ClosestIndex) * ((ElevationStop-ElevationStart))/ (ElevationNumber-1);
    this->SetCurrentElevationDoubleSpinBox->setValue(RoundedValue);
}


void ResultParametersWidget::HandleFrequencySpinBoxChange()
{
    double FrequencyValue = this->SetCurrentFrequencyDoubleSpinBox->value();
    int ClosestIndex = std::round((FrequencyValue - FrequencyStart)/(FrequencyStop-FrequencyStart)*(FrequencyNumber-1));
    double RoundedValue = FrequencyStart + double(ClosestIndex) * ((FrequencyStop-FrequencyStart))/ (FrequencyNumber-1);
    this->SetCurrentFrequencyDoubleSpinBox->setValue(RoundedValue);
}







void ResultParametersWidget::InitiateAnglesGroupBox()
{
    AnglesGroupBox = new QGroupBox("Show Azimuth, Elevation, Frequency", this);

    AnglesGroupBoxLayout = new QGridLayout(AnglesGroupBox);

    SetCurrentAzimuthLabel = new QLabel("Azimuth:", this);
    SetCurrentAzimuthDoubleSpinBox = new QDoubleSpinBox(this);
    SetCurrentAzimuthDoubleSpinBox->setRange(AzimuthStart, AzimuthStop);
    SetCurrentAzimuthDoubleSpinBox->setSingleStep((AzimuthStop - AzimuthStart)/(AzimuthNumber-1));
    SetCurrentAzimuthDoubleSpinBox->setDecimals(3);

    ////connect(SetCurrentAzimuthDoubleSpinBox, &QDoubleSpinBox::editingFinished, this, &ResultParametersWidget::HandleAzimuthSpinBoxChange);


    SetCurrentElevationLabel = new QLabel("Elevation:", this);
    SetCurrentElevationDoubleSpinBox  = new QDoubleSpinBox(this);
    SetCurrentElevationDoubleSpinBox->setRange(ElevationStart, ElevationStop);
    SetCurrentElevationDoubleSpinBox->setSingleStep((ElevationStop - ElevationStart)/(ElevationNumber-1));
    SetCurrentElevationDoubleSpinBox->setDecimals(3);

    //connect(SetCurrentElevationDoubleSpinBox, &QDoubleSpinBox::editingFinished, this, &ResultParametersWidget::HandleElevationSpinBoxChange);

    SetCurrentFrequencyLabel = new QLabel("Frequency:", this);
    SetCurrentFrequencyDoubleSpinBox  = new QDoubleSpinBox(this);
    SetCurrentFrequencyDoubleSpinBox->setRange(FrequencyStart, FrequencyStop);
    SetCurrentFrequencyDoubleSpinBox->setSingleStep((FrequencyStop - FrequencyStart)/(FrequencyNumber-1));
    SetCurrentFrequencyDoubleSpinBox->setDecimals(3);


    //connect(SetCurrentFrequencyDoubleSpinBox, &QDoubleSpinBox::editingFinished, this, &ResultParametersWidget::HandleFrequencySpinBoxChange);


    //SetCurrentAngleButton= new QPushButton("Применить", this);

    AnglesGroupBox->setLayout(AnglesGroupBoxLayout);

    AnglesGroupBoxLayout ->addWidget(SetCurrentAzimuthLabel,  0,0);
    AnglesGroupBoxLayout ->addWidget(SetCurrentAzimuthDoubleSpinBox,   0,1);

    AnglesGroupBoxLayout ->addWidget(SetCurrentElevationLabel,  1,0);
    AnglesGroupBoxLayout ->addWidget(SetCurrentElevationDoubleSpinBox,   1,1);

    AnglesGroupBoxLayout ->addWidget(SetCurrentElevationLabel,  2,0);
    AnglesGroupBoxLayout ->addWidget(SetCurrentElevationDoubleSpinBox,   2,1);

    AnglesGroupBoxLayout ->addWidget(SetCurrentFrequencyLabel,  3,0);
    AnglesGroupBoxLayout ->addWidget(SetCurrentFrequencyDoubleSpinBox,   3,1);


    //AnglesGroupBoxLayout ->addWidget(SetCurrentAngleButton,  2,0,1,2);
}



void ResultParametersWidget::InitiateBackgroundGroupBox()
{
    BackgroundGroupBox = new QGroupBox("Фон (Бэкграунд)", this);

    QVBoxLayout * BackgroundGroupBoxLayout = new QVBoxLayout(BackgroundGroupBox);
    QHBoxLayout * BackgroundButtonsLayout = new QHBoxLayout;

    BackgroundLineEdit = new QLineEdit(BackgroundGroupBox);
    BackgroundFindButton = new QPushButton("Найти", BackgroundGroupBox);
    //connect(BackgroundFindButton, &QPushButton::clicked, this, &ResultParametersWidget::FindBackground);
    BackgroundAddButton  = new QPushButton("Добавить", BackgroundGroupBox);
    ////connect(BackgroundAddButton, &QPushButton::clicked, this, &ResultParametersWidget::AddBackground); //Теперь в MainWindow
    BackgroundSubstractButton  = new QPushButton("Вычесть", BackgroundGroupBox);
    ////connect(BackgroundSubstractButton, &QPushButton::clicked, this, &ResultParametersWidget::SubstractBackground); //Теперь в MainWindow


    BackgroundGroupBox->setLayout(BackgroundGroupBoxLayout);

    BackgroundGroupBoxLayout->addWidget(BackgroundLineEdit);

    BackgroundButtonsLayout -> addWidget(BackgroundFindButton);
    BackgroundButtonsLayout -> addWidget(BackgroundAddButton);
    BackgroundButtonsLayout -> addWidget(BackgroundSubstractButton);

    BackgroundGroupBoxLayout->addLayout(BackgroundButtonsLayout);
}





void ResultParametersWidget::FileChosenInTreeWidget(int Mode, QString FileName)
{
    switch (Mode)
    {
    case 0: //Response
        qDebug()<<"Response was chosen";
        break;

    case 1: //Background
        BackgroundLineEdit->setText(FileName);
        break;

    //case 2: //Calibration
        //CalibrationLineEdit->setText(FileName);
        //break;

    default:
        qDebug() << "Invalid mode";
        break;
    }
}









/* Нужно ли?
void ResultParametersWidget::InitiateResponseGroupBox()
{

    ResponseGroupBox = new QGroupBox(this);
    QVBoxLayout * ResponseLayout = new QVBoxLayout(ResponseGroupBox);
    ResponseLineEdit = new QLineEdit(ResponseGroupBox);
    ResponseFindButton = new QPushButton("Установить", ResponseGroupBox);

    ResponseGroupBox->setLayout(ResponseLayout);

    ResponseLayout->addWidget(ResponseLineEdit  );
    ResponseLayout->addWidget(ResponseFindButton);

}
*/


