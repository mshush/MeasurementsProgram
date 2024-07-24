#include "tabwidgetfortools.h"

TabWidgetForTools::TabWidgetForTools()

{

    Tab1 = new QWidget;
    //QLabel * ExplanationLabel = new QLabel("Место для Инструментов: запуск и приостановка измерений будут здесь, а не выше в меню, так как нужно часто(я полагаю)\nТакже здесь можно в Обработке разместить переключение на дальностный портрет и работу с ним");
    QHBoxLayout * Tab1Layout = new QHBoxLayout;
    //ExplanationLabel->setWordWrap(true);


    QPushButton * StartMeasurementsButton = new QPushButton();
    StartMeasurementsButton->setIcon(QIcon("C://Users/HP/Documents/MeasurementsProgram/startbuttonicon.png"));
    //StartMeasurementsButton->setIcon(QIcon(QIcon::fromTheme(QStyle::SP_MediaPlay)));//

    Tab1Layout->addWidget(StartMeasurementsButton);
    StartMeasurementsButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    StartMeasurementsButton->setIconSize(QSize(40, 40));

    QPushButton * StopMeasurementsButton = new QPushButton();
    StopMeasurementsButton->setIcon(QIcon("C://Users/HP/Documents/MeasurementsProgram/stopbuttonicon.png"));
    Tab1Layout->addWidget(StopMeasurementsButton);
    StopMeasurementsButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    StopMeasurementsButton->setIconSize(QSize(40, 40));


    Tab1Layout->setAlignment(Qt::AlignLeft);

    //Tab1Layout->addWidget(ExplanationLabel);
    Tab1->setLayout(Tab1Layout);
    Tab2 = new QWidget;


    addTab(Tab1, "Запуск");
    addTab(Tab2, "Управление");



    //resize(800,200);
    //setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}
