#include "LoginScene.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include "User.h"


LoginScene::LoginScene(QWidget *parent,int w,int h) : BaseScene(parent,w,h)
{ 
    this->initScene();
}

//注冊&登錄account
void LoginScene::regAccount(){
    QString userName = userNameInput->text();
    QString userId = userIdInput->text();
    QString userPwd = userPwdInput->text();
    int serverIndex = serverSelect->currentIndex();  //0代表本地，1代本網路

    //判斷是否為空
    if(userName == "" || userId == "" || userPwd == ""){
        QMessageBox::critical (this,"錯誤！！！","用戶名/帳號/密碼不能為空！！！");
        return;
    }
    //判斷帳號、密碼、用戶名的長度[6~18]
    if(userId.length()<6 || userId.length()>18 || userPwd.length()<6 || userPwd.length()>18){
        QMessageBox::critical (this,"錯誤！！！","用戶名/帳號/密碼的長度限制為[6~18]");
        return;
    }


    //返回true代表注冊驗證成功
    bool ret;
    if(serverIndex == 0){ //代表本地
        ret = User::createLocalAccount(userName,userId,userPwd);
    }else{  //代表網路JSON
        ret = User::createWebAccount(userName,userId,userPwd);
    }
    if(!ret){
        QString serverName = (serverIndex == 0)?"本地":"網路JSON";
        QMessageBox::critical (this,"錯誤",QString("帳號/用戶名已存在於【%1】！").arg(serverName));
        return;
    }
    QMessageBox::information(this,"恭喜~~~","注冊成功！！");

    /* 注冊成功後，先記錄當前用戶信息，再返回【菜單界面】 */
    (serverIndex == 0)?User::setCurrentUser(userName,userId):User::setCurrentUser_Web(userName,userId);
    emit this->backToMenu();
    this->close();

}

//登錄account
void LoginScene::loginAccount(){
    QString userId = userIdInput->text();
    QString userPwd = userPwdInput->text();
    int serverIndex = serverSelect->currentIndex(); //0代表本地，1代本網路

    if(userId == "" || userPwd == ""){
        QMessageBox::critical (this,"錯誤！！！","帳戶/密碼不能為空！！！");
        return;
    }

    //返回true代表登錄驗證成功
    bool ret;
    if(serverIndex == 0){
        ret = User::loginLoaclAccount(userId,userPwd);
    }else{
        ret = User::loginWebAccount(userId,userPwd);
    }

    if(!ret){
        QMessageBox::critical (this,"錯誤","帳戶/密碼有誤！");
        return;
    }
    QMessageBox::information(this,"恭喜~~~","登錄成功！！");
    //記錄當前用戶信息
    if(serverIndex == 0)
        User::setCurrentUser(nullptr,userId);
    else
        User::setCurrentUser_Web(nullptr,userId);
    emit this->backToMenu();
    this->close();

}

//初始化界面
void LoginScene::initScene(){
    //載入和設置CSS樣式表
    QFile cssFile;
    cssFile.setFileName("./css/loginScene.css");
    cssFile.open(QIODevice::ReadOnly);
    QString styleSheet = cssFile.readAll();
    cssFile.close();
    this->setStyleSheet(styleSheet);

    this->setFixedSize(width,height);

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
    regBtn->move(width/2-regBtn->width(),height*0.83);
    //將【regBtn】的點擊信號與對應的注冊函數相連
    connect(regBtn,&QPushButton::clicked,this,&LoginScene::regAccount);

    //登錄按鈕
    QPushButton* loninBtn = new QPushButton("登錄",this);
    loninBtn->adjustSize();
    loninBtn->move(width/2+loninBtn->width(),height*0.83);

    //將【loninBtn】的點擊信號與對應的注冊函數相連
    connect(loninBtn,&QPushButton::clicked,this,&LoginScene::loginAccount);

    /* 帳號相關控件設置 */
    QLabel* userIdLabel = new QLabel("帳號：",this);
    userIdLabel->adjustSize();
    userIdLabel->move(width*0.2,height*0.3);

    userIdInput = new QLineEdit(this);
    userIdInput->setPlaceholderText("請輸入帳號");
    userIdInput->adjustSize();
    userIdInput->move(width*0.37,height*0.3);

    /* 密碼相關控件設置 */
    QLabel* userPwdLabel = new QLabel("密碼：",this);
    userPwdLabel->move(width*0.2,height*0.5);
    userPwdLabel->adjustSize();

    userPwdInput = new QLineEdit(this);
    userPwdInput->setEchoMode(QLineEdit::Password);
    userPwdInput->setPlaceholderText("請輸入密碼");
    userPwdInput->adjustSize();
    userPwdInput->move(width*0.37,height*0.5);

    /* Server選擇相關控件 */
    QLabel* serverLabel = new QLabel("伺服器選擇：",this);
    serverLabel->move(width*0.2,height*0.7);
    serverLabel->adjustSize();

    serverSelect = new QComboBox(this);
    serverSelect->move(width*0.2+serverLabel->width(),height*0.7);
    serverSelect->addItem("本地伺服器"); //本地Server的【排行榜、帳號】存在本地之中
    serverSelect->addItem("網路伺服器"); //網路Server的【排行榜、帳號】存在網路JSON中
    serverSelect->adjustSize();
    serverSelect->setCurrentIndex(0); //設置默認值
}
