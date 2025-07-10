#include "legendwidget.h"

LegendWidget::LegendWidget(QWidget *parent)
    : QWidget{parent}
{
    FillLayout();

}

void LegendWidget::OnReadDataClicked()
{
    emit ReadDataSignal();
}

void LegendWidget::OnWriteDataClicked()
{
    emit WriteDataSignal();
}

void LegendWidget::OnAddLineClicked()
{

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

void LegendWidget::OnChartTabChanged()
{

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

    LegendTable->setRowCount(5);
    LegendTable->setColumnCount(10);

    LegendTable->setHorizontalHeaderLabels(headers);

}












