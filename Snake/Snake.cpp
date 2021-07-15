#include "Snake.h"
#include <QDebug>


Snake::Snake(){
    size = 20;
    dir = RIGHT;
    num = 3;

    //初始化蛇的坐標位置
    for(int i=0;i<num;i++){
        coordinate[i].y = 0;
        coordinate[num-i-1].x = size*i;
    }

}

void Snake::move(){
    switch (this->dir) {
        case UP:{
            for(int i=0;i<this->num-1;i++){
                this->coordinate[this->num-i-1].y = this->coordinate[this->num-i-2].y;
                this->coordinate[this->num-i-1].x = this->coordinate[this->num-i-2].x;
            }
            this->coordinate[0].y-=this->size;
            break;
        }
        case DOWN:{
            for(int i=0;i<this->num-1;i++){
                this->coordinate[this->num-i-1].y = this->coordinate[this->num-i-2].y;
                this->coordinate[this->num-i-1].x = this->coordinate[this->num-i-2].x;
            }
            this->coordinate[0].y+=this->size;
            break;
        }
        case LEFT:{
            for(int i=0;i<this->num-1;i++){
                this->coordinate[this->num-i-1].x = this->coordinate[this->num-i-2].x;
                this->coordinate[this->num-i-1].y = this->coordinate[this->num-i-2].y;
            }
            this->coordinate[0].x-=this->size;
            break;
        }
        case RIGHT:{
            for(int i=0;i<this->num-1;i++){
                this->coordinate[this->num-i-1].x = this->coordinate[this->num-i-2].x;
                this->coordinate[this->num-i-1].y = this->coordinate[this->num-i-2].y;
            }
            this->coordinate[0].x+=this->size;
            break;
        }
    }
}
