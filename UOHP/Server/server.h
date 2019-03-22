#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QDebug>
#include <QJsonObject>
#include <QSignalMapper>

#include "clientthread.h"
#include "person.h"
#include "dbmanager.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    void startServer();

signals:
    void refreshPeople(std::vector<Person> people);

public slots:
    void gotNewPerson(Person person);

protected:
    virtual void incomingConnection(qintptr socketDescriptor);

private:
    DBManager database = DBManager::getInstance();
};

#endif // SERVER_H
