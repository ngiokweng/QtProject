#include "Snake.h"
#include <time.h>
Snake::Snake(int snakeNum,int snakeSize):s_num(snakeNum),s_size(snakeSize)
{
    this->init();
}

void Snake::init(){
    srand(unsigned(time(0))); //亂數種

    //初始化長度
    s_num = 3;
    //清空座標數組
    coordinates.clear();
    coordinates.resize(s_num);
    /* 初始化蛇的座標 */
    for(int i = 0;i<s_num;i++){
        //定義coordinate[0]為蛇頭
        coordinates[i].y = 0;
        coordinates[s_num - i -1].x = i*s_size;
    }
    //默認方向：右
    dir = RIGHT;

    //隨機蛇的顏色
    snakeColor = QColor(rand()%256,rand()%256,rand()%256);
}

//獲取蛇的大小
int Snake::getSize(){
    return s_size;
}

//獲取蛇的節數
int Snake::getNum(){
    return s_num;
}
//獲取蛇的座標
vector<Point> Snake::getCoords(){
    return coordinates;
}

//讓蛇移動的函數
void Snake::move(){
    for(int i = s_num - 1;i>0;i--){
        coordinates[i].x = coordinates[i-1].x;
        coordinates[i].y = coordinates[i-1].y;
    }

    switch (dir) {

    case UP:{
        coordinates[0].y -= s_size;
        break;
    }
    case DOWN:{
        coordinates[0].y += s_size;
        break;
    }
    case LEFT:{
        coordinates[0].x -= s_size;
        break;
    }
    case RIGHT:{
        coordinates[0].x += s_size;

        break;
    }


    }
}
//設置蛇的方向
void Snake::setDir(direction dir){
    this->dir = dir;
}
//獲取蛇當前的運動方向
int Snake::getDir(){
    return this->dir;
}

//將蛇的長度加1
void Snake::addNum(){
    this->s_num++;
    Point loc;
    loc.x = -9999;
    loc.y = -9999;
    coordinates.push_back(loc);
}

QColor Snake::getSnakeColor(){
    return snakeColor;
}
void Snake::setSnakeColor(QColor color){
    snakeColor = color;
}
