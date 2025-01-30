#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <QObject>
#include <QWidget>
#include "threedimensionalvector.h"
#include <QList>

class Measurement
{
    //Q_OBJECT
public:
    Measurement() = default;
    ~Measurement() = default;

    QList <ThreeDimensionalVector*> ListOfVectors;

    void AddVectorToList(ThreeDimensionalVector* VectorToBeAdded);
    void RemoveVectorFromList(int id)
        {
        ListOfVectors.removeAt(id);
        }
    ThreeDimensionalVector* GetVectorFromList(int id);
};

#endif // MEASUREMENT_H
