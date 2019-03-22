#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QQueue>
#include "person.h"
#include "dbmanager.h"

class ClientThread : public QThread
{
    Q_OBJECT
public:
    ClientThread(qintptr id, QObject *parent = nullptr)
        :socketDescriptor(id){}
    void run();
signals:
    void error(QTcpSocket::SocketError socketError);
    void newPersonAdded(Person person);

public slots:
    void readyRead();
    void disconnected();

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
};

#endif // CLIENTTHREAD_H
