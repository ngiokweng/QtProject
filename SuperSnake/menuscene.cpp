#include "menuscene.h"
#include "ui_menuscene.h"
#include <QLabel>
#include <QDebug>
#include <QPushButton>

MenuScene::MenuScene(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MenuScene)
{
    ui->setupUi(this);
    this->width = 800;
    this->hegith = 600;
    initMenu(this->width,this->hegith);
}

MenuScene::~MenuScene()
{
    delete ui;
}

//創建菜單界面的按鈕
void MenuScene::createBtn(QPushButton*& btn,QSize btnSize,QFont btnFont,int loc_y,int offset){
    btn->resize(btnSize);
    btn->setFont(btnFont);
    btn->move(width/2-btn->geometry().width()/2,loc_y+offset);
}

//初始化菜單選項
void MenuScene::initMenu(int width,int height){
    /****************** 初始化界面大小和外標題 ******************/
    this->setFixedSize(width,height);
    this->setWindowTitle("【SuperSnake】");

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

    /****************** 設置【開始遊戲】按鈕 ******************/
    QPushButton* startBtn = new QPushButton("開始遊戲",this);
    createBtn(startBtn,btn_defaultSize,btn_defaultFont,title->geometry().y()+title->geometry().height(),30);
    //待實現：連接遊戲場景、遊戲參數設置的窗口

    /****************** 設置【排行榜】按鈕 ******************/
    QPushButton* rankBtn = new QPushButton("排行榜",this);
    createBtn(rankBtn,btn_defaultSize,btn_defaultFont,startBtn->geometry().y()+startBtn->geometry().height(),30);


    /****************** 設置【個人信息】按鈕 ******************/
    QPushButton* selfInfoBtn = new QPushButton("個人信息",this);
    createBtn(selfInfoBtn,btn_defaultSize,btn_defaultFont,rankBtn->geometry().y()+rankBtn->geometry().height(),30);

    /****************** 設置【登出】按鈕 ******************/
    QPushButton* logoutBtn = new QPushButton("登出",this);
    createBtn(logoutBtn,btn_defaultSize,btn_defaultFont,selfInfoBtn->geometry().y()+selfInfoBtn->geometry().height(),30);


}

