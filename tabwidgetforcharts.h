#ifndef TABWIDGETFORCHARTS_H
#define TABWIDGETFORCHARTS_H

#include <QObject>
#include <QTabWidget>
#include <QWidget>
#include <QTabBar>
#include<widgetforchart.h>

class TabWidgetForCharts : public QTabWidget
{
    Q_OBJECT
public:

    WidgetForChart * ChartTab;
    TabWidgetForCharts();

};






#endif // TABWIDGETFORCHARTS_H
