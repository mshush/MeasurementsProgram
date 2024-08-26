#include "treewidgetforfiles.h"

TreeWidgetForFiles::TreeWidgetForFiles() //Нужно добавить меню, которое предлагает открыть как калибровку, бэкграунд или измерение объекта
{
    this->setMaximumWidth(300);


    OutermostVerticalLayout = new QVBoxLayout(this);
    DirectoryLabel = new QLabel("Директория:",this);
    DirectoryEdit = new QLineEdit("C:/Users/HP/Documents/",this);
    connect(DirectoryEdit, &QLineEdit::returnPressed, this, &TreeWidgetForFiles::ChangeRootDirectory);


    FileTree = new QTreeWidget(this);

    FileTree->setColumnCount(1);
    FileTree->setHeaderLabels(QStringList() << "Навигация по файлам");

    RootDirectory = QDir("C:/Users/HP/Documents/");
    RootItem = new QTreeWidgetItem(FileTree);

    SetRootDirectory(RootDirectory);


    OutermostVerticalLayout->addWidget(DirectoryLabel);
    OutermostVerticalLayout->addWidget(DirectoryEdit);
    OutermostVerticalLayout->addWidget(FileTree);

    this->setLayout(OutermostVerticalLayout);
}




void TreeWidgetForFiles::AddItems(const QDir &directory, QTreeWidgetItem *parent, int CurrentDepth)
{
    QFileInfoList fileList = directory.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    CurrentDepth++;

    for (const QFileInfo &fileInfo : fileList)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(parent);
        item->setText(0, fileInfo.fileName());
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
    FileTree->addTopLevelItem(RootItem);
    AddItems(RootDirectory, RootItem, 0);
}


void TreeWidgetForFiles::ChangeRootDirectory()
{
    RootDirectory.setPath(this->DirectoryEdit->text());
    if (!RootDirectory.exists()) {
        QMessageBox::warning(this, "Ошибка", "Директория не существует");
        return;
    }

    FileTree->clear();
    SetRootDirectory(RootDirectory);

}



TreeWidgetForFiles::~TreeWidgetForFiles()
{
    //delete RootItem;
}
