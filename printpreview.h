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



enum PresetSizesAndPositions
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

class PrintPreview : public QWidget {
    Q_OBJECT

public:
    PrintPreview(QWidget *parent = nullptr);
    ~PrintPreview();

    //QPainter * Painter;
    QPrintPreviewWidget * PrintPreviewWidget;
    QPrinter * Printer;

    QVector <int>    VectorOfPlotNumbers;
    QVector <QImage> VectorOfPlotImages;
    QVector <QPoint> VectorOfPlotPositions;
    QVector <QSize>  VectorOfPlotSizes;
    int ActiveButton;
    PresetSizesAndPositions Preset = usersize;

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




    QHBoxLayout * PrintPreviewLayout;
    QVBoxLayout * OldButtonsLayout; // Кнопки как в старой проге
    QGridLayout * SizeLocationLayout;
    QGridLayout * CompClearPrintClearLayout;
    QGridLayout * CheckBoxLayout;

    QWidget * SizeLocationContainerWidget;

    // Окошки для галочек: какой график сейчас добавляем/меняем
    QCheckBox * PreviewBox;
    QCheckBox * FrequencyBox;
    QCheckBox * PatternBox;
    QCheckBox * DownRangeBox;
    QCheckBox * CrossRangeBox;
    QCheckBox * StatisticaBox;
    QCheckBox * Frequency_DRBox;
    QCheckBox * CompositeBox;

    QLabel * PreviewLabel;
    QLabel * FrequencyLabel;
    QLabel * PatternLabel;
    QLabel * DownRangeLabel;
    QLabel * CrossRangeLabel;
    QLabel * StatisticaLabel;
    QLabel * Frequency_DRLabel;
    QLabel * CompositeLabel;


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


public slots:
    // При установке галочек добавляют/меняют соответствующий график
    void PreviewBoxClicked      (bool checked);
    void FrequencyBoxClicked    (bool checked);
    void PatternBoxClicked      (bool checked);
    void DownRangeBoxClicked    (bool checked);
    void CrossRangeBoxClicked   (bool checked);
    void StatisticaBoxClicked   (bool checked);
    void Frequency_DRBoxClicked (bool checked);
    void CompositeBoxClicked    (bool checked);

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



    void DrawPreset(QImage image, QPainter &painter);

    void OnPaintRequested();

    void UpdatePreview();


};


#endif // PRINTPREVIEW_H
