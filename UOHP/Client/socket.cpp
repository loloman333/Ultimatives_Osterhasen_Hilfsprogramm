#include "socket.h"

Socket::Socket(QObject *parent) : QObject(parent) {}

bool Socket::doConnect() {
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));

    qDebug() << "Connecting...";

    // this is not blocking call
    socket->connectToHost("127.0.0.1", 8081);

    // we need to wait...
    if(!socket->waitForConnected(10000))
    {
        qDebug() << "Error: " << socket->errorString();
        return false;
    }

    return true;
}

void Socket::connected()
{
    qDebug() << "Connected";
}

void Socket::disconnected()
{
    qDebug() << "Disconnected";
}

void Socket::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written";
}

void Socket::sendJson(QJsonObject& json) {
    qDebug() << "Send JSON to Server: "
             << json["name"].toString()
             << json["latitude"].toVariant().toFloat()
             << json["longitude"].toVariant().toFloat();

    QJsonDocument doc(json);
    QByteArray bytes = doc.toJson();
    socket->write(bytes);
}
