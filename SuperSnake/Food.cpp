#include "Food.h"
#include <QTime>
#include <time.h>
#include "Snake.h"


Food::Food(int foodSize):foodSize(foodSize)
{

    coordinate.x = -1;
    coordinate.y = -1;
    qsrand(time(NULL));
}

void Food::createFood(int map_row,int map_col,vector<Point> snakeCoords){

    int foodX = qrand()%map_col*foodSize;
    int foodY = qrand()%map_row*foodSize;
    // 防止將食物生成在上一個位置
    while(foodX == coordinate.x && foodY == coordinate.y){
        foodX =  qrand()%map_col*foodSize;
        foodY = qrand()%map_row*foodSize;
    }
    //防止食物生成在蛇身上
    while(1){
        bool flag = true;
        for(auto& e:snakeCoords){
            if(e.x == foodX && e.y == foodY){
                foodX =  qrand()%map_col*foodSize;
                foodY = qrand()%map_row*foodSize;
                flag = false;
                break;
            }
        }
        if(flag)break;
    }

    coordinate.x = foodX;
    coordinate.y = foodY;

}

//返回食物座標
Point Food::getCoor()const{
    return this->coordinate;
}
