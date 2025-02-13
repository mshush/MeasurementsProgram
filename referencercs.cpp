#include "referencercs.h"
#include <math.h>
void ReferenceRCS::SetCylinderParams(double r, double h)
{
    Cylinder.height = h;
    Cylinder.radius = r;
}

double ReferenceRCS::CalcCylinderRCS(double f)
{
    double LA = 0.299792458/f;
    double rcsSide = 2*M_PI*Cylinder.height*Cylinder.height*Cylinder.radius/LA;
    rcsSide = 10*log10(rcsSide);
    return rcsSide;
}



ReferenceRCS::ReferenceRCS(QObject *parent)
    : QObject{parent}
{

}
