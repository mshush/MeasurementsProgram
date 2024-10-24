#include "tabwidgetfortools.h"

TabWidgetForTools::TabWidgetForTools()

{
    this->adjustSize();
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    this->setFixedHeight(300);
    //this->adjustSize();


    PatternTab = new QWidget(this);
    MessagesTab = new QWidget(this);
    LegendTab = new QWidget(this);
    File_ManagerTab = new TreeWidgetForFiles(this);
    Debug_MessagesTab = new QTableWidget(this);



    addTab(PatternTab,       "Pattern");
    addTab(MessagesTab,      "Messages");
    addTab(LegendTab,        "Legend");
    addTab(File_ManagerTab,  "File_Manager");
    addTab(Debug_MessagesTab,"Debug_Messages");

    /*
    Debug_MessagesTab->setColumnCount(3);
    Debug_MessagesTab->setHorizontalHeaderLabels({"Время", "Отправитель", "Сообшение"});
    Debug_MessagesTab->horizontalHeader()->setStretchLastSection(true);

    */


    /*
    QHBoxLayout * Tab1Layout = new QHBoxLayout(PatternTab); // Переименовать



    StartMeasurementsButton = new QPushButton("►",this);
    //StartMeasurementsButton->setIcon(QIcon("C://Users/HP/Documents/MeasurementsProgram/startbuttonicon.png"));
    StartMeasurementsButton->setFont(QFont("Arial", 30, QFont::Bold));
    StartMeasurementsButton->setStyleSheet("QPushButton { color: green; padding-top: 0px; padding-bottom: 0px; }");
    StartMeasurementsButton->resize(30,30);
    StartMeasurementsButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    StartMeasurementsButton->setToolTip("Запустить измерение");
    Tab1Layout->addWidget(StartMeasurementsButton);

    StopMeasurementsButton = new QPushButton("🟥",this); //■🟥
    //StopMeasurementsButton->setIcon(QIcon("C://Users/HP/Documents/MeasurementsProgram/stopbuttonicon.png"));
    StopMeasurementsButton->setFont(QFont("Arial", 20, QFont::Bold));
    StopMeasurementsButton->setStyleSheet("QPushButton { color: red; padding-top: 0px; padding-bottom: 5px; padding-left: 5px; padding-right: 5px; }");
    StopMeasurementsButton->resize(30,30);
    StopMeasurementsButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    StopMeasurementsButton->setToolTip("Приостановить измерение");
    Tab1Layout->addWidget(StopMeasurementsButton);


    ContinuousMeasurementsButton = new QPushButton("Непрерывный режим",this);
    //ContinuousMeasurementsButton->setFont(QFont("Arial", 30, QFont::Bold));
    //ContinuousMeasurementsButton->setStyleSheet("QPushButton { color: blue; padding-top: 0px; padding-bottom: 0px; padding-left: 5px; padding-right: 5px; }");
    //ContinuousMeasurementsButton->resize(30,30);
    ContinuousMeasurementsButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ContinuousMeasurementsButton->setCheckable(true);
    Tab1Layout->addWidget(ContinuousMeasurementsButton);

    connect(ContinuousMeasurementsButton,&QPushButton::clicked,this,&TabWidgetForTools::SendContinuousMeasurementsButtonClickedSignal);
    */




/////////////////////////////////////////

    /*
    SaveDataButton = new QPushButton("⇩",this); //⤓⇩
    SaveDataButton->setFont(QFont("Arial", 30, QFont::Bold));
    SaveDataButton->setStyleSheet("QPushButton { color: orange; padding-top: 0px; padding-bottom: 0px; padding-left: 5px; padding-right: 5px; }");
    SaveDataButton->resize(30,30);
    SaveDataButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    Tab1Layout->addWidget(SaveDataButton);


    ImportDataButton = new QPushButton("⇧",this); //⇧
    ImportDataButton->setFont(QFont("Arial", 30, QFont::Bold));
    ImportDataButton->setStyleSheet("QPushButton { color: orange; padding-top: 0px; padding-bottom: 0px; padding-left: 5px; padding-right: 5px; }");
    ImportDataButton->resize(30,30);
    ImportDataButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    Tab1Layout->addWidget(ImportDataButton);
    */

    /*
    FourierTransformButton = new QPushButton("F",this);
    FourierTransformButton->resize(30,30);
    Tab1Layout->addWidget(FourierTransformButton);

    InverseFourierTransformButton = new QPushButton ("InvF",this);
    InverseFourierTransformButton->resize(30,30);
    Tab1Layout->addWidget(InverseFourierTransformButton);
    */
////////////////////////////////////////
    /*
    SaveThreeDimensionalVectorButton = new QPushButton("Сохранить результат измерения",this);
    Tab1Layout->addWidget(SaveThreeDimensionalVectorButton);


    GetPlotDataButton = new QPushButton("Загрузить график", this);
    Tab1Layout->addWidget(GetPlotDataButton);


    Tab1Layout->setAlignment(Qt::AlignLeft);

    PatternTab->setLayout(Tab1Layout);
    //Tab1Layout->addWidget(ExplanationLabel);
    //Tab1->setLayout(Tab1Layout);
    //Tab2 = new QWidget;


    //addTab(Tab1, "Запуск");
    //addTab(Tab2, "Управление");

    //resize(800,200);
    //setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    */
}


void TabWidgetForTools::SendContinuousMeasurementsButtonClickedSignal()
{
    emit ContinuousMeasurementsButtonClickedSignal(ContinuousMeasurementsButton->isChecked());
}



TabWidgetForTools::~TabWidgetForTools()
{
    /*
    delete StartMeasurementsButton;
    delete StopMeasurementsButton;
    delete ContinuousMeasurementsButton;
    delete SaveDataButton;
    delete ImportDataButton;
    delete Tab1;
    delete Tab2;
    */
}


void TabWidgetForTools::DisplayError(QString ErrorText)
{
    int NumberOfRows = Debug_MessagesTab->rowCount();
    Debug_MessagesTab->insertRow(NumberOfRows);
    Debug_MessagesTab->setItem(NumberOfRows, 0, new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")));
    QStringList ListOf2Items = ErrorText.split(":", Qt::SkipEmptyParts);
    QString type = ListOf2Items.size() > 0 ? ListOf2Items[0].trimmed() : "Не известен";
    QString message = ListOf2Items.size() > 1 ? ListOf2Items[1].trimmed() : "Нет сообщения";
    Debug_MessagesTab->setItem(NumberOfRows, 1, new QTableWidgetItem(type));
    Debug_MessagesTab->setItem(NumberOfRows, 2, new QTableWidgetItem(message));
}




