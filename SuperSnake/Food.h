#ifndef FOOD_H
#define FOOD_H

#include "Point.h"

class Food
{
public:
    Food(int foodSize);
    void createFood(int map_row,int map_col); //創建食物
    Point getCoor(); //返回食物座標

private:
    Point coordinate;
    int foodSize;
};

#endif // FOOD_H
