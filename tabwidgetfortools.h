#ifndef TABWIDGETFORTOOLS_H
#define TABWIDGETFORTOOLS_H

#include <QObject>
#include <QTabWidget>
#include <QWidget>
#include <QLabel>

#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QStyle>
#include <QIcon>

class TabWidgetForTools : public QTabWidget
{
    Q_OBJECT
public:
    TabWidgetForTools();
    QWidget * Tab1;
    QWidget * Tab2;
};

#endif // TABWIDGETFORTOOLS_H
