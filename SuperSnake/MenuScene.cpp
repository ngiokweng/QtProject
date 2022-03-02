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
    /*讓玩家選擇【是否新用戶】，是則進入注冊界面，反之登錄界面*/
    QMessageBox::StandardButtons flag = QMessageBox::question(this,"question","是否【新用戶】",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
    int mode = REGISTER;
    if(flag == QMessageBox::No)mode = LOGIN;

    LoginScene* loginScene = new LoginScene(this,600,400,mode);

    // 當loginScene發送backToMenu信號時，就返回到MenuScene
    connect(loginScene,&LoginScene::backToMenu,[=](){
        this->show();
    });

    loginScene->show(); //顯示登錄界面
}

//進入【設置界面】
void MenuScene::enterSettingScene(){
    SettingScene* settingScene = new SettingScene(this,600,480);
    this->hide();
    settingScene->show();
}

//創建菜單界面的按鈕
void MenuScene::createBtn(QPushButton*& btn,QSize btnSize,QFont btnFont,int loc_y,int offset){
    btn->resize(btnSize);
    btn->setFont(btnFont);
    btn->move(width/2-btn->geometry().width()/2,loc_y+offset);
}

//初始化菜單選項
void MenuScene::initMenu(){
    /****************** 初始化界面大小和外標題 ******************/
    this->setFixedSize(width,height);
    this->setWindowTitle("【SuperSnake】菜單界面");

    /****************** 設置內標題文本 ******************/
    QLabel* title = new QLabel("SuperSnake",this);
    QFont titleFont("Adobe 仿宋 Std R",38);
    titleFont.setBold(true);
    title->setFont(titleFont);
    title->adjustSize(); //自適應文本內容的大小
    title->move(width/2-title->geometry().width()/2,30); //將標題水平置中

    /* 按鈕的默認樣式 */
    QSize btn_defaultSize(150,75);
    QFont btn_defaultFont("Adobe 繁黑體 Std B",20);

    /* 設置【開始遊戲】按鈕 */
    QPushButton* startBtn = new QPushButton("開始遊戲",this);
    createBtn(startBtn,btn_defaultSize,btn_defaultFont,title->geometry().y()+title->geometry().height(),30);
    //待實現：連接遊戲場景、遊戲參數設置的窗口
    connect(startBtn,&QPushButton::clicked,this,&MenuScene::enterSettingScene);

    /* 設置【排行榜】按鈕 */
    QPushButton* rankBtn = new QPushButton("排行榜",this);
    createBtn(rankBtn,btn_defaultSize,btn_defaultFont,startBtn->geometry().y()+startBtn->geometry().height(),30);


    /* 設置【個人信息】按鈕 */
    QPushButton* selfInfoBtn = new QPushButton("個人信息",this);
    createBtn(selfInfoBtn,btn_defaultSize,btn_defaultFont,rankBtn->geometry().y()+rankBtn->geometry().height(),30);

    /* 設置【登出】按鈕 */
    QPushButton* logoutBtn = new QPushButton("登出",this);
    createBtn(logoutBtn,btn_defaultSize,btn_defaultFont,selfInfoBtn->geometry().y()+selfInfoBtn->geometry().height(),30);


}

MenuScene::~MenuScene()
{
    delete ui;
}
