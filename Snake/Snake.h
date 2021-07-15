#ifndef SNAKE_H
#define SNAKE_H

#define MAX_SNAKE_SIZE 256

//封裝一個坐標的結構體
struct Point{
    int x;
    int y;
};
//方向
enum Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT
};


//蛇類
class Snake{
public:
    Snake();
    void move();

public:
    int num; //蛇長
    int dir; //蛇頭方向
    int size; //一節蛇的大小
    Point coordinate[MAX_SNAKE_SIZE]; //蛇的坐標數組
};


#endif // SNAKE_H
