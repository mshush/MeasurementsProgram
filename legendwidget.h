#ifndef LEGENDWIDGET_H
#define LEGENDWIDGET_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include "measurmentscontrol.h"



class LegendWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LegendWidget(QWidget *parent = nullptr);

    MeasDataClass MeasData;
    int ActiveTab = 0;



    struct LegendRow
    {
        LegendRow(QWidget * parent = nullptr);
        QCheckBox * VisibilityBox;
        QLabel    * ColourLabel;
        QLabel    * TitleLabel;
        QComboBox * DataBox;
        QComboBox * PlaneBox;
        QComboBox * FreqBox;
        QComboBox * AzBox;
        QComboBox * ElBox;
        QComboBox * DistBox;
        QComboBox * ChannelBox;
        QComboBox * SmoothBox;
        QComboBox * PercentBox;
        QComboBox * ColourBox;
    };

    struct LegendRowsForOnePlot
    {
        QVector <LegendRow *> Rows;
    };


    QVector <LegendRowsForOnePlot> LegendRowsForAllPlots;

    struct DataForLegendRow
    {
        QString           Title   = "<D>";
        QVector <QString> Data;
        QVector <QString> Plane;
        QVector <double>  Freq;
        QVector <double>  Az;
        QVector <double>  El;
        QVector <double>  Dist;
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
        int Dist        = 0;
        int Channel     = 0;
        int Smooth      = 0;
        int Percent     = 0;
        int Colour      = 0;
    };

    QStringList headers =
    {
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

    QStringList ColourVector = //Чтобы было больше вариантов, можно использовать QColor::colorNames()
    {
        "Yellow",
        "Green",
        "Cyan",
        "Red",
        "Magenta",
        "Blue",
        "Green",
        "White"
    };

    QStringList DataTypes = // Типы данных, чтобы внести их в QComboBox
    {
        "Raw Target",
        "Raw Bckgnd",
        "Raw Resp",
        "Proc Bckgnd",
        "Clbr",
        "Pattern",
        "Curr Aspect",
        "ProfRange",
        "Gated ProfRange"
    };


    QVector <LegendRow> VectorOfRows; //Вектор всех строк таблицы (в строке хранится номер соответствующей графику вкладки)


    void InitiateRow();


    void RefillRows(int TabIndex);



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
    QCheckBox * DistChBox;
    QCheckBox * ChannelChBox;
    QVector <LegendRow> RowVector;
    QTableWidget * LegendTable;



    void SetNumberOfPlots(int PlotsNumber);


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
    void OnChartTabChanged(int TabNumber);

    void FillFirstRows(MeasDataClass MeasuredData);

    void SomeRowChanged();


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


    void VisibilityCheckedSignal(int TabId, int GraphId, bool Visible);
    void TitleChangedSignal     (int TabId, int GraphId, QString Title);
    void RedrawPlotSignal       (int TabId, int GraphId,
                          MeasDataClass::MeasDataType DataType,
                          QString Plane,
                          int Frequency,
                          int Azimuth,
                          int Elevation,
                          int Distance,
                          QColor Colour
);




};


#endif // LEGENDWIDGET_H
