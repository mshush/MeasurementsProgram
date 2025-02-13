#include "opu.h"
#include "common.h"

OPU::OPU(QObject *parent)
    : QObject{parent}
{

}

void OPU::ResetAbort()
{
    bAbort = false;
}

bool OPU::CheckOPUConnectionState()
{
    bool b = OPUSocket.CheckConnectionState();
    if (!b) { AppendError(3); PowerOn = false; bAbort = true; }
    return b;
}

bool OPU::ConnectToOPU()
{
    PowerOn = OPUSocket.ConnectToSocket("192.168.2.7", 5025);

    if (!PowerOn) {
        AppendError(3);
    }
    return PowerOn;
}

void OPU::StopRotation()
{
     OPUSocket.WriteToSocket("STOP_AZIMUTH\n\n");
    // STOP_AZIMUTH – плавно останавливает движение по всем координатам
    // название команды немного не соотвествует функционалу ...
}


void OPU::Abort()
{
     OPUSocket.WriteToSocket("ABORT\n\n");
     bAbort = true;

}

bool OPU::SetOPUParameters(double startAzAngl, double stopAzAngl,
                      int AzAnglStep, int Speed , MoveMode MoveMod ){

    /* bool b = CheckOPUConnectionState();
     if (b) {
    SetStartStopAz( startAzAngl,  stopAzAngl);
     SetMovementMode( MoveMod);
    SetAzSpeed( Speed);
    SetAzTriggerAnglStep( AzAnglStep);
     }
    return true;
*/
}


bool OPU::SetOPUParameters(double startAzAngl, double stopAzAngl, double startElAngl, double stopElAngl, double AzAnglStep, double ElAnglStep, int Speed, MoveMode MoveMod)
{
     /*
     SetStartStopAz( startAzAngl,  stopAzAngl);
     SetStartStopEl( startElAngl,  stopElAngl);
     SetMovementMode( MoveMod);
     SetAzSpeed( Speed);
     SetAzTriggerAnglStep( AzAnglStep);
     SetElTriggerAnglStep( ElAnglStep);
     return true;
*/
}

bool OPU::GetOPUParsFromInterface(double startAzAngle, double stopAzAngle, double startElAngle, double stopElAngle, double AzAngleStepDeg, double ElAngleStepDEg, int RotationSpeed, MoveMode MoveMod)
{
     startAzAngl = startAzAngle;
     stopAzAngl = stopAzAngle;
     startElAngl = startElAngle;
     stopElAngl = stopElAngle;
     Speed = RotationSpeed;
     AzAnglStep = AzAngleStepDeg;
     ElAnglStep = ElAngleStepDEg;
     ModeOfMove = MoveMod;
}

bool OPU::GetOPUParsFromInterface(double startAzAngle, double stopAzAngle, int AzAngleStepDeg, int RotationSpeed, MoveMode MovMode)
{
     startAzAngl = startAzAngle;
     stopAzAngl = stopAzAngle;
     Speed = RotationSpeed;
     AzAnglStep = AzAngleStepDeg;
     ModeOfMove = MovMode;
}


double OPU::GetCurrentElAngl()
{

}

double OPU::GetCurrentAzAngl()
{
     double CurrAz;
     OPUSocket.QueryDouble("GET_AZIMUTH_CURRENT_ANGLE\n\n", CurrAz);
     return CurrAz;

}

void OPU::SetCurrentElAngl(double AnglCurrentEl)
{

}

void OPU::SetCurrentAzAngl(double AnglCurrentAz)
{

}


void OPU::MoveFromTo()
{

}

void OPU::MoveAzFromTo()
{
    SimulateAzMovement();
}

void OPU::MoveElFromTo()
{

}

void OPU::SetStartStopAz(double startAz, double stopAz)
{
    OPUSocket.WriteToSocket(QString("SET_AZIMUTH_START_ANGLE %1 \n\n").arg(startAz));
    OPUSocket.WriteToSocket(QString("SET_AZIMUTH_FINISH_ANGLE %1 \n\n").arg(startAz));
}

void OPU::SetStartStopEl(double startEl, double stopEl)
{

}

void OPU::SetMovementMode(MoveMode MovMode)
{
    ModeOfMove = MovMode;
}

void OPU::SetAzSpeed(int Speed)
{
    OPUSocket.WriteToSocket(QString("SET_AZIMUTH_SPEED %1 \n\n").arg(Speed));
}

void OPU::SetElSpeed(int Speed)
{
    OPUSocket.WriteToSocket(QString("SET_ELEVATION_SPEED %1 \n\n").arg(Speed));

}

void OPU::SetAzTriggerPoi(int numOfPoin)
{

}

void OPU::SetElTriggerPoi(int numOfPoin)
{

}


int OPU::GetAzSpeed()
{
    int Speed;
    OPUSocket.QueryInt("GET_AZIMUTH_SPEED\n\n", Speed);
    return Speed;
}

int OPU::GetElSpeed()
{

}

int OPU::GetAzTriggerAnglStep()
{
    double step;
    OPUSocket.QueryDouble("GET_AZIMUTH_TRIGGER_TIME\n\n", step);
    return step;
}

int OPU::GetElTriggerAnglStep()
{

}

void OPU::SetAzTriggerAnglStep(double AnglStepDegrees)
{
    // TRIGGER_TIME имеется в виду именно шаг по углу а не времч
    OPUSocket.WriteToSocket(QString("SET_AZIMUTH_TRIGGER_TIME %1 \n\n").arg(AnglStepDegrees));
 }

void OPU::SetElTriggerAnglStep(double AnglStepDegrees)

{// Нет аналогичной команды для elevation !
   OPUSocket.WriteToSocket(QString("SET_AZIMUTH_TRIGGER_TIME %1 \n\n").arg(AnglStepDegrees));

}

void OPU::SimulateAzMovement()
{
    connect(&TriggerSimulationTimer, QTimer::timeout, this, SimulateTrigger);
    //TriggerSimulationTimer.setInterval(1000);
    TriggerSimulationTimer.start(2000);
}

void OPU::StopSimTrig()
{
    TriggerSimulationTimer.stop();
}
