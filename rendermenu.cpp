#include "global.hpp"
#include "snek.hpp"
#include <curses.h>

void rendermenu(Global global)
{
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
    mvprintw(global.max_y + 1, 1, "Press Enter To Start!");

    //Ascii SNEK
    mvprintw(global.max_y + 3, 1,"--..,_                     _,.--.");
    mvprintw(global.max_y + 4, 1,"   `'.'.                .'`__ o  `;__.");
    mvprintw(global.max_y + 5, 1,"      '.'.            .'.'`  '---'`  `");
    mvprintw(global.max_y + 6, 1,"        '.`'--....--'`.'");
    mvprintw(global.max_y + 7, 1,"          `'--....--'`");
    mvprintw(global.max_y + 9, 1,"           BEST SNEK!");
}