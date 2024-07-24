#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtWidgets>
#include <QtCharts>
#include <QObject>

#include <tabwidgetforparameters.h>
#include <tabwidgetfortools.h>
#include <widgetforchart.h>
#include <treewidgetforfiles.h>>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDir>
#include <tabwidgetforcharts.h>>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //QMenuBar * MenuBar;
    TabWidgetForParameters * TabOfParameters;
    TabWidgetForTools * TabOfTools;
    //WidgetForChart * ChartWidget;
    TabWidgetForCharts * ChartTab;
    TreeWidgetForFiles * FileTreeWidget;

    void addItems(const QDir &directory, QTreeWidgetItem *parent); // Перенести в отдельный класс для дерева

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H


/*
Будем использовать GitHub

У графика должно быть 2 функционала: "внешний" и "внутренний"?
Маркеры и поиск локального минимума

маркер
отрис
не вылазит
есть перевод между её коорд и коорд настоящими
background (Цилиндр)
respond Чтобы относительно цилиндра
Всё в файле, хранится.
Записывает меньше чем измеряет иначе очень много весит. Это нужно проверить.
Если можно сохр сырые данные, то можно
Подгружать калибровки файловым менеджером
Выбрали background и respond
Сейчас в lineedit записан длинный путь. Как сделать удобнее. ПОДУМАТЬ

Измерения загружаются с исходными калибровками. Можно поменять, но хотим загружать вместе.

Найти программу, где такая проблема не решена десятилетиями. Linker в MS VS Плохой пример

API?

Нужно будет отчитываться. Каждую неделю связываться, говорить, что делаем.
Через 2 недели решить, какие задачи решать и их решать.
Отчётность.

Диэлектрическая проницаемость ближе к 1 у менее плотных веществ.

Пирамиды для непрерывного изменения средней диэлектрической проницаемости

Почему от 1 ГГц. Подсказка -- посмотреть про рупорные БЭК.





















 */






















