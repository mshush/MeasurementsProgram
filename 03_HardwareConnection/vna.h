#ifndef VNA_H
#define VNA_H

#include <QObject>
#include <QWidget>
#include <QTcpSocket>
#include <QApplication>
#include "common.h"
#include <errorhandler.h>
#include "../03_HardwareConnection/tcpsocket.h"
#include "../03_HardwareConnection/opu.h"
#include <QEventLoop>
class VNA : public QObject
{
    Q_OBJECT
public:
    ~VNA();
    enum class ReadMode {ASC, REAL, REAL32};

    struct StateOfParamsVNA{
        QString FStart = "1";
        QString FStop = "20";
        bool ExternalTrigger = false;
        QString BinaryType = "double";
        int NumOfPoint = 1601;
        QString PowerDbm ="0";
        int IF = 10000;
        QString MeasParameter = "S11";
        QString ReadModee = "ASC";
        ReadMode CurrentReadMode = ReadMode::ASC;
    } StateOfParams;

    //QByteArray BinaryDataArr;

    int NumOfSweeps;
    int SweepsRead = 0;
    int SweepsAvailiable = 0;
    int NumOfPoi = 0;
    bool ExternalTrigger;
    bool bTargetMeas = false;

    QString type = "double";
    int expectedBytes;
    QByteArray tempArray;
    TCPSocket socketVNA;
    int bytesRead = 0;
    VNA(QObject *parent = nullptr);
    QString debug;
    int skipbytes_ = 0;


    bool ConnectToSocket(QString ip = "192.168.0.83", int port = 5025);
    void DisconnectFromSocket();

    void MeasureTestSingleSweep();

    void MeasureSingleSweep();
    void ReadSingleSweep(double *dest);
    void ReadSingleSweep(double* destRe, double* destIm);

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

   /* bool SetFIFOStateOn();
    bool SetFIFOCapacity(int cap);
    int GetFIFONumOfSweeps();
    void GetFIFOSingleSweep();
    void ReadFIFOSingleSweep(double *dest);
*/
    void ResetVNA();
    bool WriteToSocket(QString str);
    QByteArray ReadStringData();
    QString IDN();
    //void Debug();
    //void Debug(QTcpSocket* socket_);


    void SimulateTriggerOPU(OPU* opu);
    QEventLoop TrigSimLoop;
//signals:
    //void text(QString Text);
};

#endif // VNA_H
