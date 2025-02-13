#include "socketvna.h"

SocketVNA::SocketVNA(QObject *parent) : QObject(parent)
{

}


SocketVNA::SocketVNA() : QObject(nullptr)
{

}
bool SocketVNA::ConnectToSocket(QString ip, int port)
{
    SocketConnection = new QTcpSocket(&eventLoop);
    SocketConnection->connectToHost(ip, port);
   //SocketConnection->connectToHost("192.168.0.84", 5025);
    bool connection;
    connection = SocketConnection->waitForConnected(5000) ;
    PowerOn = connection;
    if (PowerOn) {qDebug("connected");
       // connect((SocketConnection), &QTcpSocket::readyRead, this, &SocketVNA::checkForData);

    }
    return PowerOn;

}

void SocketVNA::DisconnectFromSocket()
{
    SocketConnection->disconnectFromHost();
    //SocketConnection->deleteLater();
}

int SocketVNA::WriteToSocket(QString query)
{

    QByteArray tmpByteArray = query.toLocal8Bit();
    //if (PowerOn)
    {
        int byteswritten;
        byteswritten = SocketConnection->write(tmpByteArray);
        SocketConnection->waitForBytesWritten(5000);
        //QApplication::processEvents();
        if (byteswritten == -1) {
            AppendError(5);
            return 0;
        }
        return byteswritten;

    }
    //else
    {
        AppendError(1);
    }
    return 0;
}

bool SocketVNA::ReadStringData(QString &answer)
{
    QByteArray tmpByteArray ;
    //bNoError = SocketStateOn();
    if (PowerOn) {
        bool read = SocketConnection->waitForReadyRead(5000);
        tmpByteArray = SocketConnection->readAll();
        answer = QString::fromLocal8Bit(tmpByteArray);
        return read;

    }
    else {
        AppendError(1);
    }
    return false;
}

bool SocketVNA::ReadStringData(QByteArray &answer)
{
    QByteArray tmpByteArray ;
   // bNoError = SocketStateOn();

    if (PowerOn) {
        if (SocketConnection->waitForReadyRead(5000)) {
        answer = SocketConnection->readAll();
            return true;
        }

    }
    else {
        AppendError(1);

    }
    return false;
}

void SocketVNA::QueryString(QString query, QString &answer)
{
    QByteArray tmpByteArray ;
    //bNoError = SocketStateOn();

    if (PowerOn) {
        WriteToSocket(query);
        SocketConnection->waitForReadyRead(50);

        tmpByteArray = SocketConnection->readAll();

        answer = QString::fromLocal8Bit(tmpByteArray);
        qDebug() << answer;
    }
    else {

        AppendError(1);
    }
}

void SocketVNA::QueryInt(QString query, int &num)
{

        QByteArray tmpByteArray ;
        //bNoError = SocketStateOn();

        if (PowerOn) {
            WriteToSocket(query);
            SocketConnection->waitForReadyRead(5000);

            tmpByteArray = SocketConnection->readAll();

            num = QString::fromLocal8Bit(tmpByteArray).toInt();
        }
        else {

            AppendError(1);
        }

}
void SocketVNA::write(QString mess)
{
        QByteArray arr = mess.toLocal8Bit();
        socket.write(arr);
        socket.waitForBytesWritten(5000);
}
void SocketVNA::ReadFromSocket(QByteArray &byteArray)
{
    byteArray.append(SocketConnection->readAll());
    QApplication::processEvents();
}

void SocketVNA::ReadFromSocket(char *array, int maxbytes)
{
    SocketConnection->read(array, maxbytes);
    QApplication::processEvents();

}

bool SocketVNA::DebugConnect()
{
    socket.connectToHost("192.168.0.83", 5025);
    bool b = socket.waitForConnected(5000);
    if(b) return true;
    return false;
}

bool SocketVNA::DebugParams()
{
    QString sttring;


    write("SYST:PRES\n");



    sttring = "SENS:FREQ:STAR 1 GHz\n";
    write(QString("SENS:FREQ:STAR %1 GHz\n").arg(2));


    sttring = "SENS:FREQ:STOP 20 GHz\n";

    write(QString("SENS:FREQ:STOP %1 GHz\n").arg(20));

    //write("SENS:SWE:POIN 1601\n");

    write(QString("SENS:SWE:POIN %1\n").arg(1601));

    //write("CALC:PAR1:DEF S21\n");
    write(QString("CALC:PAR1:DEF %1\n").arg("S21"));

    write("CALC:PAR1:SEL\n");

    write("CALC:FORM MLOG\n");


    write("FORM:BORD SWAP\n");

    write("FORM:DATA REAL\n");
    //
    //write("TRIG:SOUR BUS\n");
    write("*OPC?\n");
    socket.waitForReadyRead(5000);
    QByteArray s = socket.readAll();
    QString ss = QString::fromLocal8Bit(s);
    int i = ss.toInt();
    if (i == 1){

            qDebug("params set");
            return true;
    }
    return false;

}

void SocketVNA::Debug()
{

    bool b = DebugParams();
    if (!b) return;
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


    write("INIT\n");
    write(":TRIG:SING\n");
    write("CALC:DATA:SDAT?\n");

    QByteArray vals;

    while (true)
    {

            bytesAvail = socket.bytesAvailable();
            QApplication::processEvents();

            if (bytesAvail > 0){
            QApplication::processEvents();

            //settext_("size:" + QString::number(bytesAvail));

            datatemp.append(socket.readAll());
            values_ = QString::fromUtf8(datatemp);
            //settext_(values_);


            AllBytes += bytesAvail;

            if (AllBytes == bytesAvail)
            {
                values_ = QString::fromUtf8(datatemp.mid(0,10));
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
                data.append(datatemp);
                break;
            }
            }
    }
    //data.squeeze();
    //settext_("size after squeeze:" + QString::number(data.size()));

    double dest[3202];
    double db[1601];
    //qDebug("size");

    int doublesize = sizeof(double);
    int BytesRead;
    int PointsRead;
    double doubleValue;
    {

            for (int i = 0; i < 2*1601; i++)
            {
            //memcpy(&doubleValue, BinaryDataArr.data() +i*doublesize, doublesize);
            memcpy(dest + i, data.constData()  + skipbytes+ i*doublesize, doublesize);
            DebugStr.append(QString::number(dest[i]));
            //dest[i] = doubleValue;
            }
    }

    for (int i =0; i< N*2; i++){

    }


}

QByteArray SocketVNA::ReadFromSocket(int maxbytes)
{
    SocketConnection->read(maxbytes);
    QApplication::processEvents();

}

QByteArray SocketVNA::ReadAllFromSocket()
{
    QByteArray tmp = SocketConnection->readAll();
    return tmp;
}

bool SocketVNA::SocketStateOn()
{
    if (SocketConnection->state() == QTcpSocket::ConnectedState) return true;
    return false;
}

int SocketVNA::CheckBytesAvailable()
{
    int bytes =  SocketConnection->bytesAvailable();
    QApplication::processEvents();
    return bytes;
}

void SocketVNA::checkForData()
{
    if (SocketConnection->bytesAvailable() > 0) {
            QByteArray data = SocketConnection->readAll();
            BinaryDataArr.append(data);
    }
}

