#ifndef REFERENCETARGET_H
#define REFERENCETARGET_H

#include <QObject>
#include "common.h"

class ReferenceTarget : public QObject
{
    Q_OBJECT
private:

public:
    enum class ReferenceTargetType{Cylinder, Sphere}RefTargetType;


    void SetRefTargetType(QString RefTrgtType);
    double *CalcRefTarget(double StartFreq, double StopFreq, int NFreq);
    //QString RefTargetType = "cylinder";
    explicit ReferenceTarget(QObject *parent = nullptr);

    struct cylinder{
        double radius = 0.062/2;
        double height = 0.037;
        void SetCylinderParams(double cylraduis, double cylheight);
        double CalcCylinderRCS(double freq);
    }Cylinder;

    struct sphere{
        double radius = 0.062/2;
        void SetSphereParams(double sphradius);
        double CalcSphereRCS(double freq);
    }Sphere;

};

#endif // REFERENCETARGET_H
