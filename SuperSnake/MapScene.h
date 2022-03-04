#ifndef MAPSCENE_H
#define MAPSCENE_H

#include <QMainWindow>
#include "Snake.h"
#include <QTimer>
#include <QKeyEvent>
#include "Food.h"
#include <QPainter>

class MapScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit MapScene(QWidget *parent = nullptr,int row = 50,int col = 30,Snake* snake = nullptr);
    ~MapScene();
    void initMap(); //初始化地圖
    void drawSnake(std::vector<Point>& snakeCoords,int snakeNum,int snakeSize);
    void drawFood(int snakeSize);
    void changeSnakeDir(QKeyEvent* event);
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


};

#endif // MAPSCENE_H
