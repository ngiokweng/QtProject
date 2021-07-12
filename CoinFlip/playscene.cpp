#include "playscene.h"
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include "mycoin.h"
#include "dataconfig.h"
#include <QDebug>
#include <QPropertyAnimation>
#include <QSound>

PlayScene::PlayScene(int level)
{
    this->levelIndex = level;

    this->setFixedSize(320,588);
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    QString str = QString("關卡%1").arg(level);
    this->setWindowTitle(str);

    QMenuBar* menuBar = this->menuBar();
    this->setMenuBar(menuBar);
    QMenu* startMenu = new QMenu("開始");
    menuBar->addMenu(startMenu);
    QAction* quitAction = startMenu->addAction("退出");

    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    dataConfig config;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }
    //返回按鈕音效
    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);
    //翻金幣音效
    QSound *flipSound = new QSound(":/res/ConFlipSound.wav",this);
    //勝利按鈕音效
    QSound *winSound = new QSound(":/res/LevelWinSound.wav",this);




    //勝利Label
    QLabel* winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move( (this->width() - tmpPix.width())*0.5 , -tmpPix.height());


    //創建金幣的背景圖片
    for(int i = 0 ; i < 4;i++)
    {
        for(int j = 0 ; j < 4; j++)
        {
           //繪製背景圖片
            QPixmap pixMap(":/res/BoardNode.png");
            QLabel* label = new QLabel;
            label->setGeometry(0,0,pixMap.width(),pixMap.height());
            label->setPixmap(pixMap);
            label->setParent(this);
            label->move(57 + i*50,200+j*50);

            //創建金幣
            QString str;
            if(gameArray[i][j]==1){
                str = ":/res/Coin0001.png";
            }else{
                str = ":/res/Coin0008.png";
            }
            MyCoin* myCoin = new MyCoin(str);
            myCoin->setParent(this);
            myCoin->move(59 + i*50,204+j*50);
            myCoin->posX = i;
            myCoin->posY = j;
            myCoin->coinFlag = gameArray[i][j];

            this->coinArray[i][j] = myCoin;

            connect(myCoin,&QPushButton::clicked,[=](){
                flipSound->play();
                //點擊時將其他金幣按鈕先禁用
                for(int i=0;i<4;i++){
                    for(int j=0;j<4;j++){
                       coinArray[i][j]->isWin = true;
                    }
                }


               myCoin->changeFlag();
               gameArray[i][j] = gameArray[i][j]==0?1:0;

               QTimer::singleShot(300,this,[=](){
                   //右邊金幣翻轉
                  if(myCoin->posX+1<=3){
                      coinArray[myCoin->posX+1][myCoin->posY]->changeFlag();
                      gameArray[myCoin->posX+1][myCoin->posY] = gameArray[myCoin->posX+1][myCoin->posY]==0?1:0;
                  }
                  //左邊金幣翻轉
                 if(myCoin->posX-1>=0){
                     coinArray[myCoin->posX-1][myCoin->posY]->changeFlag();
                     gameArray[myCoin->posX-1][myCoin->posY] = gameArray[myCoin->posX-1][myCoin->posY]==0?1:0;
                 }
                 //上邊邊金幣翻轉
                if(myCoin->posY-1>=0){
                    coinArray[myCoin->posX][myCoin->posY-1]->changeFlag();
                    gameArray[myCoin->posX][myCoin->posY-1] = gameArray[myCoin->posX][myCoin->posY-1]==0?1:0;
                }
                //下邊邊金幣翻轉
               if(myCoin->posY+1<=3){
                   coinArray[myCoin->posX][myCoin->posY+1]->changeFlag();
                   gameArray[myCoin->posX][myCoin->posY+1] = gameArray[myCoin->posX][myCoin->posY+1]==0?1:0;
               }

                //點擊後再解禁
               for(int i=0;i<4;i++){
                   for(int j=0;j<4;j++){
                      coinArray[i][j]->isWin = false;
                   }
               }

               //判斷贏未
               this->isWin = true;
               for(int i=0;i<4;i++){
                   for(int j=0;j<4;j++){
                       if(coinArray[i][j]->coinFlag==false){
                           this->isWin = false;
                           break;
                       }
                   }
               }
               if(this->isWin){
                   winSound->play();
                   qDebug()<<"YOU WIN!!!!";
                   for(int i=0;i<4;i++){
                       for(int j=0;j<4;j++){
                           coinArray[i][j]->isWin = true;
                       }
                   }
                   QPropertyAnimation* animation = new QPropertyAnimation(winLabel,"geometry");
                   animation->setDuration(1000);
                   animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->winId(),winLabel->height()));
                   animation->setEndValue(QRect(winLabel->x(),-winLabel->y(),winLabel->winId(),winLabel->height()));
                   animation->setEasingCurve(QEasingCurve::OutBounce);
                   animation->start();
               }

               });


            });
        }
    }

    MyPushButton* backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    connect(backBtn,&QPushButton::clicked,[=](){
        backSound->play();
        //延時發送返回信號
        QTimer::singleShot(200,this,[=](){
            emit this->chooseSceneBack();
        });

    });

    QLabel* label = new QLabel(this);
    QFont font;
    font.setFamily("微軟正黑體");
    font.setPointSize(20);
    label->setFont(font);
    QString str1 = QString("Level:%1").arg(this->levelIndex);
    label->setText(str1);
    label->setGeometry(30, this->height() - 50,120, 50);

}

void PlayScene::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);
}



