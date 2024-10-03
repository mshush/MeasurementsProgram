#ifndef RESULTPARAMETERSWIDGET_H
#define RESULTPARAMETERSWIDGET_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>
//#include <QIntValidator>
#include <QDoubleSpinBox>
//#include <cmath>


class ResultParametersWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ResultParametersWidget(QWidget *parent = nullptr);


    //enum ModeOfMeasurement {Response, Background, Calibration};



    QVBoxLayout * OutermostVerticalLayout;

    // Область растяжения и сдвига угла
    QGroupBox * AzimuthScaleAndOffsetGroupBox;


    // Задание углов
    void InitiateAnglesGroupBox();
    QGroupBox * AnglesGroupBox;
    QGridLayout * AnglesGroupBoxLayout;
    QLabel * SetCurrentRotationAngleLabel;
    QDoubleSpinBox * SetCurrentRotationAngleDoubleSpinBox;
    QLabel * SetCurrentTiltAngleLabel;
    QDoubleSpinBox * SetCurrentTiltAngleDoubleSpinBox;
    QPushButton * SetCurrentAngleButton; // Нужно ли? Вбивать и нажатием enter, и кнопки -- избыточно?


    double RotationStart = 0;
    double RotationStop  = 359;
    int RotationNumber = 360;

    double TiltStart     = 0;
    double TiltStop      = 9;
    int TiltNumber = 10;


    /*
    // Задание отклика
    void InitiateResponseGroupBox();
    QGroupBox * ResponseGroupBox;
    QLineEdit * ResponseLineEdit;
    QPushButton * ResponseFindButton;
    */


    // Задание бэкграунда
    void InitiateBackgroundGroupBox();
    QGroupBox * BackgroundGroupBox;
    QLineEdit * BackgroundLineEdit;
    QPushButton * BackgroundFindButton;
    QPushButton * BackgroundAddButton;
    QPushButton * BackgroundSubstractButton;



    //Область параметров калибровочного образца // Перенесено из MeasurementsParametersWidget
    void InitiateCalibrationGroupBox();

    //QVBoxLayout * CalibrationSampleMainLayout;
    QHBoxLayout * CalibrationSampleTypeLayout;
    QComboBox * CalibrationSampleComboBox;
    QHBoxLayout * CalibrationSampleParametersLayout;

    QGroupBox * CalibrationGroupBox;
    QLineEdit * CalibrationLineEdit;
    QPushButton * CalibrationFindButton;
    QPushButton * CalibrationSetButton;




    //QPushButton * CalculateDistancePortraitButton;


    //QIntValidator * IntValidator;



signals:

    void ErrorOccured(QString ErrorText);

public slots:
    void FindBackground();
    //void AddBackground(); // В MainWindow
    //void SubstractBackground(); // В MainWindow

    void FindCalibration();
    //void SetCalibration (); // В MainWindow

    void HandleRotationSpinBoxChange();
    void HandleTiltSpinBoxChange();

    void FileChosenInTreeWidget(int Mode, QString FileName);

};

#endif // RESULTPARAMETERSWIDGET_H
