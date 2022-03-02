#ifndef MAPSCENE_H
#define MAPSCENE_H

#include <QMainWindow>
#include "Snake.h"
#include <QTimer>
#include <QKeyEvent>

class MapScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit MapScene(QWidget *parent = nullptr,int row = 50,int col = 30,Snake* snake = nullptr);
    ~MapScene();
    void initMap(); //初始化地圖
protected:
    void paintEvent(QPaintEvent* event);  //繪圖事件
    void keyPressEvent(QKeyEvent* event); //鍵盤點擊事件

private:
    int row; //地圖的行數
    int col; //地圖的列數
    Snake* snake;
    QTimer* gameTimer; //控制遊戲開始、暫停的定時器
    bool moveFlag = true;  //防止玩家操作太快，同時轉了兩個方向所導致的【蛇回頭】



};

#endif // MAPSCENE_H
