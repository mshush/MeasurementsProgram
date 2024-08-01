#include "tabwidgetfortools.h"

TabWidgetForTools::TabWidgetForTools()

{

    Tab1 = new QWidget;
    //QLabel * ExplanationLabel = new QLabel("Место для Инструментов: запуск и приостановка измерений будут здесь, а не выше в меню, так как нужно часто(я полагаю)\nТакже здесь можно в Обработке разместить переключение на дальностный портрет и работу с ним");
    QHBoxLayout * Tab1Layout = new QHBoxLayout;
    //ExplanationLabel->setWordWrap(true);



    StartMeasurementsButton = new QPushButton("►");
    //StartMeasurementsButton->setIcon(QIcon("C://Users/HP/Documents/MeasurementsProgram/startbuttonicon.png"));
    StartMeasurementsButton->setFont(QFont("Arial", 30, QFont::Bold));
    StartMeasurementsButton->setStyleSheet("QPushButton { color: green; padding-top: 0px; padding-bottom: 0px; }");
    StartMeasurementsButton->resize(30,30);
    StartMeasurementsButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    Tab1Layout->addWidget(StartMeasurementsButton);

    StopMeasurementsButton = new QPushButton("🟥"); //■🟥
    //StopMeasurementsButton->setIcon(QIcon("C://Users/HP/Documents/MeasurementsProgram/stopbuttonicon.png"));
    StopMeasurementsButton->setFont(QFont("Arial", 20, QFont::Bold));
    StopMeasurementsButton->setStyleSheet("QPushButton { color: red; padding-top: 0px; padding-bottom: 5px; padding-left: 5px; padding-right: 5px; }");
    StopMeasurementsButton->resize(30,30);
    StopMeasurementsButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    Tab1Layout->addWidget(StopMeasurementsButton);


    ContinuousMeasurementsButton = new QPushButton("∞");
    ContinuousMeasurementsButton->setFont(QFont("Arial", 30, QFont::Bold));
    ContinuousMeasurementsButton->setStyleSheet("QPushButton { color: blue; padding-top: 0px; padding-bottom: 0px; padding-left: 5px; padding-right: 5px; }");
    ContinuousMeasurementsButton->resize(30,30);
    ContinuousMeasurementsButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ContinuousMeasurementsButton->setCheckable(true);
    Tab1Layout->addWidget(ContinuousMeasurementsButton);

    SaveDataButton = new QPushButton("⇩"); //⤓⇩
    SaveDataButton->setFont(QFont("Arial", 30, QFont::Bold));
    SaveDataButton->setStyleSheet("QPushButton { color: orange; padding-top: 0px; padding-bottom: 0px; padding-left: 5px; padding-right: 5px; }");
    SaveDataButton->resize(30,30);
    SaveDataButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    Tab1Layout->addWidget(SaveDataButton);

    ImportDataButton = new QPushButton("⇧"); //⇧
    ImportDataButton->setFont(QFont("Arial", 30, QFont::Bold));
    ImportDataButton->setStyleSheet("QPushButton { color: orange; padding-top: 0px; padding-bottom: 0px; padding-left: 5px; padding-right: 5px; }");
    ImportDataButton->resize(30,30);
    ImportDataButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    Tab1Layout->addWidget(ImportDataButton);


    Tab1Layout->setAlignment(Qt::AlignLeft);

    //Tab1Layout->addWidget(ExplanationLabel);
    Tab1->setLayout(Tab1Layout);
    Tab2 = new QWidget;


    addTab(Tab1, "Запуск");
    addTab(Tab2, "Управление");


    //resize(800,200);
    //setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}
