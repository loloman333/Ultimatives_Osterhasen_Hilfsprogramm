#include "clientthread.h"

void ClientThread::run() {
    qDebug() << "ClientThread started";
    socket = new QTcpSocket();

    if(!socket->setSocketDescriptor(this->socketDescriptor)) {
        emit error(socket->error());
        return;
    }

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection);

    qDebug() << socketDescriptor << "Client connected";

    exec();
}

void ClientThread::readyRead() {
    QByteArray data = socket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject json = doc.object();

    qDebug() << socketDescriptor
             << json["name"].toString()
             << json["latitude"].toDouble()
             << json["longitude"].toDouble();

    Person newPerson = Person(-1, json["name"].toString(),
                                json["latitude"].toDouble(),
                                json["longitude"].toDouble());

    emit newPersonAdded(newPerson);
}

void ClientThread::disconnected() {
    qDebug() << socketDescriptor << "Client disconnected";
    socket->deleteLater();
    exit(0);
}
