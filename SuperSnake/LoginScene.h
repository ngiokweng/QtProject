#ifndef LOGINSCENE_H
#define LOGINSCENE_H

#include <QMainWindow>
#include <QLineEdit>

#define REGISTER 0
#define LOGIN 1

class LoginScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit LoginScene(QWidget *parent = nullptr,int w = 800,int h = 600,int mode = LOGIN);
    void init(); //初始化界面

//信號
signals:
    void backToMenu(); //返回【菜單界面】的信號

//槽
public:
    void regAccount(); //注冊&登錄account
    void loginAccount(); //登錄account


private:
    int width;  //【登錄/注冊】界面的寛
    int height; //【登錄/注冊】界面的高
    int mode;  //判斷進入登錄/注冊界面的參數
    QLineEdit* userNameInput; //用戶名輸入框
    QLineEdit* userIdInput; //帳號輸入框
    QLineEdit* userPwdInput; //密碼輸入框

};

#endif // LOGINSCENE_H
