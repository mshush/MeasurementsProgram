#ifndef TREEWIDGETFORFILES_H
#define TREEWIDGETFORFILES_H

#include <QObject>
//#include <QTreeWidget>
#include <QWidget>
#include <QDir>
#include <QtWidgets>
#include <QTreeView>
#include <QFileSystemModel>
#include <QStandardItemModel>


class TreeWidgetForFiles : public QWidget
{
    Q_OBJECT
public:
    TreeWidgetForFiles(QWidget *parent = nullptr);
    //~TreeWidgetForFiles();
    QFileSystemModel * model;

    QPushButton * MoveRootToParentFolderButton;
    QLineEdit * RootPathEdit;
    QPushButton * ChooseRootButton;
    QPushButton * SaveButton;
    QPushButton * SaveCopyButton;


    QTreeView * FileTree;

public slots:
    void ChooseRootDirectory();
    void SaveFile();
    void SaveCopy();
    void OpenOnClick(const QModelIndex &index);
    void MoveRootToParentFolder();
    void ChangeRootDirectoryManually();
    //void ChangeRootEditBack();

signals:
    void ErrorOccured(QString ErrorText); // Почему вызывает ошибку?


    /*
    QTreeView * FileTree;

    void AddItems(const QDir &CurrentDirectory, QTreeWidgetItem *parent, int CurrentDepth);
    QDir RootDirectory;
    QTreeWidgetItem *RootItem;

    QVBoxLayout * OutermostVerticalLayout;
    QLabel * DirectoryLabel;
    QLineEdit * DirectoryEdit;


    //enum ModeOfMeasurement {Response, Background, Calibration};


    QIcon CreateColorIcon(const QColor &color);

    QTreeWidgetItem * ResponseItem = nullptr;
    QTreeWidgetItem * BackgroundItem = nullptr;
    QTreeWidgetItem * CalibrationItem = nullptr;


public slots:

    void SetRootDirectory(const QDir &RootDirectory);
    void ChangeRootDirectory();
    void ShowContextMenu(QTreeWidgetItem *item, int column);

    QString GetFilePathFromItem(QTreeWidgetItem *item);

    void SetResponce    (QTreeWidgetItem *item);
    void SetBackground  (QTreeWidgetItem *item);
    void SetCalibration (QTreeWidgetItem *item);

public:
signals:
    void FileWasChosenSignal(int Mode, QString FilePath);
*/


};

#endif // TREEWIDGETFORFILES_H
