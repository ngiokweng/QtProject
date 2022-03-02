#include "LoginScene.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
#include <QFile>



LoginScene::LoginScene(QWidget *parent,int w,int h,int mode) : QMainWindow(parent),width(w),height(h),mode(mode)
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
    //數據存儲順序：【用戶名】 【帳號】 【密碼】
    QString userData = QString("%1 %2 %3\n").arg(userName).arg(userId).arg(userPwd);
    //將數據寫到本地的.txt檔，以作儲存
    QFile accountFile("./data/user_account.txt");
    accountFile.open(QIODevice::Append);
    accountFile.write(userData.toUtf8().data());
    QMessageBox::information(this,"恭喜~~~","注冊成功！！");
    /* 注冊成功後，返回【菜單界面】 */
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
    //讀取所有帳戶信息
    QFile accountFile("./data/user_account.txt");
    accountFile.open(QIODevice::ReadOnly);
    while(!accountFile.atEnd()){
        QString str = accountFile.readLine();
        str.replace('\n',' '); //為了防止換行符影響到帳密的判斷
        QStringList accountInfo = str.split(' ');

        if(userId == accountInfo[1] && userPwd == accountInfo[2]){
            /* 注冊成功後，返回【菜單界面】 */
            QMessageBox::information(this,"恭喜~~~","登錄成功！！");
            emit this->backToMenu();
            this->close();
            return;
        }
    }
    // 當遍歷完所有帳戶後，仍未能匹配成功，即代表輸入有誤
    QMessageBox::critical (this,"錯誤","帳戶/密碼有誤！");

}

//初始化界面
void LoginScene::init(){
    this->setFixedSize(width,height);
    /* 根據mode來設置標題 */
    QString title = "【SuperSnake】用戶";
    title += (mode == LOGIN?"登錄":"注冊");
    this->setWindowTitle(title);

    /* 注冊模式時： */
    if(mode == REGISTER){
        /* 用戶名相關控件設置 */
        QLabel* userNameLabel = new QLabel("用戶名:",this);
        userNameLabel->move(width*0.15,height*0.1);
        userNameLabel->setFont(QFont("Arial",20));
        userNameLabel->adjustSize();

        userNameInput = new QLineEdit(this);
        userNameInput->setPlaceholderText("請輸入用戶名");
        userNameInput->setFont(QFont("Arial",20));
        userNameInput->adjustSize();
        userNameInput->move(width*0.35,height*0.1);

        //注冊按鈕
        QPushButton* regBtn = new QPushButton("注冊並登錄",this);
        regBtn->setFont(QFont("Arial",20));
        regBtn->adjustSize();
        regBtn->move(width/2-regBtn->width()/2,height-80);
        //將【regBtn】的點擊信號與對應的注冊函數相連
        connect(regBtn,&QPushButton::clicked,this,&LoginScene::regAccount);

    }
    else{ /* 登錄模式時 */
        //登錄按鈕
        QPushButton* loninBtn = new QPushButton("登錄",this);
        loninBtn->setFont(QFont("Arial",20));
        loninBtn->adjustSize();
        loninBtn->move(width/2-loninBtn->width()/2,height-80);

        //將【loninBtn】的點擊信號與對應的注冊函數相連
        connect(loninBtn,&QPushButton::clicked,this,&LoginScene::loginAccount);
    }

    /* 帳號相關控件設置 */
    QLabel* userIdLabel = new QLabel("帳號：",this);
    userIdLabel->setFont(QFont("Arial",20));
    userIdLabel->adjustSize();
    userIdLabel->move(width*0.15,height*0.35);

    userIdInput = new QLineEdit(this);
    userIdInput->setPlaceholderText("請輸入帳號");
    userIdInput->setFont(QFont("Arial",20));
    userIdInput->adjustSize();
    userIdInput->move(width*0.35,height*0.35);

    /* 密碼相關控件設置 */
    QLabel* userPwdLabel = new QLabel("密碼：",this);
    userPwdLabel->setFont(QFont("Arial",20));
    userPwdLabel->move(width*0.15,height*0.6);
    userPwdLabel->adjustSize();

    userPwdInput = new QLineEdit(this);
    userPwdInput->setEchoMode(QLineEdit::Password);
    userPwdInput->setPlaceholderText("請輸入密碼");
    userPwdInput->setFont(QFont("Arial",20));
    userPwdInput->adjustSize();
    userPwdInput->move(width*0.35,height*0.6);

}
