#include "MapScene.h"
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <vector>
#include <QPainter>


MapScene::MapScene(QWidget *parent,int row,int col,Snake* snake,int speed) : QMainWindow(parent),row(row),col(col),snake(snake),speed(speed)
{

    int mapWidth = col*snake->getSize(),mapHeight = row*snake->getSize();
    int controlBarHeight = 50;

    this->setFixedSize(mapWidth,mapHeight+controlBarHeight);
    this->setWindowTitle("【SuperSnake】遊戲界面");
    this->initControlBar(mapWidth,mapHeight,controlBarHeight); //初始化最底下的控制欄
    this->initMap();

    connect(gameTimer,&QTimer::timeout,this,&MapScene::onGameRunning);


}

void MapScene::onGameRunning(){
    snake->move();
    moveFlag = true; //表示上一次的【方向指令】已執行完成，可以接收下一個【方向指令】

    /*取得蛇的各項信息*/
    int snakeSize = snake->getSize();
    std::vector<Point> snakeCoords = snake->getCoords();
    Point foodCoord = food->getCoor();
    //獲取食物座標
    int snakeNum = snake->getNum();


    //判斷蛇有無吃東西
    if(isSnakeEat(snakeCoords,foodCoord)){
        snake->addNum();
        food->createFood(this->row,this->col);

        score+=100; //每食一個食物+100分
        scoreLabel->setText(QString("分數：%1").arg(score));
        scoreLabel->adjustSize(); //防止分數顯示不完全
    }
    //判斷蛇是否死亡
    if(isSnakeDead(snakeCoords,snakeSize,snakeNum)){
        gameTimer->stop();
        /* 注：QMessageBox要放在initMap()的下面，因為它是模態對話框，會阻塞進程，從而導致一些bug */
        this->initMap();
        QMessageBox::information(this,"GG","Game Over！！");
    }


    update(); //手動調用paintEvent
}

void MapScene::initControlBar(int mapWidth,int mapHeight,int controlBarHeight){
    //開始遊戲的按鈕
    QPushButton* startGameBtn = new QPushButton("開始遊戲",this);
    startGameBtn->setFont(QFont("Adobe 楷体 Std R",14));
    startGameBtn->adjustSize();
    startGameBtn->move(mapWidth*0.03,mapHeight+controlBarHeight/2-startGameBtn->height()/2);
    connect(startGameBtn,&QPushButton::clicked,[=](){
        gameTimer->start();

    });

    //暫停遊戲的按鈕
    QPushButton* pauseGameBtn = new QPushButton("暫停遊戲",this);
    pauseGameBtn->setFont(QFont("Adobe 楷体 Std R",14));
    pauseGameBtn->adjustSize();
    pauseGameBtn->move(mapWidth*0.05+startGameBtn->width()+10,mapHeight+controlBarHeight/2-pauseGameBtn->height()/2);
    connect(pauseGameBtn,&QPushButton::clicked,[=](){
        gameTimer->stop();

    });

    //返回的按鈕
    QPushButton* backBtn = new QPushButton("返回",this);
    backBtn->setFont(QFont("Adobe 楷体 Std R",14));
    backBtn->adjustSize();
    backBtn->move(mapWidth*0.95-backBtn->width(),mapHeight+controlBarHeight/2-backBtn->height()/2);
    connect(backBtn,&QPushButton::clicked,[=](){
        this->close();
        //發送返回【設定界面】的信號
        emit backToSettingScene();


    });

    scoreLabel = new QLabel("分數：0",this);
    scoreLabel->setFont(QFont("Adobe 楷体 Std R",14));
    scoreLabel->adjustSize();
    scoreLabel->move(mapWidth*0.05+startGameBtn->width()+pauseGameBtn->width()+20,mapHeight+controlBarHeight/2-scoreLabel->height()/2);
}

// 畫蛇的函數
void MapScene::drawSnake(QPainter& painter,std::vector<Point>& snakeCoords,int snakeNum,int snakeSize){
    //設置畫家各項屬性
    painter.setPen(QColor(Qt::red));
    //畫蛇
    for(int i = 0;i<snakeNum;i++){
        painter.drawRect(snakeCoords[i].x,snakeCoords[i].y,snakeSize,snakeSize);
    }
}

//畫食物的函數
void MapScene::drawFood(QPainter& painter,int snakeSize){
    //設置畫家各項屬性
    painter.setPen(QColor(Qt::blue));
    Point foodCoor = food->getCoor();
    painter.drawEllipse(foodCoor.x,foodCoor.y,snakeSize,snakeSize);
}

//判斷蛇是否死亡
bool MapScene::isSnakeDead(std::vector<Point>& snakeCoords,int& snakeSize,int& snakeNum){
    //檢查蛇有無超出邊界
    if(snakeCoords[0].x<0 || snakeCoords[0].x>=this->col*snakeSize || snakeCoords[0].y<0 || snakeCoords[0].y>=this->row*snakeSize )return true;
    //檢查有沒有碰到自己
    for(int i = 1;i < snakeNum;i++){
        if(snakeCoords[0].x == snakeCoords[i].x && snakeCoords[0].y == snakeCoords[i].y )return true;
    }
    return false;
}

//判斷蛇有無吃東西
bool MapScene::isSnakeEat(std::vector<Point>& snakeCoords,Point& foodCoord){
        //檢查蛇頭有沒有吃到食物
        if(snakeCoords[0].x == foodCoord.x && snakeCoords[0].y == foodCoord.y)return true;
        return false;
}

// 繪圖事件
void MapScene::paintEvent(QPaintEvent* event){

    QPainter painter(this);
    int snakeSize = snake->getSize();
    std::vector<Point> snakeCoords = snake->getCoords();
    int snakeNum = snake->getNum();

    //分隔線：分開遊戲區域和控制區域
    painter.drawLine(0,row*snakeSize,col*snakeSize,row*snakeSize);


    drawFood(painter,snakeSize);
    drawSnake(painter,snakeCoords,snakeNum,snakeSize);

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
            }
            break;
        case Qt::Key_A:
            if(snakeDir!=RIGHT){
                snake->setDir(LEFT);
                moveFlag = false;
            }
            break;
        case Qt::Key_S:
            if(snakeDir!=UP){
                snake->setDir(DOWN);
                moveFlag = false;
            }
            break;
        case Qt::Key_D:
            if(snakeDir!=LEFT){
                snake->setDir(RIGHT);
                moveFlag = false;
            }
            break;

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

    //重置分數
    score = 0;
    scoreLabel->setText(QString("分數：%1").arg(score));



}

MapScene::~MapScene(){
    //因為food沒有加入到【對象樹】中，所以要手動釋放
    if(food!=nullptr){
        delete food;
        food = nullptr;
    }

}
