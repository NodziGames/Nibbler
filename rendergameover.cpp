#include "global.hpp"
#include "snek.hpp"
#include <curses.h>

void rendergameover(Global global)
{
    mvprintw(global.max_y + 2, 1, "Game Over!");
    mvprintw(global.max_y + 3, 1, "Final score: %3d", global.score);
    //Render Box
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