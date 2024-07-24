#include "tabwidgetforcharts.h"

TabWidgetForCharts::TabWidgetForCharts()

{
    //ChartTabBar = new QTabBar(this);

    ChartTab = new WidgetForChart;
    addTab(ChartTab,"График 1");
    QWidget * Tab1 = new QWidget;
    addTab(Tab1,"График 2");
    QWidget * Tab2 = new QWidget;
    addTab(Tab2,"График 3");
    QWidget * Tab3 = new QWidget;
    addTab(Tab3,"График 4");

    for (int i=0;i< this->count();i++)
    {
        QPushButton* TempCloseButton = new QPushButton("X");

        TempCloseButton->setStyleSheet("QPushButton {"
                                  "background-color: #FF6F61;"
                                  "color: white;"
                                  "border-radius: 0px;" // Adjust the value to make it more circular
                                  "width: 15px;"
                                  "height: 15px;"
                                  "}");
        TempCloseButton->setFixedSize(15,15);

        tabBar()->setTabButton(i, QTabBar::RightSide, TempCloseButton);

        QWidget * TempTabPtr = this->widget(i);

        connect(TempCloseButton, &QPushButton::clicked, [TempTabPtr,this]()
                    {
                        removeTab(indexOf(TempTabPtr));
                    }
                );
    }

}
