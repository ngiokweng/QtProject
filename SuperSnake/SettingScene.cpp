#include "SettingScene.h"
#include <QPushButton>
#include "data.h"
#include <QLabel>
#include <QDebug>

SettingScene::SettingScene(QWidget *parent,int width,int height) : QMainWindow(parent),width(width),height(height)
{
    init();


}

SettingScene::~SettingScene(){
    //因為snake沒有加入到【對象樹】中，所以要手動釋放
    if(snake!=nullptr){
        delete snake;
        snake = nullptr;
    }
}

void SettingScene::enterMapScene(){
    int snakeSize = snakeSizeSelect->currentText().toInt();
    int mapCol = colSelect->currentText().toInt(),mapRow = rowSelect->currentText().toInt();
    int speed = speedSelect->currentIndex()+1;

    snake = new Snake(3,snakeSize);
    MapScene* mapScence = new MapScene(this,mapRow,mapCol,snake,speed);

    //當接收到mapScene傳來的backToSettingScene信號時，就返回到SettingScene界面
    connect(mapScence,&MapScene::backToSettingScene,[this](){
       this->show();
    });

    this->hide();
    mapScence->show();
}

void SettingScene::onSizeSelectChange(){
    /* 當用戶選擇【蛇大小選擇框】中不同的數值時，對應的地圖行、列的可選範圍也要改變( 否則遊戲地圖會超出屏幕大小 ) */
    int snakeSize = snakeSizeSelect->currentText().toUInt();
    colSelect->clear();
    rowSelect->clear();
    for(int i = minMapSize.width()/snakeSize;i<=maxMapSize.width()/snakeSize;i++)colSelect->addItem(QString::number(i));
    for(int i = minMapSize.height()/snakeSize;i<=maxMapSize.height()/snakeSize;i++)rowSelect->addItem(QString::number(i));

}

//初始化【設置】界面
void SettingScene::init(){
    //載入和設置CSS樣式表
    QFile cssFile;
    cssFile.setFileName("./css/settingScene.css");
    cssFile.open(QIODevice::ReadOnly);
    QString styleSheet = cssFile.readAll();
    cssFile.close();
    this->setStyleSheet(styleSheet);

    this->setFixedSize(width,height);
    this->setWindowTitle("【SuperSnake】遊戲設置");


    /*** 【蛇大小】的相關控件設置 ***/
    QLabel* snakeSizeLabel = new QLabel("選擇蛇的[大小]:",this);
    snakeSizeLabel->adjustSize(); //自適應文本內容的大小
    snakeSizeLabel->move(width*0.25,height*0.1);

    snakeSizeSelect = new QComboBox(this);
    snakeSizeSelect->move(width*0.25+snakeSizeLabel->width(),height*0.1);
    snakeSizeSelect->adjustSize();
    for(int i = minSnakeSize;i<=maxSnakeSize;i++)snakeSizeSelect->addItem(QString::number(i));
    snakeSizeSelect->setCurrentIndex(15); //設置默認值
    int snakeSize = snakeSizeSelect->currentText().toInt();

    // 當sizeSelect的選項改變時，會觸發onSizeSelectChange槽函數
    connect(snakeSizeSelect,static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&SettingScene::onSizeSelectChange);

    /*** 【地圖列數】的相關控件設置 ***/
    QLabel* mapColLabel = new QLabel("選擇地圖的[列數]:",this);
    mapColLabel->adjustSize(); //自適應文本內容的大小
    mapColLabel->move(width*0.25,height*0.3);

    colSelect = new QComboBox(this);
    colSelect->adjustSize();
    colSelect->move(width*0.25+mapColLabel->width(),height*0.3);
    // 按snakeSize來限制列數可選的上、下限( 否則遊戲地圖會超出屏幕大小 )
    for(int i = minMapSize.width()/snakeSize;i<=maxMapSize.width()/snakeSize;i++)colSelect->addItem(QString::number(i));

    /*** 【地圖行數】的相關控件設置 ***/
    QLabel* mapRowLabel = new QLabel("選擇地圖的[行數]:",this);
    mapRowLabel->adjustSize(); //自適應文本內容的大小
    mapRowLabel->move(width*0.25,height*0.5);

    rowSelect = new QComboBox(this);
    rowSelect->adjustSize();
    rowSelect->move(width*0.25+mapRowLabel->width(),height*0.5);
    // 按snakeSize來限制行數可選的上、下限( 否則遊戲地圖會超出屏幕大小 )
    for(int i = minMapSize.height()/snakeSize;i<=maxMapSize.height()/snakeSize;i++)rowSelect->addItem(QString::number(i));

    /*** 【蛇速度】的相關控件設置 ***/
    QLabel* speedLabel = new QLabel("選擇蛇的[速度]:",this);
    speedLabel->adjustSize(); //自適應文本內容的大小
    speedLabel->move(width*0.25,height*0.7);

    speedSelect = new QComboBox(this);
    speedSelect->adjustSize();
    speedSelect->move(width*0.25+speedLabel->width(),height*0.7);
    for(int i =1;i<=10;i++)speedSelect->addItem(QString("%1倍速").arg(i));




    //確定進入【MapScene】的button
    QPushButton* enter = new QPushButton("點擊進入",this);
    enter->adjustSize(); //自適應文本內容的大小
    enter->move(width/2-enter->width()/2,height*0.88);
    connect(enter,&QPushButton::clicked,this,&SettingScene::enterMapScene);

    //返回按鈕
    QPushButton* backBtn = new QPushButton("返回",this);

    backBtn->adjustSize(); //自適應文本內容的大小
    backBtn->move(width-backBtn->width()-5,5);
    connect(backBtn,&QPushButton::clicked,[this](){

        this->close();
        emit backToMenuScene();
    });

}
