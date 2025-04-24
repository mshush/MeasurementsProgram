#ifndef COMPLEXDATAVECTOR_H
#define COMPLEXDATAVECTOR_H
#include <QVector>
//#include <cstdlib>
#include <complex>

using QComplexVector = QVector<std::complex<double>>;
using QDoubleVector = QVector<double>;
//using QComplexVector = std::vector<std::complex<double>>;
//using QDoubleVector = std::vector<double>;

class ComplexDataVector
{
private:

    QComplexVector data;
    //QComplexVector DownSampledData;
    int NumPoinPerSweep = 1601;
    int NumAz = 1;
    int NumEl = 1;
    inline bool checkBounds(int iNAz, int iNEl);
    inline bool checkBounds(int iNf, int iNAz, int iNEl);
    inline bool checkBounds(int i) {if (i > Len() || i < 0) {
            throw std::out_of_range(
                std::string("ComplexVector::checkBounds : Index out of bounds. ") +
                " i = " + std::to_string(i) + "for vector size of (" +
                std::to_string(NumPoinPerSweep) + "," +
                std::to_string(NumAz) + "," +
                std::to_string(NumEl) + ")"
                );
            return false;
        }
    }  //throw std::out_of_range("Out of Bonds");}

public:
    ComplexDataVector();

    void DownSampleData();

    explicit ComplexDataVector(int NFreq, int NAz = 1, int NEl = 1, std::complex<double> initValue = {0.0,0.0});
    explicit ComplexDataVector(const QComplexVector &initialData);
    //void SetNumOfPoints(int NFreq, int NAz = 1, int NEl = 1);
    void SetNPoinPerSweep(int Npoin)  {NumPoinPerSweep = Npoin;
        if(NumAz == 0) NumAz = 1;
        if(NumEl == 0) NumEl = 1;
        data.resize(NumPoinPerSweep*NumAz*NumEl);}
    void SetNAz(int NAz)  {NumAz = NAz;
        if(NumPoinPerSweep == 0) NumPoinPerSweep = 1;
        if(NumEl == 0) NumEl = 1;
        data.resize(NumPoinPerSweep*NumAz*NumEl);}
    void SetNEl(int NEl)  {NumEl = NEl;
        if(NumPoinPerSweep == 0) NumPoinPerSweep = 1;
        if(NumAz == 0) NumEl = 1;
        data.resize(NumPoinPerSweep*NumAz*NumEl);}

    void SetZeroVector(int Npoin, int NAz = 1, int NEl = 1);
    void SetZeroVector();
    //void SetOnesVector(int Npoin, int NAz = 1, int NEl = 1);

    int GetNFreq() const { return NumPoinPerSweep; }
    int GetNAz() const {return NumAz;}
    int GetNEl() const {return NumEl;}

    int Len() const { return data.size(); }

    std::complex<double>& operator[](int index) {
       checkBounds(index);
       return data[index]; }

    bool setSweep(QComplexVector NewSweep, int AzIndex = 0, int ElIndex = 0);
    bool setValue(std::complex<double> NewValue, int NpoinIndx, int AzIndx = 0 , int ElIndx = 0);
    QComplexVector getAllData() const { return data; }
    bool getSweep(QComplexVector& DestVector, int AzIndx = 0 , int ElIndx = 0 );
    QComplexVector getSweep(int AzIndx = 0 , int ElIndx = 0 );
    bool getValue(std::complex<double>& DestVal, int NPoinIndx, int AzIndx = 0 , int ElIndx = 0);

    QDoubleVector GetAmplVectordBAt(int AzIndx = 0, int ElIndx = 0);
    void GetAmplVectordBAt(QDoubleVector &DestVector, int AzIndx = 0, int ElIndx = 0);
    QDoubleVector GetAmplVectorSqrtAt(int AzIndx = 0, int ElIndx = 0);
    void GetAmplVectorSqrtAt(QDoubleVector &DestVector, int AzIndx = 0, int ElIndx = 0);

    void ClearVector();

};

#endif // COMPLEXDATAVECTOR_H
