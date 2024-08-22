#include "resultparameterswidget.h"

ResultParametersWidget::ResultParametersWidget(QWidget *parent)
    : QWidget{parent}
{
    //IntValidator = new QIntValidator(this);


    OutermostVerticalLayout = new QVBoxLayout(this);


    // AnglesGroupBox -- область введения отображаемых углов измеренных данных

    AnglesGroupBox = new QGroupBox("Углы наклона и поворота", this);

    AnglesGroupBoxLayout = new QGridLayout(AnglesGroupBox);

    SetCurrentRotationAngleLabel = new QLabel("Поворот:", this);

    SetCurrentRotationAngleDoubleSpinBox = new QDoubleSpinBox(this);

    SetCurrentRotationAngleDoubleSpinBox->setRange(RotationStart, RotationStop);
    SetCurrentRotationAngleDoubleSpinBox->setSingleStep((RotationStop - RotationStart)/(RotationNumber-1));
    SetCurrentRotationAngleDoubleSpinBox->setDecimals(3);

    connect(SetCurrentRotationAngleDoubleSpinBox, &QDoubleSpinBox::editingFinished, this, &ResultParametersWidget::HandleRotationSpinBoxChange);


    SetCurrentTiltAngleLabel = new QLabel("Наклон:", this);
    SetCurrentTiltAngleDoubleSpinBox  = new QDoubleSpinBox(this);
    SetCurrentTiltAngleDoubleSpinBox->setRange(TiltStart, TiltStop);
    SetCurrentTiltAngleDoubleSpinBox->setSingleStep((TiltStop - TiltStart)/(TiltNumber-1));
    SetCurrentTiltAngleDoubleSpinBox->setDecimals(3);


    connect(SetCurrentTiltAngleDoubleSpinBox, &QDoubleSpinBox::editingFinished, this, &ResultParametersWidget::HandleTiltSpinBoxChange);


    SetCurrentAngleButton= new QPushButton("Применить", this);

    this->setLayout(OutermostVerticalLayout);
    OutermostVerticalLayout->addWidget(AnglesGroupBox);
    AnglesGroupBox->setLayout(AnglesGroupBoxLayout);

    AnglesGroupBoxLayout ->addWidget(SetCurrentRotationAngleLabel,  0,0);
    AnglesGroupBoxLayout ->addWidget(SetCurrentRotationAngleDoubleSpinBox,   0,1);

    AnglesGroupBoxLayout ->addWidget(SetCurrentTiltAngleLabel,  1,0);
    AnglesGroupBoxLayout ->addWidget(SetCurrentTiltAngleDoubleSpinBox,   1,1);

    AnglesGroupBoxLayout ->addWidget(SetCurrentAngleButton,  2,0,1,2);


    // Задаём BackgroundGroupBox
    BackgroundGroupBox = new QGroupBox("Фон (Бэкграунд)", this);

    QVBoxLayout * BackgroundGroupBoxLayout = new QVBoxLayout(BackgroundGroupBox);
    QHBoxLayout * BackgroundButtonsLayout = new QHBoxLayout;

    //QLabel * BackgroundLabel = new QLabel("Фон", BackgroundGroupBox);

    BackgroundLineEdit = new QLineEdit(BackgroundGroupBox);
    BackgroundFindButton = new QPushButton("Найти", BackgroundGroupBox);
    connect(BackgroundFindButton, &QPushButton::clicked, this, &ResultParametersWidget::FindBackground);
    BackgroundAddButton  = new QPushButton("Добавить", BackgroundGroupBox);
    //connect(BackgroundAddButton, &QPushButton::clicked, this, &ResultParametersWidget::AddBackground);
    BackgroundSubstractButton  = new QPushButton("Вычесть", BackgroundGroupBox);
    //connect(BackgroundSubstractButton, &QPushButton::clicked, this, &ResultParametersWidget::SubstractBackground);


    BackgroundGroupBox->setLayout(BackgroundGroupBoxLayout);

    BackgroundGroupBoxLayout->addWidget(BackgroundLineEdit);

    BackgroundButtonsLayout -> addWidget(BackgroundFindButton);
    BackgroundButtonsLayout -> addWidget(BackgroundAddButton);
    BackgroundButtonsLayout -> addWidget(BackgroundSubstractButton);

    BackgroundGroupBoxLayout->addLayout(BackgroundButtonsLayout);
    OutermostVerticalLayout->addWidget(BackgroundGroupBox);

    // Задаём CalibrationGroupBox
    CalibrationGroupBox = new QGroupBox("Калибровка", this);

    QVBoxLayout * CalibrationGroupBoxLayout = new QVBoxLayout(CalibrationGroupBox);
    QHBoxLayout * CalibrationButtonsLayout = new QHBoxLayout;

    //QLabel * CalibrationLabel = new QLabel("Калибровка", BackgroundAndCalibrationGroupBox);

    CalibrationLineEdit = new QLineEdit(CalibrationGroupBox);
    CalibrationFindButton = new QPushButton("Найти", CalibrationGroupBox);
    connect(CalibrationFindButton, &QPushButton::clicked, this, &ResultParametersWidget::FindCalibration);
    CalibrationSetButton  = new QPushButton("Установить", CalibrationGroupBox);
    //connect(CalibrationSetButton, &QPushButton::clicked, this, &ResultParametersWidget::SetCalibration);

    CalibrationGroupBox->setLayout(CalibrationGroupBoxLayout);

    CalibrationGroupBoxLayout->addWidget(CalibrationLineEdit);

    CalibrationButtonsLayout -> addWidget(CalibrationFindButton);
    CalibrationButtonsLayout -> addWidget(CalibrationSetButton);

    CalibrationGroupBoxLayout->addLayout(CalibrationButtonsLayout);

    OutermostVerticalLayout->addWidget(CalibrationGroupBox);

    /*
    BackgroundAndCalibrationGroupBoxLayout->addWidget(BackgroundLabel       ,0,0);
    BackgroundAndCalibrationGroupBoxLayout->addWidget(BackgroundLineEdit    ,1,0);
    BackgroundAndCalibrationGroupBoxLayout->addWidget(BackgroundFindButton  ,0,1);
    BackgroundAndCalibrationGroupBoxLayout->addWidget(BackgroundSetButton   ,1,1);

    BackgroundAndCalibrationGroupBoxLayout->addWidget(CalibrationLabel      ,2,0);
    BackgroundAndCalibrationGroupBoxLayout->addWidget(CalibrationLineEdit   ,3,0);
    BackgroundAndCalibrationGroupBoxLayout->addWidget(CalibrationFindButton ,2,1);
    BackgroundAndCalibrationGroupBoxLayout->addWidget(CalibrationSetButton  ,3,1);

    BackgroundAndCalibrationGroupBox->setLayout(BackgroundAndCalibrationGroupBoxLayout);
    */

}



void ResultParametersWidget::FindBackground ()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл фона", QDir::homePath(), "All Files (*.*)");
    if (!fileName.isEmpty())
    {
        BackgroundLineEdit->setText(fileName);
    }
}




void ResultParametersWidget::FindCalibration()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл калибровки", QDir::homePath(), "All Files (*.*)");
    if (!fileName.isEmpty())
    {
        CalibrationLineEdit->setText(fileName);
    }
}





void ResultParametersWidget::HandleRotationSpinBoxChange() // Переделать получше. Новый класс? Округление значений при окончании ввода? Или при нажатии кнопки enter?
{
    double RotationValue = this->SetCurrentRotationAngleDoubleSpinBox->value();
    int ClosestIndex = std::round((RotationValue - RotationStart)/(RotationStop-RotationStart)*(RotationNumber-1));
    double RoundedValue = RotationStart + double(ClosestIndex) * ((RotationStop-RotationStart))/ (RotationNumber-1);
    this->SetCurrentRotationAngleDoubleSpinBox->setValue(RoundedValue);
    //emit RotationOrTiltChanged();
}


void ResultParametersWidget::HandleTiltSpinBoxChange()
{
    double TiltValue = this->SetCurrentTiltAngleDoubleSpinBox->value();
    int ClosestIndex = std::round((TiltValue - TiltStart)/(TiltStop-TiltStart)*(TiltNumber-1));
    double RoundedValue = TiltStart + double(ClosestIndex) * ((TiltStop-TiltStart))/ (TiltNumber-1);
    this->SetCurrentTiltAngleDoubleSpinBox->setValue(RoundedValue);
}















