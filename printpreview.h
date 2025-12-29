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


    bool UserSizeActive = false; // Включена ли кнопка пользовательского размера
    bool DraggingNow = false; // Производится ли сейчас передвижение графика пользователем
    bool ResizingNow = false; // Производится ли сейчас изменение размера
    QRect UserRect;  // Прямоугольник, определяющий размер графика в режиме пользовательского размера
    QPoint LastMousePos;  // Последнее положение мыши
    QPoint ClickPos;   // Расстояние от точки клика до верхнего левого угла прямоугольника

    // Значки для изменения размера
    enum ResizeHandle
    {
        Handle_None,
        Handle_TopLeft,
        Handle_Top,
        Handle_TopRight,
        Handle_Left,
        Handle_Right,
        Handle_BottomLeft,
        Handle_Bottom,
        Handle_BottomRight
    };

    ResizeHandle CurrentResizeHandle = Handle_None; // Текущий значок (по умолчанию -- никакой)

    // Стиль
    int HandleSize = 8;  // Размер в пикселях значков изменения размера

    QPoint PreviewPosToPagePos(const QPoint& previewPos); // Пересчитывает позицию курсора относительно бумаги к позиции относительно графика
    QPoint PagePosToPreviewPos(const QPoint& pagePos); // Наоборот
    void UpdateUserRect(const QRect& newRect); // Обновляет пользовательский прямоугольник размера графика
    void UpdateCursorForHandle(ResizeHandle handle); // Обновляет значок курсора
    ResizeHandle ChooseResizeHandleAt(const QPoint& pagePos); // Выбирает вид значка в зависимости от точки
    int MinimumSize = 50;
    void EnableUserSize(bool enable);

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

    void OnCompPlusButtonClicked    ();
    void OnClearCompButtonClicked   ();
    void OnPrintPlusButtonClicked   ();
    void OnClearPrintButtonClicked  ();



    void DrawPreset(QImage image, QPainter &painter, Preset PresetInput);

    void OnPaintRequested();

    void UpdatePreview();

    void OnPixmapReceived(QPixmap Pixmap);

private:
    // Методы для работы с мышью в режиме User Size
    QPoint ConvertToPagePos(const QPoint& widgetPos);
    void HandleMousePress(QMouseEvent* event);
    void HandleMouseMove(QMouseEvent* event);
    void HandleMouseRelease(QMouseEvent* event);
    void DebugMouse(const QString& eventName, const QPoint& pos);
    bool eventFilter(QObject* obj, QEvent* event) override;


protected:
    void mouseMoveEvent     (QMouseEvent *event) override;
    void mousePressEvent    (QMouseEvent *event) override;
    void mouseReleaseEvent  (QMouseEvent *event) override;



signals:
    void NeedPixmap(int NeededTab, int NeededWidth, int NeededHeight, int NeededScale);

};


#endif // PRINTPREVIEW_H
