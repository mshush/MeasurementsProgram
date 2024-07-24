#include "treewidgetforfiles.h"

TreeWidgetForFiles::TreeWidgetForFiles()
{

    this->setColumnCount(1);
    this->setHeaderLabels(QStringList() << "Файловый менеджер");

    QDir rootDir("C:/Users/HP/Documents/MeasurementsProgram");
    QTreeWidgetItem *rootItem = new QTreeWidgetItem(this);
    rootItem->setText(0, rootDir.dirName());
    this->addTopLevelItem(rootItem);

    AddItems(rootDir, rootItem); //Если рекурсивно, то будет задержка при большой длине пути -- подумать как уменьшить.

    this->resize(800,100);
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

}




void TreeWidgetForFiles::AddItems(const QDir &directory, QTreeWidgetItem *parent) // Закомментировал, так как программа медленно запускается
{

    QFileInfoList fileList = directory.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

    for (const QFileInfo &fileInfo : fileList)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(parent);
        item->setText(0, fileInfo.fileName());

        if (fileInfo.isDir())
        {
            QDir subDir(fileInfo.filePath());
            AddItems(subDir, item); // Рекурсию лучше убрать?
        }
    }

}





