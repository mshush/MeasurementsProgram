#ifndef LEGENDROW_H
#define LEGENDROW_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>

class LegendRow : public QObject // Добавить этот класс внутрь класса  LegendWidget
{
    Q_OBJECT
public:
    LegendRow(QWidget * parent = nullptr);

public:
    QCheckBox * VisibilityBox;
    QLabel * ColourIndicatorLabel;
    QLabel * TitleLabel;
    QComboBox * DataBox;
    QComboBox * PlaneBox;
    QComboBox * FreqBox;
    QComboBox * AlBox;
    QComboBox * ElBox;
    QComboBox * ChannelBox;
    QComboBox * SmoothBox;
    QComboBox * PercentBox;
    QComboBox * ColourBox;

public slots:
    void OnChartTabChanged(int index);

signals:

};

#endif // LEGENDROW_H
