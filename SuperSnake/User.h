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
    static QString getCurrentUserId();    //取得當前登錄用戶的ID
    static QString getCurrentUserName();  //取得當前登錄用戶的Name
    static int getCurrentUserLoginTime(); //取得當前登錄用戶的登錄時間戳

};

#endif // USER_H
