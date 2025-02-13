#ifndef SOCKETVNA_H
#define SOCKETVNA_H

#include <QTcpSocket>
#include <QObject>
#include <QHostAddress>
#include <QApplication>
#include "common.h"
#include "errorhandler.h"

class SocketVNA : public QObject
{
    Q_OBJECT
public:
    SocketVNA(QObject *parent);
    SocketVNA();
    QTcpSocket socket;

    bool PowerOn;
    bool ConnectToSocket(QString ip, int port);
    void DisconnectFromSocket();

    int WriteToSocket(QString query);
    bool ReadStringData(QString& answer);
    bool ReadStringData(QByteArray& answer);

    void QueryString(QString query, QString& answer);
    void QueryInt(QString query, int& num);

    void ReadFromSocket(QByteArray& byteArray);
    void ReadFromSocket(char* array, int maxbytes);


    bool DebugConnect();
    bool DebugParams();
    void Debug();
    double debug[3202];
    double dv;
    QByteArray ReadFromSocket(int maxbytes);
    QByteArray ReadAllFromSocket();
    void write(QString mess);
    bool SocketStateOn();
    int CheckBytesAvailable();
    QTcpSocket* SocketConnection;
    QEventLoop eventLoop;
    QString ip;
    int port;
    QHostAddress ipAdress;
    QByteArray internalarr;
public slots:
    void checkForData();


};

#endif // SOCKETVNA_H
