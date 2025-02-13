#include "../03_HardwareConnection/vna.h"
#include "common.h"


QByteArray GenerateRandomData(int N) { // for sweep measurement simulation
    DoubleVector doubleArray;
    //doubleArray.reserve(N);
    //std::random_device rd;
    //std::mt19937 gen(rd());
    //std::uniform_real_distribution<> dis(0.1, 1.0);
    for (int i = 0; i < N*2; ++i) {
        //double randomValue = dis(gen);
        double randomValue =  1 + 10*std::rand()/ RAND_MAX;
        //double randomValue  = SweepsAvailableGlobal ;
        doubleArray.append(randomValue);
    }
    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream.setFloatingPointPrecision(QDataStream::DoublePrecision);
    stream.setByteOrder(QDataStream::LittleEndian);


    for (const auto& value : doubleArray) {
        stream << value;
    }

    return byteArray;
}

VNA::~VNA()
{

}

VNA::VNA(QObject *parent)
    : QObject{parent}
{

}

void VNA::SimulateTriggerOPU(OPU* opu){

    connect(opu, OPU::SimulateTrigger, &TrigSimLoop ,&QEventLoop::quit);
}


QString VNA::IDN()
{
    QString answer;
    QByteArray IDN;
    IDN = QString("*IDN?\n").toLocal8Bit();
    socketVNA.QueryString(IDN, answer);
    return answer;
}
/*
void VNA::Debug()
{

// for zva
    QByteArray data;
    QByteArray ByteDataArray;
    int N = 1601;
    QByteArray datatemp;
    int bytesAvail = 0;

    int AllBytes = 0;
    int ExpectedBytes = 2*N*sizeof(double);
    int skipbytes = 0;
    QString values_ = "";
    int AllExpectedBytes = 0;

    WriteToSocket("*RST\n");

    WriteToSocket("INIT:CONT OFF\n");

    WriteToSocket("SENS1:SWE:POIN 1601\n");


    WriteToSocket("CALC1:PAR:DEF S11\n");


    WriteToSocket ("SENS1:FREQ:STAR 2 GHz\n");

    WriteToSocket("SENS1:FREQ:STOP 20 GHz\n");
    WriteToSocket ("SENS1:FREQ:STAR 2 GHz\n");

    WriteToSocket("FORMAT:DATA REAL, 64\n");

    WriteToSocket("FORM:BORD SWAP\n");
    WriteToSocket("INIT:SCOP SING\n");

    // for (int i =0 ; i < N; i++) {


    {
        WriteToSocket("INIT:IMM; *WAI\n");

        WriteToSocket("CALC1:DATA? SDAT\n");
        //socketVNA.SocketConnection->waitForReadyRead();
        //BinaryDataArr =   socketVNA.SocketConnection->readAll();
        //socket.waitForReadyRead(5000);
        //bytesAvail = socket.bytesAvailable();
        //settext_("byteavail:" + QString::number(bytesAvail));

        //QApplication::processEvents();

        // data = socket.readAll();
    }

    /*bytesAvail = socket.bytesAvailable();
    settext_("bytesavail;" + QString::number(bytesAvail));


    data = (socket.readAll());

    AllBytes += bytesAvail;


    if (AllBytes == bytesAvail)
    {
        values_ = QString::fromUtf8(data);
        skipbytes =  values_.mid(1,1).toInt() + 2;
        QString bytesReady;
        for (int i = 0; i < values_.mid(1,1).toInt(); i++){

            bytesReady.append(values_[i + 2]);

        }
        int bytesReadyInt = bytesReady.toInt();

        settext_("byteready:" + QString::number(bytesReadyInt));
        qDebug("byteready");
        QApplication::processEvents();
        AllExpectedBytes = bytesReadyInt + skipbytes + 1;
        settext_("skip bytes:" + QString::number(skipbytes));

        settext_("all expected bytes:" + QString::number(AllExpectedBytes));

        \
    }

    settext_(QString::fromUtf8(data));
    if (datatemp.size() == AllExpectedBytes) {
        ByteDataArray.append(data);
    }


    settext_("size:" + QString::number(ByteDataArray.size()));
    qDebug("size");

    QApplication::processEvents();


   while (true)
    {
        //socket.waitForReadyRead(1);
        //bytesAvail = socket.bytesAvailable();
        //bytesAvail = bytes;
        //socket.waitForReadyRead(5000);
        QApplication::processEvents();
        bytesAvail =  socketVNA.CheckBytesAvailable();//bytesAvailable();
        //settext_("byteavail:" + QString::number(bytesAvail));
        //hello(bytesAvail);
        //QCoreApplication::
        //QCoreApplication::processEvents();

        if (bytesAvail > 0){
            //settext_("byteavail:" + QString::number(bytesAvail));
            //QApplication::processEvents();
            //datatemp.append( socketVNA.SocketConnection->readAll() );
            datatemp.append( socketVNA.ReadAllFromSocket());

            QApplication::processEvents();

            AllBytes += bytesAvail;

            if (AllBytes == bytesAvail)
            {
                values_ = QString::fromUtf8(datatemp);
                skipbytes =  values_.mid(1,1).toInt() + 2;
                //settext_("skip bytes:" + QString::number(skipbytes));
                QString bytesReady;
                for (int i = 0; i < values_.mid(1,1).toInt(); i++){

                    bytesReady.append(values_[i + 2]);

                }
                int bytesReadyInt = bytesReady.toInt();

                //settext_(QString::number(bytesReadyInt));
                AllExpectedBytes = bytesReadyInt + skipbytes + 1;
                //settext_("all expected bytes:" + QString::number(AllExpectedBytes));


            }

            //settext_("size bytes:" + QString::number(datatemp.size()));

            if (datatemp.size() == AllExpectedBytes) {
                data.append(datatemp);
                BinaryDataArr.append(data);
                break;
            }
        }
    }


    int doublesize = sizeof(double);
    double* db = new double[N*2];

    for (int i = 0; i < N*2; i++)
    {
        double doubleValue;
        memcpy(&doubleValue, data.constData() + skipbytes +i*doublesize, doublesize);
        db[i] = doubleValue;
    }



}


*/


bool VNA::ConnectToSocket(QString ip, int port)
{
    bool b = socketVNA.ConnectToSocket(ip, port); // planar
    if (!b) {
        AppendError(2);
    }
    return b;
}

void VNA::MeasureSingleSweep()
{
   // for planar


    // for zva

   // if(!ExternalTrigger) WriteToSocket("INIT:IMM; *WAI\n");
  //  WriteToSocket("CALC1:DATA? SDAT\n");


    //int ExpectedBytes = 2*NumOfPoi*sizeof(double);

 /*   QByteArray data;
    QByteArray ByteDataArray;
    int N = 1601;
    QByteArray datatemp;
    int bytesAvail = 0;

    int AllBytes = 0;
    int ExpectedBytes = 2*N*sizeof(double);
    int skipbytes = 0;
    QString values_ = "";
    int AllExpectedBytes = 0;

    if(!ExternalTrigger) {
        WriteToSocket("INIT; *WAI\n");
        //WriteToSocket(":TRIG:SING\n");
       }
    WriteToSocket("CALC:DATA:SDAT?\n");

    while (true)
    {

        bytesAvail = socketVNA.CheckBytesAvailable();
        QApplication::processEvents();

        if (bytesAvail > 0){
            QApplication::processEvents();

            //settext_("size:" + QString::number(bytesAvail));

            datatemp.append(socketVNA.ReadAllFromSocket());
            DebugStr.append(QString::number(datatemp.size()) + "\n\n\n");
            //DebugStr.append(datatemp);
            AllBytes += bytesAvail;

            /*if (AllBytes == bytesAvail)
            {
                values_ = QString::fromUtf8(datatemp.mid(0,11));
                skipbytes_ =  values_.mid(1,1).toInt() + 2;

                QString bytesReady;
                for (int i = 0; i < values_.mid(1,1).toInt(); i++){

                    bytesReady.append(values_[i + 2]);

                }
                int bytesReadyInt = bytesReady.toInt();

                AllExpectedBytes = bytesReadyInt + skipbytes_ + 1;


            }


            if (datatemp.size() == AllExpectedBytes) {
                BinaryDataArr.append(datatemp);

                DebugStr.append(QString::number(skipbytes_));
                SweepsAvailiable++;
                SweepsAvailableGlobal++;
                break;
            }
        }
    }
*/
    /*
    while (true)
    {

     bytesAvail = socketVNA.SocketConnection->bytesAvailable();
     QApplication::processEvents();

     if (bytesAvail > 0){

            datatemp.append(socketVNA.SocketConnection->readAll());
            QApplication::processEvents();

            AllBytes += bytesAvail;

            if (AllBytes == bytesAvail)
            {
                values_ = QString::fromUtf8(datatemp);
                skipbytes =  values_.mid(1,1).toInt() + 2;
                skipbytes = skipbytes;
                QString bytesReady;
                for (int i = 0; i < values_.mid(1,1).toInt(); i++){

                    bytesReady.append(values_[i + 2]);

                }
                int bytesReadyInt = bytesReady.toInt();

                AllExpectedBytes = bytesReadyInt + skipbytes + 1;


            }


            if (datatemp.size() == AllExpectedBytes) {
                BinaryDataArr.append(datatemp);
                SweepsAvailiable++;
                SweepsAvailableGlobal++;
                break;
            }
     }
    }*/
/*
    while (true)
    {

        bytesAvail = socketVNA.CheckBytesAvailable();

        if (bytesAvail > 0){
            datatemp.append(socketVNA.ReadAllFromSocket() );

            AllBytes += bytesAvail;

            if (AllBytes == bytesAvail)
            {
                data = datatemp.chopped(10);
                values_ = QString::fromUtf8(data);
                skipbytes_ =  values_.mid(1,1).toInt() + 2;
                skipbytes = skipbytes_;
                  QString bytesReady;
                for (int i = 0; i < values_.mid(1,1).toInt(); i++){

                    bytesReady.append(values_[i + 2]);

                }
                int bytesReadyInt = bytesReady.toInt();

                AllExpectedBytes = bytesReadyInt + skipbytes + 1;


            }


            if (datatemp.size() == AllExpectedBytes) {
                BinaryDataArr.append(datatemp);
                SweepsAvailiable++;
                SweepsAvailableGlobal++;
                break;
            }
        }
    }
*/
    //_sleep(1000);
    auto start = std::chrono::high_resolution_clock::now();

    QByteArray data;
    QByteArray ByteDataArray;
    int N = 1601;
    QByteArray datatemp;
    int bytesAvail = 0;

    int AllBytes = 0;
    int ExpectedBytes = 2*N*sizeof(double);
    int skipbytes = 0;
    QString values_ = "";
    int AllExpectedBytes = 2*N*sizeof(double) + skipbytes_ + 1;

    if(!ExternalTrigger) {
        qDebug() << "int trig";

        WriteToSocket("INIT\n");
        WriteToSocket("*TRG\n");
        WriteToSocket("TRIG:WAIT ENDM\n");

        //WriteToSocket(":TRIG:SING\n");
    }
    else WriteToSocket("TRIG:WAIT ENDM\n");

    WriteToSocket("CALC:DATA:SDAT?\n");
    int bytes =   AllExpectedBytes + bytesRead;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    qDebug() << "commands time: " << duration << "ms" ;

    /*while (true)
    {

        QApplication::processEvents();
        if (BinaryDataArr.size()  == bytes) {

            SweepsAvailiable++;
            SweepsAvailableGlobal++;
            break;
        }

    }*/

    bool measbegin = false;
    while (true)
    {
         bytesAvail = socketVNA.CheckBytesAvailable();

        if (bytesAvail > 0){
            if (!measbegin) auto start = std::chrono::high_resolution_clock::now();
            measbegin = true;

            qDebug() << "bytes avail";
            datatemp.append(socketVNA.ReadAllFromSocket() );

            AllBytes += bytesAvail;

            if (AllBytes == bytesAvail)
            {
                skipbytes_ = 10;
                AllExpectedBytes = 2*NumOfPoi*sizeof(double) + 1 + skipbytes_;
            }

            if (datatemp.size() == AllExpectedBytes) {
                qDebug() << "datatempsize: " << datatemp.size();// << duration << "ms" ;

                datatemp.trimmed();
                datatemp.remove(0,10);
                tempArray.append(datatemp);
                qDebug() << "temarraysize: " << tempArray.size();// << duration << "ms" ;

                SweepsAvailiable++;
                //SweepsAvailableGlobal++;
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                qDebug() << "measuring time: " << duration << "ms" ;
                break;
            }
        }
    }


}

void VNA::MeasureTestSingleSweep()
{
     TrigSimLoop.exec(); // simulation of OPU trigger wait
    // enters infinite loop until signal from OPU is emited
     tempArray.append( GenerateRandomData(1601) );
    SweepsAvailiable++;
    //SweepsAvailableGlobal++;

/*
    QByteArray data;
    QByteArray ByteDataArray;
    int N = 1601;
    QByteArray datatemp;
    int bytesAvail = 0;

    int AllBytes = 0;
    int ExpectedBytes = 2*N*sizeof(double);
    int skipbytes = 0;
    QString values_ = "";
    int AllExpectedBytes = 0;
    QString sttring;

    WriteToSocket("INIT\n");
    WriteToSocket(":TRIG:SING\n");
    WriteToSocket("CALC:DATA:SDAT?\n");

    while (true)
    {

     bytesAvail = socketVNA.SocketConnection->bytesAvailable();
     QApplication::processEvents();

     if (bytesAvail > 0){

            datatemp.append(socketVNA.SocketConnection->readAll());
            QApplication::processEvents();

            AllBytes += bytesAvail;

            if (AllBytes == bytesAvail)
            {
                values_ = QString::fromUtf8(datatemp);
                skipbytes_ =  values_.mid(1,1).toInt() + 2;

                QString bytesReady;
                for (int i = 0; i < values_.mid(1,1).toInt(); i++){

                    bytesReady.append(values_[i + 2]);

                }
                int bytesReadyInt = bytesReady.toInt();

                AllExpectedBytes = bytesReadyInt + skipbytes_ + 1;


            }


            if (datatemp.size() == AllExpectedBytes) {
                BinaryDataArr.append(datatemp);

                SweepsAvailiable++;
                SweepsAvailableGlobal++;
                break;
            }
     }
    }*/
}




bool VNA::SetAllParameters(bool ExtTrigOn, QString StartFreq, QString StopFreq, QString Pow, int NumOfPoints, QString MeasParameter, QString type, int IF)
{
// add num of sweeps;

  // for planar
    bool b = true;
    QString sttring;

      WriteToSocket("SYST:PRES\n");


      WriteToSocket("CALC:PAR1:SEL\n");

      WriteToSocket("CALC:FORM MLOG\n");


    sttring = "SENS:FREQ:STAR 1 GHz\n";
    //WriteToSocket(QString("SENS:FREQ:STAR %1 GHz\n").arg(StartFreq));

    WriteToSocket("SENS:FREQ:STAR 1 GHz\n");

    sttring = "SENS:FREQ:STOP 20 GHz\n";

   // WriteToSocket(QString("SENS:FREQ:STOP %1 GHz\n").arg(StopFreq));
    WriteToSocket(("SENS:FREQ:STOP 20 GHz\n"));


    WriteToSocket("SENS:SWE:POIN 1601\n");

   // WriteToSocket(QString("SENS:SWE:POIN %1\n").arg(NumOfPoints));
   // if (b) b = SetNumOfPoi(NumOfPoints);

    //writeToSocket("CALC:PAR1:DEF S21\n");


    WriteToSocket(("CALC:PAR1:DEF S43\n"));

    //if (b) b = SetMeasParameter(MeasParameter);

    WriteToSocket(("SOUR:POW 0\n"));

    //if (b) b = SetPow(Pow);
    WriteToSocket("FORM:DATA REAL\n");

    WriteToSocket("FORM:BORD SWAP\n");


   // if (b) b = SetTriggerMode(ExtTrigOn);
   // if (b) b = SetTriggerMode(false);







    ExternalTrigger = ExtTrigOn;
    if (ExternalTrigger) {b = WriteToSocket(":TRIG:SOUR EXT\n");     StateOfParams.ExternalTrigger = true;}
    else{
        qDebug() << "int trig";
        b = WriteToSocket(":TRIG:SOUR BUS\n");
        b = WriteToSocket("INIT:CONT OFF\n");
    }
   //  ExternalTrigger = false;

    int OPCQ = 1;
    NumOfPoi = NumOfPoints;

   // socketVNA.QueryInt("*OPC?\n", OPCQ);


    if (OPCQ == 1) b = true;
    else b = false;


    return b;
/*



  //  WriteToSocket("SYST:PRES\n");
    ResetVNA();

/*


    if (b) b = SetBinaryReadMode();

    if (b) b = SetStartStopFreq(StartFreq, StopFreq);

    if (b) b = SetNumOfPoi(NumOfPoints);


    if (b) b = SetMeasParameter(MeasParameter);


    if (b) b = SetPow(Pow);

    if (b) b = SetTriggerMode(false);


    WriteToSocket("CALC:PAR:SEL\n");

    WriteToSocket("CALC:FORM MLOG\n");


  //  WriteToSocket("TRIG:SOUR INT\n");
  //  WriteToSocket("INIT:CONT OFF\n");

    ExternalTrigger = false;
    int OPC_ = true;
    NumOfPoi = NumOfPoints;
  /*  int OPC_;
    socketVNA.QueryInt("*OPC?\n", OPC_);


    if (OPC_ == 1) return true;
    return false;

    b = OPC();

    return b;*/

    // for zva
   /* WriteToSocket("*RST\n");

    WriteToSocket("INIT:CONT OFF\n");

    WriteToSocket("SENS1:SWE:POIN 1601\n");


    WriteToSocket("CALC1:PAR:DEF S11\n");


    WriteToSocket ("SENS1:FREQ:STAR 2 GHz\n");

    WriteToSocket("SENS1:FREQ:STOP 20 GHz\n");
    WriteToSocket ("SENS1:FREQ:STAR 2 GHz\n");

    WriteToSocket("FORMAT:DATA REAL, 64\n");

    WriteToSocket("FORM:BORD SWAP\n");
    WriteToSocket("INIT:SCOP SING\n");

    socketVNA.QueryInt("*OPC?\n", OPC);
*/


}

bool VNA::SetStartStopFreq(QString StartFreq, QString StopFreq)
{
    bool b;
    b = WriteToSocket(QString("SENS:FREQ:STAR %1 GHz\n").arg(StartFreq));

    b = WriteToSocket(QString("SENS:FREQ:STOP %1 GHz\n").arg(StopFreq));

    b = WriteToSocket(QString("SENS:FREQ:STAR %1 GHz\n").arg(StartFreq));

    StateOfParams.FStart = StartFreq;
    StateOfParams.FStop = StopFreq;

    b = OPC();
    return b;

}

bool VNA::SetPow(QString Pow)
{
    WriteToSocket(QString("SOUR:POW %1\n").arg(Pow));
    StateOfParams.PowerDbm = Pow;
    bool b = OPC();
    return b;

}

bool VNA::SetNumOfPoi(int NumOfPoin)
{
    bool b;

    b = WriteToSocket(QString("SENS:SWE:POIN %1\n").arg(NumOfPoin));
    b = OPC();
    StateOfParams.NumOfPoint = NumOfPoin;
    return b;

}

bool VNA::SetMeasParameter(QString Par)
{
    bool b;
    b = WriteToSocket(QString("CALC:PAR1:DEF %1\n").arg(Par));
    b = OPC();
    StateOfParams.MeasParameter = Par;
    return b;
}

bool VNA::SetIF(int IF)
{
    bool b;

    b = WriteToSocket(QString("SENS:BAND %1\n").arg(IF));
    b = OPC();
    StateOfParams.IF = IF;
    return b;
}


bool VNA::SetReadMode(ReadMode ReadMod)
{
     if(ReadMod == ReadMode::ASC) WriteToSocket("FORM:DATA ASC\n");
     else if (ReadMod == ReadMode::REAL32) WriteToSocket("FORM:DATA REAL32\n");
     else if (ReadMod == ReadMode::REAL) WriteToSocket("FORM:DATA REAL\n");

}

bool VNA::OPC()
{
    int OPC_ = 0;
    if (StateOfParams.CurrentReadMode == ReadMode::ASC)
    {
        //SetBinaryReadMode(true);
        SetReadMode(ReadMode::REAL);
        socketVNA.QueryInt("*OPC?\n", OPC_);
        SetReadMode(ReadMode::ASC);
    }
    else socketVNA.QueryInt("*OPC?\n", OPC_);

    if (OPC_ == 1) return true;
    return false;

}

bool VNA::Preset()
{
    WriteToSocket("*RST\n");

}

bool VNA::SetTriggerMode(bool ExtTrigger)
{
    bool b;
    if(ExtTrigger) { b = WriteToSocket(":TRIG:SOUR EXT\n");     StateOfParams.ExternalTrigger = true;}
    else {b = WriteToSocket(":TRIG:SOUR INT\n");     StateOfParams.ExternalTrigger = false;}
    WriteToSocket("INIT:CONT OFF\n");

    //b = OPC();
    return b;

}
/*
bool VNA::SetFIFOStateOn()
{
    bool b;
    b = WriteToSocket("SYST:FIFO:STAT ON\n");
    return b;
}

bool VNA::SetFIFOCapacity(int cap)
{
    bool b;
    b = WriteToSocket("FORM:DATA ASC\n");

    b = WriteToSocket(("SYS:FIFO:SWE:CAP 100\N"));
    return b;
}

int VNA::GetFIFONumOfSweeps()
{
    QByteArray numarray;
    QString num;

   // qDebug() << "numofsweeps";
    socketVNA.WriteToSocket("SYST:FIFO:SWE:COUN?\n");
    numarray = socketVNA.ReadAllFromSocket();
    num = QString::fromLocal8Bit(numarray);
    DebugStr.append(num);
    //numarray = socketVNA.ReadFromSocket(4);
    //numarray = socketVNA.ReadAllFromSocket();

    return num.toInt();
}

void VNA::GetFIFOSingleSweep()
{



        while (true)
        {
        bytesAvail = socketVNA.CheckBytesAvailable();

        if (bytesAvail > 0){

            qDebug() << "bytes avail";
            datatemp.append(socketVNA.ReadAllFromSocket() );

            AllBytes += bytesAvail;

            if (AllBytes == bytesAvail)
            {
                skipbytes_ = 10;
                AllExpectedBytes = 2*NumOfPoi*sizeof(double) + 1 + skipbytes_;
            }

            if (datatemp.size() == AllExpectedBytes) {
                qDebug() << "datatempsize: " << datatemp.size();// << duration << "ms" ;

                datatemp.trimmed();
                datatemp.remove(0,10);
                tempArray.append(datatemp);
                qDebug() << "temarraysize: " << tempArray.size();// << duration << "ms" ;

                SweepsAvailiable++;
                SweepsAvailableGlobal++;
                break;
            }
        }
        }



}


void VNA::ReadFIFOSingleSweep(double* dest)
{
        double temp;
    int BytesRead;
    int PointsRead;
    {
        //std::lock_guard<std::mutex> lock(MeasMutex);

        if (SweepsAvailiable > SweepsRead)
        {
            bytesRead = SweepsRead*2*NumOfPoi*sizeof(double);
            PointsRead = SweepsRead*2*NumOfPoi;
            for (int i = 0; i < 2*NumOfPoi; i++) {
                memcpy(&temp, tempArray.constData() + bytesRead + i*sizeof(double), sizeof(double));
                dest[PointsRead + i] = temp;
                DebugStr.append(QString::number(temp));

            }

            SweepsRead++;
            SweepsReadGlobal++;
        }

        QApplication::processEvents();

    }
}
*/
void VNA::ResetVNA()
{
    WriteToSocket("SYST:PRES\n");
}

void VNA::ReadSingleSweep(double* dest)
{
/*

    for planar
   *  double temp;
    int BytesRead;
    int PointsRead;
    {
        //std::lock_guard<std::mutex> lock(MeasMutex);

        if (SweepsAvailiable > SweepsRead)
        {
            BytesRead = SweepsRead*2*NumOfPoi*sizeof(double);
            PointsRead = SweepsRead*2*NumOfPoi;
            for (int i = 0; i < 2*NumOfPoi; i++) {
                memcpy(&temp, BinaryDataArr.constData() + BytesRead + i*sizeof(double), sizeof(double));
                dest[PointsRead + i] = temp;
            }
            SweepsRead++;

        }

        QApplication::processEvents();

    }*/
    //for zva
 /*   int doublesize = sizeof(double);
    int BytesRead;
    int PointsRead;
     double doubleValue;
    {
        if (SweepsAvailiable > SweepsRead) {

            BytesRead = SweepsRead*2*NumOfPoi*doublesize;
            PointsRead = SweepsRead*2*NumOfPoi;
            {
            for (int i = 0; i < 2*NumOfPoi; i++)
                {
                    //memcpy(&doubleValue, BinaryDataArr.data() +i*doublesize, doublesize);
                    memcpy(&doubleValue, BinaryDataArr.constData()  + BytesRead + skipbytes_+ i*doublesize, doublesize);
                    dest[i+PointsRead] = doubleValue;
                }

                SweepsReadGlobal++;
                SweepsRead++;
            }
        }
    }*/ // old version



    //qDebug("size");

   /* int doublesize = sizeof(double);
    int BytesRead;
    int PointsRead;
    double doubleValue;
    qDebug("reads");
    DebugStr.append(QString::number(skipbytes_));
    if (SweepsAvailiable > SweepsRead)
    {
        qDebug("reading");
        for (int i = 0; i < 2*NumOfPoi; i++)
        {
            BytesRead = SweepsRead*2*NumOfPoi*doublesize;
            PointsRead = SweepsRead*2*NumOfPoi;
            //memcpy(&doubleValue, BinaryDataArr.data() +i*doublesize, doublesize);
            memcpy(&doubleValue, BinaryDataArr.constData()  + skipbytes_ + BytesRead + i*doublesize, doublesize);
            DebugStr.append(QString::number(doubleValue));

            dest[i] = doubleValue;

        }
        qDebug("sweeps arrived");

        SweepsReadGlobal++;
        SweepsRead++;
    }*/
    auto start = std::chrono::high_resolution_clock::now();


     double db[1601];
    //qDebug("size");

     int doublesize = sizeof(double);
     int BytesRead;
     int PointsRead;
     double doubleValue;
     if (SweepsAvailiable > SweepsRead)
     {
       // qDebug("if");
        PointsRead = SweepsRead*2*NumOfPoi;

        qDebug() << "array size: " << tempArray.size();
       qDebug() << "array expected: " << NumOfPoi*2*SweepsAvailiable*8;

       qDebug() << "bytesread:" << bytesRead;


        for (int i = 0; i < 2*NumOfPoi; i++)

        {
            //qDebug("iff");

            //memcpy(&doubleValue, tempArray.constData(), 8);


            //memcpy(&doubleValue, BinaryDataArr.data() +i*doublesize, doublesize);
            memcpy(&doubleValue, tempArray.constData()  + bytesRead +  i*doublesize, doublesize);
           // qDebug() << doubleValue;

            dest[i+PointsRead] = doubleValue;
            DebugStr.append(QString::number(doubleValue));
            //qDebug("to dest");


        }
        bytesRead =  tempArray.size();
        //SweepsReadGlobal++;
        SweepsRead++;
     }

     auto end = std::chrono::high_resolution_clock::now();
     auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
     qDebug() << "read time: " << duration << "ms";


}

void VNA::ReadSingleSweep(double* destRe, double* destIm)
{


     auto start = std::chrono::high_resolution_clock::now();

     int doublesize = sizeof(double);
     double doubleValue;
     qDebug() << SweepsAvailiable;
     qDebug() << SweepsRead;

     if (SweepsAvailiable > SweepsRead)
     {
        qDebug() << NumOfPoi;

        for (int i = 0; i < 2*NumOfPoi; i++)
        {
            memcpy(&doubleValue, tempArray.constData()  + bytesRead +  i*doublesize, doublesize);
            if(i%2 == 0) destRe[(int)(i/2)] = doubleValue;
            else destIm[(int)((i-1)/2)] = doubleValue;

            //DebugStr.append(QString::number(doubleValue));
        }
        bytesRead =  tempArray.size();
        //SweepsReadGlobal++;
        SweepsRead++;
     }

     auto end = std::chrono::high_resolution_clock::now();
     auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
     qDebug() << "read time: " << duration << "ms";


}

bool VNA::WriteToSocket(QString str)
{
   return socketVNA.WriteToSocket(str);
}

void VNA::DisconnectFromSocket()
{
    socketVNA.DisconnectFromSocket();
}



QByteArray VNA::ReadStringData()
{
    QString answer;
    QByteArray data ;
    //QApplication::processEvents();
    //data = SocketPtr->readAll();
    socketVNA.ReadStringData(data);
    return data;
    //reportError("Error while reading data");
    //return NULL;
}

