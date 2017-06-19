#pragma once
#include "snek.hpp"
#include <iostream>
#include <vector>

class Global
{
    public:
        Global();
        Global(Global const & src);
        ~Global();

        Global &        operator=(Global const & rhs);

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
        bool quit;
        std::vector<SnakePart> snek;
};