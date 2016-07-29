#ifndef SERVER_H
#define SERVER_H

#include <QMap>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>


class Server : public QObject
{
    Q_OBJECT
    QTcpServer *server;
    QTcpSocket *socket;
    QList <QTcpSocket*> Clients;


public:
    Server(QObject *parent = 0);
    void SendMsg (QByteArray str);

signals:

public slots:
    void NewClient ();
    void ReadyRead ();
    void ClientDisconnect ();
};

#endif // SERVER_H
