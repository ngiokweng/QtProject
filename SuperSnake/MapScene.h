#ifndef MAPSCENE_H
#define MAPSCENE_H

#include "BaseScene.h"
#include "Snake.h"
#include <QTimer>
#include <QKeyEvent>
#include "Food.h"
#include <QPainter>
#include <QLabel>

class MapScene : public BaseScene
{
    Q_OBJECT
public:
    explicit MapScene(QWidget *parent = nullptr,int row = 50,int col = 30,Snake* snake = nullptr,int speed = 100);
    ~MapScene();
    void initMap(); //初始化地圖
    void drawSnake(QPainter& painter,std::vector<Point>& snakeCoords,int snakeNum,int snakeSize);
    void drawFood(QPainter& painter,int snakeSize);
    void changeSnakeDir(QKeyEvent* event);
    void initControlBar(int mapWidth,int mapHeight,int controlBarHeight); //初始化控制欄
    bool isSnakeDead(std::vector<Point>& snakeCoords,int& snakeSize,int& snakeNum); //檢查蛇的死活
    bool isSnakeEat(std::vector<Point>& snakeCoords,Point& foodCoord);  //判斷蛇有無進食
    bool updateRankList();  //更新本地排行榜
    bool updateRankList(QString url);  //更新網路排行榜

public slots:
    void onGameRunning();

signals:
    void backToSettingScene();

protected:
    void paintEvent(QPaintEvent* event);  //繪圖事件
    void keyPressEvent(QKeyEvent* event); //鍵盤點擊事件

private:
    int row; //地圖的行數
    int col; //地圖的列數
    Snake* snake = nullptr;
    QTimer* gameTimer = nullptr; //控制遊戲開始、暫停的定時器
    bool moveFlag = true;  //防止玩家操作太快，同時轉了兩個方向所導致的【蛇回頭】
    Food* food = nullptr;
    int speed; //蛇的速度
    int score = 0;  //分數
    QLabel* scoreLabel; //分數的Label

};

#endif // MAPSCENE_H
