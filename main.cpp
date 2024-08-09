#include "mainwindow.h"
#include <QApplication>






double Function(double a, int b)
{
    double power = 1;
    for (int i=0;i<b;i++)
    {
        power*=a;
    }
    return power;
}

int main(int argc, char *argv[])
{

    qDebug()<<Function(1.41, 2);


    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "0");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
