#include "MenuScene.h"
#include "ui_menuscene.h"
#include <QLabel>
#include <QDebug>
#include <QPushButton>
#include <QDialog>
#include "LoginScene.h"
#include <QMessageBox>
#include <MapScene.h>
#include "SettingScene.h"
#include "RankListScene.h"
#include "User.h"
#include <QDateTime>

MenuScene::MenuScene(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MenuScene)
{
    ui->setupUi(this);
    //設置菜單界面的大小
    this->width = 800;
    this->height = 600;
    initMenu(); //初始化菜單界面

    enterLoginScene();  //進入登錄界面

}

//進入【登錄界面】
void MenuScene::enterLoginScene(){

    LoginScene* loginScene = new LoginScene(this,600,400);

    // 當loginScene發送backToMenu信號時，就返回到MenuScene
    connect(loginScene,&LoginScene::backToMenu,[this](){
        this->show();
    });

    loginScene->show(); //顯示登錄界面
}

//進入【設置界面】
void MenuScene::enterSettingScene(){
    SettingScene* settingScene = new SettingScene(this,600,480);

    //當接收到SettingScene傳來的backToMenuScene信號時，就返回到MenuScene界面
    connect(settingScene,&SettingScene::backToMenuScene,[this](){
        this->show();
    });

    this->hide();
    settingScene->show();
}
// 進入【排行榜界面】
void MenuScene::enterRankListScene(){
    RankListScene* rankListScene = new RankListScene(this,1200,720);
    //當接收到RankListScene傳來的backToMenuScene信號時，就返回到MenuScene界面
    connect(rankListScene,&RankListScene::backToMenuScene,[this](){
       this->show();
    });
    this->hide();
    rankListScene->show();
}

//登出
void MenuScene::logout(){
    //讓用戶確定是否要登出
    QMessageBox::StandardButtons confirm=QMessageBox::question(this,"提示","確定要登出？",QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
    if(confirm == QMessageBox::No)
        return;

    LoginScene* loginScene = new LoginScene(this,600,400);

    // 當loginScene發送backToMenu信號時，就返回到MenuScene
    connect(loginScene,&LoginScene::backToMenu,[this](){
        this->show();
    });
    this->hide();
    loginScene->show(); //顯示登錄界面
}
 //顯示個人信息
void MenuScene::showSelfInfo(){
    //設置個人信息的窗口
    QMainWindow* selfInfoScene = new QMainWindow(this);
    selfInfoScene->setFixedSize(400,300);
    selfInfoScene->setWindowTitle("【SuperSnake】個人信息");

    //獲取個人信息
    QString userName = User::getCurrentUserName();
    QString userId = User::getCurrentUserId();
    int playHowLong = QDateTime::currentDateTime().toTime_t() - User::getCurrentUserLoginTime(); //獲取上線時長(單位：s)
    /*轉化為時分秒的形式*/
    int hour,minute,second;
    hour = playHowLong/3600;
    minute = (playHowLong - hour*3600)/60;
    second = playHowLong - 3600*hour - 60*minute;
    //格式化到字符串中
    QString playDate = QString("%1:%2:%3").arg(hour,2,10,QLatin1Char('0')).arg(minute,2,10,QLatin1Char('0')).arg(second,2,10,QLatin1Char('0'));


    //設置個人信息內容
    QString selfInfo = QString("用戶名：%1\n\n用戶ID：%2\n\n上線時長：%3").arg(userName).arg(userId).arg(playDate);
    QLabel* infoLabel = new QLabel(selfInfo,selfInfoScene);
    infoLabel->setFont(QFont("Adobe 繁黑體 Std B",16));
    infoLabel->adjustSize();
    infoLabel->move(selfInfoScene->width()/2-infoLabel->width()/2,selfInfoScene->height()/2-infoLabel->height()/2);

    selfInfoScene->show();
}

//創建菜單界面的按鈕
void MenuScene::createBtn(QPushButton*& btn,QSize btnSize,int loc_y,int offset){
    btn->resize(btnSize);
    btn->move(width/2-btn->geometry().width()/2,loc_y+offset);
}

//初始化菜單選項
void MenuScene::initMenu(){
    //載入CSS樣式
    QFile cssFile;
    cssFile.setFileName("./css/menuScene.css");
    cssFile.open(QIODevice::ReadOnly);
    QString styleSheet = cssFile.readAll();
    cssFile.close();

    /****************** 初始化界面大小和外標題 ******************/
    this->setFixedSize(width,height);
    this->setWindowTitle("【SuperSnake】菜單界面");

    this->setStyleSheet(styleSheet); //設置樣式表


    /****************** 設置內標題文本 ******************/
    QLabel* title = new QLabel("SuperSnake",this);
    title->setObjectName("title");

    title->adjustSize(); //自適應文本內容的大小
    title->move(width/2-title->geometry().width()/2,30); //將標題水平置中

    /* 按鈕的默認大小 */
    QSize btn_defaultSize(150,75);

    /* 設置【開始遊戲】按鈕 */
    QPushButton* startBtn = new QPushButton("開始遊戲",this);

    startBtn->setIcon(QIcon("./img/start.png"));
    createBtn(startBtn,btn_defaultSize,title->geometry().y()+title->geometry().height(),30);
    //連接遊戲場景、遊戲參數設置的窗口
    connect(startBtn,&QPushButton::clicked,this,&MenuScene::enterSettingScene);

    /* 設置【排行榜】按鈕 */
    QPushButton* rankBtn = new QPushButton("排行榜",this);

    rankBtn->setIcon(QIcon("./img/rank.png"));
    createBtn(rankBtn,btn_defaultSize,startBtn->geometry().y()+startBtn->geometry().height(),30);
    connect(rankBtn,&QPushButton::clicked,this,&MenuScene::enterRankListScene);


    /* 設置【個人信息】按鈕 */
    QPushButton* selfInfoBtn = new QPushButton("個人信息",this);

    selfInfoBtn->setIcon(QIcon("./img/selfInfo.png"));
    createBtn(selfInfoBtn,btn_defaultSize,rankBtn->geometry().y()+rankBtn->geometry().height(),30);
    connect(selfInfoBtn,&QPushButton::clicked,this,&MenuScene::showSelfInfo);


    /* 設置【登出】按鈕 */
    QPushButton* logoutBtn = new QPushButton("登出",this);
    logoutBtn->setIcon(QIcon("./img/leave.png"));

    createBtn(logoutBtn,btn_defaultSize,selfInfoBtn->geometry().y()+selfInfoBtn->geometry().height(),30);
    connect(logoutBtn,&QPushButton::clicked,this,&MenuScene::logout);

}

MenuScene::~MenuScene()
{
    delete ui;
}
