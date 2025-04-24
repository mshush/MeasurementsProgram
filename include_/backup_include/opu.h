#ifndef OPU_H
#define OPU_H
#include <QObject>
#include "include_/tcpsocket.h"
#include "include_/measdata.h"

class OPU : public QObject
{
    Q_OBJECT

private:

    double startAzAngl = 0;
    double stopAzAngl = 180;
    double startElAngl = 0;
    double stopElAngl = 0;
    int Speed = 1;
    double AzAnglStep = 0.1;
    double ElAnglStep = 0.1;

    TCPSocket OPUSocket;

    bool bAbort;
    bool PowerOn;

    double AnglCurrentAz;
    double AnglCurrentEl;


public:
    ~OPU();
    OPU(QObject *parent = nullptr);

    enum class MoveMode{CCW, CW}ModeOfMove;

    void ResetAbort();
    bool CheckOPUConnectionState();

    bool ConnectToOPU();
    void SmoothStopRotation();
    void Abort();

    bool SetOPUParameters(double startAzAngl = 0, double stopAzAngl = 360, double startElAngl = 0, double stopElAngl = 0,
                          double AzAnglStep = 0.01, double ElAnglStep = 0.01, int Speed = 1.0, MoveMode MoveMod = MoveMode::CCW);
    bool SetOPUParameters(double startAzAngl = 0, double stopAzAngl = 360,
                          int AzAnglStep = 0.1, int Speed = 1, MoveMode MoveMod = MoveMode::CCW);
/*
    bool GetOPUParsFromInterface(double startAzAngle = 0, double stopAzAngle = 360, double startElAngle = 0, double stopElAngle = 0,
                          double AzAngleStepDeg = 0.01, double ElAngleStepDEg = 0.01, int RotationSpeed = 1.0, MoveMode MoveMod = MoveMode::CCW);
    bool GetOPUParsFromInterface(double startAzAngl = 0, double stopAzAngl = 360,
                                 int AzTriggerPoints = 3600, int Speed = 1, MoveMode MovMode = MoveMode::CCW);
*/

    bool CheckSetParams();

    void MoveFromTo();
    void BeginMovementwithTriggerAzFromTo();
    void BeginMovementwithTriggerElFromTo();
    void MoveAzToStartAzAngle();
    void MoveElToStartElAngle();
    void MoveAzToStopAzAngle(MoveMode MoveMod);
    void MoveElToStopElAngle(MoveMode MoveMod);

    void SetCurrentElAngl(double AnglCurrentEl);
    void SetCurrentAzAngl(double AnglCurrentAz);
    void SetStartStopAz(double startAz, double stopAz);
    void SetStartStopEl(double startEl, double stopEl);
    void SetMovementMode(MoveMode MovMode);
    void SetAzSpeed(int Speed_);
    void SetElSpeed(int Speed_);
    void SetAzTriggerPoi(int numOfPoin, double AzStart, double AzStop);
    void SetElTriggerPoi(int numOfPoin);
    void SetAzTriggerAnglStep(double AnglStepDegrees);
    //void SetElTriggerAnglStep(double AnglStepDegrees);

    int GetAzSpeed();
    int GetElSpeed();
    int GetAzTriggerAnglStep();
    double GetCurrentElAngl();
    double GetCurrentAzAngl();


};

#endif // OPU_H
