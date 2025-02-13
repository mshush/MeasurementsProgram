#include "tcpsocket.h"

TCPSocket::TCPSocket(QObject *parent) : QObject(parent)
{

}


TCPSocket::TCPSocket() : QObject(nullptr)
{

}
bool TCPSocket::ConnectToSocket(QString ip, int port)
{
    SocketConnectionPtr = new QTcpSocket(&eventLoop);
    SocketConnectionPtr->connectToHost(ip, port);
   //SocketConnection->connectToHost("192.168.0.84", 5025);
    bool connection;
    connection = SocketConnectionPtr->waitForConnected(5000) ;
    PowerOn = connection;
    if (PowerOn) {qDebug("connected");
       // connect((SocketConnection), &QTcpSocket::readyRead, this, &SocketVNA::checkForData);

    }
    return PowerOn;

}

void TCPSocket::DisconnectFromSocket()
{
    SocketConnectionPtr->disconnectFromHost();
    //SocketConnection->deleteLater();
}

bool TCPSocket::CheckConnectionState()
{
    bool b;
    if (SocketConnectionPtr->state() == QTcpSocket::ConnectedState) b = true;
    else b = false;
    return b;

}

int TCPSocket::WriteToSocket(QString query)
{

    QByteArray tmpByteArray = query.toLocal8Bit();
    //if (PowerOn)
    {
        int byteswritten;
        byteswritten = SocketConnectionPtr->write(tmpByteArray);
        SocketConnectionPtr->waitForBytesWritten(5000);
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

bool TCPSocket::ReadStringData(QString &answer)
{
    QByteArray tmpByteArray ;
    //bNoError = SocketStateOn();
    if (PowerOn) {
        bool read = SocketConnectionPtr->waitForReadyRead(5000);
        tmpByteArray = SocketConnectionPtr->readAll();
        answer = QString::fromLocal8Bit(tmpByteArray);
        return read;

    }
    else {
        AppendError(1);
    }
    return false;
}

bool TCPSocket::ReadStringData(QByteArray &answer)
{
    QByteArray tmpByteArray ;
   // bNoError = SocketStateOn();

    if (PowerOn) {
        if (SocketConnectionPtr->waitForReadyRead(5000)) {
        answer = SocketConnectionPtr->readAll();
            return true;
        }

    }
    else {
        AppendError(1);

    }
    return false;
}

void TCPSocket::QueryString(QString query, QString &answer)
{
    QByteArray tmpByteArray ;
    //bNoError = SocketStateOn();

    if (PowerOn) {
        WriteToSocket(query);
        SocketConnectionPtr->waitForReadyRead(50);

        tmpByteArray = SocketConnectionPtr->readAll();

        answer = QString::fromLocal8Bit(tmpByteArray);
        qDebug() << answer;
    }
    else {

        AppendError(1);
    }
}

void TCPSocket::QueryInt(QString query, int &num)
{
   // bool ReadModeChanged = false;
        QByteArray tmpByteArray ;
        //bNoError = SocketStateOn();

        if (PowerOn) {

       // if(CurrentReadMode == ReadMode::Asc)
            {
           // WriteToSocket("FORM:DATA REAL\n");
           // WriteToSocket("FORM:BORD SWAP\n");
            //ReadModeChanged = true;
        }

        WriteToSocket(query);
        SocketConnectionPtr->waitForReadyRead(5000);

        tmpByteArray = SocketConnectionPtr->readAll();

        num = QString::fromLocal8Bit(tmpByteArray).toInt();
        //if(ReadModeChanged) WriteToSocket("FORM:DATA ASC\n");
        //???
        }
        else {

            AppendError(1);
        }

}

void TCPSocket::QueryDouble(QString query, double &num)
{
        QByteArray tmpByteArray ;
        //bNoError = SocketStateOn();

        if (PowerOn) {
            WriteToSocket(query);
            SocketConnectionPtr->waitForReadyRead(50);

            tmpByteArray = SocketConnectionPtr->readAll();

            num = QString::fromLocal8Bit(tmpByteArray).toDouble();
            qDebug() << num;
        }
        else {

            AppendError(1);
        }
}

void TCPSocket::ReadFromSocket(QByteArray &byteArray)
{
    byteArray.append(SocketConnectionPtr->readAll());
    QApplication::processEvents();
}

void TCPSocket::ReadFromSocket(char *array, int maxbytes)
{
    SocketConnectionPtr->read(array, maxbytes);
    QApplication::processEvents();

}


/*
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
*/
QByteArray TCPSocket::ReadFromSocket(int maxbytes)
{
    SocketConnectionPtr->read(maxbytes);
    QApplication::processEvents();

}

QByteArray TCPSocket::ReadAllFromSocket()
{
    QByteArray tmp = SocketConnectionPtr->readAll();
    return tmp;
}

bool TCPSocket::IsSocketStateOn()
{
    if (SocketConnectionPtr->state() == QTcpSocket::ConnectedState) return true;
    return false;
}

int TCPSocket::CheckBytesAvailable()
{
    int bytes =  SocketConnectionPtr->bytesAvailable();
    QApplication::processEvents();
    return bytes;
}


