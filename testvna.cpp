#include "testvna.h"

TestVNA::TestVNA()
{
    QTcpSocket * Socket = new QTcpSocket();

    Socket->connectToHost("192.168.0.83", 5025);
    if (!Socket->waitForConnected(5000)) {
        qDebug() << "Connection failed:" << Socket->errorString();
        return;
    }

    QByteArray tmpByteArray = QString("*IDN?\n").toLocal8Bit();
    Socket->write(tmpByteArray);
    Socket->waitForBytesWritten(5000);
    Socket->waitForReadyRead(5000);
    QString Response = QString::fromLocal8Bit(Socket->readAll());
    qDebug()<<Response;



    QComplexVector CurrentAspectData;

    int NumOfPoi = 1601;

    double* destReal = new double[1601];
    double* destIm = new double[1601];
    CurrentAspectData.resize(NumOfPoi);



    QByteArray data;
    QByteArray ByteDataArray;
    int N = 1601;
    QByteArray datatemp;
    int bytesAvail = 0;

    int AllBytes = 0;
    int ExpectedBytes = 2*N*sizeof(double);
    int skipbytes = 0;
    QString values_ = "";


    Socket->write("INIT\n");
    Socket->write("*TRG\n");
    Socket->write("TRIG:WAIT ENDM\n");
    Socket->write("CALC:DATA:SDAT?\n");


    Socket->waitForReadyRead(5000);
    Response = QString::fromLocal8Bit(Socket->readAll());

    int SkipBytes = 5;

    int DoubleSize = sizeof(double);

    QVector <double> DoubleVector1;
    for (int i = 0; i < 100; i++)
    {
        double doubleValue;
        memcpy(&doubleValue, data.constData()  + SkipBytes +  i*DoubleSize, DoubleSize);
        DoubleVector1.append(doubleValue);
    }

    qDebug()<<Response;
    qDebug()<<"\n\n\n\n\n\n\n ============================================== \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n ============================================== \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n ============================================== \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n ============================================== \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n ============================================== \n\n\n\n\n\n\n\n";
    qDebug()<<DoubleVector1;
    qDebug()<<"check";


    QStringList stringList = Response.split(',');

    QVector<double> doubleVector;

    for (const QString& str : stringList)
    {
        bool ok;
        double value = str.toDouble(&ok);
        if (ok)
        {
            doubleVector.append(value);
        }
        else
        {
            qDebug() << "Conversion failed for value:" << str;
        }
    }

    qDebug()<<doubleVector;
    QDoubleVector VectorForSending;

    for (int k; k<doubleVector.size()/2;k++)
    {
        //doubleVector[2*k]2 + doubleVector[2*k+1];
    }

    /*
    while (true)
    {
        QCoreApplication::processEvents();
        bytesAvail = socketVNA.CheckBytesAvailable();

        if (bytesAvail > 0){
            //if (!measbegin) auto start = std::chrono::high_resolution_clock::now();
            //measbegin = true;

            datatemp.append(socketVNA.ReadAllFromSocket() );

            AllBytes += bytesAvail;
            values_ = QString::fromLocal8Bit(datatemp);

            if (AllBytes == bytesAvail)
            {
                skipbytes_ = 10;
                AllExpectedBytes = 2*StateOfParams.NumOfPoi*sizeof(double) + 1 + skipbytes_;
            }

            if (datatemp.size() == AllExpectedBytes)
            {
                datatemp.trimmed();
                datatemp.remove(0,10);
                tempArray.append(datatemp);
                SweepsAvailiable++;
                break;
            }
        }
    }
    */
}

















    /*
    Socket->write("*RST\n");

    Socket->write("INIT:CONT OFF\n");

    Socket->write("SENS1:SWE:POIN 1601\n");


    Socket->write("CALC1:PAR:DEF S11\n");


    Socket->write("SENS1:FREQ:STAR 2 GHz\n");

    Socket->write("SENS1:FREQ:STOP 20 GHz\n");
    Socket->write("SENS1:FREQ:STAR 2 GHz\n");

    Socket->write("FORMAT:DATA REAL, 64\n");

    Socket->write("FORM:BORD SWAP\n");
    Socket->write("INIT:SCOP SING\n");
    */





    //socketVNA.QueryInt("*OPC?\n", OPC);


    /*
    Socket->write(QString("SENS:FREQ:STAR %1 GHz\n").arg(2));
    Socket->write(QString("SENS:FREQ:STOP %1 GHz\n").arg(4));
    Socket->write(QString("SENS:FREQ:STAR %1 GHz\n").arg(2));
    */



    //MeasureCurrentAspectInternal(params, CurrentAspectData);
    //MeasData.WriteSweepAt(MeasDataClass::MeasDataType::CurrentAspect, CurrentAspectData);
    /*
    for (int i=0; i< CurrentAspectData.size(); i++){
        qDebug() << CurrentAspectData[i].real() << " " << CurrentAspectData[i].imag();
    }
    */










