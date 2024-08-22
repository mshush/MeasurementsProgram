#ifndef RESULTPARAMETERSWIDGET_H
#define RESULTPARAMETERSWIDGET_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>
//#include <QIntValidator>
#include <QDoubleSpinBox>
#include <cmath>


class ResultParametersWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ResultParametersWidget(QWidget *parent = nullptr);


    QVBoxLayout * OutermostVerticalLayout;

    // Задание углов
    QGroupBox * AnglesGroupBox;
    QGridLayout * AnglesGroupBoxLayout;
    QLabel * SetCurrentRotationAngleLabel;
    QDoubleSpinBox * SetCurrentRotationAngleDoubleSpinBox;

    QLabel * SetCurrentTiltAngleLabel;
    QDoubleSpinBox * SetCurrentTiltAngleDoubleSpinBox;

    QPushButton * SetCurrentAngleButton; // Нужно ли?


    double RotationStart = 0;
    double RotationStop  = 359;
    int RotationNumber = 360;

    double TiltStart     = 0;
    double TiltStop      = 9;
    int TiltNumber = 10;



    // Задание бэкграунда
    QGroupBox * BackgroundGroupBox;

    QLineEdit * BackgroundLineEdit;
    QPushButton * BackgroundFindButton;
    QPushButton * BackgroundAddButton;
    QPushButton * BackgroundSubstractButton;

    // Задание фона
    QGroupBox * CalibrationGroupBox;
    QLineEdit * CalibrationLineEdit;
    QPushButton * CalibrationFindButton;
    QPushButton * CalibrationSetButton;



    //QIntValidator * IntValidator;

signals:



public slots:
    void FindBackground();
    //void AddBackground(); // В MainWindow
    //void SubstractBackground(); // В MainWindow

    void FindCalibration();
    //void SetCalibration (); // В MainWindow

    void HandleRotationSpinBoxChange();
    void HandleTiltSpinBoxChange();

};

#endif // RESULTPARAMETERSWIDGET_H
