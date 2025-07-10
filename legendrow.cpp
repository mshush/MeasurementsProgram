#include "legendrow.h"

LegendRow::LegendRow(QWidget *parent): QObject{parent}
{
    VisibilityBox = new QCheckBox(parent);

    ColourIndicatorLabel = new QLabel(parent);
    TitleLabel = new QLabel(parent);

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


void LegendRow::OnChartTabChanged(int index)
{

}

















