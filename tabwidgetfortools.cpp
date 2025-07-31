#include "tabwidgetfortools.h"

TabWidgetForTools::TabWidgetForTools()
{

    //this->adjustSize();
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);


    PatternTab = new WidgetForCustomPlot(this);
    PatternTab->setMaximumHeight(300);
    PatternTab->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    //setContentsMarginsToZero(PatternTab);
    //PatternTab->ControlsWidget->setContentsMargins(QMargins(0,0,0,0));
    //PatternTab->VerticalControlsLayout->setContentsMargins(QMargins(0,0,0,0));
    //PatternTab->SetRangeVerticalLayout->setContentsMargins(QMargins(0,0,0,0));
    PatternTab->customPlot->xAxis->setLabel("Az, deg");
    //PatternTab->MarkerFrame->setVisible(false);
    MessagesTab = new QTreeWidget(this);
    LegendTab = new LegendWidget(this);
    ScriptTab = new QWidget(this);
    File_ManagerTab = new TreeWidgetForFiles(this);
    DebugMessagesTab = new QTreeWidget(this);







    addTab(PatternTab,       "Pattern");
    addTab(MessagesTab,      "Messages");
    addTab(LegendTab,        "Legend");
    addTab(ScriptTab,        "Script");
    addTab(File_ManagerTab,  "File_Manager");
    addTab(DebugMessagesTab, "Debug_Messages");



    MessagesTab->setColumnCount(1); // Set the number of columns
    MessagesTab->setHeaderLabel("Messages"); // Set the header label

    // Create root item
    QTreeWidgetItem *rootItem = new QTreeWidgetItem(MessagesTab, QStringList() << "Legend Item");

    // Create child items
    QTreeWidgetItem *childItem1 = new QTreeWidgetItem(rootItem, QStringList() << "Item 1");
    QTreeWidgetItem *childItem2 = new QTreeWidgetItem(rootItem, QStringList() << "Item 2");

    // Create sub-child item
    QTreeWidgetItem *subChildItem = new QTreeWidgetItem(childItem1, QStringList() << "Item3");

    // Expand the root item to show children
    rootItem->setExpanded(true);


    FillDebugMessagesTab();



    // Create root item
    QTreeWidgetItem *rootItem1 = new QTreeWidgetItem(MessagesTab, QStringList() << "Legend Item");

    // Create child items
    QTreeWidgetItem *childItem11 = new QTreeWidgetItem(rootItem1, QStringList() << "Item 1");
    QTreeWidgetItem *childItem21 = new QTreeWidgetItem(rootItem1, QStringList() << "Item 2");

    // Create sub-child item
    QTreeWidgetItem *subChildItem1 = new QTreeWidgetItem(childItem11, QStringList() << "Item3");

    // Expand the root item to show children
    rootItem1->setExpanded(true);

    /*
    DebugMessagesTab->setColumnCount(3);
    DebugMessagesTab->setHorizontalHeaderLabels({"Время", "Отправитель", "Сообшение"});
    DebugMessagesTab->horizontalHeader()->setStretchLastSection(true);

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

    ////connect(ContinuousMeasurementsButton,&QPushButton::clicked,this,&TabWidgetForTools::SendContinuousMeasurementsButtonClickedSignal);
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




    //this->adjustSize();

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
    /*
    int NumberOfRows = DebugMessagesTab->rowCount();
    DebugMessagesTab->insertRow(NumberOfRows);
    DebugMessagesTab->setItem(NumberOfRows, 0, new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")));
    QStringList ListOf2Items = ErrorText.split(":", Qt::SkipEmptyParts);
    QString type = ListOf2Items.size() > 0 ? ListOf2Items[0].trimmed() : "Не известен";
    QString message = ListOf2Items.size() > 1 ? ListOf2Items[1].trimmed() : "Нет сообщения";
    DebugMessagesTab->setItem(NumberOfRows, 1, new QTableWidgetItem(type));
    DebugMessagesTab->setItem(NumberOfRows, 2, new QTableWidgetItem(message));
*/
}

void TabWidgetForTools::setContentsMarginsToZero(QWidget *widget)
{
    /*
    widget->setContentsMargins(0, 0, 0, 0);
    widget->layout()->setContentsMargins(0, 0, 0, 0);

    for (QObject *child : widget->children())
    {
        if (QWidget *childWidget = qobject_cast<QWidget *>(child))
        {
            setContentsMarginsToZero(childWidget);
            qDebug()<<child;
        }
    }
    */
}

void TabWidgetForTools :: FillDebugMessagesTab()
{

    DebugMessagesTab->setColumnCount(1);
    QTreeWidgetItem * Error1 = new QTreeWidgetItem(DebugMessagesTab);
    Error1->setText(0,"Error1");
    DebugMessagesTab->addTopLevelItem(Error1);

    DebugMessagesTab->setHeaderLabel("Errors");



}


