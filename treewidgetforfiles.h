#ifndef TREEWIDGETFORFILES_H
#define TREEWIDGETFORFILES_H

#include <QObject>
#include <QTreeWidget>
#include <QWidget>
#include <QDir>



class TreeWidgetForFiles : public QTreeWidget // Без рекурсии!!!
{
    Q_OBJECT
public:
    TreeWidgetForFiles();
    void AddItems(const QDir &directory, QTreeWidgetItem *parent);
};

#endif // TREEWIDGETFORFILES_H
