#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QJsonDocument>

class NetworkManager : public QObject
{
public:
    explicit NetworkManager(QObject *parent = nullptr);
    static QByteArray get(QString url);
    static void put(QString url,QJsonDocument jsonDoc);

signals:

};

#endif // NETWORKMANAGER_H
