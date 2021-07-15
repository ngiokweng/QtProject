#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QBrush>
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <time.h>
#include <stdlib.h>
#include <QMessageBox>
#include <QLabel>
#include <QPushButton>
#include <QSlider>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    srand(unsigned(time(NULL)));
    this->setFixedSize(MAP_WIDTH+CTRL_AREA,MAP_HEIGHT);
    timer = new QTimer(this);
    this->initGame();
    this->initCtrl();

    //連接蛇移動的定時器
    connect(timer,&QTimer::timeout,[=](){
        snake->move();
        //蛇頭碰到食物時
        if(snake->coordinate[0].x == food->x && snake->coordinate[0].y == food->y){
            //若食物與先前的位置相等，則重新設置
            int beforeX = food->x;
            int beforeY = food->y;
            do{
                food->x = (rand()%(MAP_WIDTH/snake->size))*snake->size;
                food->y = (rand()%(MAP_HEIGHT/snake->size))*snake->size;
            }while(food->x==beforeX && food->y==beforeY);

            score+=100;
            //蛇身變長
            snake->num++;
            //以下兩行代碼，若不加，可能會出現 "蛇的最後一格在(0,0)點瞬間出現又消失" 的情況
            snake->coordinate[snake->num-1].y = snake->coordinate[snake->num-2].y;
            snake->coordinate[snake->num-1].x = snake->coordinate[snake->num-2].x;

        }
        //判斷蛇頭有冇碰到自身
        for(int i=1;i<snake->num;i++){
            if(snake->coordinate[0].x == snake->coordinate[i].x && snake->coordinate[0].y == snake->coordinate[i].y){
                QMessageBox::information(this,"提示","你的得分為："+QString::number(score));
                initGame();
                timer->stop();
                playFlag = false;
            }
        }
        //判斷蛇頭有冇碰到邊界
        if(snake->coordinate[0].x >= MAP_WIDTH || snake->coordinate[0].x < 0 ||
           snake->coordinate[0].y >= MAP_HEIGHT || snake->coordinate[0].y < 0){
            QMessageBox::information(this,"提示","你的得分為："+QString::number(score));
            initGame();
            timer->stop();
            playFlag = false;
        }
        update();
    });

}
 //初始化遊戲區
void Widget::initGame(){
    //重置分數
    score = 0;
    //初始化出一條蛇
    delete snake;
    snake = NULL;
    snake = new Snake();
    //初始化食物，在地圖中隨機生成
    delete food;
    food = NULL;
    food = new Food(snake);
    //重置速度
    speed = 100;
}
 //初始化控制區
void Widget::initCtrl(){
    //開始按鈕
    QPushButton* startBtn = new QPushButton(this);
    startBtn->setGeometry(MAP_WIDTH+50,MAP_HEIGHT-80,100,60);
    startBtn->setText("開始遊戲");
    QFont font;
    font.setPixelSize(22);
    startBtn->setFont(font);
    //連接開始遊戲按鈕
    connect(startBtn,&QPushButton::clicked,[=](){
       if(playFlag){
           return;
       }
       playFlag = true;
       speed-=speedCtrl->value();
       timer->start(speed);
    });
    //暫停按鈕
    QPushButton* closeBtn = new QPushButton(this);
    closeBtn->setGeometry(MAP_WIDTH+250,MAP_HEIGHT-80,100,60);
    closeBtn->setText("暫停遊戲");
    closeBtn->setFont(font);
    connect(closeBtn,&QPushButton::clicked,[=](){
       playFlag = false;
       speed = 100;
       timer->stop();
    });
    //速度選擇
    speedCtrl = new QSlider(Qt::Horizontal,this);
    speedCtrl->setGeometry(MAP_WIDTH+90,300,230,30);

    QLabel* label = new QLabel("速度選擇(0~99)：",this);
    label->setFont(font);
    label->move(MAP_WIDTH+90,250);

}

void Widget::paintEvent(QPaintEvent *event){
     QPainter painter(this);
    //遊戲區與控制區的分界線
     painter.drawLine(MAP_WIDTH,0,MAP_WIDTH,MAP_HEIGHT);
     //畫分數
     QFont font;
     font.setPixelSize(30);
     painter.setFont(font);
     painter.drawText(MAP_WIDTH+90,50,"分數："+QString::number(this->score));


    //畫蛇
     //RGB的效果，以count限制顏色轉換速度
     if(count == 2){
         r = rand()%255;
         g = rand()%255;
         b = rand()%255;
         count = 0;
     }else{
         count++;
     }
     painter.setBrush(QBrush(QColor(r,g,b)));
    //去除邊框
    painter.setPen(QColor(0,0,0,0));

    for(int i=0;i<snake->num;i++){
        int posX = snake->coordinate[i].x;
        int posY = snake->coordinate[i].y;
        if(i==0){
            painter.drawEllipse(posX,posY,snake->size,snake->size);
        }else{
            painter.drawRect(posX,posY,snake->size,snake->size);
        }
    }
    bugFlag = false;    //在畫出蛇後將標誌變假
    //畫食物
    painter.setBrush(QBrush(Qt::red));
    painter.drawEllipse(food->x,food->y,snake->size,snake->size);
}

void Widget::keyPressEvent(QKeyEvent *event){
        //w a s d == 87 65 83 68
        if(bugFlag){
            return;
        }
        switch (event->key()) {
        case 87:
            if(snake->dir!=DOWN)snake->dir=UP;
            bugFlag = true;
            break;
        case 83:
            if(snake->dir!=UP)snake->dir=DOWN;
             bugFlag = true;
            break;
        case 65:
            if(snake->dir!=RIGHT)snake->dir=LEFT;
            bugFlag = true;
            break;
        case 68:
            if(snake->dir!=LEFT)snake->dir=RIGHT;
            bugFlag = true;
            break;

        }
}


Widget::~Widget()
{
    delete ui;
    delete snake;
    delete food;
}

