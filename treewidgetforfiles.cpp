#include "treewidgetforfiles.h"

TreeWidgetForFiles::TreeWidgetForFiles()
{
    this->setColumnCount(1);
    this->setHeaderLabels(QStringList() << "Файловый менеджер");

    RootDirectory = QDir("C:/Users/HP/Documents/MeasurementsProgram");
    RootItem = new QTreeWidgetItem(this);

    SetRootDirectory(RootDirectory);

    this->resize(800,100);
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
}




void TreeWidgetForFiles::AddItems(const QDir &directory, QTreeWidgetItem *parent, int CurrentDepth)
{
    QFileInfoList fileList = directory.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    CurrentDepth++;

    for (const QFileInfo &fileInfo : fileList)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(parent);
        item->setText(0, fileInfo.fileName());
        if (fileInfo.isDir() and CurrentDepth<6)
        {
            QDir subDir(fileInfo.filePath());
            AddItems(subDir, item, CurrentDepth);
        }
    }
}


void TreeWidgetForFiles::SetRootDirectory(const QDir &RootDirectory)
{
    RootItem->setText(0, RootDirectory.dirName());
    this->addTopLevelItem(RootItem);
    AddItems(RootDirectory, RootItem, 0);
}
