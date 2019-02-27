#include "clientpart.h"

ClientPart::ClientPart(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
        connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
        connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));
}

void ClientPart::sockReady()
{

}

void ClientPart::sockDisc()
{
    socket->deleteLater();
}

void ClientPart::on_pushButton_clicked()
{

}
