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

    const std::pair<double, double> FrequencyRanges[7] = {
                                                          {1.0, 2.0},     //L
                                                          {2.0, 4.0},     //S
                                                          {4.0, 8.0},     //C
                                                          {8.0, 12.0},    //X
                                                          {12.0, 18.0},   //Ku
                                                          {18.0, 26.5},   //K
                                                          {26.5, 40.0}};  //Ka
    QHBoxLayout * ButtonGroupLayout;
    QButtonGroup * FrequencyRangesButtonGroup;
    QPushButton * NoRangeButton;
    QPushButton * LRangeButton;
    QPushButton * SRangeButton;
    QPushButton * CRangeButton;
    QPushButton * XRangeButton;
    QPushButton * KuRangeButton;
    QPushButton * KRangeButton;
    QPushButton * KaRangeButton;



    //Область задания углов
    void InitializeAngleGroupBox();

    QGroupBox * AngleGroupBox;
    QVBoxLayout * AngleGroupBoxLayout;
    QLabel * AngleFromLabel;
    QLabel * AngleToLabel;
    QLineEdit * AngleFromEdit;
    QLineEdit * AngleToEdit;
    QGridLayout * AngleFromToGridLayout;
    QHBoxLayout * AngleNumberOfPointsLayout;
    QLabel * AngleNumberOfPointsLabel;
    QLineEdit * AngleNumberOfPointsEdit;




    //Область параметров калибровочного образца
    void InitializeCalibrationSampleGroupBox();
    QGroupBox * CalibrationSampleGroupBox;
    QVBoxLayout * CalibrationSampleMainLayout;
    QHBoxLayout * CalibrationSampleTypeLayout;
    QComboBox * CalibrationSampleComboBox;
    QHBoxLayout * CalibrationSampleParametersLayout;


    double StartFrequency = 0;
    double StopFrequency = 1600;
    int NumberOfPoints = 1601;



public slots:
    void StartStopButtonClicked  (bool StartStopButtonCheckStatus );
    void CenterSpanButtonClicked (bool CenterSpanButtonCheckStatus);
    void OnSetFrequencyParametersButtonClicked();
    void FrequencyRangeButtonPressed(int ChosenRangeId);
    void FrequencyRangeButtonClicked(int ChosenRangeId);
    void RenewStartStopFrequencies();

signals:
    void ParametersOfMeasurementsChanged(double FreqStart, double FreqStop, int PointsNumber);
};

#endif // MEASUREMENTSPARAMETERSWIDGET_H
