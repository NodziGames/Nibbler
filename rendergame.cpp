#include "global.hpp"
#include "snek.hpp"
#include <curses.h>

void rendergame(Global global)
{
    for (size_t i = 0; i < global.snek.size(); i++)
    {
        if (i != 0)
        {
            mvprintw(global.snek[i].y, global.snek[i].x, "O");
        }
        else
        {
            mvprintw(global.snek[i].y, global.snek[i].x, "@");
        }
    }
    mvprintw(global.foody, global.foodx, "*");
    mvprintw(global.max_y + 2, 1, "Score: %d", global.score);
    //Render Map Borders
    for (int y = 0; y < global.max_y; y++)
    {
        mvprintw(y, 0, "#");
        mvprintw(y, global.max_x - 1, "#");
    }
    for (int x = 0; x < global.max_x; x++)
    {
        mvprintw(0, x, "#");
        mvprintw(global.max_y - 1, x, "#");
    }
}