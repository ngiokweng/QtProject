#include "Food.h"
#include "stdlib.h"
#include "widget.h"


Food::Food(Snake* snake)
{
    this->x = (rand()%(MAP_WIDTH/snake->size))*snake->size;
    this->y = (rand()%(MAP_HEIGHT/snake->size))*snake->size;
}
