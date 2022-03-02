#include "MapScene.h"
#include <QDebug>
#include <QPainter>


MapScene::MapScene(QWidget *parent,int row,int col,Snake* snake) : QMainWindow(parent),row(row),col(col),snake(snake)
{
    this->initMap();
}

// 繪圖事件
void MapScene::paintEvent(QPaintEvent* event){

    Point* snakeCoords = snake->getCoords();
    int snakeNum = snake->getNum();
    int snakeSize = snake->getSize();
    QPainter painter(this);
    painter.setPen(QColor(Qt::red));

    qDebug()<<snakeSize<<" "<<snakeNum<<endl;

    for(int i = 0;i<snakeNum;i++){
//        qDebug()<<snakeCoords[i].x<<" "<<snakeCoords[i].y<<endl;
        painter.drawRect(snakeCoords[i].x,snakeCoords[i].y,snakeSize,snakeSize);
    }
}
//鍵盤點擊事件
void MapScene::keyPressEvent(QKeyEvent* event){
    //當moveFlag為false時，代表上一次發出的【方向指令】還在使用中，故直接return，防止有bug
    if(!moveFlag)return;

    // wasd->上下左右
    //通過wasd改變蛇的運動方向
    int snakeDir = snake->getDir();
    switch(event->key()){
        case Qt::Key_W:
            if(snakeDir!=DOWN){
                snake->setDir(UP);
                moveFlag = false;
                break;
            }
        case Qt::Key_A:
            if(snakeDir!=RIGHT){
                snake->setDir(LEFT);
                moveFlag = false;
                break;
            }
        case Qt::Key_S:
            if(snakeDir!=UP){
                snake->setDir(DOWN);
                moveFlag = false;
                break;
            }
        case Qt::Key_D:
            if(snakeDir!=LEFT){
                snake->setDir(RIGHT);
                moveFlag = false;
                break;
            }

    }
}

void MapScene::initMap(){
//    this->snake = new Snake(5,50);

    this->setFixedSize(col*snake->getSize(),row*snake->getSize());
    this->setWindowTitle("【SuperSnake】遊戲界面");

    //設置定時器
    this->gameTimer = new QTimer(this);
    gameTimer->setInterval(40);
    gameTimer->start();
    connect(gameTimer,&QTimer::timeout,[=](){
        snake->move();
        moveFlag = true; //表示上一次的【方向指令】已執行完成，可以接收下一個【方向指令】
        update();
    });

}

MapScene::~MapScene(){
//    delete this->snake;
}
