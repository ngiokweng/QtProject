#include "MapScene.h"
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <vector>


MapScene::MapScene(QWidget *parent,int row,int col,Snake* snake,int speed) : QMainWindow(parent),row(row),col(col),snake(snake),speed(speed)
{
    this->setFixedSize(col*snake->getSize(),row*snake->getSize());
    this->setWindowTitle("【SuperSnake】遊戲界面");
    this->initMap();

    connect(gameTimer,&QTimer::timeout,[=](){
        snake->move();
        moveFlag = true; //表示上一次的【方向指令】已執行完成，可以接收下一個【方向指令】
        update();
    });

    //for test
    QPushButton* startGameBtn = new QPushButton("點擊後開始遊戲",this);
    startGameBtn->setFont(QFont("Adobe 楷体 Std R",20));
    startGameBtn->adjustSize();
    startGameBtn->move(col*snake->getSize()/2-startGameBtn->width()/2,row*snake->getSize()/2-startGameBtn->height()/2);
    connect(startGameBtn,&QPushButton::clicked,[=](){
        gameTimer->start();

    });

}

// 畫蛇的函數
void MapScene::drawSnake(std::vector<Point>& snakeCoords,int snakeNum,int snakeSize){
    //設置畫家各項屬性
    QPainter painter(this);
    painter.setPen(QColor(Qt::red));
    //畫蛇
    for(int i = 0;i<snakeNum;i++){
        painter.drawRect(snakeCoords[i].x,snakeCoords[i].y,snakeSize,snakeSize);
    }
}

//畫食物的函數
void MapScene::drawFood(int snakeSize){
    //設置畫家各項屬性
    QPainter painter(this);
    painter.setPen(QColor(Qt::blue));
    Point foodCoor = food->getCoor();
    painter.drawEllipse(foodCoor.x,foodCoor.y,snakeSize,snakeSize);
}

// 繪圖事件
void MapScene::paintEvent(QPaintEvent* event){


    std::vector<Point> snakeCoords = snake->getCoords();
    Point foodCoord = food->getCoor();
    int snakeSize = snake->getSize();

    //檢查蛇頭有沒有吃到食物
    if(snakeCoords[0].x == foodCoord.x && snakeCoords[0].y == foodCoord.y){

        snake->addNum();
        food->createFood(this->row,this->col);
    }
    int snakeNum = snake->getNum();

    //檢查蛇有無超出邊界
    if(snakeCoords[0].x<0 || snakeCoords[0].x>=this->col*snakeSize || snakeCoords[0].y<0 || snakeCoords[0].y>=this->row*snakeSize ){
        gameTimer->stop();
        /* 注：QMessageBox要放在initMap()的下面，因為它是模態對話框，會阻塞進程，從而導致一些bug */
        this->initMap();
        QMessageBox::information(this,"GG","Game Over！！");
        return;

    }
    //檢查有沒有碰到自己
    for(int i = 1;i < snakeNum;i++){
        if(snakeCoords[0].x == snakeCoords[i].x && snakeCoords[0].y == snakeCoords[i].y ){
            gameTimer->stop();
            /* 注：QMessageBox要放在initMap()的下面，因為它是模態對話框，會阻塞進程，從而導致一些bug */
            this->initMap();
            QMessageBox::information(this,"GG","Game Over！！");
            return;
        }
    }


    drawFood(snakeSize);
    drawSnake(snakeCoords,snakeNum,snakeSize);
}

// 通過 wasd 改變蛇的方向
void MapScene::changeSnakeDir(QKeyEvent* event){
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

//鍵盤點擊事件
void MapScene::keyPressEvent(QKeyEvent* event){
    //當moveFlag為false時，代表上一次發出的【方向指令】還在使用中，故直接return，防止有bug
    if(!moveFlag)return;
    changeSnakeDir(event);

}

void MapScene::initMap(){

    //設置定時器
    if(!gameTimer)gameTimer = new QTimer(this);
    gameTimer->setInterval(speed);

    //初始化食物對象
    if(!food)food = new Food(snake->getSize());
    food->createFood(this->row,this->col);

    //初始化蛇
    snake->init();



}

MapScene::~MapScene(){
    //因為food沒有加入到【對象樹】中，所以要手動釋放
    if(food!=nullptr){
        delete food;
        food = nullptr;
    }
}
