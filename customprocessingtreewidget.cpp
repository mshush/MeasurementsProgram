#include "customprocessingtreewidget.h"
#include "qcheckbox.h"
#include "qcombobox.h"
#include "qheaderview.h"
//#include "qlabel.h"
#include "qlineedit.h"
#include "qpushbutton.h"


CustomProcessingTreeWidget::CustomProcessingTreeWidget()
{

    QBrush brush = QBrush(QColor(200,200,255));

    this->setFixedWidth(280);
    //this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setColumnCount(1);
    this->setHeaderHidden(true);

    setIndentation(0);
    //setHeaderLabels(QStringList() << "Parameter Groups");

    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Добавляем 12 элементов:

    AzimuthScale = new QTableWidget(this);
    AzimuthScaleItem = new QTreeWidgetItem(this);
    AzimuthScaleItem->setBackground(0,brush);
    QTreeWidgetItem * AzimuthScaleTableItem = new QTreeWidgetItem(AzimuthScaleItem);
    AzimuthScaleItem->setText(0,"AzimuthScale");
    setItemWidget(AzimuthScaleTableItem, 0, AzimuthScale);
    FillAzimuthScale();


    AzimuthOffset = new QTableWidget(this);
    AzimuthOffsetItem = new QTreeWidgetItem(this);
    AzimuthOffsetItem->setBackground(0,brush);
    QTreeWidgetItem * AzimuthOffsetTableItem = new QTreeWidgetItem(AzimuthOffsetItem);
    AzimuthOffsetItem->setText(0,"AzimuthOffset");
    setItemWidget(AzimuthOffsetTableItem, 0, AzimuthOffset);
    FillAzimuthOffset();


    ZOffset = new QTableWidget(this);
    ZOffsetItem = new QTreeWidgetItem(this);
    ZOffsetItem->setBackground(0,brush);
    QTreeWidgetItem * ZOffsetTableItem = new QTreeWidgetItem(ZOffsetItem);
    ZOffsetItem->setText(0,"ZOffset");
    setItemWidget(ZOffsetTableItem, 0, ZOffset);
    FillZOffset();


    FrequencyProcessingSubrange = new QTableWidget(this);
    FrequencyProcessingSubrangeItem = new QTreeWidgetItem(this);
    FrequencyProcessingSubrangeItem->setBackground(0,brush);
    QTreeWidgetItem * FrequencyProcessingSubrangeTableItem = new QTreeWidgetItem(FrequencyProcessingSubrangeItem);
    FrequencyProcessingSubrangeItem->setText(0,"FrequencyProcessingSubrange");
    setItemWidget(FrequencyProcessingSubrangeTableItem, 0, FrequencyProcessingSubrange);
    FillFrequencyProcessingSubrange();


    AngularProcessingSubrange = new QTableWidget(this);
    AngularProcessingSubrangeItem = new QTreeWidgetItem(this);
    AngularProcessingSubrangeItem->setBackground(0,brush);
    QTreeWidgetItem * AngularProcessingSubrangeTableItem = new QTreeWidgetItem(AngularProcessingSubrangeItem);
    AngularProcessingSubrangeItem->setText(0,"AngularProcessingSubrange");
    setItemWidget(AngularProcessingSubrangeTableItem, 0, AngularProcessingSubrange);
    FillAngularProcessingSubrange();


    StatisticaSubrange = new QTableWidget(this);
    StatisticaSubrangeItem = new QTreeWidgetItem(this);
    StatisticaSubrangeItem->setBackground(0,brush);
    QTreeWidgetItem * StatisticaSubrangeTableItem = new QTreeWidgetItem(StatisticaSubrangeItem);
    StatisticaSubrangeItem->setText(0,"StatisticaSubrange");
    setItemWidget(StatisticaSubrangeTableItem, 0, StatisticaSubrange);
    FillStatisticaSubrange();


    WindowDR = new QTableWidget(this);
    WindowDRItem = new QTreeWidgetItem(this);
    WindowDRItem->setBackground(0,brush);
    QTreeWidgetItem * WindowDRTableItem = new QTreeWidgetItem(WindowDRItem);
    WindowDRItem->setText(0,"WindowDR");
    setItemWidget(WindowDRTableItem, 0, WindowDR);
    FillWindowDR();


    WindowCR = new QTableWidget(this);
    WindowCRItem = new QTreeWidgetItem(this);
    WindowCRItem->setBackground(0,brush);
    QTreeWidgetItem * WindowCRTableItem = new QTreeWidgetItem(WindowCRItem);
    WindowCRItem->setText(0,"WindowCR");
    setItemWidget(WindowCRTableItem, 0, WindowCR);
    FillWindowCR();


    Gate = new QTableWidget(this);
    GateItem = new QTreeWidgetItem(this);
    GateItem->setBackground(0,brush);
    QTreeWidgetItem * GateTableItem = new QTreeWidgetItem(GateItem);
    GateItem->setText(0,"Gate");
    setItemWidget(GateTableItem, 0, Gate);
    FillGate();


    ImageSubrange = new QTableWidget(this);
    ImageSubrangeItem = new QTreeWidgetItem(this);
    ImageSubrangeItem->setBackground(0,brush);
    QTreeWidgetItem * ImageSubrangeTableItem = new QTreeWidgetItem(ImageSubrangeItem);
    ImageSubrangeItem->setText(0,"ImageSubrange");
    setItemWidget(ImageSubrangeTableItem, 0, ImageSubrange);
    FillImageSubrange();


    ISARParameters = new QTableWidget(this);
    ISARParametersItem = new QTreeWidgetItem(this);
    ISARParametersItem->setBackground(0,brush);
    QTreeWidgetItem * ISARParametersTableItem = new QTreeWidgetItem(ISARParametersItem);
    ISARParametersItem->setText(0,"ISARParameters");
    setItemWidget(ISARParametersTableItem, 0, ISARParameters);
    FillISARParameters();


    Sketch = new QTableWidget(this);
    SketchItem = new QTreeWidgetItem(this);
    SketchItem->setBackground(0,brush);
    QTreeWidgetItem * SketchTableItem = new QTreeWidgetItem(SketchItem);
    SketchItem->setText(0,"Sketch");
    setItemWidget(SketchTableItem, 0, Sketch);
    FillSketch();



    this->expandAll();


}

void CustomProcessingTreeWidget::FillAzimuthScale()
{
    AzimuthScale->setColumnCount(2);

    AzimuthScale->verticalHeader()->setVisible(false);
    AzimuthScale->horizontalHeader()->setVisible(false);
    AzimuthScale->horizontalHeader()->setStretchLastSection(true);
    AzimuthScale->setEditTriggers(QAbstractItemView::SelectedClicked);

    AzimuthScale->insertRow(0);
    AzimuthScale->setItem(0, 0, new QTableWidgetItem("Az (deg)"));
    AzimuthScale->setCellWidget(0, 1, new QLineEdit("0"));

    AzimuthScale->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    AzimuthScale->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    AzimuthScale->setFixedHeight(30);
    AzimuthScale->setColumnWidth(0, 120);
    AzimuthScale->setColumnWidth(1, 120);

};

void CustomProcessingTreeWidget::FillAzimuthOffset()
{

    AzimuthOffset->setColumnCount(2);

    AzimuthOffset->verticalHeader()->setVisible(false);
    AzimuthOffset->horizontalHeader()->setVisible(false);
    AzimuthOffset->horizontalHeader()->setStretchLastSection(true);
    AzimuthOffset->setEditTriggers(QAbstractItemView::SelectedClicked);

    AzimuthOffset->insertRow(0);
    AzimuthOffset->setItem(0, 0, new QTableWidgetItem("Az (deg)"));
    AzimuthOffset->setCellWidget(0, 1, new QLineEdit("0"));

    AzimuthOffset->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    AzimuthOffset->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    AzimuthOffset->setFixedHeight(30);
    AzimuthOffset->setColumnWidth(0, 120);
    AzimuthOffset->setColumnWidth(1, 120);

};

void CustomProcessingTreeWidget::FillZOffset()
{

    ZOffset->setColumnCount(2);

    ZOffset->verticalHeader()->setVisible(false);
    ZOffset->horizontalHeader()->setVisible(false);
    ZOffset->horizontalHeader()->setStretchLastSection(true);
    ZOffset->setEditTriggers(QAbstractItemView::SelectedClicked);

    ZOffset->insertRow(0);
    ZOffset->setItem(0, 0, new QTableWidgetItem("Z Offset (m)"));
    ZOffset->setCellWidget(0, 1, new QLineEdit("-0.120",this));

    ZOffset->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ZOffset->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ZOffset->setFixedHeight(30);
    ZOffset->setColumnWidth(0, 120);
    ZOffset->setColumnWidth(1, 120);

};

void CustomProcessingTreeWidget::FillFrequencyProcessingSubrange()
{

    FrequencyProcessingSubrange->setColumnCount(2);

    FrequencyProcessingSubrange->verticalHeader()->setVisible(false);
    FrequencyProcessingSubrange->horizontalHeader()->setVisible(false);
    FrequencyProcessingSubrange->horizontalHeader()->setStretchLastSection(true);
    FrequencyProcessingSubrange->setEditTriggers(QAbstractItemView::SelectedClicked);


    FrequencyProcessingSubrange->insertRow(0);
    FrequencyProcessingSubrange->setItem(0, 0, new QTableWidgetItem("Center (GHz)"));
    FrequencyProcessingSubrange->setCellWidget(0, 1, new QLineEdit(""));

    FrequencyProcessingSubrange->insertRow(1);
    FrequencyProcessingSubrange->setItem(1, 0, new QTableWidgetItem("Span (GHz)"));
    FrequencyProcessingSubrange->setCellWidget(1, 1, new QLineEdit(""));

    FrequencyProcessingSubrange->insertRow(2);
    FrequencyProcessingSubrange->setItem(2, 0, new QTableWidgetItem("N"));
    FrequencyProcessingSubrange->setCellWidget(2, 1, new QLineEdit(""));

    FrequencyProcessingSubrange->insertRow(3);
    FrequencyProcessingSubrange->setItem(3, 0, new QTableWidgetItem("Subrange"));
    QComboBox * FrequencyProcessingSubrangeBox = new QComboBox(FrequencyProcessingSubrange);
    FrequencyProcessingSubrangeBox->addItem("Manual");
    FrequencyProcessingSubrangeBox->addItem("Whole range");
    FrequencyProcessingSubrange->setCellWidget(3, 1, FrequencyProcessingSubrangeBox);

    FrequencyProcessingSubrange->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    FrequencyProcessingSubrange->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    FrequencyProcessingSubrange->setFixedHeight(120);
    FrequencyProcessingSubrange->setColumnWidth(0, 120);
    FrequencyProcessingSubrange->setColumnWidth(1, 120);

};

void CustomProcessingTreeWidget::FillAngularProcessingSubrange()
{

    AngularProcessingSubrange->setColumnCount(2);

    AngularProcessingSubrange->verticalHeader()->setVisible(false);
    AngularProcessingSubrange->horizontalHeader()->setVisible(false);
    AngularProcessingSubrange->horizontalHeader()->setStretchLastSection(true);
    AngularProcessingSubrange->setEditTriggers(QAbstractItemView::SelectedClicked);


    AngularProcessingSubrange->insertRow(0);
    AngularProcessingSubrange->setItem(0, 0, new QTableWidgetItem("Center (deg)"));
    AngularProcessingSubrange->setCellWidget(0, 1, new QLineEdit(""));

    AngularProcessingSubrange->insertRow(1);
    AngularProcessingSubrange->setItem(1, 0, new QTableWidgetItem("Span (deg)"));
    AngularProcessingSubrange->setCellWidget(1, 1, new QLineEdit(""));

    AngularProcessingSubrange->insertRow(2);
    AngularProcessingSubrange->setItem(2, 0, new QTableWidgetItem("N"));
    AngularProcessingSubrange->setCellWidget(2, 1, new QLineEdit(""));

    AngularProcessingSubrange->insertRow(3);
    AngularProcessingSubrange->setItem(3, 0, new QTableWidgetItem("Subrange"));
    QComboBox * AngularProcessingSubrangeBox = new QComboBox(AngularProcessingSubrange);
    AngularProcessingSubrangeBox->addItem("Manual");
    AngularProcessingSubrangeBox->addItem("Whole range");
    AngularProcessingSubrange->setCellWidget(3, 1, AngularProcessingSubrangeBox);

    AngularProcessingSubrange->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    AngularProcessingSubrange->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    AngularProcessingSubrange->setFixedHeight(120);
    AngularProcessingSubrange->setColumnWidth(0, 120);
    AngularProcessingSubrange->setColumnWidth(1, 120);

};

void CustomProcessingTreeWidget::FillStatisticaSubrange()
{

    StatisticaSubrange->setColumnCount(2);

    StatisticaSubrange->verticalHeader()->setVisible(false);
    StatisticaSubrange->horizontalHeader()->setVisible(false);
    StatisticaSubrange->horizontalHeader()->setStretchLastSection(true);
    StatisticaSubrange->verticalHeader()->setStretchLastSection(true);
    StatisticaSubrange->setEditTriggers(QAbstractItemView::SelectedClicked);


    StatisticaSubrange->insertRow(0);
    StatisticaSubrange->setItem(0, 0, new QTableWidgetItem("Center (deg)"));
    StatisticaSubrange->setCellWidget(0, 1, new QLineEdit(""));

    StatisticaSubrange->insertRow(1);
    StatisticaSubrange->setItem(1, 0, new QTableWidgetItem("Span (deg)"));
    StatisticaSubrange->setCellWidget(1, 1, new QLineEdit(""));

    StatisticaSubrange->insertRow(2);
    StatisticaSubrange->setItem(2, 0, new QTableWidgetItem("N"));
    StatisticaSubrange->setCellWidget(2, 1, new QLineEdit(""));

    StatisticaSubrange->insertRow(3);
    StatisticaSubrange->setItem(3, 0, new QTableWidgetItem("Subrange"));
    QComboBox * StatisticaSubrangeBox = new QComboBox(StatisticaSubrange);
    StatisticaSubrangeBox->addItem("Manual");
    StatisticaSubrangeBox->addItem("Whole range");
    StatisticaSubrange->setCellWidget(3, 1, StatisticaSubrangeBox);


    StatisticaSubrange->insertRow(4);

    QTableWidget * StatisticaSubrangeInsideTable = new QTableWidget(StatisticaSubrange);
    StatisticaSubrangeInsideTable->setRowCount(5);
    StatisticaSubrangeInsideTable->setColumnCount(3);
    StatisticaSubrangeInsideTable->verticalHeader()->setVisible(false);
    StatisticaSubrangeInsideTable->horizontalHeader()->setVisible(false);
    StatisticaSubrangeInsideTable->horizontalHeader()->setStretchLastSection(true);

    StatisticaSubrangeInsideTable->setCellWidget(0,0,new QPushButton("Param"));
    StatisticaSubrangeInsideTable->setCellWidget(0,1,new QPushButton("Whole"));
    StatisticaSubrangeInsideTable->setCellWidget(0,2,new QPushButton("Subrange"));

    StatisticaSubrangeInsideTable->setItem(1,0, new QTableWidgetItem("Average"));
    StatisticaSubrangeInsideTable->setItem(2,0, new QTableWidgetItem("Median"));
    StatisticaSubrangeInsideTable->setItem(3,0, new QTableWidgetItem("Pcnt90"));
    StatisticaSubrangeInsideTable->setItem(4,0, new QTableWidgetItem("Pcnt10"));

    //StatisticaSubrangeInsideTable->setFixedSize(280,150);

    StatisticaSubrange->setCellWidget(4, 0, StatisticaSubrangeInsideTable);
    StatisticaSubrange->setSpan(4, 0, 1, 2);


    StatisticaSubrange->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    StatisticaSubrange->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //StatisticaSubrange->setFixedHeight(280);
    StatisticaSubrange->setColumnWidth(0, 120);
    StatisticaSubrange->setColumnWidth(1, 120);

};

void CustomProcessingTreeWidget::FillWindowDR()
{

    WindowDR->setFixedSize(280,30);
    WindowDR->setColumnCount(2);

    WindowDR->verticalHeader()->setVisible(false);
    WindowDR->horizontalHeader()->setVisible(false);
    WindowDR->horizontalHeader()->setStretchLastSection(true);
    WindowDR->setEditTriggers(QAbstractItemView::SelectedClicked);

    WindowDR->insertRow(0);
    WindowDR->setItem(0, 0, new QTableWidgetItem("Shape"));
    QComboBox * WindowDRShapeBox = new QComboBox(this);
    WindowDRShapeBox->addItem("No Window");
    WindowDRShapeBox->addItem("Normal");
    WindowDRShapeBox->addItem("Wide");
    WindowDRShapeBox->addItem("Maximal");
    WindowDR->setCellWidget(0, 1, WindowDRShapeBox);

    WindowDR->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    WindowDR->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    WindowDR->setColumnWidth(0, 120);
    WindowDR->setColumnWidth(1, 120);

};
void CustomProcessingTreeWidget::FillWindowCR()
{

    WindowCR->setFixedSize(280,30);
    WindowCR->setColumnCount(2);

    WindowCR->verticalHeader()->setVisible(false);
    WindowCR->horizontalHeader()->setVisible(false);
    WindowCR->horizontalHeader()->setStretchLastSection(true);
    WindowCR->setEditTriggers(QAbstractItemView::SelectedClicked);

    WindowCR->insertRow(0);
    WindowCR->setItem(0, 0, new QTableWidgetItem("Shape"));
    QComboBox * WindowCRShapeBox = new QComboBox(WindowCR);
    WindowCRShapeBox->addItem("No Window");
    WindowCRShapeBox->addItem("Normal");
    WindowCRShapeBox->addItem("Wide");
    WindowCRShapeBox->addItem("Maximal");
    WindowCR->setCellWidget(0, 1, WindowCRShapeBox);

    WindowCR->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    WindowCR->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    WindowCR->setColumnWidth(0, 120);
    WindowCR->setColumnWidth(1, 120);

};

void CustomProcessingTreeWidget::FillGate()
{

    Gate->setColumnCount(2);

    Gate->verticalHeader()->setVisible(false);
    Gate->horizontalHeader()->setVisible(false);
    Gate->horizontalHeader()->setStretchLastSection(true);
    Gate->setEditTriggers(QAbstractItemView::SelectedClicked);


    Gate->insertRow(0);
    Gate->setItem(0, 0, new QTableWidgetItem("Start (m)"));
    Gate->setCellWidget(0, 1, new QLineEdit("0"));

    Gate->insertRow(1);
    Gate->setItem(1, 0, new QTableWidgetItem("Stop (m)"));
    Gate->setCellWidget(1, 1, new QLineEdit("0"));

    Gate->insertRow(2);
    Gate->setItem(2, 0, new QTableWidgetItem("Shape"));
    QComboBox * GateBox = new QComboBox(Gate);
    GateBox->addItem("Minimal"); // Зачем это?
    Gate->setCellWidget(2, 1, GateBox);

    Gate->insertRow(3);
    Gate->setItem(3, 0, new QTableWidgetItem("Allow gate"));
    Gate->setCellWidget(3, 1, new QCheckBox(Gate));

    Gate->insertRow(4);
    Gate->setItem(4, 0, new QTableWidgetItem("Apply only to DR"));
    Gate->setCellWidget(4, 1, new QCheckBox(Gate));

    Gate->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    Gate->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    Gate->setFixedHeight(150);
    Gate->setColumnWidth(0, 120);
    Gate->setColumnWidth(1, 120);

};

void CustomProcessingTreeWidget::FillImageSubrange()
{


    ImageSubrange->setColumnCount(2);

    ImageSubrange->verticalHeader()->setVisible(false);
    ImageSubrange->horizontalHeader()->setVisible(false);
    ImageSubrange->horizontalHeader()->setStretchLastSection(true);
    ImageSubrange->setEditTriggers(QAbstractItemView::SelectedClicked);


    ImageSubrange->insertRow(0);
    ImageSubrange->setItem(0, 0, new QTableWidgetItem("Center (deg)"));
    ImageSubrange->setCellWidget(0, 1, new QLineEdit(""));

    ImageSubrange->insertRow(1);
    ImageSubrange->setItem(1, 0, new QTableWidgetItem("Span (deg)"));
    ImageSubrange->setCellWidget(1, 1, new QLineEdit(""));

    ImageSubrange->insertRow(2);
    ImageSubrange->setItem(2, 0, new QTableWidgetItem("N"));
    ImageSubrange->setCellWidget(2, 1, new QLineEdit(""));

    ImageSubrange->insertRow(3);
    ImageSubrange->setItem(3, 0, new QTableWidgetItem("Subrange"));
    QComboBox * ImageSubrangeBox = new QComboBox(ImageSubrange);
    ImageSubrangeBox->addItem("Manual");
    ImageSubrangeBox->addItem("Default range");
    ImageSubrange->setCellWidget(3, 1, ImageSubrangeBox);

    ImageSubrange->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ImageSubrange->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ImageSubrange->setFixedHeight(120);
    ImageSubrange->setColumnWidth(0, 120);
    ImageSubrange->setColumnWidth(1, 120);

};

void CustomProcessingTreeWidget::FillISARParameters()
{
    ISARParameters->setFixedHeight(10);
};

void CustomProcessingTreeWidget::FillSketch()
{

    Sketch->setColumnCount(2);

    Sketch->verticalHeader()->setVisible(false);
    Sketch->horizontalHeader()->setVisible(false);
    Sketch->horizontalHeader()->setStretchLastSection(true);
    Sketch->setEditTriggers(QAbstractItemView::SelectedClicked);


    Sketch->insertRow(0);
    Sketch->setItem(0, 0, new QTableWidgetItem("X Scale"));
    Sketch->setCellWidget(0, 1, new QLineEdit("1"));

    Sketch->insertRow(1);
    Sketch->setItem(1, 0, new QTableWidgetItem("Y Scale"));
    Sketch->setCellWidget(1, 1, new QLineEdit("1"));

    Sketch->insertRow(2);
    Sketch->setItem(2, 0, new QTableWidgetItem("X Shift (m)"));
    Sketch->setCellWidget(2, 1, new QLineEdit("0"));

    Sketch->insertRow(3);
    Sketch->setItem(3, 0, new QTableWidgetItem("Y Shift (m)"));
    Sketch->setCellWidget(3, 1, new QLineEdit("0"));

    Sketch->insertRow(4);
    Sketch->setItem(4, 0, new QTableWidgetItem("Angle Shift (deg)"));
    Sketch->setCellWidget(4, 1, new QLineEdit("0"));


    Sketch->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    Sketch->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    Sketch->setMaximumHeight(120);
    Sketch->setColumnWidth(0, 120);
    Sketch->setColumnWidth(1, 120);

};
