#include "opu.h"
#include "common.h"

OPU::OPU(QObject *parent)
    : QObject{parent}
{

}

bool OPU::ConnectToOPU()
{
    bool b = true;

    // bool b = cpnnect to opu
    if (!b) {
        AppendError(3);
    }
    return true;
}

void OPU::StopRotation()
{

}

void OPU::ResumeRotation()
{

}

bool OPU::SetOPUParameters(double startAzAngl, double stopAzAngl,
                      int AzTriggerPoints, int Speed , int MovMode ){
    SetStartStopAz( startAzAngl,  stopAzAngl);
    SetMovementMode( MovMode);
    SetSpeed( Speed);
    SetAzStep( AzAnglStep);
    return true;
}

bool OPU::SetOPUParameters(double startAzAngl, double stopAzAngl, double startElAngl, double stopElAngl, double AzAnglStep, double ElAnglStep, int Speed, int MovMode)
{
     SetStartStopAz( startAzAngl,  stopAzAngl);
     SetStartStopEl( startElAngl,  stopElAngl);
     SetMovementMode( MovMode);
     SetSpeed( Speed);
     SetAzStep( AzAnglStep);
     SetElStep( ElAnglStep);
     return true;
}
bool OPU::SetOPUParameters(double startAzAngl, double stopAzAngl, double startElAngl, double stopElAngl,int AzTriggerPoints,int ElTriggerPoints, int Speed, int MovMode)
{
     SetStartStopAz( startAzAngl,  stopAzAngl);
     SetStartStopEl( startElAngl,  stopElAngl);
     SetMovementMode( MovMode);
     SetSpeed( Speed);
     SetAzTriggerPoi( AzTriggerPoints);
     SetElTriggerPoi(ElTriggerPoints );
     return true;

}
/*
 *
void OPU::MeasureOPU(double startAzAngl, double stopAzAngl, double startElAngl, double stopElAngl, double PolAngl, int Speed, double AzAnglStep, double ElAnglStep)
{

}

void OPU::ReadOPUSingleSweep()
{

}

void OPU::MeasureOPUSingleSweep()
{

}
*/
double OPU::GetCurrentElAngl()
{

}

double OPU::GetCurrentAzAngl()
{

}

void OPU::SetCurrentElAngl(double AnglCurrentEl)
{

}

void OPU::SetCurrentAzAngl(double AnglCurrentAz)
{

}

void OPU::SetCoord(double ElAngl, double AzAngl)
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

}

void OPU::SetStartStopEl(double startEl, double stopEl)
{

}

void OPU::SetMovementMode(int MovMode)
{

}

void OPU::SetSpeed(int Speed)
{

}

void OPU::SetAzTriggerPoi(int numOfPoin)
{

}

void OPU::SetElTriggerPoi(int numOfPoin)
{

}

int OPU::GetAzTriggerPoi()
{

}

int OPU::GetElTriggerPoi()
{

}

void OPU::SetAzStep(int step)
{

}

void OPU::SetElStep(int step)
{

}

void OPU::SimulateAzMovement()
{
    connect(&TriggerSimulationTimer, QTimer::timeout, this, SimulateTrigger);
    //TriggerSimulationTimer.setInterval(1000);
    //TriggerSimulationTimer.start(2000);
}

void OPU::StopSimTrig()
{
    TriggerSimulationTimer.stop();
}
