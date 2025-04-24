#ifndef VNA_H
#define VNA_H

#include <QObject>
#include <QCoreApplication>
#include <QEventLoop>
#include "include_/tcpsocket.h"
#include <complex>
//#include "MeasData.h"
//using QComplexVector = QVector<std::complex<double>>;
//using QDoubleVector = QVector<double>;
//using QComplexVector = std::vector<std::complex<double>>;
//using QDoubleVector = std::vector<double>;


class VNA : public QObject
{
    Q_OBJECT

public:

    ~VNA();
    enum class ReadMode {ASC, REAL, REAL32};

    VNA(QObject *parent = nullptr);
    bool ConnectToSocket(QString ip = "192.168.0.83", int port = 5025);
    void DisconnectFromSocket();
    void MeasureTestSingleSweep();
    void MeasureTestSingleSweepCurrAsp();
    void MeasureSingleSweep();
    void ReadSingleSweep(double *dest);
    void ReadSingleSweep(double* destRe, double* destIm);

    bool SetAllParametersObsolete(bool ExtTrigOn, QString StartFreq, QString StopFreq, QString Pow, int NumOfPoints, QString MeasParameter, QString type, int IF);
    bool SetAllParameters(bool ExtTrigOn, QString StartFreq, QString StopFreq, QString Pow, int NumOfPoints, QString MeasParameter, QString type, int IF);
    bool SetStartStopFreq(QString StartFreq, QString StopFreq);
    bool SetPow(QString Pow);
    bool SetNumOfPoi(int NumOfPoin);
    bool SetMeasParameter(QString Par);
    bool SetIF(int IF);
    bool SetTriggerMode(bool ExtTrigger);
    bool SetReadMode(ReadMode ReadMod);
    bool OPC();
    bool Preset();
    bool getVNAError();

   /* bool SetFIFOStateOn();
    bool SetFIFOCapacity(int cap);
    int GetFIFONumOfSweeps();
    void GetFIFOSingleSweep();
    void ReadFIFOSingleSweep(double *dest);
*/
    bool WriteToSocket(QString str);
    QString IDN();
    //void Debug();
    //void Debug(QTcpSocket* socket_);
    //void SimulateTriggerOPU(OPU* opu);
private:

    QEventLoop TrigSimLoop;
    QString debug;
    int skipbytes_ = 0;
    int bytesRead = 0;
    int SweepsRead = 0;
    int SweepsAvailiable = 0;
    QByteArray tempArray;
    struct VNAParams
    {
        QString ip = "192.168.0.83";
        int port = 5025;
        int Pow = 0;
        double StartFreq = 2;
        double StopFreq = 4;
        int NumOfPoi = 1601;
        int IF = 10000;
        QString Datatype = "double";
        QString MeasParameter = "S21";

        void CopyTo(VNAParams Dest)
        {
            Dest.ip = ip;
            Dest.port = port;
            Dest.Pow = Pow;
            Dest.StartFreq = StartFreq;
            Dest.StopFreq = StopFreq;
            Dest.NumOfPoi = NumOfPoi;
            Dest.IF = IF;
            Dest.Datatype = Datatype;
            Dest.MeasParameter = MeasParameter;
        }

    } StateOfParams;
    TCPSocket socketVNA;
    ReadMode CurrentReadMode;
    bool ExternalTrigger;


};

#endif // VNA_H
