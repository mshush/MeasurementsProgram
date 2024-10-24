#ifndef MEASUREMENTSPARAMETERSWIDGET_H
#define MEASUREMENTSPARAMETERSWIDGET_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QGroupBox>
#include <QComboBox>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QButtonGroup>


class MeasurementsParametersWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MeasurementsParametersWidget(QWidget *parent = nullptr);
    ~MeasurementsParametersWidget();

    QVBoxLayout * VerticalLayoutOfParameters;

    //Область задания частоты
    void InitializeFrequencyGroupBox();

    QGroupBox * FrequencyGroupBox;
    QVBoxLayout * FrequencyGroupBoxLayout;
    QRadioButton * StartStopButton;
    QRadioButton * CenterSpanButton;
    QGridLayout * FrequencyRangeLayout;
    QLabel * FrequencyStartCenterLabel;
    QLineEdit * FrequencyStartCenterEdit;
    QLabel * FrequencyStartCenterUnitsLabel;
    QLabel * FrequencyStopSpanLabel;
    QLineEdit * FrequencyStopSpanEdit;
    QLabel * FrequencyStopSpanUnitsLabel;
    QPushButton * SetFrequencyParametersButton;
    QHBoxLayout * FrequencyNumberOfPointsLayout;
    QLabel * FrequencyNumberOfPointsLabel;
    QLineEdit * FrequencyNumberOfPointsEdit;
    QDoubleValidator * DoubleValidator;
/*
    const std::pair<double, double> FrequencyRanges[7] = {
                                                          {1.0, 2.0},     //L
                                                          {2.0, 4.0},     //S
                                                          {4.0, 8.0},     //C
                                                          {8.0, 12.0},    //X
                                                          {12.0, 18.0},   //Ku Ka1 26-36 12-26 - не мер. больш погл
                                                          {18.0, 26.5},   //K  УБРАТЬ!!!!!!! Посмотреть диапазоны в проге
                                                          {26.5, 40.0}};  //Ka Ka2 36-40
*/

    const std::pair<double, double> FrequencyRanges[6] = {
                                                          {1.0,  2.0},     //L
                                                          {2.0,  4.0},     //S
                                                          {4.0,  8.0},     //C
                                                          {8.0,  12.0},    //X
                                                          {26.0, 36.0},   //Ka1  12-26 - не мер. больш погл
                                                          //{18.0, 26.5},   //K  УБРАТЬ!!!!!!! Посмотреть диапазоны в проге
                                                          {36.0, 40.0}};  //Ka2





    QHBoxLayout * ButtonGroupLayout;
    QButtonGroup * FrequencyRangesButtonGroup;
    QPushButton * NoRangeButton;
    QPushButton * LRangeButton;
    QPushButton * SRangeButton;
    QPushButton * CRangeButton;
    QPushButton * XRangeButton;
    //QPushButton * KuRangeButton;
    //QPushButton * KRangeButton;
    QPushButton * K1RangeButton;
    QPushButton * K2RangeButton;


    //Область задания углов
    void InitializeAngleGroupBox();

    QGroupBox * AngleGroupBox;
    QVBoxLayout * AngleGroupBoxLayout;
    QGridLayout * AngleGridLayout;

    QLabel * AzimuthStartLabel;
    QLabel * AzimuthStopLabel;
    QLineEdit * AzimuthStartEdit;
    QLineEdit * AzimuthStopEdit;
    QLabel * AzimuthNumberOfPointsLabel;
    QLineEdit * AzimuthNumberOfPointsEdit;

    QLabel * ElevationStartLabel;
    QLabel * ElevationStopLabel;
    QLineEdit * ElevationStartEdit;
    QLineEdit * ElevationStopEdit;
    QLabel * ElevationNumberOfPointsLabel;
    QLineEdit * ElevationNumberOfPointsEdit;

    QPushButton * SetAngleParametersButton;




    double FrequencyStart = 1;
    double FrequencyStop = 2;
    int FrequencyNumber = 1601;

    double AzimuthStart = 0;
    double AzimuthStop = 359;
    int AzimuthNumber = 360;

    double ElevationStart = 0;
    double ElevationStop = 9;
    int ElevationNumber = 10;




public slots:
    void StartStopButtonClicked  (bool StartStopButtonCheckStatus );
    void CenterSpanButtonClicked (bool CenterSpanButtonCheckStatus);
    void OnSetFrequencyParametersButtonClicked();
    void OnSetAngleParametersButtonClicked();
    void FrequencyRangeButtonPressed(int ChosenRangeId);
    void FrequencyRangeButtonClicked(int ChosenRangeId);
    void RenewStartStopFrequencies();

signals:
    void FrequencyParametersChanged(double FreqStart, double FreqStop, int FreqNum); //Объединить с углами?
    void AngleParametersChanged(double RotStart, double RotStop, int RotNum, double TiltStart, double TiltStop, int TiltNum);
    void ErrorOccured(QString ErrorText);
};

#endif // MEASUREMENTSPARAMETERSWIDGET_H
