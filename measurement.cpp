#include "measurement.h"


void Measurement::AddVectorToList(ThreeDimensionalVector* VectorToBeAdded)
{
    ListOfVectors.append(VectorToBeAdded);
}

ThreeDimensionalVector * Measurement::GetVectorFromList(int d)
{
    return ListOfVectors[d];
}
