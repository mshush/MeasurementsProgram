#ifndef TREEWIDGETFORFILES_H
#define TREEWIDGETFORFILES_H

#include <QObject>
#include <QTreeWidget>
#include <QWidget>
#include <QDir>



class TreeWidgetForFiles : public QTreeWidget // Переделать, чтобы без бесконечной рекурсии.
{
    Q_OBJECT
public:
    TreeWidgetForFiles();
    void AddItems(const QDir &CurrentDirectory, QTreeWidgetItem *parent, int CurrentDepth);
    QDir RootDirectory;
    QTreeWidgetItem *RootItem;

public slots:

    void SetRootDirectory(const QDir &RootDirectory);
};

#endif // TREEWIDGETFORFILES_H
