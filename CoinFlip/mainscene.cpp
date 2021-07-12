#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include "chooselevelscene.h"
#include <QSound>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    setFixedSize(320,588);
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    setWindowTitle("翻金幣遊戲");

    connect(ui->actionQuit,&QAction::triggered,[=](){
       this->close();
    });

    //加載->點擊開始的音效
    QSound* startSound = new QSound(":/res/TapButtonSound.wav",this);

    MyPushButton* startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);

    chooseLevelScene = new ChooseLevelScene;

    //連接返回信號，顯示主場景
    connect(chooseLevelScene,&ChooseLevelScene::chooseSceneBack,[=](){
       chooseLevelScene->hide();
       this->setGeometry(chooseLevelScene->geometry());
       this->show();
    });

    connect(startBtn,&QPushButton::clicked,[=](){
        startSound->play();

       //start按鈕的動畫效果(彈起)
       startBtn->zoom1();
       startBtn->zoom2();

       //延時進入選關界面
       QTimer::singleShot(500,this,[=](){
          chooseLevelScene->setGeometry(this->geometry());
          this->hide();
          chooseLevelScene->show();
       });
    });
}

void MainScene::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);
}


MainScene::~MainScene()
{
    delete ui;
}

