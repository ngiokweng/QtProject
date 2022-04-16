#include "NetworkManager.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include "data.h"


NetworkManager::NetworkManager(QObject *parent) : QObject(parent){}

void NetworkManager::showLoadDialog(){
    loadDialog = new QDialog();
    QLabel *label = new QLabel(loadDialog);
    label->setText("請耐心地等待~~~");
    label->setFont(QFont("Adobe 繁黑體 Std B",30));
    label->adjustSize();
    loadDialog->setAttribute(Qt::WA_DeleteOnClose); //在關閉對話框時釋放內存
    loadDialog->adjustSize();
    loadDialog->setWindowTitle("加載中...");
    loadDialog->show();

    /*以下三行代碼：
     * - 是一段小小的阻塞函數
     * - 為了讓loadDialog這個非模態對話框有【show出來】的時間。若不這樣做，dialog上的字會延遲顯示出來
    */
    QEventLoop loop;
    QTimer::singleShot(10,&loop,&QEventLoop::quit);
    loop.exec();
}

void NetworkManager::closeLoadDialog(){
    loadDialog->close();
}

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
