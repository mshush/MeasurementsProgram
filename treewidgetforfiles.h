#ifndef TREEWIDGETFORFILES_H
#define TREEWIDGETFORFILES_H

#include <QObject>
#include <QTreeWidget>
#include <QWidget>
#include <QDir>
#include <QtWidgets>


class TreeWidgetForFiles : public QWidget
{
    Q_OBJECT
public:
    TreeWidgetForFiles();
    ~TreeWidgetForFiles();

    QTreeWidget * FileTree;

    void AddItems(const QDir &CurrentDirectory, QTreeWidgetItem *parent, int CurrentDepth);
    QDir RootDirectory;
    QTreeWidgetItem *RootItem;

    QVBoxLayout * OutermostVerticalLayout;
    QLabel * DirectoryLabel;
    QLineEdit * DirectoryEdit;


public slots:

    void SetRootDirectory(const QDir &RootDirectory);
    void ChangeRootDirectory();
};

#endif // TREEWIDGETFORFILES_H
