#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QSound>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(320,588);
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    this->setWindowTitle("選取關卡");



    QMenuBar* menuBar = this->menuBar();
    this->setMenuBar(menuBar);
    QMenu* startMenu = new QMenu("開始");
    menuBar->addMenu(startMenu);
    QAction* quitAction = startMenu->addAction("退出");

    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    MyPushButton* backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //選擇關卡按鈕音效
    QSound *chooseSound = new QSound(":/res/TapButtonSound.wav",this);
    //返回按鈕音效
    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);


    connect(backBtn,&QPushButton::clicked,[=](){
        //延時發送返回信號
        backSound->play();
        QTimer::singleShot(200,this,[=](){
            emit this->chooseSceneBack();
        });

    });
    for(int i=0;i<20;i++){
        MyPushButton* btn = new MyPushButton(":/res/LevelIcon.png");
        btn->setParent(this);
        btn->move(25+i%4*70,130+i/4*70);
        connect(btn,&QPushButton::clicked,[=](){
//            QString str = QString("選擇了第%1關").arg(i+1);
//            qDebug()<<str;
            chooseSound->play();
            pScene = new PlayScene(i+1);
            this->hide();
            pScene->setGeometry(this->geometry());
            pScene->show();

            connect(pScene,&PlayScene::chooseSceneBack,[=](){
                this->setGeometry(pScene->geometry());
                this->show();
                delete pScene;
                pScene = NULL;
            });
        });



        QLabel* label = new QLabel(this);
        label->setFixedSize(btn->width(),btn->height());
        label->move(25+i%4*70,130+i/4*70);
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        label->setText(QString::number(i+1));
        label->setAttribute(Qt::WA_TransparentForMouseEvents,true); //設置鼠標事件穿透

    }

}

void ChooseLevelScene::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    QPixmap pixmap;
    //background
    pixmap.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
    //title
    pixmap.load(":/res/Title.png");
    painter.drawPixmap(this->width()*0.5-pixmap.width()*0.5,30,pixmap.width(),pixmap.height(),pixmap);
}
