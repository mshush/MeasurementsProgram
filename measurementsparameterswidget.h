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


class MeasurementsParametersWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MeasurementsParametersWidget(QWidget *parent = nullptr);

    //Область задания частоты
    QVBoxLayout * FrequencyButtonLayout;
    QRadioButton * StartStopButton;
    QRadioButton * CenterSpanButton;

    QHBoxLayout * FrequencyStartCenterLayout;
    QLabel * FrequencyStartCenterLabel;
    QLineEdit * FrequencyStartCenterEdit;
    QComboBox * FrequencyStartCenterComboBox;

    QHBoxLayout * FrequencyStopSpanLayout;
    QLabel * FrequencyStopSpanLabel;
    QLineEdit * FrequencyStopSpanEdit;
    QComboBox * FrequencyStopSpanComboBox;



    double StartFrequency;
    double StopFrequency;

public slots:
    void SetStartStopMode (bool StartStopButtonCheckStatus );
    void SetCenterSpanMode(bool CenterSpanButtonCheckStatus);
    void ProcessChangedStartSpanEdit();
    void ProcessChangedStopCenterEdit();

signals:
    void StartStopFrequenciesChanged(double StartFreq, double StopFreq);
};

#endif // MEASUREMENTSPARAMETERSWIDGET_H
