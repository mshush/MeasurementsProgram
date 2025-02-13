#include "referencetarget.h"
#include <math.h>
void ReferenceTarget::cylinder::SetCylinderParams(double cylraduis, double cylheight)
{

   height = cylheight;
   radius = cylraduis;
}

double ReferenceTarget::cylinder::CalcCylinderRCS(double freq)
{
    double LA = 0.299792458/freq;
    double rcsSide = 2*M_PI*height*height*radius/LA;
    //rcsSide = 10*log10(rcsSide);
    return rcsSide;
}

void ReferenceTarget::sphere::SetSphereParams(double sphradius)
{

    radius = sphradius;
}

double ReferenceTarget::sphere::CalcSphereRCS(double freq)
{

    return 0.0;
}



void ReferenceTarget::SetRefTargetType(QString RefTrgtType)
{
    if (RefTrgtType == "Sphere") RefTargetType = ReferenceTarget::ReferenceTargetType::Sphere;
    else RefTargetType = ReferenceTarget::ReferenceTargetType::Cylinder;
}

double* ReferenceTarget::CalcRefTarget(double StartFreq, double StopFreq, int NFreq)
{
    double* RefTargetArray = new double[NFreq];
    double FreqStep = (StopFreq - StartFreq)/NFreq;
    if (RefTargetType == ReferenceTargetType::Cylinder)
    {

        for (int i = 0; i < NFreq; i++)
        {
            RefTargetArray[i] = Cylinder.CalcCylinderRCS(StartFreq + i * FreqStep);
        }
    }


    return RefTargetArray;
}


ReferenceTarget::ReferenceTarget(QObject *parent)
    : QObject{parent}
{

}
