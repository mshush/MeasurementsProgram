#include "legendwidget.h"

LegendWidget::LegendWidget(QWidget *parent)
    : QWidget{parent}
{

    VerticalLegendLayot             = new QVBoxLayout(this);
    HorizontalUpperButtonsLayout    = new QHBoxLayout(this);
    HorizontalLowerCheckboxLayout   = new QHBoxLayout(this);


    ReadDataButton        = new QPushButton(this);
    WriteDataButton       = new QPushButton(this);
    AddLineButton         = new QPushButton(this);
    DeleteLineButton      = new QPushButton(this);
    ClearAllButton        = new QPushButton(this);
    UpLineButton          = new QPushButton(this);
    DownLineButton        = new QPushButton(this);
    CopyToMemoryLineButton= new QPushButton(this);
    RefreshButton         = new QPushButton(this);



    ShowInLegendBoxLabel    = new QLabel("Show in legend box"   , this);
    GraphTitleLabel         = new QLabel("Graph title"          , this);
    TitleLabel              = new QLabel("Title"                , this);


    TitleChBox  = new QCheckBox("Title"  ,this);
    DataChBox   = new QCheckBox("Data"   ,this);
    PlaneChBox  = new QCheckBox("Plane"  ,this);
    FreqChBox   = new QCheckBox("Freq"   ,this);
    AzChBox     = new QCheckBox("Az"     ,this);
    ElChBox     = new QCheckBox("El"     ,this);
    ChannelChBox= new QCheckBox("Channel",this);


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


}
