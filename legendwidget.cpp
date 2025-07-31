#include "legendwidget.h"

LegendWidget::LegendWidget(QWidget *parent)
    : QWidget{parent}
{
    FillLayout();
}

void LegendWidget::FillLayout()
{

    VerticalLegendLayot             = new QVBoxLayout(this);
    HorizontalUpperButtonsLayout    = new QHBoxLayout();
    HorizontalLowerCheckboxLayout   = new QHBoxLayout();

    ReadDataButton        = new QPushButton(tr("Read Data"),            this);
    WriteDataButton       = new QPushButton(tr("Write Data"),           this);
    AddLineButton         = new QPushButton(tr("Add Line"),             this);
    DeleteLineButton      = new QPushButton(tr("Delete Line"),          this);
    ClearAllButton        = new QPushButton(tr("Clear All"),            this);
    UpLineButton          = new QPushButton(tr("Up Line"),              this);
    DownLineButton        = new QPushButton(tr("Down Line"),            this);
    CopyToMemoryLineButton= new QPushButton(tr("Copy To Memory Line"),  this);
    RefreshButton         = new QPushButton(tr("Refresh"),this);


    ShowInLegendBoxLabel    = new QLabel(tr("Show in legend box"   ), this);
    GraphTitleLabel         = new QLabel(tr("Graph title"          ), this);
    TitleLabel              = new QLabel(tr("Title"                ), this);


    TitleChBox  = new QCheckBox(tr("Title")  ,this);
    DataChBox   = new QCheckBox(tr("Data")   ,this);
    PlaneChBox  = new QCheckBox(tr("Plane")  ,this);
    FreqChBox   = new QCheckBox(tr("Freq")   ,this);
    AzChBox     = new QCheckBox(tr("Az")     ,this);
    ElChBox     = new QCheckBox(tr("El")     ,this);
    ChannelChBox= new QCheckBox(tr("Channel"),this);


    LegendTable = new QTableWidget(this);

    HorizontalUpperButtonsLayout->addWidget(ReadDataButton);
    HorizontalUpperButtonsLayout->addWidget(WriteDataButton);
    HorizontalUpperButtonsLayout->addWidget(AddLineButton);
    HorizontalUpperButtonsLayout->addWidget(DeleteLineButton);
    HorizontalUpperButtonsLayout->addWidget(ClearAllButton);
    HorizontalUpperButtonsLayout->addWidget(UpLineButton);
    HorizontalUpperButtonsLayout->addWidget(DownLineButton);
    HorizontalUpperButtonsLayout->addWidget(CopyToMemoryLineButton);
    HorizontalUpperButtonsLayout->addWidget(RefreshButton);

    VerticalLegendLayot->addLayout(HorizontalUpperButtonsLayout);

    VerticalLegendLayot->addWidget(LegendTable);

    HorizontalLowerCheckboxLayout->addWidget(ShowInLegendBoxLabel);
    HorizontalLowerCheckboxLayout->addWidget(TitleChBox);
    HorizontalLowerCheckboxLayout->addWidget(DataChBox);
    HorizontalLowerCheckboxLayout->addWidget(PlaneChBox);
    HorizontalLowerCheckboxLayout->addWidget(FreqChBox);
    HorizontalLowerCheckboxLayout->addWidget(AzChBox);
    HorizontalLowerCheckboxLayout->addWidget(ElChBox);
    HorizontalLowerCheckboxLayout->addWidget(ChannelChBox);
    HorizontalLowerCheckboxLayout->addWidget(GraphTitleLabel);
    HorizontalLowerCheckboxLayout->addWidget(TitleLabel);


    VerticalLegendLayot->addLayout(HorizontalLowerCheckboxLayout);

    LegendTable->setRowCount(0); // Пусть для начала она пустой будет
    LegendTable->setColumnCount(10);

    LegendTable->setHorizontalHeaderLabels(headers);
    LegendTable->verticalHeader()->setVisible(false);

    OnAddLineClicked();
}

void LegendWidget::OnReadDataClicked()
{
    emit ReadDataSignal();
}

void LegendWidget::OnWriteDataClicked()
{
    emit WriteDataSignal();
}

LegendWidget::LegendRow::LegendRow(QWidget * parent)
{
    VisibilityBox = new QCheckBox(parent); // Поменять внешний вид
    ColourLabel = new QLabel("—",parent);
    ColourLabel->setStyleSheet("font-weight: bold; font-size: 50px; color: yellow;");
    ColourLabel->setAlignment(Qt::AlignCenter);
    TitleLabel  = new QLabel("Title",parent);
    DataBox     = new QComboBox(parent);
    PlaneBox    = new QComboBox(parent);
    FreqBox     = new QComboBox(parent);
    AlBox       = new QComboBox(parent);
    ElBox       = new QComboBox(parent);
    ChannelBox  = new QComboBox(parent);
    SmoothBox   = new QComboBox(parent);
    PercentBox  = new QComboBox(parent);
    ColourBox   = new QComboBox(parent);
}



void LegendWidget::OnAddLineClicked()
{
    // Создаём новую пустую строку
    LegendRow NewRow;

    // Добавляем пустую строку
    int RowCount = LegendTable->rowCount();
    LegendTable->insertRow(RowCount);

    // Заполняем её
    QWidget * ZeroCellWidget = new QWidget(this);
    QHBoxLayout * CellLayout = new QHBoxLayout(ZeroCellWidget);

    CellLayout->addWidget(NewRow.VisibilityBox);
    CellLayout->addWidget(NewRow.ColourLabel);
    CellLayout->addWidget(NewRow.TitleLabel);

    LegendTable->setCellWidget(RowCount, 0, ZeroCellWidget);



    LegendTable->setCellWidget(RowCount, 1, NewRow.DataBox);
    LegendTable->setCellWidget(RowCount, 2, NewRow.PlaneBox);
    LegendTable->setCellWidget(RowCount, 3, NewRow.FreqBox);
    LegendTable->setCellWidget(RowCount, 4, NewRow.AlBox);
    LegendTable->setCellWidget(RowCount, 5, NewRow.ElBox);
    LegendTable->setCellWidget(RowCount, 6, NewRow.ChannelBox);
    LegendTable->setCellWidget(RowCount, 7, NewRow.SmoothBox);
    LegendTable->setCellWidget(RowCount, 8, NewRow.PercentBox);
    LegendTable->setCellWidget(RowCount, 9, NewRow.ColourBox);

    //QStringList ColoueVector = QColor::colorNames(); // Слишком много цветов

    for (int i=0;i<ColourVector.size();i++)
    {
        NewRow.ColourBox->addItem(ColourVector[i]);
    }

    emit AddLineSignal();
    // Если графику есть, что передавать, то он отправит сигнал к слоту заполнения строки
}

void LegendWidget::OnDeleteLineClicked()
{

}

void LegendWidget::OnClearAllClicked()
{

}

void LegendWidget::OnUpLineClicked()
{

}

void LegendWidget::OnDownLineClicked()
{

}

void LegendWidget::OnCopyToMemoryLineClicked()
{

}

void LegendWidget::OnRefreshClicked()
{

}


void LegendWidget::RefillRows(int TabIndex)
{
    LegendTable->clearContents();
    for (int i = 0; i < RowVector.size(); i++)
    {
        LegendRow Row = RowVector[i];
        if (Row.ChartTabIndex == TabIndex)
        {
            qDebug()<<TabIndex;
        }
    }
}



void LegendWidget::OnChartTabChanged(int TabIndex)
{
    ActiveTab = TabIndex;


    if (ActiveTab == -1) // Деактивируем, если это PrintPreview
    {
        setEnabled(false);
    }
    else // Заполняем, если это не PrintPreview
    {
        setEnabled(true);
        for (int r=0; r< RowVector.size(); r++)
        {
            RefillRows(TabIndex);
        }
    }
}


