#include "snek.hpp"

SnakePart::SnakePart(int s_x, int s_y)
{
    this->x = s_x;
    this->y = s_y;
    this->prevx = 0;
    this->prevy = 0;
}

SnakePart::~SnakePart()
{
    
}