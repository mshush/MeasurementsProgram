#include "custommeasurementtreewidget.h"



CustomMeasurementTreeWidget::CustomMeasurementTreeWidget(QWidget * parent) : QTreeWidget(parent)
{

    QBrush brush(QColor(191, 205, 219));

    //this->setFixedWidth(280);
    //this->setFixedSize(280,810);
    //this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    setColumnCount(1);
    this->setHeaderHidden(true);

    setIndentation(0);
    //setHeaderLabels(QStringList() << "Parameter Groups");

    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Добавляем 9 элементов:

    Navigator = new QTableWidget(this);
    NavigatorItem = new QTreeWidgetItem(this);
    NavigatorItem->setBackground(0,brush);
    QTreeWidgetItem * NavigatorTableItem = new QTreeWidgetItem(NavigatorItem);
    NavigatorItem->setText(0,"Navigator");
    addTopLevelItem(NavigatorItem);
    setItemWidget(NavigatorTableItem, 0, Navigator);
    FillNavigator();



    Summary = new QTableWidget(this);
    SummaryItem = new QTreeWidgetItem(this);
    SummaryItem->setBackground(0,brush);
    QTreeWidgetItem * SummaryTableItem = new QTreeWidgetItem(SummaryItem);
    SummaryItem->setText(0,"Summary");
    addTopLevelItem(SummaryItem);
    setItemWidget(SummaryTableItem, 0, Summary);
    FillSummary();


    Configs = new QTableWidget(this);
    ConfigsItem = new QTreeWidgetItem(this);
    ConfigsItem->setBackground(0,brush);
    QTreeWidgetItem * ConfigsTableItem = new QTreeWidgetItem(ConfigsItem);
    ConfigsItem->setText(0,"Configs");
    //Configs->setContentsMargins(0,0,0,0);
    addTopLevelItem(ConfigsItem);
    setItemWidget(ConfigsTableItem, 0, Configs);
    FillConfigs();


    Files = new QTableWidget(this);
    FilesItem = new QTreeWidgetItem(this);
    FilesItem->setBackground(0,brush);
    QTreeWidgetItem * FilesTableItem = new QTreeWidgetItem(FilesItem);
    FilesItem->setText(0,"Files");
    addTopLevelItem(FilesItem);
    setItemWidget(FilesTableItem, 0, Files);
    FillFiles();


    FrequencyRange = new QTableWidget(this);
    FrequencyRangeItem = new QTreeWidgetItem(this);
    FrequencyRangeItem->setBackground(0,brush);
    QTreeWidgetItem * FrequencyRangeTableItem = new QTreeWidgetItem(FrequencyRangeItem);
    FrequencyRangeItem->setText(0,"FrequencyRange");
    addTopLevelItem(FrequencyRangeItem);
    setItemWidget(FrequencyRangeTableItem, 0, FrequencyRange);
    FillFrequencyRange();


    AzimuthRange = new QTableWidget(this);
    AzimuthRangeItem = new QTreeWidgetItem(this);
    AzimuthRangeItem->setBackground(0,brush);
    QTreeWidgetItem * AzimuthRangeTableItem = new QTreeWidgetItem(AzimuthRangeItem);
    AzimuthRangeItem->setText(0,"AzimuthRange");
    addTopLevelItem(AzimuthRangeItem);
    setItemWidget(AzimuthRangeTableItem, 0, AzimuthRange);
    FillAzimuthRange();


    Pre_ProcessingGate = new QTableWidget(this);
    Pre_ProcessingGateItem = new QTreeWidgetItem(this);
    Pre_ProcessingGateItem->setBackground(0,brush);
    QTreeWidgetItem * Pre_ProcessingGateTableItem = new QTreeWidgetItem(Pre_ProcessingGateItem);
    Pre_ProcessingGateItem->setText(0,"Pre_ProcessingGate");
    addTopLevelItem(Pre_ProcessingGateItem);
    setItemWidget(Pre_ProcessingGateTableItem, 0, Pre_ProcessingGate);
    FillPre_ProcessingGate();


    CalibrationTarget = new QTableWidget(this);
    CalibrationTargetItem = new QTreeWidgetItem(this);
    CalibrationTargetItem->setBackground(0,brush);
    QTreeWidgetItem * CalibrationTargetTableItem = new QTreeWidgetItem(CalibrationTargetItem);
    CalibrationTargetItem->setText(0,"CalibrationTarget");
    addTopLevelItem(CalibrationTargetItem);
    setItemWidget(CalibrationTargetTableItem, 0, CalibrationTarget);
    FillCalibrationTarget();


    PNA = new QTableWidget(this);
    PNAItem = new QTreeWidgetItem(this);
    PNAItem->setBackground(0,brush);
    QTreeWidgetItem * PNATableItem = new QTreeWidgetItem(PNAItem);
    PNAItem->setText(0,"PNA");
    addTopLevelItem(PNAItem);
    setItemWidget(PNATableItem, 0, PNA);
    FillPNA();


    connect(ConfigsRangeComboBox, &QComboBox::currentIndexChanged, this, &CustomMeasurementTreeWidget::FrequencyRangeChanged);

    this->ConfigsRangeComboBox->setCurrentIndex(1);

    this->expandAll();
}




void CustomMeasurementTreeWidget::FillNavigator()
{
    //Navigator->setFixedWidth(280);
    Navigator->setColumnCount(4);

    Navigator->verticalHeader()->setVisible(false);
    Navigator->horizontalHeader()->setVisible(false);
    //Navigator->setHorizontalHeaderLabels(QStringList() << "Parameter" << "Value");
    Navigator->horizontalHeader()->setStretchLastSection(true);
    Navigator->setEditTriggers(QAbstractItemView::SelectedClicked); // Изменение нажатием?

    Navigator->insertRow(0);
    Navigator->setItem(0, 0, new QTableWidgetItem("Az (deg)"));
    QLineEdit * NavigatorEdit = new QLineEdit("");
    Navigator->setCellWidget(0, 1, NavigatorEdit);
    Navigator->setCellWidget(0, 2, new QPushButton(""));
    Navigator->setCellWidget(0, 3, new QPushButton(""));
    QDoubleValidator * NavigatorValidator = new QDoubleValidator(0.0, 100.0, 2, NavigatorEdit);
    NavigatorValidator->setRange(0,100);
    NavigatorEdit->setValidator(NavigatorValidator);

    //connect (NavigatorEdit,&QLineEdit::editingFinished,this,[this](){qDebug()<<NavigatorValidator->State();})
    /*
    connect(NavigatorEdit, &QLineEdit::editingFinished, this, [this, NavigatorValidator, NavigatorEdit]() {
        QString text = NavigatorEdit->text();
        int pos = 0; // Position of the text cursor
        QValidator::State state = NavigatorValidator->validate(text, pos);
        qDebug() << state; // This will print the validation state
    });
    */

    Navigator->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    Navigator->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    Navigator->setMaximumHeight(25);
    Navigator->setColumnWidth(0, 80);
    Navigator->setColumnWidth(1, 30);
    Navigator->setColumnWidth(2, 30);
    Navigator->setColumnWidth(3, 30);



}



void CustomMeasurementTreeWidget::FillSummary()
{


    Summary->setColumnCount(2);

    Summary->verticalHeader()->setVisible(false);
    Summary->horizontalHeader()->setVisible(false);
    Summary->horizontalHeader()->setStretchLastSection(true);
    Summary->setEditTriggers(QAbstractItemView::SelectedClicked); // Изменение нажатием?



    Summary->insertRow(0);
    Summary->setItem(0, 0, new QTableWidgetItem("Title"));
    Summary->setCellWidget(0, 1, new QLineEdit("Iteration 5"));

    Summary->insertRow(1);
    Summary->setItem(1, 0, new QTableWidgetItem("Group"));
    Summary->setCellWidget(1, 1, new QLineEdit("Adjustment"));

    Summary->insertRow(2);
    Summary->setItem(2, 0, new QTableWidgetItem("Operator"));
    Summary->setCellWidget(2, 1, new QLineEdit("Mr. Operator"));


    Summary->insertRow(3);
    QLineEdit * Description = new QLineEdit();
    Description->setPlaceholderText("Description");
    Summary->setCellWidget(3, 0, Description);
    Summary->setSpan(3, 0, 1, 2);


    Summary->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    Summary->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    Summary->setMaximumHeight(150);
    Summary->setColumnWidth(0, 120);
    Summary->setColumnWidth(1, 120);
    Summary->setRowHeight(3, 60);

}



void CustomMeasurementTreeWidget::FillConfigs()
{


    Configs->setColumnCount(2);

    Configs->verticalHeader()->setVisible(false);
    Configs->horizontalHeader()->setVisible(false);
    Configs->horizontalHeader()->setStretchLastSection(true);
    Configs->setEditTriggers(QAbstractItemView::SelectedClicked); // Изменение нажатием?



    Configs->insertRow(0);
    Configs->setItem(0, 0, new QTableWidgetItem("Range"));
    Configs->horizontalHeader()->setStretchLastSection(true);
    ConfigsRangeComboBox = new QComboBox(this);
    ConfigsRangeComboBox->addItem("User");
    ConfigsRangeComboBox->addItem("S-Band");
    ConfigsRangeComboBox->addItem("C-Band");
    ConfigsRangeComboBox->addItem("C2-Band");
    ConfigsRangeComboBox->addItem("X-Band");
    ConfigsRangeComboBox->addItem("Ku-Band");
    ConfigsRangeComboBox->addItem("Ka-Band");
    Configs->setCellWidget(0, 1, ConfigsRangeComboBox);


    Configs->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    Configs->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    Configs->setMaximumHeight(30);
    Configs->setColumnWidth(0, 120);
    Configs->setColumnWidth(1, 120);
}








void CustomMeasurementTreeWidget::FillFiles()
{
    Files->setColumnCount(3);

    Files->verticalHeader()->setVisible(false);
    Files->horizontalHeader()->setVisible(false);
    Files->horizontalHeader()->setStretchLastSection(true);
    Files->setEditTriggers(QAbstractItemView::SelectedClicked); // Изменение нажатием?



    Files->insertRow(0);
    Files->setItem(0, 0, new QTableWidgetItem("Background"));
    Files->setCellWidget(0, 1, new QLineEdit("---"));
    Files->setCellWidget(0, 2, new QPushButton("Select"));

    Files->insertRow(1);
    Files->setItem(1, 0, new QTableWidgetItem("Calibration"));
    Files->setCellWidget(1, 1, new QLineEdit("---"));
    Files->setCellWidget(1, 2, new QPushButton("Select"));

    Files->insertRow(2);
    Files->setItem(2, 0, new QTableWidgetItem("Sketch"));
    Files->setCellWidget(2, 1, new QLineEdit("---"));
    Files->setCellWidget(2, 2, new QPushButton("Select"));

    Files->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    Files->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    Files->setMaximumHeight(90);
    Files->setColumnWidth(0, 100);
    Files->setColumnWidth(1, 100);
    Files->setColumnWidth(2, 40);
}



void CustomMeasurementTreeWidget::FillFrequencyRange()
{
    FrequencyRange->setColumnCount(2);

    FrequencyRange->verticalHeader()->setVisible(false);
    FrequencyRange->horizontalHeader()->setVisible(false);
    FrequencyRange->horizontalHeader()->setStretchLastSection(true);
    FrequencyRange->setEditTriggers(QAbstractItemView::SelectedClicked); // Изменение нажатием?


    FrequencyRange->insertRow(0);
    FrequencyRange->setItem(0, 0, new QTableWidgetItem("Center (GHz)"));
    FrequencyRangeCenterEdit = new QLineEdit("",this);
    FrequencyRange->setCellWidget(0, 1, FrequencyRangeCenterEdit);

    FrequencyRange->insertRow(1);
    FrequencyRange->setItem(1, 0, new QTableWidgetItem("Span (GHz)"));
    FrequencyRangeSpanEdit = new QLineEdit("",this);
    FrequencyRange->setCellWidget(1, 1, FrequencyRangeSpanEdit);


    FrequencyRange->insertRow(2);
    FrequencyRange->setItem(2, 0, new QTableWidgetItem("N"));
    FrequencyRangeNEdit = new QLineEdit("",this);
    FrequencyRange->setCellWidget(2, 1, FrequencyRangeNEdit);

    //FrequencyRange->insertRow(3);
    //FrequencyRange->setCellWidget(3, 0, new QPushButton("Center-Span"));
    //FrequencyRange->setCellWidget(3, 1, new QPushButton("Start-Stop"));


    FrequencyRange->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    FrequencyRange->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    FrequencyRange->setMaximumHeight(90);
    FrequencyRange->setColumnWidth(0, 120);
    FrequencyRange->setColumnWidth(1, 120);

}



void CustomMeasurementTreeWidget::FillAzimuthRange()
{
    AzimuthRange->setColumnCount(2);

    AzimuthRange->verticalHeader()->setVisible(false);
    AzimuthRange->horizontalHeader()->setVisible(false);
    AzimuthRange->horizontalHeader()->setStretchLastSection(true);
    AzimuthRange->setEditTriggers(QAbstractItemView::SelectedClicked); // Изменение нажатием?


    AzimuthRange->insertRow(0);
    AzimuthRange->setItem(0, 0, new QTableWidgetItem("Center (m)"));
    AzimuthRangeCenterEdit = new QLineEdit("1.5");
    AzimuthRange->setCellWidget(0, 1, AzimuthRangeCenterEdit);

    AzimuthRange->insertRow(1);
    AzimuthRange->setItem(1, 0, new QTableWidgetItem("Span (m)"));
    AzimuthRangeSpanEdit = new QLineEdit("0");
    AzimuthRange->setCellWidget(1, 1, AzimuthRangeSpanEdit);

    AzimuthRange->insertRow(2);
    AzimuthRange->setItem(2, 0, new QTableWidgetItem("N"));
    AzimuthRangeNEdit = new QLineEdit("101");
    AzimuthRange->setCellWidget(2, 1, AzimuthRangeNEdit);

    AzimuthRange->insertRow(3);
    AzimuthRange->setItem(3, 0, new QTableWidgetItem("Default N"));
    AzimuthRangeDefaultNCheckBox = new QCheckBox();
    AzimuthRange->setCellWidget(3, 1, AzimuthRangeDefaultNCheckBox);

    //AzimuthRange->insertRow(4);
    //AzimuthRange->setCellWidget(4, 0, new QPushButton("Center-Span"));
    //AzimuthRange->setCellWidget(4, 1, new QPushButton("Start-Stop"));

    AzimuthRange->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    AzimuthRange->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    AzimuthRange->setMaximumHeight(120);
    AzimuthRange->setColumnWidth(0, 120);
    AzimuthRange->setColumnWidth(1, 120);

}





void CustomMeasurementTreeWidget::FillPre_ProcessingGate()
{
    Pre_ProcessingGate->setColumnCount(2);

    Pre_ProcessingGate->verticalHeader()->setVisible(false);
    Pre_ProcessingGate->horizontalHeader()->setVisible(false);
    Pre_ProcessingGate->horizontalHeader()->setStretchLastSection(true);
    Pre_ProcessingGate->setEditTriggers(QAbstractItemView::SelectedClicked); // Изменение нажатием?


    Pre_ProcessingGate->insertRow(0);
    Pre_ProcessingGate->setItem(0, 0, new QTableWidgetItem("Start (m)"));
    Pre_ProcessingGateStartEdit = new QLineEdit("",this);
    Pre_ProcessingGate->setCellWidget(0, 1, Pre_ProcessingGateStartEdit);

    Pre_ProcessingGate->insertRow(1);
    Pre_ProcessingGate->setItem(1, 0, new QTableWidgetItem("Stop (m)"));
    Pre_ProcessingGateStopEdit  = new QLineEdit("",this);
    Pre_ProcessingGate->setCellWidget(1, 1, Pre_ProcessingGateStopEdit);

    Pre_ProcessingGate->insertRow(2);
    Pre_ProcessingGate->setItem(2, 0, new QTableWidgetItem("Shape"));
    Pre_ProcessingGateShapeBox = new QComboBox(this);
    Pre_ProcessingGateShapeBox->addItem("Minimal");
    Pre_ProcessingGateShapeBox->addItem("Normal");
    Pre_ProcessingGateShapeBox->addItem("Maximal");
    Pre_ProcessingGate->setCellWidget(2, 1, Pre_ProcessingGateShapeBox);

    //Pre_ProcessingGate->insertRow(3);
    //Pre_ProcessingGate->setCellWidget(3, 0, new QPushButton("Center-Span"));
    //Pre_ProcessingGate->setCellWidget(3, 1, new QPushButton("Start-Stop"));

    Pre_ProcessingGate->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    Pre_ProcessingGate->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    Pre_ProcessingGate->setMaximumHeight(90);
    Pre_ProcessingGate->setColumnWidth(0, 120);
    Pre_ProcessingGate->setColumnWidth(1, 120);

}



void CustomMeasurementTreeWidget::FillCalibrationTarget()
{

    CalibrationTarget->setColumnCount(2);

    CalibrationTarget->verticalHeader()->setVisible(false);
    CalibrationTarget->horizontalHeader()->setVisible(false);
    CalibrationTarget->horizontalHeader()->setStretchLastSection(true);
    CalibrationTarget->setEditTriggers(QAbstractItemView::SelectedClicked); // Изменение нажатием?



    CalibrationTarget->insertRow(0);
    CalibrationTarget->setItem(0, 0, new QTableWidgetItem("Target"));
    QComboBox * TargetBox = new QComboBox(this);
    TargetBox->addItem("Sphere");
    TargetBox->addItem("Cylinder");
    TargetBox->addItem("Reflect");
    CalibrationTarget->setCellWidget(0, 1, TargetBox);

    CalibrationTarget->insertRow(1);
    CalibrationTarget->setItem(1, 0, new QTableWidgetItem("Diameter (m)"));
    CalibrationTarget->setCellWidget(1, 1, new QLineEdit(""));

    CalibrationTarget->insertRow(2);
    CalibrationTarget->setItem(2, 0, new QTableWidgetItem("Height (m)"));
    CalibrationTarget->setCellWidget(2, 1, new QLineEdit(""));



    CalibrationTarget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    CalibrationTarget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    CalibrationTarget->setMaximumHeight(90);
    CalibrationTarget->setColumnWidth(0, 120);
    CalibrationTarget->setColumnWidth(1, 120);
}



void CustomMeasurementTreeWidget::FillPNA()
{

    PNA->setColumnCount(2);

    PNA->verticalHeader()->setVisible(false);
    PNA->horizontalHeader()->setVisible(false);
    PNA->horizontalHeader()->setStretchLastSection(true);
    PNA->setEditTriggers(QAbstractItemView::SelectedClicked); // Изменение нажатием?



    PNA->insertRow(0);
    PNA->setItem(0, 0, new QTableWidgetItem("Port"));
    QComboBox * PortBox = new QComboBox(this);
    PortBox->addItem("A/R1");
    PortBox->addItem("B/R1");
    PortBox->addItem("R2/R1");
    PNA->setCellWidget(0, 1, PortBox);


    PNA->insertRow(1);
    PNA->setItem(1, 0, new QTableWidgetItem("Generator (dBm)"));
    PNAGeneratorEdit = new QLineEdit("0",this);
    PNA->setCellWidget(1, 1, PNAGeneratorEdit);

    PNA->insertRow(2);
    PNA->setItem(2, 0, new QTableWidgetItem("IF"));
    PNAIFBox = new QComboBox(this);
    PNAIFBox->addItem("0.01 kHz");
    PNAIFBox->addItem( "0.1 kHz");
    PNAIFBox->addItem( "1.0 kHz");
    PNAIFBox->addItem( "3.0 kHz");
    PNAIFBox->addItem("10.0 kHz");
    PNAIFBox->addItem("35.0 kHz");
    PNA->setCellWidget(2, 1, PNAIFBox);

    PNA->insertRow(3);
    PNA->setItem(3, 0, new QTableWidgetItem("OptimalValues"));
    PNA->setCellWidget(3, 1, new QCheckBox());

    PNA->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    PNA->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    PNA->setMaximumHeight(115);
    PNA->setColumnWidth(0, 140);
    PNA->setColumnWidth(1, 100);
}





////////////////////////////////////////////////////////////////////////////////



void CustomMeasurementTreeWidget::FrequencyRangeChanged(int index)
{
    if (index == 0)
    {
        FrequencyRangeCenterEdit->setReadOnly(false);
        FrequencyRangeSpanEdit->setReadOnly(false);
        FrequencyRangeNEdit->setReadOnly(false);
        PNAGeneratorEdit->setReadOnly(false);
        Pre_ProcessingGateStartEdit->setReadOnly(false);
        Pre_ProcessingGateStopEdit->setReadOnly(false);
        Pre_ProcessingGateShapeBox->setCurrentIndex(true);
    }
    else
    {
        int RangeIndex = index - 1;

        FrequencyRangeCenterEdit->setText(QString::number(FrequencyRanges[RangeIndex].first));
        FrequencyRangeSpanEdit->setText(QString::number(FrequencyRanges[RangeIndex].second));
        if (RangeIndex < 4)
        {
            FrequencyRangeNEdit->setText(QString::number(1601));
        }
        else
        {
            FrequencyRangeNEdit->setText(QString::number(2001));
        }

        if (RangeIndex<5)
        {
            FrequencyRangeCenterEdit->setReadOnly(true);
            FrequencyRangeSpanEdit->setReadOnly(true);
            FrequencyRangeNEdit->setReadOnly(true);
        }
        else
        {
            FrequencyRangeCenterEdit->setReadOnly(false);
            FrequencyRangeSpanEdit->setReadOnly(false);
            FrequencyRangeNEdit->setReadOnly(false);
        }


        if (RangeIndex<2)
        {
            PNAGeneratorEdit->setText(QString::number(0));
            PNAGeneratorEdit->setReadOnly(true);
        }
        else
        {
            PNAGeneratorEdit->setText(QString::number(10));

            if (RangeIndex == 5)
                PNAGeneratorEdit->setReadOnly(false);
            else
                PNAGeneratorEdit->setReadOnly(true);
        }


        Pre_ProcessingGateStartEdit->setText(QString::number(34));
        Pre_ProcessingGateStopEdit->setText(QString::number(48));
        Pre_ProcessingGateShapeBox->setCurrentIndex(1);


        if (RangeIndex == 5)
        {
            Pre_ProcessingGateStartEdit->setReadOnly(false);
            Pre_ProcessingGateStopEdit->setReadOnly(false);
            Pre_ProcessingGateShapeBox->setDisabled(false);
        }
        else
        {
            Pre_ProcessingGateStartEdit->setReadOnly(true);
            Pre_ProcessingGateStopEdit->setReadOnly(true);
            Pre_ProcessingGateShapeBox->setDisabled(true);
        }

    }

}

