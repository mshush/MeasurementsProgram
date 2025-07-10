#ifndef LEGENDWIDGET_H
#define LEGENDWIDGET_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>
//#include <legendrow.h>





class LegendWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LegendWidget(QWidget *parent = nullptr);

    struct LegendRow
    {
        QCheckBox * VisibilityBox;
        QLabel    * ColourIndicatorLabel;
        QLabel    * TitleLabel;
        QComboBox * DataBox;
        QComboBox * PlaneBox;
        QComboBox * FreqBox;
        QComboBox * AlBox;
        QComboBox * ElBox;
        QComboBox * ChannelBox;
        QComboBox * SmoothBox;
        QComboBox * PercentBox;
        QComboBox * ColourBox;
    };

    struct DataForLegendRow
    {
        QString           Title   = "<D>";
        QVector <QString> Data;
        QVector <QString> Plane;
        QVector <double>  Freq;
        QVector <double>  Az;
        QVector <double>  El;
        QVector <QString> Channel;
        QVector <QString> Smooth;
        QVector <int>     Percent;
        QVector <QString> Colour;
    };

    struct DataFromLegendRow
    {
        QString Title   = "<D>";
        int Data        = 0;
        int Plane       = 0;
        int Freq        = 0;
        int Az          = 0;
        int El          = 0;
        int Channel     = 0;
        int Smooth      = 0;
        int Percent     = 0;
        int Colour      = 0;
    };

    QStringList headers = {
        "Title",
        "Data",
        "Plane",
        "Freq",
        "Az",
        "El",
        "Channel",
        "Smooth",
        "%",
        "Color"
    };

    int SelectedRow = 0;

    QVector<QColor> ColourVector = //Чтобы было больше вариантов, можно добавить функцию из PlotClass генерации цветов
    {
        QColor(Qt::yellow),
        QColor(Qt::green),
        QColor(Qt::cyan),
        QColor(Qt::red),
        QColor(Qt::magenta),
        QColor(Qt::blue),
        QColor(Qt::green),
        QColor(Qt::white),
    };




    // Заполнение компоновки
    void FillLayout();
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
    QVector <LegendRow> RowVector;
    QTableWidget * LegendTable;

public slots:
    void OnReadDataClicked();
    void OnWriteDataClicked();
    void OnAddLineClicked();
    void OnDeleteLineClicked();
    void OnClearAllClicked();
    void OnUpLineClicked();
    void OnDownLineClicked();
    void OnCopyToMemoryLineClicked();
    void OnRefreshClicked();

    //void ReceiveMeasurementsData();

    void OnChartTabChanged();

signals:
    void ReadDataSignal();
    void WriteDataSignal();
    void AddLineSignal();
    void DeleteLineSignal();
    void ClearAllSignal();
    void UpLineSignal();
    void DownLineSignal();
    void CopyToMemoryLineSignal();
    void RefreshSignal();
};
















#endif // LEGENDWIDGET_H
