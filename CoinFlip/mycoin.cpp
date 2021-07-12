#include "mycoin.h"
#include <QDebug>



MyCoin::MyCoin(QString butImg){
    QPixmap pixMap;
    bool ret = pixMap.load(butImg);
    if(!ret){
        qDebug()<<"圖片加載失敗";
    }

    this->setFixedSize(pixMap.width(),pixMap.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pixMap);
    this->setIconSize(QSize(pixMap.width(),pixMap.height()));

    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    connect(timer1,&QTimer::timeout,[=](){
       QPixmap pixMap;
       QString str = QString(":/res/Coin000%1").arg(this->min++);
       pixMap.load(str);

       this->setFixedSize(pixMap.width(),pixMap.height());
       this->setStyleSheet("QPushButton{border:0px}");
       this->setIcon(pixMap);
       this->setIconSize(QSize(pixMap.width(),pixMap.height()));

       if(this->min>this->max){
           this->min = 1;
           this->isAnimation = false;
           timer1->stop();
       }

    });

    connect(timer2,&QTimer::timeout,[=](){
       QPixmap pixMap;
       QString str = QString(":/res/Coin000%1").arg(this->max--);
       pixMap.load(str);

       this->setFixedSize(pixMap.width(),pixMap.height());
       this->setStyleSheet("QPushButton{border:0px}");
       this->setIcon(pixMap);
       this->setIconSize(QSize(pixMap.width(),pixMap.height()));

       if(this->max<this->min){
           this->max = 8;
           this->isAnimation = false;
           timer2->stop();
       }

    });
}

void MyCoin::changeFlag(){
    if(this->coinFlag){
        timer1->start(30); //正->反
        this->isAnimation = true;
        this->coinFlag = false;
    }else{
        timer2->start(30); //反->正
        this->isAnimation = true;
        this->coinFlag = true;
    }
}

void MyCoin::mousePressEvent(QMouseEvent* event){
    if(!this->isAnimation&&!this->isWin){
        QPushButton::mousePressEvent(event);
    }
}

