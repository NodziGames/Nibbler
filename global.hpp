#pragma once
#include "snek.hpp"
#include <iostream>
#include <vector>

class Global
{
    public:
        Global();
        ~Global();

        int state;
        unsigned long t;
        int xdir; //Temp Dir
        int dir; //0 = right, 2 = left, 1 = up, 3 = down
        int score;
        int max_x;
        int max_y;
        int foodx;
        int foody;
        bool ate;
        std::vector<SnakePart> snek;
};

void rendergame(Global global);
void rendermenu(Global global);
void rendergameover(Global global);