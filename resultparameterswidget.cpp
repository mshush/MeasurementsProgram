#include "resultparameterswidget.h"

ResultParametersWidget::ResultParametersWidget(QWidget *parent)
    : QWidget{parent}
{

    OutermostVerticalLayout = new QVBoxLayout(this);

    AnglesGroupBox = new QGroupBox("Углы наклона и поворота", this);

    AnglesGroupBoxLayout = new QGridLayout(AnglesGroupBox);

    SetCurrentRotationAngleLabel = new QLabel("Поворот:", this);
    SetCurrentRotationAngleEdit  = new QLineEdit("", this);
    SetCurrentTiltAngleLabel = new QLabel("Наклон:", this);
    SetCurrentTiltAngleEdit  = new QLineEdit("", this);

    SetCurrentTiltAngleButton= new QPushButton("Ввод", this);

    this->setLayout(OutermostVerticalLayout);
    OutermostVerticalLayout->addWidget(AnglesGroupBox);
    AnglesGroupBox->setLayout(AnglesGroupBoxLayout);

    AnglesGroupBoxLayout ->addWidget(SetCurrentRotationAngleLabel,  0,0);
    AnglesGroupBoxLayout ->addWidget(SetCurrentRotationAngleEdit,   0,1);

    AnglesGroupBoxLayout ->addWidget(SetCurrentTiltAngleLabel,  1,0);
    AnglesGroupBoxLayout ->addWidget(SetCurrentTiltAngleEdit,   1,1);

}
