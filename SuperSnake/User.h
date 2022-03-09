#ifndef USER_H
#define USER_H
#include <QString>


class User
{
public:
    User();
    static bool createAccount(QString userName,QString userId,QString userPwd); //創建帳號
    static bool loginAccount(QString userId,QString userPwd); //登錄帳號

};

#endif // USER_H
