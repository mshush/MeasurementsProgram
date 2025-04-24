#include "printpreview.h"



PrintPreview::PrintPreview(QWidget *parent) : QWidget{parent}
{
    Printer = new QPrinter(QPrinter::HighResolution);
    Printer->setOutputFormat(QPrinter::PdfFormat);
    Printer->setOutputFileName("C:/Users/HP/Desktop/Напечатанные графики.pdf");
    Printer->setPageSize(QPageSize::A4);
    Printer->setFullPage(true);
    Printer->setResolution(300);
    Printer->setPageMargins(QMargins(20,10,10,10), QPageLayout::Millimeter);

    dpi = Printer->resolution();
    LeftMargin    = LeftMarginInMM  *dpi/25.4; // Отступ слева
    TopMargin     = TopMarginInMM   *dpi/25.4; // Отступ сверху
    RightMargin   = RightMarginInMM *dpi/25.4; // Отступ справа
    BottomMargin  = BottomMarginInMM*dpi/25.4; // Отступ снизу
    RightMarginX  = (Printer->pageRect(QPrinter::Millimeter).width()  - RightMarginInMM )*dpi/25.4; //Координата правой границы
    BottomMarginY = (Printer->pageRect(QPrinter::Millimeter).height() - BottomMarginInMM)*dpi/25.4; //Координата нижней  границы


    PrintPreviewWidget = new QPrintPreviewWidget(Printer,this);
    PrintPreviewWidget->setCurrentPage(0);
    PrintPreviewWidget->setPortraitOrientation();
    PrintPreviewWidget->setSinglePageViewMode();

    PrintPreviewWidget->setMouseTracking(true);

    connect(PrintPreviewWidget, &QPrintPreviewWidget::paintRequested, this, [this](QPrinter *printer)
    {
        QPainter Painter(Printer);
        Painter.drawText(9*dpi/25.4, 9*dpi/25.4, "Графики:");
        QPen DottedPen(Qt::black);
        DottedPen.setStyle(Qt::DashLine);
        DottedPen.setWidth(0.3*dpi/25.4);
        Painter.setPen(DottedPen);

        Painter.drawLine(LeftMargin    , TopMargin     , RightMarginX  , TopMargin    ); // Верхняя линия
        Painter.drawLine(LeftMargin    , BottomMarginY , RightMarginX  , BottomMarginY); // Нижняя линия
        Painter.drawLine(LeftMargin    , TopMargin     , LeftMargin    , BottomMarginY); // Левая линия
        Painter.drawLine(RightMarginX  , TopMargin     , RightMarginX  , BottomMarginY); // Правая линия



        this->DrawPreset(VectorOfPlotImages[0], Painter);
        qDebug()<<"Works here";

        //PrintPreviewWidget->updatePreview();
        //PrintPreviewWidget->print();
        //PrintPreviewWidget->show();
    });




    PrintPreviewLayout       = new QHBoxLayout(this);
    OldButtonsLayout         = new QVBoxLayout();
    CheckBoxLayout           = new QGridLayout();
    SizeLocationLayout       = new QGridLayout();
    CompClearPrintClearLayout= new QGridLayout();

    SizeLocationContainerWidget = new QWidget(this);


    setLayout(PrintPreviewLayout);

    PrintPreviewLayout->addWidget(PrintPreviewWidget);
    PrintPreviewLayout->addLayout(OldButtonsLayout);

    OldButtonsLayout->addLayout(CheckBoxLayout);
    OldButtonsLayout->addWidget(SizeLocationContainerWidget);
    SizeLocationContainerWidget->setLayout(SizeLocationLayout);
    OldButtonsLayout->addLayout(CompClearPrintClearLayout);

    // Окошки для галочек, с каким графиком работаем
    PreviewBox      = new QCheckBox();
    FrequencyBox    = new QCheckBox();
    PatternBox      = new QCheckBox();
    DownRangeBox    = new QCheckBox();
    CrossRangeBox   = new QCheckBox();
    StatisticaBox   = new QCheckBox();
    Frequency_DRBox = new QCheckBox();
    CompositeBox    = new QCheckBox();


    QButtonGroup *CheckboxGroup = new QButtonGroup(this);
    CheckboxGroup->setExclusive(true);
    CheckboxGroup->addButton(PreviewBox);
    CheckboxGroup->addButton(FrequencyBox);
    CheckboxGroup->addButton(PatternBox);
    CheckboxGroup->addButton(DownRangeBox);
    CheckboxGroup->addButton(CrossRangeBox);
    CheckboxGroup->addButton(StatisticaBox);
    CheckboxGroup->addButton(Frequency_DRBox);
    CheckboxGroup->addButton(CompositeBox);


    // Подписи к окошкам
    PreviewLabel        = new QLabel("Preview");
    FrequencyLabel      = new QLabel("Frequency");
    PatternLabel        = new QLabel("Pattern");
    DownRangeLabel      = new QLabel("Down-Range");
    CrossRangeLabel     = new QLabel("Cross-Range");
    StatisticaLabel     = new QLabel("Statistica");
    Frequency_DRLabel   = new QLabel("Frequency/DR");
    CompositeLabel      = new QLabel("Composite");

    // Кнопки изменения размеров
    UserSize            = new QPushButton("User Size");
    WholePage           = new QPushButton("");

    UpperHalf           = new QPushButton("");
    LowerHalf           = new QPushButton("");

    UpperThird          = new QPushButton("");
    MiddleThird         = new QPushButton("");
    BottomThird         = new QPushButton("");

    TopLeftQuarter      = new QPushButton("");
    TopRightQuarter     = new QPushButton("");
    BottomLeftQuarter   = new QPushButton("");
    BottomRightQuarter  = new QPushButton("");

    TopLeftSixth        = new QPushButton("");
    TopRightSixth       = new QPushButton("");
    MiddleLeftSixth     = new QPushButton("");
    MiddleRightSixth    = new QPushButton("");
    BottomLeftSixth     = new QPushButton("");
    BottomRightSixth    = new QPushButton("");

    UserSize            ->setCheckable(true);
    WholePage           ->setCheckable(true);
    UpperHalf           ->setCheckable(true);
    LowerHalf           ->setCheckable(true);
    UpperThird          ->setCheckable(true);
    MiddleThird         ->setCheckable(true);
    BottomThird         ->setCheckable(true);
    TopLeftQuarter      ->setCheckable(true);
    TopRightQuarter     ->setCheckable(true);
    BottomLeftQuarter   ->setCheckable(true);
    BottomRightQuarter  ->setCheckable(true);
    TopLeftSixth        ->setCheckable(true);
    TopRightSixth       ->setCheckable(true);
    MiddleLeftSixth     ->setCheckable(true);
    MiddleRightSixth    ->setCheckable(true);
    BottomLeftSixth     ->setCheckable(true);
    BottomRightSixth    ->setCheckable(true);

    UserSize->setChecked(true);


    //Кнопки очистки и сохранения
    CompPlusButton      = new QPushButton("Comp +");
    ClearCompButton     = new QPushButton("Clear");
    PrintPlusButton     = new QPushButton("Print +");
    ClearPrintButton    = new QPushButton("Clear");


    CheckBoxLayout->addWidget(PreviewLabel,       0,0);
    CheckBoxLayout->addWidget(FrequencyLabel,     1,0);
    CheckBoxLayout->addWidget(PatternLabel,       2,0);
    CheckBoxLayout->addWidget(DownRangeLabel,     3,0);
    CheckBoxLayout->addWidget(CrossRangeLabel,    4,0);
    CheckBoxLayout->addWidget(StatisticaLabel,    5,0);
    CheckBoxLayout->addWidget(Frequency_DRLabel,  6,0);
    CheckBoxLayout->addWidget(CompositeLabel,     7,0);

    CheckBoxLayout->addWidget(PreviewBox,         0,1);
    CheckBoxLayout->addWidget(FrequencyBox,       1,1);
    CheckBoxLayout->addWidget(PatternBox,         2,1);
    CheckBoxLayout->addWidget(DownRangeBox,       3,1);
    CheckBoxLayout->addWidget(CrossRangeBox,      4,1);
    CheckBoxLayout->addWidget(StatisticaBox,      5,1);
    CheckBoxLayout->addWidget(Frequency_DRBox,    6,1);
    CheckBoxLayout->addWidget(CompositeBox,       7,1);

    connect(PreviewBox,     &QCheckBox::toggled, this, &PrintPreview::PreviewBoxClicked);
    connect(FrequencyBox,   &QCheckBox::toggled, this, &PrintPreview::PreviewBoxClicked);
    connect(PatternBox,     &QCheckBox::toggled, this, &PrintPreview::PreviewBoxClicked);
    connect(DownRangeBox,   &QCheckBox::toggled, this, &PrintPreview::PreviewBoxClicked);
    connect(CrossRangeBox,  &QCheckBox::toggled, this, &PrintPreview::PreviewBoxClicked);
    connect(StatisticaBox,  &QCheckBox::toggled, this, &PrintPreview::PreviewBoxClicked);
    connect(Frequency_DRBox,&QCheckBox::toggled, this, &PrintPreview::PreviewBoxClicked);
    connect(CompositeBox,   &QCheckBox::toggled, this, &PrintPreview::PreviewBoxClicked);


    SizeLocationLayout->addWidget(UserSize,              0,0,4,12);

    SizeLocationLayout->addWidget(WholePage,             4,0,12,2);

    SizeLocationLayout->addWidget(UpperHalf,             4,2,6,2);
    SizeLocationLayout->addWidget(LowerHalf,             10,2,6,2);

    SizeLocationLayout->addWidget(UpperThird,            4,4,4,2);
    SizeLocationLayout->addWidget(MiddleThird,           8,4,4,2);
    SizeLocationLayout->addWidget(BottomThird,           12,4,4,2);

    SizeLocationLayout->addWidget(TopLeftQuarter,        4,6,6,1);
    SizeLocationLayout->addWidget(TopRightQuarter,       4,7,6,1);
    SizeLocationLayout->addWidget(BottomLeftQuarter,     10,6,6,1);
    SizeLocationLayout->addWidget(BottomRightQuarter,    10,7,6,1);

    SizeLocationLayout->addWidget(TopLeftSixth,          4,8,4,1);
    SizeLocationLayout->addWidget(TopRightSixth,         4,9,4,1);
    SizeLocationLayout->addWidget(MiddleLeftSixth,       8,8,4,1);
    SizeLocationLayout->addWidget(MiddleRightSixth,      8,9,4,1);
    SizeLocationLayout->addWidget(BottomLeftSixth,       12,8,4,1);
    SizeLocationLayout->addWidget(BottomRightSixth,      12,9,4,1);


    UserSize            ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    WholePage           ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    UpperHalf           ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    LowerHalf           ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    UpperThird          ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    MiddleThird         ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    BottomThird         ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    TopLeftQuarter      ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    TopRightQuarter     ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    BottomLeftQuarter   ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    BottomRightQuarter  ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    TopLeftSixth        ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    TopRightSixth       ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    MiddleLeftSixth     ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    MiddleRightSixth    ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    BottomLeftSixth     ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    BottomRightSixth    ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(UserSize,           &QPushButton::clicked, this, &PrintPreview::MoveAndResizeToUserSize);
    connect(WholePage,          &QPushButton::clicked, this, &PrintPreview::MoveAndResizeToWholePage);
    connect(UpperHalf,          &QPushButton::clicked, this, &PrintPreview::MoveAndResizeToUpperHalf);
    connect(LowerHalf,          &QPushButton::clicked, this, &PrintPreview::MoveAndResizeToLowerHalf);
    connect(UpperThird,         &QPushButton::clicked, this, &PrintPreview::MoveAndResizeToUpperThird);
    connect(MiddleThird,        &QPushButton::clicked, this, &PrintPreview::MoveAndResizeToMiddleThird);
    connect(BottomThird,        &QPushButton::clicked, this, &PrintPreview::MoveAndResizeToBottomThird);
    connect(TopLeftQuarter,     &QPushButton::clicked, this, &PrintPreview::MoveAndResizeToTopLeftQuarter);
    connect(TopRightQuarter,    &QPushButton::clicked, this, &PrintPreview::MoveAndResizeToTopRightQuarter);
    connect(BottomLeftQuarter,  &QPushButton::clicked, this, &PrintPreview::MoveAndResizeToBottomLeftQuarter);
    connect(BottomRightQuarter, &QPushButton::clicked, this, &PrintPreview::MoveAndResizeToBottomRightQuarter);
    connect(TopLeftSixth,       &QPushButton::clicked, this, &PrintPreview::MoveAndResizeToTopLeftSixth);
    connect(TopRightSixth,      &QPushButton::clicked, this, &PrintPreview::MoveAndResizeToTopRightSixth);
    connect(MiddleLeftSixth,    &QPushButton::clicked, this, &PrintPreview::MoveAndResizeToMiddleLeftSixth);
    connect(MiddleRightSixth,   &QPushButton::clicked, this, &PrintPreview::MoveAndResizeToMiddleRightSixth);
    connect(BottomLeftSixth,    &QPushButton::clicked, this, &PrintPreview::MoveAndResizeToBottomLeftSixth);
    connect(BottomRightSixth,   &QPushButton::clicked, this, &PrintPreview::MoveAndResizeToBottomRightSixth);


    SizeLocationLayout->setSpacing(0);
    SizeLocationLayout->setContentsMargins(0, 0, 0, 0);

    SizeLocationContainerWidget->setMaximumSize(200,100);


    CompClearPrintClearLayout->addWidget(CompPlusButton     ,0,0);
    CompClearPrintClearLayout->addWidget(ClearCompButton    ,0,1);
    CompClearPrintClearLayout->addWidget(PrintPlusButton    ,1,0);
    CompClearPrintClearLayout->addWidget(ClearPrintButton   ,1,1);

    connect(CompPlusButton,    &QPushButton::clicked, this, &PrintPreview::OnCompPlusButtonClicked);
    connect(ClearCompButton,   &QPushButton::clicked, this, &PrintPreview::OnClearCompButtonClicked);
    connect(PrintPlusButton,   &QPushButton::clicked, this, &PrintPreview::OnPrintPlusButtonClicked);
    connect(ClearPrintButton,  &QPushButton::clicked, this, &PrintPreview::OnClearPrintButtonClicked);




    QButtonGroup * LocationSizeButtonGroup = new QButtonGroup(this);
    LocationSizeButtonGroup->setExclusive(true);
    LocationSizeButtonGroup->addButton(UserSize);
    LocationSizeButtonGroup->addButton(WholePage);
    LocationSizeButtonGroup->addButton(UpperHalf);
    LocationSizeButtonGroup->addButton(LowerHalf);
    LocationSizeButtonGroup->addButton(UpperThird);
    LocationSizeButtonGroup->addButton(MiddleThird);
    LocationSizeButtonGroup->addButton(BottomThird);
    LocationSizeButtonGroup->addButton(TopLeftQuarter);
    LocationSizeButtonGroup->addButton(TopRightQuarter);
    LocationSizeButtonGroup->addButton(BottomLeftQuarter);
    LocationSizeButtonGroup->addButton(BottomRightQuarter);
    LocationSizeButtonGroup->addButton(TopLeftSixth);
    LocationSizeButtonGroup->addButton(TopRightSixth);
    LocationSizeButtonGroup->addButton(MiddleLeftSixth);
    LocationSizeButtonGroup->addButton(MiddleRightSixth);
    LocationSizeButtonGroup->addButton(BottomLeftSixth);
    LocationSizeButtonGroup->addButton(BottomRightSixth);



















    /*
    for (int page = 0; page < 5; page++)
    {
        p.drawText(1750, 200, QString("Date: %1").arg(QDateTime::currentDateTime().toString("dd.MM.yyyy")));


        p.fillRect(QRect(150,150,2179,125),QBrush(QColor(222,222,230,255)));
        Printer->newPage();
    }
    PrintPreviewWidget->print();
    PrintPreviewWidget->show();
    PreviewButton = new QPushButton("Show Print Preview", this);

    HPrintLayout->addWidget(PrintPreviewWidget);
    HPrintLayout->addWidget(PreviewButton);
    */


}



void PrintPreview::PreviewBoxClicked      (bool checked){if (checked){ActiveButton = 0;VectorOfPlotNumbers.append(ActiveButton);}else {ActiveButton=-1;}}
void PrintPreview::FrequencyBoxClicked    (bool checked){if (checked){ActiveButton = 1;VectorOfPlotNumbers.append(ActiveButton);}else {ActiveButton=-1;}}
void PrintPreview::PatternBoxClicked      (bool checked){if (checked){ActiveButton = 2;VectorOfPlotNumbers.append(ActiveButton);}else {ActiveButton=-1;}}
void PrintPreview::DownRangeBoxClicked    (bool checked){if (checked){ActiveButton = 3;VectorOfPlotNumbers.append(ActiveButton);}else {ActiveButton=-1;}}
void PrintPreview::CrossRangeBoxClicked   (bool checked){if (checked){ActiveButton = 4;VectorOfPlotNumbers.append(ActiveButton);}else {ActiveButton=-1;}}
void PrintPreview::StatisticaBoxClicked   (bool checked){if (checked){ActiveButton = 5;VectorOfPlotNumbers.append(ActiveButton);}else {ActiveButton=-1;}}
void PrintPreview::Frequency_DRBoxClicked (bool checked){if (checked){ActiveButton = 6;VectorOfPlotNumbers.append(ActiveButton);}else {ActiveButton=-1;}}
void PrintPreview::CompositeBoxClicked    (bool checked){if (checked){ActiveButton = 7;VectorOfPlotNumbers.append(ActiveButton);}else {ActiveButton=-1;}}



void PrintPreview::MoveAndResizeToUserSize              (){Preset = usersize;           UpdatePreview();}
void PrintPreview::MoveAndResizeToWholePage             (){Preset = wholepage;          UpdatePreview();}
void PrintPreview::MoveAndResizeToUpperHalf             (){Preset = upperhalf;          UpdatePreview();}
void PrintPreview::MoveAndResizeToLowerHalf             (){Preset = lowerhalf;          UpdatePreview();}
void PrintPreview::MoveAndResizeToUpperThird            (){Preset = upperthird;         UpdatePreview();}
void PrintPreview::MoveAndResizeToMiddleThird           (){Preset = middlethird;        UpdatePreview();}
void PrintPreview::MoveAndResizeToBottomThird           (){Preset = bottomthird;        UpdatePreview();}
void PrintPreview::MoveAndResizeToTopLeftQuarter        (){Preset = topleftquarter;     UpdatePreview();}
void PrintPreview::MoveAndResizeToTopRightQuarter       (){Preset = toprightquarter;    UpdatePreview();}
void PrintPreview::MoveAndResizeToBottomLeftQuarter     (){Preset = bottomleftquarter;  UpdatePreview();}
void PrintPreview::MoveAndResizeToBottomRightQuarter    (){Preset = bottomrightquarter; UpdatePreview();}
void PrintPreview::MoveAndResizeToTopLeftSixth          (){Preset = topleftsixth;       UpdatePreview();}
void PrintPreview::MoveAndResizeToTopRightSixth         (){Preset = toprightsixth;      UpdatePreview();}
void PrintPreview::MoveAndResizeToMiddleLeftSixth       (){Preset = middleleftsixth;    UpdatePreview();}
void PrintPreview::MoveAndResizeToMiddleRightSixth      (){Preset = middlerightsixth;   UpdatePreview();}
void PrintPreview::MoveAndResizeToBottomLeftSixth       (){Preset = bottomleftsixth;    UpdatePreview();}
void PrintPreview::MoveAndResizeToBottomRightSixth      (){Preset = bottomrightsixth;   UpdatePreview();}




void PrintPreview::OnCompPlusButtonClicked  (){}
void PrintPreview::OnClearCompButtonClicked (){}
void PrintPreview::OnPrintPlusButtonClicked (){}
void PrintPreview::OnClearPrintButtonClicked(){}







// Поменять upper на top



void PrintPreview::DrawPreset(QImage image, QPainter & painter)
{
    QRect targetRect(LeftMargin, TopMargin, image.width(), image.height());
    int width;
    int height;
    switch (Preset) {
    case usersize:
        targetRect = QRect(LeftMargin, TopMargin, image.width(), image.height());
        break;
    case wholepage:
        width = RightMarginX-LeftMargin;
        height= BottomMarginY-TopMargin;
        targetRect = QRect(LeftMargin, TopMargin, width, height);
        break;
    case upperhalf:
        width = (RightMarginX-LeftMargin);
        height= (BottomMarginY-TopMargin)/2;
        targetRect = QRect(LeftMargin, TopMargin, width, height);
        break;
    case lowerhalf:
        width = (RightMarginX-LeftMargin);
        height= (BottomMarginY-TopMargin)/2;
        targetRect = QRect(LeftMargin, TopMargin+height, width, height);
        break;
    case upperthird:
        width = (RightMarginX-LeftMargin);
        height= (BottomMarginY-TopMargin)/3;
        targetRect = QRect(LeftMargin, TopMargin, width, height);
        break;
    case middlethird:
        width = (RightMarginX-LeftMargin);
        height= (BottomMarginY-TopMargin)/3;
        targetRect = QRect(LeftMargin, TopMargin+height, width, height);
        break;
    case bottomthird:
        width = (RightMarginX-LeftMargin);
        height= (BottomMarginY-TopMargin)/3;
        targetRect = QRect(LeftMargin, TopMargin+height*2, width, height);
        break;
    case topleftquarter:
        width = (RightMarginX-LeftMargin)/2;
        height= (BottomMarginY-TopMargin)/2;
        targetRect = QRect(LeftMargin, TopMargin, width, height);
        break;
    case toprightquarter:
        width = (RightMarginX-LeftMargin)/2;
        height= (BottomMarginY-TopMargin)/2;
        targetRect = QRect(LeftMargin+width, TopMargin, width, height);
        break;
    case bottomleftquarter:
        width = (RightMarginX-LeftMargin)/2;
        height= (BottomMarginY-TopMargin)/2;
        targetRect = QRect(LeftMargin, TopMargin+height, width, height);
        break;
    case bottomrightquarter:
        width = (RightMarginX-LeftMargin)/2;
        height= (BottomMarginY-TopMargin)/2;
        targetRect = QRect(LeftMargin+width, TopMargin+height, width, height);
        break;
    case topleftsixth:
        width = (RightMarginX - LeftMargin) / 2;
        height = (BottomMarginY - TopMargin) / 3;
        targetRect = QRect(LeftMargin, TopMargin, width, height);
        break;
    case toprightsixth:
        width = (RightMarginX - LeftMargin) / 2;
        height = (BottomMarginY - TopMargin) / 3;
        targetRect = QRect(LeftMargin + width, TopMargin, width, height);
        break;
    case middleleftsixth:
        width = (RightMarginX - LeftMargin) / 2;
        height = (BottomMarginY - TopMargin) / 3;
        targetRect = QRect(LeftMargin, TopMargin + height, width, height);
        break;
    case middlerightsixth:
        width = (RightMarginX - LeftMargin) / 2;
        height = (BottomMarginY - TopMargin) / 3;
        targetRect = QRect(LeftMargin + width, TopMargin + height, width, height);
        break;
    case bottomleftsixth:
        width = (RightMarginX - LeftMargin) / 2;
        height = (BottomMarginY - TopMargin) / 3;
        targetRect = QRect(LeftMargin, TopMargin + height * 2, width, height);
        break;
    case bottomrightsixth:
        width = (RightMarginX - LeftMargin) / 2;
        height = (BottomMarginY - TopMargin) / 3;
        targetRect = QRect(LeftMargin + width, TopMargin + height * 2, width, height);
        break;
    }

    painter.drawImage(targetRect, image);
    qDebug()<<"painted in " << targetRect;
}


















void PrintPreview::UpdatePreview()
{
    PrintPreviewWidget->updatePreview();
    PrintPreviewWidget->print();
    PrintPreviewWidget->show();
}

































PrintPreview::~PrintPreview()
{
}





// Попробовать через QPdfDocument

