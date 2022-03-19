#include "LoginScene.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include "User.h"



LoginScene::LoginScene(QWidget *parent,int w,int h) : QMainWindow(parent),width(w),height(h)
{ 
    this->init();
}

//注冊&登錄account
void LoginScene::regAccount(){
    QString userName = userNameInput->text();
    QString userId = userIdInput->text();
    QString userPwd = userPwdInput->text();

    if(userName == "" || userId == "" || userPwd == ""){
        QMessageBox::critical (this,"錯誤！！！","用戶名/帳戶/密碼不能為空！！！");
        return;
    }
    //返回true代表注冊驗證成功
    bool ret = User::createAccount(userName,userId,userPwd);
    if(!ret){
        QMessageBox::critical (this,"錯誤","帳號/用戶名已存在！");
        return;
    }
    QMessageBox::information(this,"恭喜~~~","注冊成功！！");

    /* 注冊成功後，先記錄當前用戶信息，再返回【菜單界面】 */
    User::setCurrentUser(userName,userId);
    emit this->backToMenu();
    this->close();

}

//登錄account
void LoginScene::loginAccount(){
    QString userId = userIdInput->text();
    QString userPwd = userPwdInput->text();

    if(userId == "" || userPwd == ""){
        QMessageBox::critical (this,"錯誤！！！","帳戶/密碼不能為空！！！");
        return;
    }
    //返回true代表登錄驗證成功
    bool ret = User::loginAccount(userId,userPwd);
    if(!ret){
        QMessageBox::critical (this,"錯誤","帳戶/密碼有誤！");
        return;
    }
    QMessageBox::information(this,"恭喜~~~","登錄成功！！");
    //記錄當前用戶信息
    User::setCurrentUser(nullptr,userId);
    emit this->backToMenu();
    this->close();

}

//初始化界面
void LoginScene::init(){
    //載入和設置CSS樣式表
    QFile cssFile;
    cssFile.setFileName("./css/loginScene.css");
    cssFile.open(QIODevice::ReadOnly);
    QString styleSheet = cssFile.readAll();
    cssFile.close();
    this->setStyleSheet(styleSheet);

    this->setFixedSize(width,height);
    /* 根據mode來設置標題 */
    QString title = "【SuperSnake】用戶登錄";

    this->setWindowTitle(title);


    /* 用戶名相關控件設置 */
    QLabel* userNameLabel = new QLabel("用戶名:",this);
    userNameLabel->move(width*0.2,height*0.1);
    userNameLabel->adjustSize();

    userNameInput = new QLineEdit(this);
    userNameInput->setPlaceholderText("注冊才需輸入");
    userNameInput->adjustSize();
    userNameInput->move(width*0.37,height*0.1);

    //注冊按鈕
    QPushButton* regBtn = new QPushButton("注冊並登錄",this);
    regBtn->adjustSize();
    regBtn->move(width/2-regBtn->width(),height-80);
    //將【regBtn】的點擊信號與對應的注冊函數相連
    connect(regBtn,&QPushButton::clicked,this,&LoginScene::regAccount);

    //登錄按鈕
    QPushButton* loninBtn = new QPushButton("登錄",this);
    loninBtn->adjustSize();
    loninBtn->move(width/2+loninBtn->width(),height-80);

    //將【loninBtn】的點擊信號與對應的注冊函數相連
    connect(loninBtn,&QPushButton::clicked,this,&LoginScene::loginAccount);

    /* 帳號相關控件設置 */
    QLabel* userIdLabel = new QLabel("帳號：",this);
    userIdLabel->adjustSize();
    userIdLabel->move(width*0.2,height*0.35);

    userIdInput = new QLineEdit(this);
    userIdInput->setPlaceholderText("請輸入帳號");
    userIdInput->adjustSize();
    userIdInput->move(width*0.37,height*0.35);

    /* 密碼相關控件設置 */
    QLabel* userPwdLabel = new QLabel("密碼：",this);
    userPwdLabel->move(width*0.2,height*0.6);
    userPwdLabel->adjustSize();

    userPwdInput = new QLineEdit(this);
    userPwdInput->setEchoMode(QLineEdit::Password);
    userPwdInput->setPlaceholderText("請輸入密碼");
    userPwdInput->adjustSize();
    userPwdInput->move(width*0.37,height*0.6);

}
