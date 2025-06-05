#ifndef WIDGETFORCUSTOMPLOT_H
#define WIDGETFORCUSTOMPLOT_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qcustomplot.h>
#include <QFileDialog>
#include <plotclass.h>
#include <QDoubleValidator>
#include <selectionrectclass.h>


class WidgetForCustomPlot : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetForCustomPlot(QWidget *parent = nullptr);
    ~WidgetForCustomPlot();

    PlotClass * customPlot;
    QWidget * ControlsWidget;
    QHBoxLayout * HorizontalPlotLayout;
    QVBoxLayout * VerticalControlsLayout;

    //Кнопки для сохранения
    void InitiateSaveLayout();
    QHBoxLayout * HorizontalSaveLayout;
    QPushButton * SaveButton;
    QPushButton * CopyButton;


    QColor HighlightColor = QColor(200, 200, 255);


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

    //Отдельное окно с настройкой внешнего вида маркера
    //QDialog * MarkerSettingsDialogue;
    //QDialogButtonBox * MarkerSettingsDialogueButtonBox;

    //QVBoxLayout * MarkerSettingsDialogueLayout;
    //int MarkerStyleChoice;

    QFrame * MarkerFrame;

    QLabel      * YAxisMaxLabel;
    QLabel      * YAxisSpanLabel;
    QComboBox   * YAxisMaxBox;
    QComboBox   * YAxisSpanBox;

    void ConnectControlsWidget();
    void InitiateButtons();

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


    void SetupContextMenu();

public slots:
    void EnterSelectLocalMinMode();
    void PutMarkerAtLocalMin();
    void EnterSelectLocalMaxMode();
    void PutMarkerAtLocalMax();

    void ToNextMax();
    void ToPrevMax();
    //void ToNextMin(); // Перенесены в OnMarkerNextMinClicked
    //void ToPrevMin(); // ...

    void ToNextKey();
    void ToPrevKey();

    void SetRange();

    void DeleteMarkerSlot();
    void AddMarkerSlot();
    void AddMarkerToTable(QCPItemTracer * MarkerPtr);

    void OpenMarkerColourDialogue();
    void ChangeMarkerStyle( int ComboIndex);
    //void DialogueResultAccepted();
    void ActivateRubberBand();
    void LockXAxis();
    void LockYAxis();
    void XAxisRangeChanged(const QCPRange &range);
    void YAxisRangeChanged(const QCPRange &range);
    //void SavePlotAsDat(); // Перенесено в PlotClass
    void ClearTable();
    void RemoveMarkerFromTable(int RowNumberOfMarker);
    void HighlightMarkerInTable(int RowNumberOfMarker);
    void UnHighlightMarkerInTable(int RowNumberOfMarker);
    //void SubstractMarkers();


    void FillControlsWidget();
    void AdjustContentsOfTableOfDifference(int row, int column);

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
