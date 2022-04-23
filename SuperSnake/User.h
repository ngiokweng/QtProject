#ifndef USER_H
#define USER_H
#include <QString>
#include <QObject>

typedef int State;
#define TRUE 1
#define FALSE 0
#define ERROR -1

class User:public QObject
{
public:
    User();
    static bool createLocalAccount(QString userName,QString userId,QString userPwd); //創建【本地】的帳號
    static bool loginLoaclAccount(QString userId,QString userPwd); //登錄【本地】的本地帳號
    static State createWebAccount(QString userName,QString userId,QString userPwd); //創建【網路JSON】的帳號
    static State loginWebAccount(QString userId,QString userPwd); //登錄【網路JSON】的帳號
    static void setCurrentUser(QString userName,QString userId);  //記錄當前登錄用戶(For【本地】)
    static void setCurrentUser_Web(QString userName,QString userId);  //記錄當前登錄用戶(For【網路JSON】)
    static QString getCurrentUserId();    //取得當前登錄用戶的ID
    static QString getCurrentUserName();  //取得當前登錄用戶的Name
    static QString getCurrentServer(); //獲取當前伺服器
    static int getCurrentUserLoginTime(); //取得當前登錄用戶的登錄時間戳

};

#endif // USER_H
