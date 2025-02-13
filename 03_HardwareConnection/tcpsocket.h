#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QTcpSocket>
#include <QObject>
#include <QHostAddress>
#include <QApplication>
#include "common.h"
#include "errorhandler.h"

class TCPSocket : public QObject
{
    Q_OBJECT
public:
    TCPSocket(QObject *parent);
    TCPSocket();


    bool PowerOn;
    bool ConnectToSocket(QString ip, int port);
    void DisconnectFromSocket();
    bool CheckConnectionState();


    int WriteToSocket(QString query);
    bool ReadStringData(QString& answer);
    bool ReadStringData(QByteArray& answer);

    void QueryString(QString query, QString& answer);
    void QueryInt(QString query, int& num);
    void QueryDouble(QString query, double& num);

    void ReadFromSocket(QByteArray& byteArray);
    void ReadFromSocket(char* array, int maxbytes);

    QByteArray ReadFromSocket(int maxbytes);
    QByteArray ReadAllFromSocket();

    bool IsSocketStateOn();
    int CheckBytesAvailable();
    QTcpSocket* SocketConnectionPtr;
    QEventLoop eventLoop;
    QString ip;
    int port;
    QHostAddress ipAdress;
    QByteArray internalarr;

};

#endif // TCPSOCKET_H
