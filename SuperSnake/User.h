#ifndef USER_H
#define USER_H
#include <QString>


class User
{
public:
    User();
    static bool createAccount(QString userName,QString userId,QString userPwd); //創建帳號
    static bool loginAccount(QString userId,QString userPwd); //登錄帳號
    static void setCurrentUser(QString userName,QString userId);  //記錄當前登錄用戶
    static QString getCurrentUserId();
    static QString getCurrentUserName();
    static int getCurrentUserLoginTime();


};

#endif // USER_H
