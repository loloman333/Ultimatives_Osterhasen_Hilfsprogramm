#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QJsonObject>
#include <QJsonDocument>

class Socket : public QObject
{
    Q_OBJECT
public:
    explicit Socket(QObject *parent = nullptr);

    bool doConnect();
signals:

public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void sendJson(QJsonObject& json);

private:
    QTcpSocket *socket;
};

#endif // SOCKET_H
