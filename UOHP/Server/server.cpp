#include "server.h"
#include <QMetaType>

Server::Server(QObject *parent) :
    QTcpServer (parent)
{
    qRegisterMetaType<Person>();
}

void Server::startServer() {
    if (!this->listen(QHostAddress::LocalHost, 8081)) {
        qDebug() << "Could not start server";
    } else {
        qDebug() << "Server listening...";
    }
}

void Server::incomingConnection(qintptr socketDescriptor) {
    qDebug() << socketDescriptor << " connecting... ";
    ClientThread *thread = new ClientThread(socketDescriptor, this);

    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, &ClientThread::newPersonAdded, this, &Server::gotNewPerson);

    thread->start();
}

// ClientThread signal triggered
// Send MainWindow new information
void Server::gotNewPerson(Person person) {
    database.insertPerson(person);
    emit refreshPeople(database.getPeople());
}


