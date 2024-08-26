#ifndef TABWIDGETFORTOOLS_H
#define TABWIDGETFORTOOLS_H

#include <QObject>
#include <QTabWidget>
#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QStyle>
#include <QIcon>
#include <QProgressBar>

class TabWidgetForTools :public QWidget//: public QTabWidget
{
    Q_OBJECT
public:
    TabWidgetForTools();
    ~TabWidgetForTools();

    //QWidget * Tab1;
    //QWidget * Tab2;

    QPushButton * StartMeasurementsButton;
    QPushButton * StopMeasurementsButton;
    QPushButton * ContinuousMeasurementsButton;

    //QPushButton * SaveDataButton;
    //QPushButton * ImportDataButton;

    //QPushButton * FourierTransformButton;
    //QPushButton * InverseFourierTransformButton;

    QPushButton * SaveMeasuredFunctionButton;

signals:
    void ContinuousMeasurementsButtonClickedSignal(bool CheckedStatus);

public slots:
    void SendContinuousMeasurementsButtonClickedSignal();
};

#endif // TABWIDGETFORTOOLS_H
