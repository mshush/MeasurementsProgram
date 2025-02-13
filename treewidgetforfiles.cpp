#include "treewidgetforfiles.h"

TreeWidgetForFiles::TreeWidgetForFiles (QWidget *parent)  : QWidget(parent)
{

    FileTree = new QTreeView(this);


    model = new QFileSystemModel(this);
    model->setRootPath(QDir::rootPath());

    FileTree->setModel(model);
    FileTree->setRootIndex(model->index(QDir::rootPath())); //Сменить папку
    FileTree->setColumnWidth(10, 250);

    MoveRootToParentFolderButton = new QPushButton("↑", this);
    RootPathEdit = new QLineEdit(QDir::rootPath(),this);
    ChooseRootButton = new QPushButton("Открыть", this);
    //SaveButton = new QPushButton("Сохранить", this);
    //SaveCopyButton = new QPushButton("Сохранить копию", this);


    ////connect(MoveRootToParentFolderButton, &QPushButton::clicked, this, &TreeWidgetForFiles::MoveRootToParentFolder);
    ////connect(ChooseRootButton, &QPushButton::clicked, this, &TreeWidgetForFiles::ChooseRootDirectory);
    //////connect(SaveButton, &QPushButton::clicked, this, &TreeWidgetForFiles::SaveFile);
    ////connect(SaveCopyButton, &QPushButton::clicked, this, &TreeWidgetForFiles::SaveCopy);
    //connect(RootPathEdit,&QLineEdit::returnPressed,this, &TreeWidgetForFiles::ChangeRootDirectoryManually);
    ////connect(RootPathEdit,&QLineEdit::editingFinished,this, &TreeWidgetForFiles::ChangeRootEditBack);



    QVBoxLayout * VerticalFileManagerLayout = new QVBoxLayout(this);
    QHBoxLayout * ButtonLayout = new QHBoxLayout();
    ButtonLayout->setAlignment(Qt::AlignLeft);


    ButtonLayout->addWidget(MoveRootToParentFolderButton);
    ButtonLayout->addWidget(RootPathEdit);
    ButtonLayout->addWidget(ChooseRootButton);
    //ButtonLayout->addWidget(SaveButton);
    //ButtonLayout->addWidget(SaveCopyButton);
    VerticalFileManagerLayout->addLayout(ButtonLayout);
    VerticalFileManagerLayout->addWidget(FileTree);


    //connect(FileTree, &QTreeView::doubleClicked, this, &TreeWidgetForFiles::OpenOnClick);

}



void TreeWidgetForFiles::ChooseRootDirectory()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Choose Directory", QDir::rootPath());
    if (!dir.isEmpty())
    {
        FileTree->setRootIndex(model->index(dir));
    }
    this->RootPathEdit->setText(dir);
}



void TreeWidgetForFiles::SaveFile()
{
    /*
    QString filePath = QFileDialog::getSaveFileName(this, "Save File", "", "Data files (*.dat)");
    if (!filePath.isEmpty())
    {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly))
        {
            // Внести в открытый файл какие-то нужные изменения и сохранить
            file.close();
            QMessageBox::information(this, "Сохранено!", "Файл успешно сохранён");
        }
        else
        {
            QMessageBox::warning(this, "Ошибка!", "Не удалось сохранить файл");
        }
    }
    */
}

void TreeWidgetForFiles::SaveCopy()
{

}


void TreeWidgetForFiles::OpenOnClick(const QModelIndex &index)
{
    if (!index.isValid())
    {
        return;
    }

    QString filePath = model->filePath(index);
    QFileInfo fileInfo(filePath);

    if (fileInfo.isDir())
    {
        FileTree->setRootIndex(model->index(filePath));
        this->RootPathEdit->setText(filePath);
    }
    else if (fileInfo.isFile())
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
    }


}



void TreeWidgetForFiles::MoveRootToParentFolder()
{

    QModelIndex CurrentRootIndex = FileTree->rootIndex();

    QString FilePathOfCurrentRoot = model->filePath(CurrentRootIndex);



    QFileInfo FileInfoOfRoot(FilePathOfCurrentRoot);

    QString ParentDirectoryPath = FileInfoOfRoot.absolutePath();

    FileTree->setRootIndex(model->index(ParentDirectoryPath));

    RootPathEdit->setText(ParentDirectoryPath);

    /*  Не нужно
    if (ParentDirectoryPath != "???????")
    {
        QMessageBox::warning(this, "Недопустимая операция", "Нет более старших папок");
        return;
    }
    */
}

void TreeWidgetForFiles::ChangeRootDirectoryManually()
{

    qDebug() << "ChangeRootDirectoryManually called";

    if (!RootPathEdit) {
        qDebug() << "RootPathEdit is null!";
        return;
    }

    QString NewRootPath = RootPathEdit->text();
    qDebug() << "NewRootPath:" << NewRootPath;

    QFileInfo fileInfo(NewRootPath);
    qDebug() << "FileInfo exists:" << fileInfo.exists() << "isDir:" << fileInfo.isDir();

    /*
    if (fileInfo.exists() && fileInfo.isDir())
    {
        qDebug() << "Valid directory, proceeding...";
        // FileTree->setRootIndex(model->index(NewRootPath));
    }
    else
    {
        qDebug() << "Invalid path, emitting error...";
        //emit ErrorOccured("TreeWidgetForFiles : Папка не найдена");
    }
*/


    /*
    QString NewRootPath = RootPathEdit->text();

    QFileInfo fileInfo(NewRootPath);

    if (fileInfo.exists() && fileInfo.isDir())
    {
        //FileTree->setRootIndex(model->index(NewRootPath));
    }
    else
    {
        //emit ErrorOccured("TreeWidgetForFiles : Папка не найдена");
    }

    */
}

/*
void TreeWidgetForFiles::ChangeRootEditBack()
{
    QModelIndex CurrentRootIndex = FileTree->rootIndex();

    QString FilePathOfCurrentRoot = model->filePath(CurrentRootIndex);

    RootPathEdit->setText(FilePathOfCurrentRoot);

}
*/


































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

    //connect(ChooseResponce      , &QAction::triggered, this, [this, item]() { SetResponce     (item); });
    //connect(ChooseBackground    , &QAction::triggered, this, [this, item]() { SetBackground   (item); });
    ////connect(ChooseCalibration   , &QAction::triggered, this, [this, item]() { SetCalibration  (item); });


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
