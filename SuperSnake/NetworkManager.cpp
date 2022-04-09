#include "NetworkManager.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include "data.h"


NetworkManager::NetworkManager(QObject *parent) : QObject(parent){}

QByteArray NetworkManager::get(QString url){
    /*網路請求相關操作*/
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest request;
    request.setUrl(url);
    QNetworkReply *reply = manager->get(request);

    QEventLoop eventLoop;
    connect(reply, &QNetworkReply::finished, &eventLoop,&QEventLoop::quit);
    eventLoop.exec();  //阻塞函數，直至請求完成

    QByteArray data = reply->readAll();

    manager->deleteLater();
    reply->deleteLater();

    return data;  //返回取得的所有數據
}

void NetworkManager::put(QString url,QJsonDocument jsonDoc){
    /*網路請求相關操作*/
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest request;
    request.setUrl(url);


    /* 發送put網路請求，更新【網路Server】的帳號信息 */
    request.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));
    request.setRawHeader(QByteArray("Security-key"),securityKey);

    QNetworkReply *reply = manager->put(request,jsonDoc.toJson());

    QEventLoop eventLoop;
    connect(reply, &QNetworkReply::finished, &eventLoop,&QEventLoop::quit);
    eventLoop.exec();       //阻塞函數，直至請求完成

    manager->deleteLater();
    reply->deleteLater();
}
