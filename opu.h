#ifndef OPU_H
#define OPU_H
#include <QTimer>
#include <QTimerEvent>
#include <QObject>

class OPU : public QObject
{
    Q_OBJECT

private:
    double startAzAngl;
    double stopAzAngl;
    double startElAngl;
    double stopElAngl;
    int Speed;
    double AzAnglStep;
    double ElAnglStep;
    bool PowerOn;
    QTimer TriggerSimulationTimer; // for simulation only

public:
    OPU(QObject *parent = nullptr);
    bool bStopRotation;

    bool ConnectToOPU();
    void StopRotation();
    void ResumeRotation();

    bool SetOPUParameters(double startAzAngl = 0, double stopAzAngl = 360, double startElAngl = 0, double stopElAngl = 0,
     double AzAnglStep = 0.01, double ElAnglStep = 0.01, int Speed = 1.0, int MovMode = 1);
    bool SetOPUParameters(double startAzAngl = 0, double stopAzAngl = 360, double startElAngl = 0, double stopElAngl = 0,
                          int AzTriggerPoints = 3600,int ElTriggerPoints = 1, int Speed = 1, int MovMode = 1);
    bool SetOPUParameters(double startAzAngl = 0, double stopAzAngl = 360,
                          int AzTriggerPoints = 3600, int Speed = 1, int MovMode = 1);

/*
    void MeasureOPU(double startAzAngl, double stopAzAngl, double startElAngl, double stopElAngl,
    double PolAngl, int Speed, double AzAnglStep, double ElAnglStep);
    void ReadOPUSingleSweep(); // чтение одного измерения в многомерный массив
    void MeasureOPUSingleSweep(); // одно измерение при установленных углах */
    double AnglCurrentAz;
    double AnglCurrentEl;

    double GetCurrentElAngl();
    double GetCurrentAzAngl();

    void SetCurrentElAngl(double AnglCurrentEl);
    void SetCurrentAzAngl(double AnglCurrentAz);

    void SetCoord(double ElAngl, double AzAngl);
    void MoveFromTo();
    void MoveAzFromTo();
    void MoveElFromTo();

    void SetStartStopAz(double startAz, double stopAz);
    void SetStartStopEl(double startEl, double stopEl);
    void SetMovementMode(int MovMode);
    void SetSpeed(int Speed);
    void SetAzTriggerPoi(int numOfPoin);
    void SetElTriggerPoi(int numOfPoin);
    int GetAzTriggerPoi();
    int GetElTriggerPoi();

    void SetAzStep(int step);
    void SetElStep(int step);

    void SimulateAzMovement();
    void StopSimTrig();
signals:
    void SimulateTrigger();
};

#endif // OPU_H
