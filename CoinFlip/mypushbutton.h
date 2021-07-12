#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //normalImg 代表正常显示的图片
    //pressImg  代表按下后显示的图片，默认为空
     MyPushButton(QString normalImg,QString pressImg = "");

     void zoom1();
     void zoom2();

     //重寫鼠標點擊和釋放
     void mousePressEvent(QMouseEvent* event);
     void mouseReleaseEvent(QMouseEvent* event);


     QString normalImgPath;
     QString pressImgPath;
signals:

};

#endif // MYPUSHBUTTON_H
