#include "treewidgetforfiles.h"

TreeWidgetForFiles::TreeWidgetForFiles (QWidget *parent)  : QWidget(parent)
{
    /*
    this->setMaximumWidth(300);


    OutermostVerticalLayout = new QVBoxLayout(this);
    DirectoryLabel = new QLabel("Корневая папка:",this);
    DirectoryEdit = new QLineEdit("C:/Users/HP/Documents/",this);
    connect(DirectoryEdit, &QLineEdit::returnPressed, this, &TreeWidgetForFiles::ChangeRootDirectory);


    FileTree = new QTreeView(this);

    //FileTree->setColumnCount(1);
    //FileTree->setHeaderLabels(QStringList() << "Навигация по файлам");

    RootDirectory = QDir("C:/Users/HP/Documents/");
    //RootItem = new QTreeWidgetItem(FileTree);

    SetRootDirectory(RootDirectory);


    OutermostVerticalLayout->addWidget(DirectoryLabel);
    OutermostVerticalLayout->addWidget(DirectoryEdit);
    OutermostVerticalLayout->addWidget(FileTree);

    this->setLayout(OutermostVerticalLayout);


    //connect(FileTree, &QTreeWidget::itemClicked, this, &TreeWidgetForFiles::ShowContextMenu);
    */



    QHBoxLayout * HorizontalFileManagerLayout = new QHBoxLayout(this);
    FileTree = new QTreeView(this);


    QFileSystemModel *model = new QFileSystemModel(this);
    model->setRootPath(QDir::rootPath());

    FileTree->setModel(model);
    FileTree->setRootIndex(model->index(QDir::rootPath())); //Сменить папку
    FileTree->setColumnWidth(0, 250);
    HorizontalFileManagerLayout->addWidget(FileTree);




}







/*


void TreeWidgetForFiles::AddItems(const QDir &directory, QTreeWidgetItem *parent, int CurrentDepth)
{
    QFileInfoList fileList = directory.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    CurrentDepth++;

    for (const QFileInfo &fileInfo : fileList)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(parent);
        item->setText(0, fileInfo.fileName());
        //qDebug()<<fileInfo.fileName();

        if (!fileInfo.isReadable())
        {
            //qDebug() << "НЕ ЧИТАЕТСЯ!!!!!!!!!" << fileInfo.filePath();
            continue;
        }


        if (fileInfo.isDir() and CurrentDepth<2)
        {
            QDir subDir(fileInfo.filePath());
            AddItems(subDir, item, CurrentDepth);
        }
    }

}


void TreeWidgetForFiles::SetRootDirectory(const QDir &RootDirectory)
{
    RootItem->setText(0, RootDirectory.dirName());
    //FileTree->addTopLevelItem(RootItem);
    AddItems(RootDirectory, RootItem, 0);
}


void TreeWidgetForFiles::ChangeRootDirectory()
{
    RootDirectory.setPath(this->DirectoryEdit->text());
    if (!RootDirectory.exists()) {
        QMessageBox::warning(this, "Ошибка", "Директория не существует");
        return;
    }
    while (RootItem->childCount() > 0)
    {
        delete RootItem->child(0);
    }
    //SetRootDirectory(RootDirectory);
    RootItem->setText(0, RootDirectory.dirName());
    AddItems(RootDirectory, RootItem, 0);

}



void TreeWidgetForFiles::ShowContextMenu(QTreeWidgetItem *item, int column)
{
    if (!item)
    {
        return;
    }

    QMenu ContextMenu;

    QAction * ChooseResponce    = ContextMenu.addAction(CreateColorIcon(Qt::red  )  , "Отклик"    );
    QAction * ChooseBackground  = ContextMenu.addAction(CreateColorIcon(Qt::green)  , "Фон"       );
    QAction * ChooseCalibration = ContextMenu.addAction(CreateColorIcon(Qt::blue )  , "Калибровка");
    QAction * TurnIntoRoot      = ContextMenu.addAction("Сделать корневой");

    connect(ChooseResponce      , &QAction::triggered, this, [this, item]() { SetResponce     (item); });
    connect(ChooseBackground    , &QAction::triggered, this, [this, item]() { SetBackground   (item); });
    connect(ChooseCalibration   , &QAction::triggered, this, [this, item]() { SetCalibration  (item); });


    ContextMenu.exec(QCursor::pos());
}



void TreeWidgetForFiles::SetResponce(QTreeWidgetItem *item)
{
    QString FilePath = GetFilePathFromItem(item);

    if (!FilePath.isEmpty())
    {
        if (FilePath.endsWith(".dat", Qt::CaseInsensitive))
        {
            //QDesktopServices::openUrl(QUrl::fromLocalFile(FilePath));
            if (ResponseItem)
            {
                ResponseItem->setBackground(0, QBrush(Qt::transparent));
            }
            ResponseItem = item;
            item->setBackground(0, QBrush(QColor(255,0,0,100)));

            emit FileWasChosenSignal(0, FilePath);
        }
        else
        {
            QMessageBox::warning(this, "Ошибка", "Формат файла не подходит"); // Как сделать проверку получше?
        }
    } else
    {
        QMessageBox::warning(this, "Ошибка", "Не удаётся открыть файл");
    }


}

void TreeWidgetForFiles::SetBackground(QTreeWidgetItem *item)
{
    QString FilePath = GetFilePathFromItem(item);

    if (!FilePath.isEmpty())
    {
        if (FilePath.endsWith(".dat", Qt::CaseInsensitive))
        {
            //QDesktopServices::openUrl(QUrl::fromLocalFile(FilePath));
            if (BackgroundItem)
            {
                BackgroundItem->setBackground(0, QBrush(Qt::transparent));
            }
            BackgroundItem = item;
            item->setBackground(0, QBrush(QColor(0,255,0,100)));

            emit FileWasChosenSignal(1, FilePath);
        }
        else
        {
            QMessageBox::warning(this, "Ошибка", "Формат файла не подходит"); // Как сделать проверку получше?
        }
    } else
    {
        QMessageBox::warning(this, "Error", "Unable to open the file.");
    }


}

void TreeWidgetForFiles::SetCalibration(QTreeWidgetItem *item)
{

    QString FilePath = GetFilePathFromItem(item);

    if (!FilePath.isEmpty())
    {
        if (FilePath.endsWith(".dat", Qt::CaseInsensitive))
        {
            //QDesktopServices::openUrl(QUrl::fromLocalFile(FilePath));
            if (CalibrationItem)
            {
                CalibrationItem->setBackground(0, QBrush(Qt::transparent));
            }
            CalibrationItem = item;
            item->setBackground(0, QBrush(QColor(0,0,255,100)));
            emit FileWasChosenSignal(2, FilePath);
        }
        else
        {
            QMessageBox::warning(this, "Ошибка", "Формат файла не подходит"); // Как сделать проверку получше?
        }
    } else
    {
        QMessageBox::warning(this, "Error", "Unable to open the file.");
    }


}



QString TreeWidgetForFiles::GetFilePathFromItem(QTreeWidgetItem *item)
{
    QString fileName = item->text(0);
    QDir currentDir = RootDirectory;
    return currentDir.filePath(fileName);
}


QIcon TreeWidgetForFiles::CreateColorIcon(const QColor &color)
{
    QPixmap pixmap(16, 16);
    pixmap.fill(Qt::transparent); //

    QPainter painter(&pixmap);
    painter.setBrush(QBrush(color));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(2, 2, 12, 12);
    painter.end();

    return QIcon(pixmap);
}




TreeWidgetForFiles::~TreeWidgetForFiles()
{
    delete RootItem;
}

*/



//Коренная папка неправильно выбирается
//Добавить выбор директории через меню итд
