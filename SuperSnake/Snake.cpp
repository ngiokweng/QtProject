#include "Snake.h"

Snake::Snake(int snakeNum,int snakeSize):s_num(snakeNum),s_size(snakeSize)
{
    /* 初始化蛇的座標 */
    for(int i = 0;i<s_num;i++){
        //定義coordinate[0]為蛇頭
        coordinates[i].y = 0;
        coordinates[s_num - i -1].x = i*s_size;
    }
    //默認方向：右
    dir = DOWN;

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
Point* Snake::getCoords(){
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
void Snake::setDir(int dir){
    this->dir = dir;
}
//獲取蛇當前的運動方向
int Snake::getDir(){
    return this->dir;
}
