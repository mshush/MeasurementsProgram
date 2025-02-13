#ifndef REFERENCERCS_H
#define REFERENCERCS_H

#include <QObject>

class ReferenceRCS : public QObject
{
    Q_OBJECT
private:
    struct cylinder{
        double radius = 0.062/2;
        double height = 0.037;
    }Cylinder;

public:
    void SetCylinderParams(double r, double h);
    double CalcCylinderRCS(double f);
    explicit ReferenceRCS(QObject *parent = nullptr);

signals:

};

#endif // REFERENCERCS_H
