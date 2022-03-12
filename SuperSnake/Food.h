#ifndef FOOD_H
#define FOOD_H

#include "Point.h"
#include <vector>

using std::vector;

class Food
{
public:
    Food(int foodSize);
    void createFood(int map_row,int map_col,vector<Point> snakeCoords); //創建食物
    Point getCoor(); //返回食物座標

private:
    Point coordinate;
    int foodSize;
};

#endif // FOOD_H
