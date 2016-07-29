#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{

    server = new QTcpServer (this);

    if (!server->listen(QHostAddress::Any, 27012))
        {
            qDebug () << "[!]: Server couldn`t start. Error: "+ server->errorString();
        }
    else
        {
            qDebug () << "[!]: Server has been started. Listenig port: 27012";
        }
    connect(server,SIGNAL(newConnection()),this,SLOT(NewClient()));
}


void Server::NewClient()
{
    socket = server->nextPendingConnection();

    Clients.append(socket);

    connect(socket,SIGNAL(readyRead()),this,SLOT(ReadyRead()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(ClientDisconnect()));

//    connect(Clients[userID],SIGNAL(readyRead()),this,SLOT(ReadyRead()));
//    connect(Clients[userID],SIGNAL(disconnected()),this,SLOT(ClientDisconnect()));
}

void Server::ReadyRead()
{
    socket = (QTcpSocket*)sender();

    QByteArray msg = socket->readAll();

    qDebug () << "[U]"<< QString::number(socket->socketDescriptor())<< QString::fromUtf8(msg);
    SendMsg(msg);
}

void Server::ClientDisconnect()
{
    for (int i = 0; i < Clients.size(); i++)
        if (Clients[i]->socketDescriptor() == -1)
            Clients.removeAt(i);
}

void Server::SendMsg(QByteArray message)
{
    for (int i = 0; i < Clients.size();i++)
         Clients[i]->write(message);
}
