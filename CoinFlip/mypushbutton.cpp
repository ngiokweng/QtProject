#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>

MyPushButton::MyPushButton(QString normalImg,QString pressImg){
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;
    QPixmap pixmap;
    bool ret = pixmap.load(normalImg);
    if(!ret){
        qDebug()<<"圖片加載失敗";
    }

    this->setFixedSize(pixmap.width(),pixmap.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));
}

void MyPushButton::zoom1(){
    QPropertyAnimation* animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置缓和曲线，QEasingCurve::OutBounce 为弹跳效果
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();

}
void MyPushButton::zoom2(){
    QPropertyAnimation* animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置缓和曲线，QEasingCurve::OutBounce 为弹跳效果
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

void MyPushButton::mousePressEvent(QMouseEvent* event){
    if(this->pressImgPath!=""){
        QPixmap pixmap;
        bool ret = pixmap.load(this->pressImgPath);
        if(!ret){
            qDebug()<<"圖片加載失敗";
        }

        this->setFixedSize(pixmap.width(),pixmap.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    }
    //交給父類執行點擊事件
    return QPushButton::mousePressEvent(event);
}
void MyPushButton::mouseReleaseEvent(QMouseEvent* event){
    if(this->pressImgPath!=""){
        QPixmap pixmap;
        bool ret = pixmap.load(this->normalImgPath);
        if(!ret){
            qDebug()<<"圖片加載失敗";
        }

        this->setFixedSize(pixmap.width(),pixmap.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    }
    //交給父類執行釋放事件
    return QPushButton::mouseReleaseEvent(event);
}
