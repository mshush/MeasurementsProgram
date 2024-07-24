#include "tabwidgetfortools.h"

TabWidgetForTools::TabWidgetForTools()

{

    Tab1 = new QWidget;
    //QLabel * ExplanationLabel = new QLabel("Место для Инструментов: запуск и приостановка измерений будут здесь, а не выше в меню, так как нужно часто(я полагаю)\nТакже здесь можно в Обработке разместить переключение на дальностный портрет и работу с ним");
    QHBoxLayout * Tab1Layout = new QHBoxLayout;
    //ExplanationLabel->setWordWrap(true);



    QPushButton * StartMeasurementsButton = new QPushButton("►");
    //StartMeasurementsButton->setIcon(QIcon("C://Users/HP/Documents/MeasurementsProgram/startbuttonicon.png"));
    StartMeasurementsButton->setFont(QFont("Arial", 50, QFont::Bold));
    StartMeasurementsButton->setStyleSheet("QPushButton { color: green; padding-top: 0px; padding-bottom: 0px; }");
    StartMeasurementsButton->resize(50,50);
    StartMeasurementsButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    Tab1Layout->addWidget(StartMeasurementsButton);

    QPushButton * StopMeasurementsButton = new QPushButton("🟥"); //■🟥
    //StopMeasurementsButton->setIcon(QIcon("C://Users/HP/Documents/MeasurementsProgram/stopbuttonicon.png"));
    StopMeasurementsButton->setFont(QFont("Arial", 50, QFont::Bold));
    StopMeasurementsButton->setStyleSheet("QPushButton { color: red; padding-top: 0px; padding-bottom: 0px; padding-left: 5px; padding-right: 5px; }");
    StopMeasurementsButton->resize(50,50);
    StopMeasurementsButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    Tab1Layout->addWidget(StopMeasurementsButton);


    Tab1Layout->setAlignment(Qt::AlignLeft);

    //Tab1Layout->addWidget(ExplanationLabel);
    Tab1->setLayout(Tab1Layout);
    Tab2 = new QWidget;


    addTab(Tab1, "Запуск");
    addTab(Tab2, "Управление");



    //resize(800,200);
    //setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}
