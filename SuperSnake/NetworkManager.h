#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QJsonDocument>

#include <QDialog>
#include <QTimer>
#include <QLabel>

class NetworkManager : public QObject
{
public:
    explicit NetworkManager(QObject *parent = nullptr);
    static QByteArray get(QString url);
    static void put(QString url,QJsonDocument jsonDoc);
    void createLoadDialog();
    void closeLoadDialog();
    void showLoadDialog();
    void hideLoadDialog();
    bool isDialogCreate(); //判斷加載對話框是否已被創建

private:
    QDialog* loadDialog; //網路請求時用來過渡的加載對話框

};

#endif // NETWORKMANAGER_H
