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


class MeasurementsParametersWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MeasurementsParametersWidget(QWidget *parent = nullptr);
    ~MeasurementsParametersWidget();

    QVBoxLayout * VerticalLayoutOfParameters;

    //Область задания частоты
    QGroupBox * FrequencyGroupBox;
    QVBoxLayout * FrequencyGroupBoxLayout;
    QRadioButton * StartStopButton;
    QRadioButton * CenterSpanButton;
    QGridLayout * FrequencyRangeLayout;
    QLabel * FrequencyStartCenterLabel;
    QLineEdit * FrequencyStartCenterEdit;
    //QComboBox * FrequencyStartCenterComboBox;
    QLabel * FrequencyStartCenterUnitsLabel;
    QLabel * FrequencyStopSpanLabel;
    QLineEdit * FrequencyStopSpanEdit;
    //QComboBox * FrequencyStopSpanComboBox;
    QLabel * FrequencyStopSpanUnitsLabel;
    QPushButton * SetFrequencyParametersButton;
    QHBoxLayout * FrequencyNumberOfPointsLayout;
    QLabel * FrequencyNumberOfPointsLabel;
    QLineEdit * FrequencyNumberOfPointsEdit;


    //Область параметров калибровочного образца
    QGroupBox * CalibrationSampleGroup;
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
signals:
    void ParametersOfMeasurementsChanged(double FreqStart, double FreqStop, int PointsNumber);
};

#endif // MEASUREMENTSPARAMETERSWIDGET_H
