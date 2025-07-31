#ifndef WIDGETFORCUSTOMPLOT_H
#define WIDGETFORCUSTOMPLOT_H

#include <QObject>
#include <QtWidgets>
#include <qcustomplot.h>
#include <plotclass.h>
#include <selectionrectclass.h>


class WidgetForCustomPlot : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetForCustomPlot(QWidget *parent = nullptr);
    ~WidgetForCustomPlot();

    // Функции из конструктора
    void SetUpGeneralStyle();
    void SetUpPlot();
    void FillControlsWidget();
    void FillLayouts();
    void SetUpContextMenu();
    void SetUpConnections();

    // Функции из функций конструктора
    // Внутри FillControlsWidget:
    void InitiateButtons();
    void FillYAxisControl();
    void FillXAxisAndMarkerControl();
    void FillMarkerTable();

    // Внутри SetUpConnections:
    void ConnectControlsWidget();



    // Компоновки
    QHBoxLayout * HorizontalPlotLayout;   // В ней и график, и панель
    QVBoxLayout * VerticalControlsLayout; // Компоновка панели

    //Основной график
    PlotClass * customPlot;

    // Виджет панели управления
    QWidget * ControlsWidget;

    // Заголовки групп кнопок (для смены языка пишу отдельно)
    QLabel      * YAxisTitleLabel;
    QLabel      * XAxisTitleLabel;
    QLabel      *  MarkerTitleLabel;

    // Виджеты настройки шкалы по Y
    QLabel      * YAxisMaxLabel;
    QLabel      * YAxisSpanLabel;
    QComboBox   * YAxisMaxBox;
    QComboBox   * YAxisSpanBox;



    QPushButton * YLinScaleButton;
    QPushButton * YLogScaleButton;
    QPushButton * YFitMaxSpanButton   ;
    QPushButton * YFitMaxButton       ;
    QPushButton * YManualScaleButton  ;
    QPushButton * XScaleRectButton    ;
    QPushButton * XFitScaleButton     ;
    QPushButton * XUserScaleButton    ;
    QPushButton * XHighlightButton    ;
    QPushButton * MarkerMoveLeftButton    ;
    QPushButton * MarkerMoveRightButton   ;
    QPushButton * MarkerRightMaxButton    ;
    QPushButton * MarkerLeftMaxButton     ;
    QPushButton * MarkerRightMinButton    ;
    QPushButton * MarkerLeftMinButton     ;
    QPushButton * MarkerLocalMaxButton    ;
    QPushButton * MinusRightButton        ;
    QPushButton * MinusLeftButton         ;
    QPushButton * MarkerAddButton         ;
    QPushButton * MarkerGraphButton       ;
    QPushButton * MarkerIncreaseNButton   ;
    QPushButton * MarkerPrintButton       ;
    QPushButton * MarkerIncreaseButton    ;
    QPushButton * MarkerUnlockYButton     ;
    QPushButton * MarkerUnlockXButton     ;
    QPushButton * MarkerDeleteButton      ;
    QPushButton * MarkerUpButton          ;
    QPushButton * MarkerDownButton        ;

    QButtonGroup * YLinLogScaleButtonGroup;
    QButtonGroup * YFitMaxSpanOrManualButtonGroup;



    QVector <QPushButton *> PlotButtonVector;

    double SelectedRangeXMin = 0;
    double SelectedRangeXMax = 0;



    QMenu * contextMenu;
    QAction * DisableScalePanelAction;
    QAction * PolarFormatAction;
    QAction * AmplitudeAction;
    QAction * PhaseAction;
    QAction * RealPartAction;
    QAction * ImagPartAction;
    QAction * LegendInsideAction;
    QAction * DisableLegendAction;




    QStringList iconPaths =
        {
            "C:/Users/HP/Documents/MeasurementsProgram/Icons/Y1.png",
            "C:/Users/HP/Documents/MeasurementsProgram/Icons/Y2.png",
            "C:/Users/HP/Documents/MeasurementsProgram/Icons/Y3.png",
            "C:/Users/HP/Documents/MeasurementsProgram/Icons/Y4.png",
            "C:/Users/HP/Documents/MeasurementsProgram/Icons/Y5.png",
            "C:/Users/HP/Documents/MeasurementsProgram/Icons/X1.png",
            "C:/Users/HP/Documents/MeasurementsProgram/Icons/X2.png",
            "C:/Users/HP/Documents/MeasurementsProgram/Icons/X3.png",
            "C:/Users/HP/Documents/MeasurementsProgram/Icons/X4.png",
            "C:/Users/HP/Documents/MeasurementsProgram/Icons/X5.png",
            "C:/Users/HP/Documents/MeasurementsProgram/Icons/X6.png",
            "C:/Users/HP/Documents/MeasurementsProgram/Icons/X7.png",
            "C:/Users/HP/Documents/MeasurementsProgram/Icons/X8.png",
            "C:/Users/HP/Documents/MeasurementsProgram/Icons/X9.png",
            "C:/Users/HP/Documents/MeasurementsProgram/Icons/X10.png",
            "C:/Users/HP/Documents/MeasurementsProgram/Icons/X11.png",
            "C:/Users/HP/Documents/MeasurementsProgram/Icons/X12.png",
            "C:/Users/HP/Documents/MeasurementsProgram/Icons/X13.png",
            "C:/Users/HP/Documents/MeasurementsProgram/Icons/M1.png",
            "C:/Users/HP/Documents/MeasurementsProgram/Icons/M2.png",
            "C:/Users/HP/Documents/MeasurementsProgram/Icons/M3.png",
            "C:/Users/HP/Documents/MeasurementsProgram/Icons/M4.png",
            "C:/Users/HP/Documents/MeasurementsProgram/Icons/M5.png",
            "C:/Users/HP/Documents/MeasurementsProgram/Icons/M6.png",
            "C:/Users/HP/Documents/MeasurementsProgram/Icons/M7.png",
            "C:/Users/HP/Documents/MeasurementsProgram/Icons/M8.png",
            "C:/Users/HP/Documents/MeasurementsProgram/Icons/M9.png",
            "C:/Users/HP/Documents/MeasurementsProgram/Icons/M10.png"
        };



public slots:
    //void EnterSelectLocalMinMode();
    //void PutMarkerAtLocalMin();
    void EnterSelectLocalMaxMode();
    void PutMarkerAtLocalMax();

    void ToNextMax();
    void ToPrevMax();
    //void ToNextMin(); // Перенесены в OnMarkerNextMinClicked
    //void ToPrevMin(); // ...

    void ToNextKey();
    void ToPrevKey();

    //void SetRange();

    void DeleteMarkerSlot();
    void AddMarkerSlot();
    void AddMarkerToTable(QCPItemTracer * MarkerPtr);

    void OpenMarkerColourDialogue();
    void ChangeMarkerStyle( int ComboIndex);
    //void DialogueResultAccepted();
    //void ActivateRubberBand();
    //void LockXAxis();
    //void LockYAxis();
    void XAxisRangeChanged(const QCPRange &range);
    void YAxisRangeChanged(const QCPRange &range);
    //void SavePlotAsDat(); // Перенесено в PlotClass
    void ClearTable();
    void RemoveMarkerFromTable(int RowNumberOfMarker);
    void HighlightMarkerInTable(int RowNumberOfMarker);
    void UnHighlightMarkerInTable(int RowNumberOfMarker);
    //void SubstractMarkers();


    //void AdjustContentsOfTableOfDifference(int row, int column);

    void OnYLinScaleClicked();
    void OnYLogScaleClicked();
    void OnYFitMaxSpanClicked();
    void OnYFitMaxClicked();
    void OnYManualScaleClicked();
    void OnXScaleRectClicked();
    void OnXFitScaleClicked();
    void OnXUserScaleClicked();
    void OnXHighlightClicked();
    void OnMarkerMoveLeftClicked();
    void OnMarkerMoveRightClicked();
    void OnMarkerRightMaxClicked();
    void OnMarkerLeftMaxClicked();
    void OnMarkerRightMinClicked();
    void OnMarkerLeftMinClicked();
    void OnMarkerLocalMaxClicked();
    void OnMinusRightClicked();
    void OnMinusLeftClicked();
    void OnMarkerAddClicked();
    void OnMarkerGraphClicked();
    void OnMarkerIncreaseNClicked();
    void OnMarkerPrintClicked();
    void OnMarkerIncreaseClicked();
    void OnMarkerUnlockYClicked();
    void OnMarkerUnlockXClicked();
    void OnMarkerDeleteClicked();
    void OnMarkerUpClicked();
    void OnMarkerDownClicked();



    void ShowContextMenu(const QPoint &pos);

    void OnDisableScalePanel();
    void OnPolarFormat();
    void OnAmplitude();
    void OnPhase();
    void OnRealPart();
    void OnImagPart();
    void OnLegendInside();
    void OnDisableLegend();

signals:
    void ErrorOccured(QString ErrorText);
};



#endif // WIDGETFORCUSTOMPLOT_H


























/*
// Устаревшее
//Кнопки для сохранения
void InitiateSaveLayout();
QHBoxLayout * HorizontalSaveLayout;
QPushButton * SaveButton;
QPushButton * CopyButton;


//GroupBox для движения/приближения
void InitiateMovementGroupBox();
QGroupBox * MovementGroupBox;
QVBoxLayout * MovementGroupBoxLayout;
QHBoxLayout * LockAxesLayout;
QPushButton * ResetButton;
QPushButton * RubberBandButton;
QPushButton * LockXAxisButton;
QPushButton * LockYAxisButton;

//GroupBox для установки диапазона вручную
void InitiateSetRangeGroupBox();
QGroupBox * SetRangeGroupBox;
QGridLayout * SetRangeLayout;
QLabel * XRangeLabel1;
QLineEdit *XRangeEditFrom;
QLabel * XRangeLabel2;
QLineEdit *XRangeEditTo;
QLabel * YRangeLabel1;
QLineEdit *YRangeEditFrom;
QLabel * YRangeLabel2;
QLineEdit *YRangeEditTo;
QLabel * XRangeUnitsLabel;
QLabel * YRangeUnitsLabel;
QVBoxLayout * SetRangeVerticalLayout;
QPushButton * SetRangeButton;
QDoubleValidator * DoubleValidator;

//GroupBox для манипуляций с маркерами
void InitiateMarkerGroupBox();
QGroupBox * MarkerGroupBox;
QVBoxLayout * MarkerGroupBoxLayout;
QHBoxLayout * MarkerStyleLayout;
QHBoxLayout * MarkerAddDeleteLayout;
//QPushButton * MarkerAddButton; Ниже
//QPushButton * MarkerDeleteButton;
QPushButton * DeleteAllMarkersButton;
QPushButton * MarkerSettingsButton;
QColor MarkerColourChoise = Qt::black;
int MarkerStyleChoise = 0;
QComboBox * MarkerStyleComboBox;
QPushButton * MarkerColourButton;
QColorDialog * ColourDialogue;
void InitiateMarkerPreviewPlot();
QCustomPlot * MarkerPreviewPlot;
QCPItemTracer * PreviewMarker;

QHBoxLayout * SelectLocalMarkerLayout;
QPushButton * SelectLocalMaxButton;
QPushButton * SelectLocalMinButton;

//QThread * PlotThread;
QVBoxLayout  * VerticalMarkerStyleConfigurationLayout;
QComboBox * GraphChoiceComboBox;

//int NumberOfRows=0;
int CurrentMarkerIndex = 0;

QTableWidget * MarkerPositionsTable;
QTableWidget * MarkerDifferenceTable;


QFrame * MarkerFrame;
*/



