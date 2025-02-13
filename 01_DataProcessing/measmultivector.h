#ifndef MEASMULTIVECTOR_H
#define MEASMULTIVECTOR_H

#include <QObject>

class MeasMultiVector : public QObject
{
    Q_OBJECT
private:
    double* DataArrayPtr;
    int NPoinAz;
    int NPoinEl;
    SetZeroVector();
public:
    MeasMultiVector();


signals:

};

#endif // MEASMULTIVECTOR_H
