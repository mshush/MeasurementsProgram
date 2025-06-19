#ifndef LEGENDWIDGET_H
#define LEGENDWIDGET_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>



class LegendWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LegendWidget(QWidget *parent = nullptr);

    QVBoxLayout * VerticalLegendLayot;
    QHBoxLayout * HorizontalUpperButtonsLayout;
    QHBoxLayout * HorizontalLowerCheckboxLayout;



    QPushButton * ReadDataButton;
    QPushButton * WriteDataButton;
    QPushButton * AddLineButton;
    QPushButton * DeleteLineButton;
    QPushButton * ClearAllButton;
    QPushButton * UpLineButton;
    QPushButton * DownLineButton;
    QPushButton * CopyToMemoryLineButton;
    QPushButton * RefreshButton;

    QLabel * ShowInLegendBoxLabel;
    QLabel * GraphTitleLabel;
    QLabel * TitleLabel;

    QCheckBox * TitleChBox;
    QCheckBox * DataChBox;
    QCheckBox * PlaneChBox;
    QCheckBox * FreqChBox;
    QCheckBox * AzChBox;
    QCheckBox * ElChBox;
    QCheckBox * ChannelChBox;


    QTableWidget * LegendTable;

signals:
};

#endif // LEGENDWIDGET_H
