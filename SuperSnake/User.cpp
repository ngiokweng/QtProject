#include "User.h"
#include "data.h"
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QDateTime>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>

#include "NetworkManager.h"


User::User(){}


bool User::createLocalAccount(QString userName,QString userId,QString userPwd){
    /* 打開文件 */
    QFile userList;
    userList.setFileName(accountPath);
    userList.open(QIODevice::ReadOnly);
    //讀取所有內容
    QByteArray userData = userList.readAll();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(userData); //將數據解析為Json格式
    QJsonObject jsonObj = jsonDoc.object(); //轉為QJsonObject類型

    //判斷用戶ID是否已存在
    if(jsonObj.contains(userId))return false;

    //判斷用戶名是否已存在
    for(auto& key:jsonObj.keys()){
        if(jsonObj[key].toObject()["userName"].toString() == userName)return false;
    }


    //相當於在.json中創建一個新用戶
    //存儲結構-> "userId":{ "userName":XXXX, "userPwd":XXXX }
    QJsonObject userIdObj;
    userIdObj.insert("userName",userName);
    userIdObj.insert("userPwd",userPwd);
    jsonObj.insert(userId,userIdObj);

    jsonDoc.setObject(jsonObj);  //更新QJsonObect的內容

    userList.close();

    /* 保存文件 */
    userList.open(QIODevice::WriteOnly);
    userList.write(jsonDoc.toJson());
    userList.close();

    return true;
}

 //登錄帳號
bool User::loginLoaclAccount(QString userId,QString userPwd){
    /* 打開文件 */
    QFile userList;
    userList.setFileName(accountPath);
    userList.open(QIODevice::ReadOnly);
    //讀取所有內容
    QByteArray userData = userList.readAll();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(userData); //將數據解析為Json格式
    QJsonObject jsonObj = jsonDoc.object(); //轉為QJsonObject類型

    //判斷帳號是否存在，若存在則判斷密碼是否正確
    if(jsonObj.contains(userId)){
        if(jsonObj[userId].toObject()["userPwd"] == userPwd)return true;
    }

    return false;



}

void User::setCurrentUser(QString userName,QString userId){
    //當userName為nullptr，代表是登錄時調用這個函數
    //由於登錄不用輸入用戶名，所以要打開儲存【所有用戶】的文件來找到指定id的用戶名
    if(userName == nullptr){
        QFile userList;
        userList.setFileName(accountPath);
        userList.open(QIODevice::ReadOnly);
        QByteArray userData = userList.readAll();

        QJsonDocument userList_jsonDoc = QJsonDocument::fromJson(userData); //將數據解析為Json格式
        QJsonObject userList_jsonObj = userList_jsonDoc.object(); //轉為QJsonObject類型

        userName = userList_jsonObj[userId].toObject()["userName"].toString();

        userList.close();

    }

    /* 打開文件指定文件 */
    QFile currentUserFile;
    currentUserFile.setFileName(currentUserPath);
    currentUserFile.open(QIODevice::WriteOnly);

    QJsonDocument currentUser_jsonDoc;
    QJsonObject currentUser_jsonObj{
        {"userId",userId},
        {"userName",userName}
    };
    int time = QDateTime::currentDateTime().toTime_t();
    currentUser_jsonObj.insert("loginTime",time);

    currentUser_jsonDoc.setObject(currentUser_jsonObj);


    currentUserFile.write(currentUser_jsonDoc.toJson());
    currentUserFile.close();
}

void User::setCurrentUser_Web(QString userName,QString userId){
    //當userName為nullptr，代表是登錄時調用這個函數
    //由於登錄不用輸入用戶名，所以要在【網路JSON】找到指定id的用戶名
    if(userName == nullptr){

        QByteArray responseData = NetworkManager::get(webJsonUrl_AC);  //讀取所有數據

        /*JSON相關操作：將請求過來的數據轉為JSON格式，然後再進行處理*/
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObj = jsonDoc.object();

        userName = jsonObj[userId].toObject()["userName"].toString();

    }

    /* 打開文件指定文件 */
    QFile currentUserFile;
    currentUserFile.setFileName(currentUserPath);
    currentUserFile.open(QIODevice::WriteOnly);

    QJsonDocument currentUser_jsonDoc;
    QJsonObject currentUser_jsonObj{
        {"userId",userId},
        {"userName",userName}
    };
    int time = QDateTime::currentDateTime().toTime_t();
    currentUser_jsonObj.insert("loginTime",time);

    currentUser_jsonDoc.setObject(currentUser_jsonObj);


    currentUserFile.write(currentUser_jsonDoc.toJson());
    currentUserFile.close();
}

QString User::getCurrentUserId(){
    /* 打開文件指定文件 */
    QFile currentUserFile;
    currentUserFile.setFileName(currentUserPath);
    currentUserFile.open(QIODevice::ReadOnly);
    QByteArray userData = currentUserFile.readAll();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(userData);
    QJsonObject jsonObj = jsonDoc.object();

    currentUserFile.close();
    return jsonObj["userId"].toString();

}

QString User::getCurrentUserName(){
    /* 打開文件指定文件 */
    QFile currentUserFile;
    currentUserFile.setFileName(currentUserPath);
    currentUserFile.open(QIODevice::ReadOnly);
    QByteArray userData = currentUserFile.readAll();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(userData);
    QJsonObject jsonObj = jsonDoc.object();

    currentUserFile.close();
    return jsonObj["userName"].toString();

}

int User::getCurrentUserLoginTime(){
    /* 打開文件指定文件 */
    QFile currentUserFile;
    currentUserFile.setFileName(currentUserPath);
    currentUserFile.open(QIODevice::ReadOnly);
    QByteArray userData = currentUserFile.readAll();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(userData);
    QJsonObject jsonObj = jsonDoc.object();

    currentUserFile.close();
    return jsonObj["loginTime"].toInt();
}

bool User::createWebAccount(QString userName,QString userId,QString userPwd){
    QByteArray responseData = NetworkManager::get(webJsonUrl_AC);  //發送get請求，取得所有數據

    /*JSON相關操作：將請求過來的數據轉為JSON格式，然後再進行處理*/
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObj = jsonDoc.object();

    //判斷用戶ID是否已存在於【網路Server】
    if(jsonObj.contains(userId))return false;

    //判斷用戶名是否已存在於【網路Server】
    for(auto& key:jsonObj.keys()){
        if(jsonObj[key].toObject()["userName"].toString() == userName)return false;
    }

    //創建一個新用戶於【網路Server】
    //存儲結構-> "userId":{ "userName":XXXX, "userPwd":XXXX }
    QJsonObject userIdObj;
    userIdObj.insert("userName",userName);
    userIdObj.insert("userPwd",userPwd);
    jsonObj.insert(userId,userIdObj);

    jsonDoc.setObject(jsonObj);  //更新QJsonObect的內容

    NetworkManager::put(webJsonUrl_AC,jsonDoc); //發送put請求，更新數據

    return true;
}

bool User::loginWebAccount(QString userId,QString userPwd){

    QByteArray responseData = NetworkManager::get(webJsonUrl_AC);
    /*JSON相關操作：將請求過來的數據轉為JSON格式，然後再進行處理*/
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObj = jsonDoc.object();

    //判斷帳號是否存在於【網路Server】，若存在則判斷密碼是否正確
    if(jsonObj.contains(userId)){
        if(jsonObj[userId].toObject()["userPwd"] == userPwd)return true;
    }

    return false;
}

