#include "printpreview.h"



PrintPreview::PrintPreview(int NumberOfPlotTabs, QWidget *parent) : QWidget{parent}
{
    SetUpGeneralStyle(); // Настраиваем общий стиль

    SetUpPrinter(); // Настраиваем принтер

    SetUpPreviewArea(); // Настраиваем область предпросмотра

    FillCheckBoxes(NumberOfPlotTabs); // Заполняем область галочек

    FillPresetButtons(); //Заполняем область шаблонов расположения

    FillCompClearPrintClearButtons(); // Заполняем область кнопок печати и очистки

    SetUpConnections(); // Настраиваем соединения

    CalculateMargins(); // Вычисляем значения отступов в пикселях

    FillLayout(); // Инициируем и заполняем компоновки
}



void PrintPreview::SetUpGeneralStyle()
{
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
}

void PrintPreview::SetUpPrinter()
{
    qDebug()<< "Here1?";
    Printer = new QPrinter(QPrinter::HighResolution); // Спросить Алексея
    qDebug()<< "Here2?";
    Printer->setOutputFormat(QPrinter::PdfFormat);
    Printer->setOutputFileName("C:/Users/HP/Desktop/Напечатанные графики.pdf"); //Название файла для сохранения -- надо бы добавить место, где его менять
    Printer->setPageSize(QPageSize::A4);
    Printer->setFullPage(true);
    Printer->setResolution(300);
    Printer->setPageMargins(QMargins(20,10,10,10), QPageLayout::Millimeter);
    dpi = Printer->resolution();
    if (!Printer || !Printer->isValid())
    {
        qDebug()<<"Not Valid!";
    }
}

void PrintPreview::SetUpPreviewArea()
{
    PrintPreviewWidget = new QPrintPreviewWidget(Printer, this);
    PrintPreviewWidget->setCurrentPage(0);
    PrintPreviewWidget->setPortraitOrientation();
    PrintPreviewWidget->setSinglePageViewMode();
    PrintPreviewWidget->setMouseTracking(true);
}

void PrintPreview::FillCheckBoxes(int NumberOfPlotTabs)
{

    CheckBoxLayout = new QVBoxLayout();

    CheckBoxGroup = new QButtonGroup(this);
    CheckBoxGroup->setExclusive(true);

    // Окошки для галочек, с каким графиком работаем
    for (int i=0; i<NumberOfPlotTabs; i++)
    {
        QCheckBox * NewCheckBox = new QCheckBox("");
        NewCheckBox->setLayoutDirection(Qt::RightToLeft);
        CheckBoxGroup->addButton(NewCheckBox, i);
        CheckBoxLayout->addWidget(NewCheckBox);
    }
    CheckBoxGroup->button(0)->setChecked(true);
}

void PrintPreview::FillPresetButtons()
{

    PresetButtonsContainerWidget = new QWidget(this);
    PresetLayout       = new QGridLayout();

    // Кнопки изменения размеров
    UserSize            = new QPushButton("User Size",this);
    WholePage           = new QPushButton("", this);

    UpperHalf           = new QPushButton("", this);
    LowerHalf           = new QPushButton("", this);

    UpperThird          = new QPushButton("", this);
    MiddleThird         = new QPushButton("", this);
    BottomThird         = new QPushButton("", this);

    TopLeftQuarter      = new QPushButton("", this);
    TopRightQuarter     = new QPushButton("", this);
    BottomLeftQuarter   = new QPushButton("", this);
    BottomRightQuarter  = new QPushButton("", this);

    TopLeftSixth        = new QPushButton("", this);
    TopRightSixth       = new QPushButton("", this);
    MiddleLeftSixth     = new QPushButton("", this);
    MiddleRightSixth    = new QPushButton("", this);
    BottomLeftSixth     = new QPushButton("", this);
    BottomRightSixth    = new QPushButton("", this);

    QButtonGroup * PresetButtonGroup = new QButtonGroup(this);
    PresetButtonGroup->setExclusive(true);
    PresetButtonGroup->addButton(UserSize);
    PresetButtonGroup->addButton(WholePage);
    PresetButtonGroup->addButton(UpperHalf);
    PresetButtonGroup->addButton(LowerHalf);
    PresetButtonGroup->addButton(UpperThird);
    PresetButtonGroup->addButton(MiddleThird);
    PresetButtonGroup->addButton(BottomThird);
    PresetButtonGroup->addButton(TopLeftQuarter);
    PresetButtonGroup->addButton(TopRightQuarter);
    PresetButtonGroup->addButton(BottomLeftQuarter);
    PresetButtonGroup->addButton(BottomRightQuarter);
    PresetButtonGroup->addButton(TopLeftSixth);
    PresetButtonGroup->addButton(TopRightSixth);
    PresetButtonGroup->addButton(MiddleLeftSixth);
    PresetButtonGroup->addButton(MiddleRightSixth);
    PresetButtonGroup->addButton(BottomLeftSixth);
    PresetButtonGroup->addButton(BottomRightSixth);

    PresetLayout->addWidget(UserSize,              0,0,4,12);

    PresetLayout->addWidget(WholePage,             4,0,12,2);

    PresetLayout->addWidget(UpperHalf,             4,2,6,2);
    PresetLayout->addWidget(LowerHalf,             10,2,6,2);

    PresetLayout->addWidget(UpperThird,            4,4,4,2);
    PresetLayout->addWidget(MiddleThird,           8,4,4,2);
    PresetLayout->addWidget(BottomThird,           12,4,4,2);

    PresetLayout->addWidget(TopLeftQuarter,        4,6,6,1);
    PresetLayout->addWidget(TopRightQuarter,       4,7,6,1);
    PresetLayout->addWidget(BottomLeftQuarter,     10,6,6,1);
    PresetLayout->addWidget(BottomRightQuarter,    10,7,6,1);

    PresetLayout->addWidget(TopLeftSixth,          4,8,4,1);
    PresetLayout->addWidget(TopRightSixth,         4,9,4,1);
    PresetLayout->addWidget(MiddleLeftSixth,       8,8,4,1);
    PresetLayout->addWidget(MiddleRightSixth,      8,9,4,1);
    PresetLayout->addWidget(BottomLeftSixth,       12,8,4,1);
    PresetLayout->addWidget(BottomRightSixth,      12,9,4,1);


    for (QAbstractButton * button : PresetButtonGroup->buttons()) {
        if (button)
        {
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            button->setCheckable(true);
        }
        else
        {
            qDebug() << "Null Button in Preset";
        }
    }


    UserSize->setChecked(true);


    PresetLayout->setSpacing(0);
    PresetLayout->setContentsMargins(0, 0, 0, 0);
    PresetButtonsContainerWidget->setMaximumSize(250,120);

    PresetButtonsContainerWidget->setLayout(PresetLayout);


}

void PrintPreview::FillCompClearPrintClearButtons()
{
    CompClearPrintClearLayout= new QGridLayout();

    //Кнопки очистки и сохранения
    CompPlusButton      = new QPushButton("Comp +",this);
    ClearCompButton     = new QPushButton("Clear",this);
    PrintPlusButton     = new QPushButton("Print +",this);
    ClearPrintButton    = new QPushButton("Clear",this);



    CompClearPrintClearLayout->addWidget(CompPlusButton     ,0,0);
    CompClearPrintClearLayout->addWidget(ClearCompButton    ,0,1);
    CompClearPrintClearLayout->addWidget(PrintPlusButton    ,1,0);
    CompClearPrintClearLayout->addWidget(ClearPrintButton   ,1,1);
}

void PrintPreview::SetUpConnections()
{
    ConnectPresetButtons();

    // Соединяем сигнал запроса на отрисовку к нашей функции рисования
    connect(PrintPreviewWidget, &QPrintPreviewWidget::paintRequested, this, &PrintPreview::OnPaintRequested);


    // Подсоединяем галочки
    // (Можно сразу все через группу подсоединить)
    connect(CheckBoxGroup, &QButtonGroup::idClicked, this,  &PrintPreview::SendSignalForPixmap);

    connect(CompPlusButton,    &QPushButton::clicked, this, &PrintPreview::OnCompPlusButtonClicked);
    connect(ClearCompButton,   &QPushButton::clicked, this, &PrintPreview::OnClearCompButtonClicked);
    connect(PrintPlusButton,   &QPushButton::clicked, this, &PrintPreview::OnPrintPlusButtonClicked);
    connect(ClearPrintButton,  &QPushButton::clicked, this, &PrintPreview::OnClearPrintButtonClicked);
}

void PrintPreview::ConnectPresetButtons()
{
    // Соединяем кнопки шаблонов
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
}

void PrintPreview::CalculateMargins()
{
    LeftMargin    = LeftMarginInMM  *dpi/25.4; // Отступ слева
    TopMargin     = TopMarginInMM   *dpi/25.4; // Отступ сверху
    RightMargin   = RightMarginInMM *dpi/25.4; // Отступ справа
    BottomMargin  = BottomMarginInMM*dpi/25.4; // Отступ снизу
    RightMarginX  = (Printer->pageRect(QPrinter::Millimeter).width()  - RightMarginInMM )*dpi/25.4; //Координата правой границы
    BottomMarginY = (Printer->pageRect(QPrinter::Millimeter).height() - BottomMarginInMM)*dpi/25.4; //Координата нижней  границы
}



void PrintPreview::FillLayout()
{
    PrintPreviewLayout = new QHBoxLayout(this);


    PrintPreviewLayout->addWidget(PrintPreviewWidget);

    ButtonsPanelWidget = new QWidget(this);
    ButtonsPanelWidget->setMaximumWidth(250);

    ButtonsPanelWidget->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    ButtonsPanelLayout = new QVBoxLayout(ButtonsPanelWidget);
    ButtonsPanelWidget->setLayout(ButtonsPanelLayout);

    PrintPreviewLayout->addWidget(ButtonsPanelWidget);

    ButtonsPanelLayout->addLayout(CheckBoxLayout);
    ButtonsPanelLayout->addWidget(PresetButtonsContainerWidget);
    ButtonsPanelLayout->addLayout(CompClearPrintClearLayout);

    setLayout(PrintPreviewLayout);
}



void PrintPreview::OnPixmapReceived(QPixmap Pixmap)
{
    CurrentPixmap = Pixmap;
    PrintPreviewWidget->updatePreview();
}



void PrintPreview::SendSignalForPixmap(int TabID)
{
    QRect rect = RectFromPreset(CurrentPreset);
    int width = rect.width()*25.4/dpi;
    int height = rect.height()*25.4/dpi;
    emit NeedPixmap(TabID, width, height, 1.0);
}





void PrintPreview::MoveAndResizeToUserSize              (){CurrentPreset = Preset::usersize;           SendSignalForPixmap(CheckBoxGroup->checkedId());}
void PrintPreview::MoveAndResizeToWholePage             (){CurrentPreset = Preset::wholepage;          SendSignalForPixmap(CheckBoxGroup->checkedId());}
void PrintPreview::MoveAndResizeToUpperHalf             (){CurrentPreset = Preset::upperhalf;          SendSignalForPixmap(CheckBoxGroup->checkedId());}
void PrintPreview::MoveAndResizeToLowerHalf             (){CurrentPreset = Preset::lowerhalf;          SendSignalForPixmap(CheckBoxGroup->checkedId());}
void PrintPreview::MoveAndResizeToUpperThird            (){CurrentPreset = Preset::upperthird;         SendSignalForPixmap(CheckBoxGroup->checkedId());}
void PrintPreview::MoveAndResizeToMiddleThird           (){CurrentPreset = Preset::middlethird;        SendSignalForPixmap(CheckBoxGroup->checkedId());}
void PrintPreview::MoveAndResizeToBottomThird           (){CurrentPreset = Preset::bottomthird;        SendSignalForPixmap(CheckBoxGroup->checkedId());}
void PrintPreview::MoveAndResizeToTopLeftQuarter        (){CurrentPreset = Preset::topleftquarter;     SendSignalForPixmap(CheckBoxGroup->checkedId());}
void PrintPreview::MoveAndResizeToTopRightQuarter       (){CurrentPreset = Preset::toprightquarter;    SendSignalForPixmap(CheckBoxGroup->checkedId());}
void PrintPreview::MoveAndResizeToBottomLeftQuarter     (){CurrentPreset = Preset::bottomleftquarter;  SendSignalForPixmap(CheckBoxGroup->checkedId());}
void PrintPreview::MoveAndResizeToBottomRightQuarter    (){CurrentPreset = Preset::bottomrightquarter; SendSignalForPixmap(CheckBoxGroup->checkedId());}
void PrintPreview::MoveAndResizeToTopLeftSixth          (){CurrentPreset = Preset::topleftsixth;       SendSignalForPixmap(CheckBoxGroup->checkedId());}
void PrintPreview::MoveAndResizeToTopRightSixth         (){CurrentPreset = Preset::toprightsixth;      SendSignalForPixmap(CheckBoxGroup->checkedId());}
void PrintPreview::MoveAndResizeToMiddleLeftSixth       (){CurrentPreset = Preset::middleleftsixth;    SendSignalForPixmap(CheckBoxGroup->checkedId());}
void PrintPreview::MoveAndResizeToMiddleRightSixth      (){CurrentPreset = Preset::middlerightsixth;   SendSignalForPixmap(CheckBoxGroup->checkedId());}
void PrintPreview::MoveAndResizeToBottomLeftSixth       (){CurrentPreset = Preset::bottomleftsixth;    SendSignalForPixmap(CheckBoxGroup->checkedId());}
void PrintPreview::MoveAndResizeToBottomRightSixth      (){CurrentPreset = Preset::bottomrightsixth;   SendSignalForPixmap(CheckBoxGroup->checkedId());}




void PrintPreview::OnCompPlusButtonClicked  ()
{
    QImage CurrentImage = CurrentPixmap.toImage();

    VectorOfImages.append(CurrentImage);
    VectorOfPresets.append(CurrentPreset);
}

void PrintPreview::OnClearCompButtonClicked ()
{
    VectorOfImages.clear();
    VectorOfPresets.clear();
    UpdatePreview();
}

void PrintPreview::OnPrintPlusButtonClicked ()
{

}

void PrintPreview::OnClearPrintButtonClicked()
{

}







// Поменять upper на top

QRect PrintPreview::RectFromPreset(Preset PresetInput)
{
    QRect Rect(LeftMargin, TopMargin,0,0);
    int width;
    int height;
    switch (PresetInput)
    {
    case Preset::usersize:
        Rect = QRect(LeftMargin, TopMargin, 10, 10);
        break;
    case Preset::wholepage:
        width = RightMarginX-LeftMargin;
        height= BottomMarginY-TopMargin;
        Rect = QRect(LeftMargin, TopMargin, width, height);
        break;
    case Preset::upperhalf:
        width = (RightMarginX-LeftMargin);
        height= (BottomMarginY-TopMargin)/2;
        Rect = QRect(LeftMargin, TopMargin, width, height);
        break;
    case Preset::lowerhalf:
        width = (RightMarginX-LeftMargin);
        height= (BottomMarginY-TopMargin)/2;
        Rect = QRect(LeftMargin, TopMargin+height, width, height);
        break;
    case Preset::upperthird:
        width = (RightMarginX-LeftMargin);
        height= (BottomMarginY-TopMargin)/3;
        Rect = QRect(LeftMargin, TopMargin, width, height);
        break;
    case Preset::middlethird:
        width = (RightMarginX-LeftMargin);
        height= (BottomMarginY-TopMargin)/3;
        Rect = QRect(LeftMargin, TopMargin+height, width, height);
        break;
    case Preset::bottomthird:
        width = (RightMarginX-LeftMargin);
        height= (BottomMarginY-TopMargin)/3;
        Rect = QRect(LeftMargin, TopMargin+height*2, width, height);
        break;
    case Preset::topleftquarter:
        width = (RightMarginX-LeftMargin)/2;
        height= (BottomMarginY-TopMargin)/2;
        Rect = QRect(LeftMargin, TopMargin, width, height);
        break;
    case Preset::toprightquarter:
        width = (RightMarginX-LeftMargin)/2;
        height= (BottomMarginY-TopMargin)/2;
        Rect = QRect(LeftMargin+width, TopMargin, width, height);
        break;
    case Preset::bottomleftquarter:
        width = (RightMarginX-LeftMargin)/2;
        height= (BottomMarginY-TopMargin)/2;
        Rect = QRect(LeftMargin, TopMargin+height, width, height);
        break;
    case Preset::bottomrightquarter:
        width = (RightMarginX-LeftMargin)/2;
        height= (BottomMarginY-TopMargin)/2;
        Rect = QRect(LeftMargin+width, TopMargin+height, width, height);
        break;
    case Preset::topleftsixth:
        width = (RightMarginX - LeftMargin) / 2;
        height = (BottomMarginY - TopMargin) / 3;
        Rect = QRect(LeftMargin, TopMargin, width, height);
        break;
    case Preset::toprightsixth:
        width = (RightMarginX - LeftMargin) / 2;
        height = (BottomMarginY - TopMargin) / 3;
        Rect = QRect(LeftMargin + width, TopMargin, width, height);
        break;
    case Preset::middleleftsixth:
        width = (RightMarginX - LeftMargin) / 2;
        height = (BottomMarginY - TopMargin) / 3;
        Rect = QRect(LeftMargin, TopMargin + height, width, height);
        break;
    case Preset::middlerightsixth:
        width = (RightMarginX - LeftMargin) / 2;
        height = (BottomMarginY - TopMargin) / 3;
        Rect = QRect(LeftMargin + width, TopMargin + height, width, height);
        break;
    case Preset::bottomleftsixth:
        width = (RightMarginX - LeftMargin) / 2;
        height = (BottomMarginY - TopMargin) / 3;
        Rect = QRect(LeftMargin, TopMargin + height * 2, width, height);
        break;
    case Preset::bottomrightsixth:
        width = (RightMarginX - LeftMargin) / 2;
        height = (BottomMarginY - TopMargin) / 3;
        Rect = QRect(LeftMargin + width, TopMargin + height * 2, width, height);
        break;
    }
    return Rect;
}

void PrintPreview::DrawPreset(QImage image, QPainter & painter, Preset PresetInput)
{
    QRect rect = RectFromPreset(PresetInput);
    painter.drawImage(rect, image);
}






void PrintPreview::UpdatePreview()
{  
    PrintPreviewWidget->updatePreview();
    PrintPreviewWidget->print();
    PrintPreviewWidget->show();
}


void PrintPreview::OnPaintRequested()
{
    QPainter Painter(Printer);

    //Painter.drawText(9*dpi/25.4, 9*dpi/25.4, "Графики:");
    QPen DottedPen(Qt::black);
    DottedPen.setStyle(Qt::DashLine);
    DottedPen.setWidth(0.3*dpi/25.4);
    Painter.setPen(DottedPen);

    Painter.drawLine(LeftMargin    , TopMargin     , RightMarginX  , TopMargin    ); // Верхняя линия
    Painter.drawLine(LeftMargin    , BottomMarginY , RightMarginX  , BottomMarginY); // Нижняя линия
    Painter.drawLine(LeftMargin    , TopMargin     , LeftMargin    , BottomMarginY); // Левая линия
    Painter.drawLine(RightMarginX  , TopMargin     , RightMarginX  , BottomMarginY); // Правая линия

    QImage CurrentPlotImage = CurrentPixmap.toImage();

    DrawPreset(CurrentPlotImage, Painter, CurrentPreset);

    for (int i=0; i<VectorOfImages.size(); i++)
    {
        DrawPreset(VectorOfImages[i], Painter, VectorOfPresets[i]);
    }

    //PrintPreviewWidget->updatePreview();
    //PrintPreviewWidget->print();
    //PrintPreviewWidget->show();

}





void PrintPreview::UpdateText()
{

}


PrintPreview::~PrintPreview()
{
    delete Printer;
    Printer = nullptr;
}

































// Попробовать через QPdfDocument
// Устаревшее

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


