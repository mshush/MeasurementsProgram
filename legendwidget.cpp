#include "legendwidget.h"

LegendWidget::LegendWidget(QWidget *parent)
    : QWidget{parent}
{
    FillLayout();
}

void LegendWidget::FillLayout()
{

    //Компоновки
    VerticalLegendLayot             = new QVBoxLayout(this);
    HorizontalUpperButtonsLayout    = new QHBoxLayout();
    HorizontalLowerCheckboxLayout   = new QHBoxLayout();

    // Кнопки вверху таблицы
    ReadDataButton        = new QPushButton(tr("Read Data"),            this);
    WriteDataButton       = new QPushButton(tr("Write Data"),           this);
    AddLineButton         = new QPushButton(tr("Add Line"),             this);
    DeleteLineButton      = new QPushButton(tr("Delete Line"),          this);
    ClearAllButton        = new QPushButton(tr("Clear All"),            this);
    UpLineButton          = new QPushButton(tr("Up Line"),              this);
    DownLineButton        = new QPushButton(tr("Down Line"),            this);
    CopyToMemoryLineButton= new QPushButton(tr("Copy To Memory Line"),  this);
    RefreshButton         = new QPushButton(tr("Refresh"),this);



    // Под таблицей
    ShowInLegendBoxLabel    = new QLabel(tr("Show in legend box"   ), this);
    GraphTitleEdit         = new QLabel(tr("Graph title"          ), this);
    TitleEdit              = new QLineEdit(tr("Title"                ), this);

    TitleChBox  = new QCheckBox(tr("Title")  ,this);
    DataChBox   = new QCheckBox(tr("Data")   ,this);
    PlaneChBox  = new QCheckBox(tr("Plane")  ,this);
    FreqChBox   = new QCheckBox(tr("Freq")   ,this);
    AzChBox     = new QCheckBox(tr("Az")     ,this);
    ElChBox     = new QCheckBox(tr("El")     ,this);
    DistChBox   = new QCheckBox(tr("Dist")   ,this);
    ChannelChBox= new QCheckBox(tr("Channel"),this);

    LegendTable = new QTableWidget(this);



    HorizontalUpperButtonsLayout->addWidget(ReadDataButton);
    HorizontalUpperButtonsLayout->addWidget(WriteDataButton);
    HorizontalUpperButtonsLayout->addWidget(AddLineButton);
    HorizontalUpperButtonsLayout->addWidget(DeleteLineButton);
    HorizontalUpperButtonsLayout->addWidget(ClearAllButton);
    HorizontalUpperButtonsLayout->addWidget(UpLineButton);
    HorizontalUpperButtonsLayout->addWidget(DownLineButton);
    HorizontalUpperButtonsLayout->addWidget(CopyToMemoryLineButton);
    HorizontalUpperButtonsLayout->addWidget(RefreshButton);

    VerticalLegendLayot->addLayout(HorizontalUpperButtonsLayout);

    VerticalLegendLayot->addWidget(LegendTable);

    HorizontalLowerCheckboxLayout->addWidget(ShowInLegendBoxLabel);
    HorizontalLowerCheckboxLayout->addWidget(TitleChBox);
    HorizontalLowerCheckboxLayout->addWidget(DataChBox);
    HorizontalLowerCheckboxLayout->addWidget(PlaneChBox);
    HorizontalLowerCheckboxLayout->addWidget(FreqChBox);
    HorizontalLowerCheckboxLayout->addWidget(AzChBox);
    HorizontalLowerCheckboxLayout->addWidget(ElChBox);
    HorizontalLowerCheckboxLayout->addWidget(DistChBox);
    HorizontalLowerCheckboxLayout->addWidget(ChannelChBox);
    HorizontalLowerCheckboxLayout->addWidget(GraphTitleEdit);
    HorizontalLowerCheckboxLayout->addWidget(TitleEdit);


    VerticalLegendLayot->addLayout(HorizontalLowerCheckboxLayout);

    LegendTable->setRowCount(0); // Пусть для начала она пустой будет
    LegendTable->setColumnCount(11);

    LegendTable->setColumnWidth(0,100);
    LegendTable->setColumnWidth(1,100);
    LegendTable->setColumnWidth(2,100);
    LegendTable->setColumnWidth(3,100);
    LegendTable->setColumnWidth(4,100);
    LegendTable->setColumnWidth(5,100);
    LegendTable->setColumnWidth(6,100);
    LegendTable->setColumnWidth(7,100);
    LegendTable->setColumnWidth(8,100);
    LegendTable->setColumnWidth(9,100);
    LegendTable->setColumnWidth(10,100);

    LegendTable->setHorizontalHeaderLabels(headers);
    LegendTable->verticalHeader()->setVisible(false);


}

void LegendWidget::OnReadDataClicked()
{
    emit ReadDataSignal();
}

void LegendWidget::OnWriteDataClicked()
{
    emit WriteDataSignal();
}

LegendWidget::LegendRow::LegendRow(QWidget * parent)
{
    VisibilityBox = new QCheckBox(parent); // Поменять внешний вид
    ColourLabel = new QLabel("—",parent);
    ColourLabel ->setStyleSheet("font-weight: bold; font-size: 50px; color: yellow;");
    ColourLabel ->setAlignment(Qt::AlignCenter);
    TitleEdit   = new QLineEdit("Title",parent);
    DataBox     = new QComboBox(parent);
    PlaneBox    = new QComboBox(parent);
    FreqBox     = new QComboBox(parent);
    AzBox       = new QComboBox(parent);
    ElBox       = new QComboBox(parent);
    DistBox     = new QComboBox(parent);
    ChannelBox  = new QComboBox(parent);
    SmoothBox   = new QComboBox(parent);
    PercentBox  = new QComboBox(parent);
    ColourBox   = new QComboBox(parent);
}



void LegendWidget::OnAddLineClicked()
{
    // Создаём новую пустую строку
    LegendRow NewRow;

    // Добавляем пустую строку
    int RowCount = LegendTable->rowCount();
    LegendTable->insertRow(RowCount);

    // Заполняем её
    QWidget * ZeroCellWidget = new QWidget(this);
    QHBoxLayout * CellLayout = new QHBoxLayout(ZeroCellWidget);

    CellLayout->addWidget(NewRow.VisibilityBox);
    CellLayout->addWidget(NewRow.ColourLabel);
    CellLayout->addWidget(NewRow.TitleEdit);

    LegendTable->setCellWidget(RowCount, 0, ZeroCellWidget);

    LegendTable->setCellWidget(RowCount, 1, NewRow.DataBox);
    LegendTable->setCellWidget(RowCount, 2, NewRow.PlaneBox);
    LegendTable->setCellWidget(RowCount, 3, NewRow.FreqBox);
    LegendTable->setCellWidget(RowCount, 4, NewRow.AzBox);
    LegendTable->setCellWidget(RowCount, 5, NewRow.ElBox);
    LegendTable->setCellWidget(RowCount, 6, NewRow.DistBox);
    LegendTable->setCellWidget(RowCount, 7, NewRow.ChannelBox);
    LegendTable->setCellWidget(RowCount, 8, NewRow.SmoothBox);
    LegendTable->setCellWidget(RowCount, 9, NewRow.PercentBox);
    LegendTable->setCellWidget(RowCount, 10,NewRow.ColourBox);

    //QStringList ColourVector = QColor::colorNames(); // Слишком много цветов

    for (int i=0;i<ColourVector.size();i++)
    {
        NewRow.ColourBox->addItem(ColourVector[i]);
    }

    emit AddLineSignal();
    // Если графику есть, что передавать, то он отправит сигнал к слоту заполнения строки
}


void LegendWidget::OnDeleteLineClicked()
{
    if (LegendRowsForAllPlots[ActiveTab].Rows.isEmpty())
        return;

    int currentRow = LegendTable->currentRow();
    if (currentRow >= 0 && currentRow < LegendRowsForAllPlots[ActiveTab].Rows.size())
    {
        LegendRowsForAllPlots[ActiveTab].Rows.remove(currentRow);
        LegendTable->removeRow(currentRow);
        emit DeleteLineSignal();
    }
}

void LegendWidget::OnClearAllClicked()
{

}

void LegendWidget::OnUpLineClicked()
{

}

void LegendWidget::OnDownLineClicked()
{

}

void LegendWidget::OnCopyToMemoryLineClicked()
{

}

void LegendWidget::OnRefreshClicked()
{

}



void LegendWidget::RefillRows()
{
    LegendTable->clearContents();

    int AmountOfRows = LegendRowsForAllPlots[ActiveTab].Rows.size();
    LegendTable->setRowCount(AmountOfRows);

    for (int r=0; r<AmountOfRows; r++)
    {
        QWidget * ZeroCellWidget = new QWidget(this);
        QHBoxLayout * CellLayout = new QHBoxLayout(ZeroCellWidget);

        CellLayout->addWidget(LegendRowsForAllPlots[ActiveTab].Rows[r]->VisibilityBox);
        CellLayout->addWidget(LegendRowsForAllPlots[ActiveTab].Rows[r]->ColourLabel);
        CellLayout->addWidget(LegendRowsForAllPlots[ActiveTab].Rows[r]->TitleEdit);

        LegendTable->setCellWidget(r, 0, ZeroCellWidget);
        LegendTable->setCellWidget(r, 1, LegendRowsForAllPlots[ActiveTab].Rows[r]->DataBox);
        LegendTable->setCellWidget(r, 2, LegendRowsForAllPlots[ActiveTab].Rows[r]->PlaneBox);
        LegendTable->setCellWidget(r, 3, LegendRowsForAllPlots[ActiveTab].Rows[r]->FreqBox);
        LegendTable->setCellWidget(r, 4, LegendRowsForAllPlots[ActiveTab].Rows[r]->AzBox);
        LegendTable->setCellWidget(r, 5, LegendRowsForAllPlots[ActiveTab].Rows[r]->ElBox);
        LegendTable->setCellWidget(r, 6, LegendRowsForAllPlots[ActiveTab].Rows[r]->DistBox);
        LegendTable->setCellWidget(r, 7, LegendRowsForAllPlots[ActiveTab].Rows[r]->ChannelBox);
        LegendTable->setCellWidget(r, 8, LegendRowsForAllPlots[ActiveTab].Rows[r]->SmoothBox);
        LegendTable->setCellWidget(r, 9, LegendRowsForAllPlots[ActiveTab].Rows[r]->PercentBox);
        LegendTable->setCellWidget(r, 10,LegendRowsForAllPlots[ActiveTab].Rows[r]->ColourBox);
    }
}



void LegendWidget::OnChartTabChanged(int TabIndex)
{
    ActiveTab = TabIndex;

    if (ActiveTab == -1) // Деактивируем, если это PrintPreview
    {
        setEnabled(false);
    }
    else // Заполняем, если это не PrintPreview
    {
        setEnabled(true);
        RefillRows();
    }
}



void LegendWidget::SetNumberOfPlots(int PlotsNumber)
{
    LegendRowsForAllPlots.resize(PlotsNumber);
}


void LegendWidget::FillFirstRows(MeasDataClass MeasuredData)
{
    int NumberOfPlots = LegendRowsForAllPlots.size();

    QDoubleVector FreqVector = MeasuredData.GetFreqVectorGHz();
    QStringList FreqVectorStrings;
    for (double freq : FreqVector)
    {
        FreqVectorStrings << QString::number(freq);
    }

    QDoubleVector AzVector = MeasuredData.GetAzimuthVector();
    QStringList AzVectorStrings;
    for (double az : AzVector)
    {
        AzVectorStrings << QString::number(az);
    }

    QDoubleVector ElVector = MeasuredData.GetElevationVector();
    QStringList ElVectorStrings;
    for (double el : ElVector)
    {
        ElVectorStrings << QString::number(el);
    }

    QDoubleVector DistVector = MeasuredData.GetDistVector();
    QStringList DistVectorStrings;
    for (double dist : DistVector)
    {
        DistVectorStrings << QString::number(dist);
    }


    for (int p=0; p<NumberOfPlots; p++)
    {
        if (LegendRowsForAllPlots[p].Rows.size()==0)
        {
            LegendRow * NewRow = new LegendRow(this);
            NewRow->VisibilityBox->setChecked(true);
            NewRow->ColourLabel->setStyleSheet("color: green;");
            NewRow->TitleEdit->setText("<D>");

            NewRow->DataBox    ->addItems(DataTypes);
            NewRow->PlaneBox   ->addItems({"Freq","El","Az","Dist"});
            NewRow->FreqBox    ->addItems(FreqVectorStrings);
            NewRow->AzBox      ->addItems(AzVectorStrings);
            NewRow->ElBox      ->addItems(ElVectorStrings);
            NewRow->DistBox    ->addItems(DistVectorStrings);
            NewRow->ChannelBox ->addItems({"--"});;
            NewRow->SmoothBox  ->addItems({"None"});;
            NewRow->PercentBox ->addItems({"--"});;
            NewRow->ColourBox  ->addItems(ColourVector);
            LegendRowsForAllPlots[p].Rows.append(NewRow);

            connect(NewRow->VisibilityBox,  &QCheckBox::stateChanged, this,&LegendWidget::SomeRowChanged);

            //connect(NewRow->DataBox,        &QComboBox::highlighted, this, &LegendWidget::DataBoxHighLighted);
            //connect(NewRow->PlaneBox,       &QComboBox::highlighted, this, &LegendWidget::PlaneBoxHighLighted);
            //connect(NewRow->FreqBox,        &QComboBox::highlighted, this, &LegendWidget::FreqBoxHighLighted);
            //connect(NewRow->AzBox,          &QComboBox::highlighted, this, &LegendWidget::AzBoxHighLighted);
            //connect(NewRow->ElBox,          &QComboBox::highlighted, this, &LegendWidget::ElBoxHighLighted);
            //connect(NewRow->DistBox,        &QComboBox::highlighted, this, &LegendWidget::DistBoxHighLighted);
            //connect(NewRow->ColourBox,      &QComboBox::highlighted, this, &LegendWidget::ColourBoxHighLighted);

            connect(NewRow->DataBox,        &QComboBox::currentIndexChanged, this, &LegendWidget::SomeRowChanged);
            connect(NewRow->PlaneBox,       &QComboBox::currentIndexChanged, this, &LegendWidget::SomeRowChanged);
            connect(NewRow->FreqBox,        &QComboBox::currentIndexChanged, this, &LegendWidget::SomeRowChanged);
            connect(NewRow->AzBox,          &QComboBox::currentIndexChanged, this, &LegendWidget::SomeRowChanged);
            connect(NewRow->ElBox,          &QComboBox::currentIndexChanged, this, &LegendWidget::SomeRowChanged);
            connect(NewRow->DistBox,        &QComboBox::currentIndexChanged, this, &LegendWidget::SomeRowChanged);
            connect(NewRow->ColourBox,      &QComboBox::currentIndexChanged, this, &LegendWidget::SomeRowChanged);


        }
        else
        {
            LegendRowsForAllPlots[p].Rows[0]->VisibilityBox->setChecked(true);
            LegendRowsForAllPlots[p].Rows[0]->ColourLabel->setStyleSheet("color: yellow;");
            LegendRowsForAllPlots[p].Rows[0]->TitleEdit ->setText("<D>");

            LegendRowsForAllPlots[p].Rows[0]->DataBox    ->addItems(DataTypes);
            LegendRowsForAllPlots[p].Rows[0]->PlaneBox   ->addItems({"Freq","Az","El","Dist"});
            LegendRowsForAllPlots[p].Rows[0]->FreqBox    ->addItems(FreqVectorStrings);
            LegendRowsForAllPlots[p].Rows[0]->AzBox      ->addItems(  AzVectorStrings);
            LegendRowsForAllPlots[p].Rows[0]->ElBox      ->addItems(  ElVectorStrings);
            LegendRowsForAllPlots[p].Rows[0]->DistBox    ->addItems(DistVectorStrings);
            LegendRowsForAllPlots[p].Rows[0]->ChannelBox ->addItems({"--"});;
            LegendRowsForAllPlots[p].Rows[0]->SmoothBox  ->addItems({"None"});;
            LegendRowsForAllPlots[p].Rows[0]->PercentBox ->addItems({"--"});;
            LegendRowsForAllPlots[p].Rows[0]->ColourBox  ->addItems(ColourVector);
        }
    }
    RefillRows();

}



LegendWidget::DataFromLegendRow * LegendWidget::ExtractRowData(LegendRow * row)
{

    DataFromLegendRow * Data = new DataFromLegendRow;

    Data->Title     = row->TitleEdit    ->text();
    Data->Data      = row->DataBox      ->currentIndex();
    Data->Plane     = row->PlaneBox     ->currentText();
    Data->Freq      = row->FreqBox      ->currentIndex();
    Data->Az        = row->AzBox        ->currentIndex();
    Data->El        = row->ElBox        ->currentIndex();
    Data->Dist      = row->DistBox      ->currentIndex();
    Data->Channel   = row->ChannelBox   ->currentIndex();
    Data->Smooth    = row->SmoothBox    ->currentIndex();
    Data->Percent   = row->PercentBox   ->currentIndex();
    Data->Colour    = row->ColourBox    ->currentIndex();

    return Data;
}



void LegendWidget::SomeRowChanged()
{

    LegendRow * row = LegendRowsForAllPlots[ActiveTab].Rows[0];


    DataFromLegendRow * Data = ExtractRowData(row);


    QColor PCol = ColorVector[Data->Colour];
    MeasDataClass::MeasDataType DType= DataTypeVector[Data->Data];

    qDebug()<<"000";
    emit RedrawPlotSignal(0,0,DType,Data->Plane, Data->Freq, Data->Az, Data->El, Data->Dist, PCol);


    /*
    //int NumberOfRows = LegendRowsForAllPlots[ActiveTab].Rows.size();

    for (int r=0; r < NumberOfRows; r++)
    {
        MeasDataClass::MeasDataType DType;
        //Meas??? Откуда это и зачем?
        LegendRowsForAllPlots[ActiveTab].Rows[r]->DataBox   ->currentText(),
        LegendRowsForAllPlots[ActiveTab].Rows[r]->PlaneBox  ->currentIndex(),
        emit RedrawPlotSignal(
            ActiveTab,
            r,
            LegendRowsForAllPlots[ActiveTab].Rows[r]->DataBox   ->currentIndex(),
            LegendRowsForAllPlots[ActiveTab].Rows[r]->PlaneBox  ->currentIndex(),
            LegendRowsForAllPlots[ActiveTab].Rows[r]->FreqBox   ->currentIndex(),
            LegendRowsForAllPlots[ActiveTab].Rows[r]->AzBox     ->currentIndex(),
            LegendRowsForAllPlots[ActiveTab].Rows[r]->ElBox     ->currentIndex(),
            LegendRowsForAllPlots[ActiveTab].Rows[r]->DistBox   ->currentIndex(),
            LegendRowsForAllPlots[ActiveTab].Rows[r]->ColourBox ->currentIndex()
            );
    }
    */



}




void LegendWidget::DataBoxHighLighted     (int ID){LegendRowsForAllPlots[ActiveTab].Rows[0]->DataBox->  setCurrentIndex(ID);}
void LegendWidget::PlaneBoxHighLighted    (int ID){LegendRowsForAllPlots[ActiveTab].Rows[0]->PlaneBox-> setCurrentIndex(ID);}
void LegendWidget::FreqBoxHighLighted     (int ID){LegendRowsForAllPlots[ActiveTab].Rows[0]->FreqBox->  setCurrentIndex(ID);}
void LegendWidget::AzBoxHighLighted       (int ID){LegendRowsForAllPlots[ActiveTab].Rows[0]->AzBox->    setCurrentIndex(ID);}
void LegendWidget::ElBoxHighLighted       (int ID){LegendRowsForAllPlots[ActiveTab].Rows[0]->ElBox->    setCurrentIndex(ID);}
void LegendWidget::DistBoxHighLighted     (int ID){LegendRowsForAllPlots[ActiveTab].Rows[0]->DistBox->  setCurrentIndex(ID);}
void LegendWidget::ColourBoxHighLighted   (int ID){LegendRowsForAllPlots[ActiveTab].Rows[0]->ColourBox->setCurrentIndex(ID);}








