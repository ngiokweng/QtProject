#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "Snake.h"
#include "Food.h"
#include <QSlider>

#define MAP_WIDTH 800
#define MAP_HEIGHT 600
#define CTRL_AREA 400

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void initGame(); //初始化遊戲區
    void initCtrl(); //初始化控制區
protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

    Snake* snake;
    Food* food;
    int score = 0; //分數
    QTimer* timer; //控制蛇移動的定時器
    bool bugFlag = false; //用于解决操控过快导致撞死自己的bug的标志
    int speed = 100; //速度
    QSlider* speedCtrl = NULL; //控制速度的拉動條
    bool playFlag = false; //true:遊玩中

    int r = 0,g = 0,b = 0; //蛇顏色
    int count = 0;  //限制蛇顏色轉變速度

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
