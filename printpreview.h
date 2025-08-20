#ifndef PRINTPREVIEW_H
#define PRINTPREVIEW_H

#include <QPrintPreviewWidget>
#include <QPrintPreviewDialog>
#include <QHBoxLayout>
#include <QObject>
#include <QWidget>
#include <QPrinter>
#include <QPainter>
#include <QtWidgets>
#include <QFileDialog>
#include <QPrinter>





class PrintPreview : public QWidget {
    Q_OBJECT

public:
    PrintPreview(int NumberOfPlotTabs, QWidget *parent = nullptr);
    ~PrintPreview();

    // Функции из конструктора
    void SetUpGeneralStyle();
    void SetUpPrinter();
    void SetUpPreviewArea();
    void FillCheckBoxes(int NumberOfPlotTabs);
    void FillPresetButtons();
    void FillCompClearPrintClearButtons();
    void SetUpConnections();
    void CalculateMargins();
    void FillLayout();

    // Функции из функций из конструктора
    void ConnectPresetButtons();


    // Класс-перебор шаблонов
    enum class Preset
    {
        usersize,
        wholepage           ,

        upperhalf           ,
        lowerhalf           ,

        upperthird          ,
        middlethird         ,
        bottomthird         ,

        topleftquarter      ,
        toprightquarter     ,
        bottomleftquarter   ,
        bottomrightquarter  ,

        topleftsixth        ,
        toprightsixth       ,
        middleleftsixth     ,
        middlerightsixth    ,
        bottomleftsixth     ,
        bottomrightsixth    ,
    };

    QVector <QImage> VectorOfImages;
    QVector <Preset> VectorOfPresets;



    // Выбранные шаблон и картинка (на данный момент)
    Preset CurrentPreset = Preset::usersize;
    QPixmap CurrentPixmap;

    QPrintPreviewWidget * PrintPreviewWidget;
    QPrinter * Printer;

    QVector <int>    VectorOfPlotNumbers;
    QVector <QImage> VectorOfPlotImages;
    QVector <QPoint> VectorOfPlotPositions;
    QVector <QSize>  VectorOfPlotSizes;
    int ActiveButton;

    int LeftMarginInMM      = 20; // Отступ слева
    int TopMarginInMM       = 10; // Отступ сверху
    int RightMarginInMM     = 10; // Отступ справа
    int BottomMarginInMM    = 10; // Отступ снизу

    double LeftMargin;
    double TopMargin;
    double RightMargin;
    double BottomMargin;
    double RightMarginX;
    double BottomMarginY;
    qreal dpi;

    QButtonGroup * CheckBoxGroup;

    // Компоновки
    QHBoxLayout * PrintPreviewLayout;
    QGridLayout * PresetLayout;
    QGridLayout * CompClearPrintClearLayout;
    QVBoxLayout * CheckBoxLayout;
    QVBoxLayout * ButtonsPanelLayout;

    QWidget * ButtonsPanelWidget; // Виджет-контейнер всей панели управления справа
    QWidget * PresetButtonsContainerWidget; // Виджет-контейнер кнопок шаблона


    // Кнопки изменения размеров
    QPushButton * UserSize;

    QPushButton * WholePage;

    QPushButton * UpperHalf;
    QPushButton * LowerHalf;

    QPushButton * UpperThird;
    QPushButton * MiddleThird;
    QPushButton * BottomThird;

    QPushButton * TopLeftQuarter;
    QPushButton * TopRightQuarter;
    QPushButton * BottomLeftQuarter;
    QPushButton * BottomRightQuarter;

    QPushButton * TopLeftSixth;
    QPushButton * TopRightSixth;
    QPushButton * MiddleLeftSixth;
    QPushButton * MiddleRightSixth;
    QPushButton * BottomLeftSixth;
    QPushButton * BottomRightSixth;

    //Кнопки очистки и сохранения
    QPushButton * CompPlusButton;
    QPushButton * ClearCompButton;
    QPushButton * PrintPlusButton;
    QPushButton * ClearPrintButton;

    void UpdateText();


    QRect RectFromPreset(Preset PresetInput);
public slots:
    // При установке галочек добавляет/меняет соответствующий график
    void SendSignalForPixmap(int CorrespondingTabId);


    // При нажатии меняют размер выбранного графика:
    void  MoveAndResizeToUserSize           ();
    void  MoveAndResizeToWholePage          ();
    void  MoveAndResizeToUpperHalf          ();
    void  MoveAndResizeToLowerHalf          ();
    void  MoveAndResizeToUpperThird         ();
    void  MoveAndResizeToMiddleThird        ();
    void  MoveAndResizeToBottomThird        ();
    void  MoveAndResizeToTopLeftQuarter     ();
    void  MoveAndResizeToTopRightQuarter    ();
    void  MoveAndResizeToBottomLeftQuarter  ();
    void  MoveAndResizeToBottomRightQuarter ();
    void  MoveAndResizeToTopLeftSixth       ();
    void  MoveAndResizeToTopRightSixth      ();
    void  MoveAndResizeToMiddleLeftSixth    ();
    void  MoveAndResizeToMiddleRightSixth   ();
    void  MoveAndResizeToBottomLeftSixth    ();
    void  MoveAndResizeToBottomRightSixth   ();

    void OnCompPlusButtonClicked();
    void OnClearCompButtonClicked();
    void OnPrintPlusButtonClicked();
    void OnClearPrintButtonClicked();



    void DrawPreset(QImage image, QPainter &painter, Preset PresetInput);

    void OnPaintRequested();

    void UpdatePreview();

    void OnPixmapReceived(QPixmap Pixmap);
signals:
    void NeedPixmap(int NeededTab, int NeededWidth, int NeededHeight, int NeededScale);

};


#endif // PRINTPREVIEW_H
