#include "User.h"
#include "data.h"
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

User::User()
{

}


bool User::createAccount(QString userName,QString userId,QString userPwd){
    /* 讀取文件 */
    QFile userList;
    userList.setFileName(accountPath);
    userList.open(QIODevice::ReadOnly);
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
}

 //登錄帳號
bool User::loginAccount(QString userId,QString userPwd){
    /* 讀取文件 */
    QFile userList;
    userList.setFileName(accountPath);
    userList.open(QIODevice::ReadOnly);
    QByteArray userData = userList.readAll();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(userData); //將數據解析為Json格式
    QJsonObject jsonObj = jsonDoc.object(); //轉為QJsonObject類型

    //判斷帳號是否存在，若存在則判斷密碼是否正確
    if(jsonObj.contains(userId)){
        if(jsonObj[userId].toObject()["userPwd"] == userPwd)return true;
    }

    return false;



}

