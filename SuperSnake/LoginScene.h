#ifndef LOGINSCENE_H
#define LOGINSCENE_H

#include "BaseScene.h"
#include <QLineEdit>
#include <QComboBox>



class LoginScene : public BaseScene
{
    Q_OBJECT
public:
    explicit LoginScene(QWidget *parent,int w,int h);
    void initScene(); //初始化場景

//信號
signals:
    void backToMenu(); //返回【菜單界面】的信號

//槽
public:
    void regAccount(); //注冊&登錄account
    void loginAccount(); //登錄account


private:
    QLineEdit* userNameInput; //用戶名輸入框
    QLineEdit* userIdInput; //帳號輸入框
    QLineEdit* userPwdInput; //密碼輸入框
    QComboBox* serverSelect;  //Server選擇框

};

#endif // LOGINSCENE_H
