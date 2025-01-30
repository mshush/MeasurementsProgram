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

    QLabel * SetCurrentAzimuthLabel;
    QLabel * SetCurrentElevationLabel;
    QLabel * SetCurrentFrequencyLabel;

    QDoubleSpinBox * SetCurrentAzimuthDoubleSpinBox;
    QDoubleSpinBox * SetCurrentElevationDoubleSpinBox;
    QDoubleSpinBox * SetCurrentFrequencyDoubleSpinBox;

    QPushButton * SetCurrentAngleButton; // Кнопку убрать -- вводить через сигнал об окончании изменений

    double AzimuthStart      = 0;
    double AzimuthStop       = 359;
    int    AzimuthNumber     = 360;

    double ElevationStart    = 0;
    double ElevationStop     = 9;
    int    ElevationNumber   = 10;

    double FrequencyStart    = 1;
    double FrequencyStop     = 2;
    int    FrequencyNumber   = 1601;

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








    //QPushButton * CalculateDistancePortraitButton;


    //QIntValidator * IntValidator;



signals:

    void ErrorOccured(QString ErrorText);

public slots:
    void FindBackground();
    //void AddBackground(); // В MainWindow
    //void SubstractBackground(); // В MainWindow

    //void FindCalibration();
    //void SetCalibration (); // В MainWindow


    void HandleAzimuthSpinBoxChange();
    void HandleElevationSpinBoxChange();
    void HandleFrequencySpinBoxChange();

    void FileChosenInTreeWidget(int Mode, QString FileName);

};

#endif // RESULTPARAMETERSWIDGET_H
