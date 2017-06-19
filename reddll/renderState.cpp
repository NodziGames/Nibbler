#include "renderState.hpp"

extern "C" Imain        *createRenderState()
{
	return (new RenderState);
}

extern "C" void         deleteRenderState(Imain *renderState)
{
	delete renderState;
}

RenderState::RenderState()
{
	return ;
}

RenderState::~RenderState()
{
	return ;
}

void		RenderState::initgame()
{
	initscr();
	start_color();
    noecho();
    curs_set(FALSE);
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
}

void        RenderState::endgame()
{
    endwin();
}

int			RenderState::checkscreen(Global global, int win_x, int win_y)
{
	getmaxyx(stdscr, win_y, win_x);
    if (win_x < global.max_x + 14 || win_y < global.max_y + 10)
    {
        clear();
        mvprintw(1,1,"Screen too small!");
        usleep(1000);
        return (0);
    }
    return (1);
}

void		RenderState::render(Global global)
{
	clear();
	init_pair(1, COLOR_WHITE, COLOR_RED);
	bkgd(COLOR_PAIR(1));
    if (global.state == MENU) {this->renderMenu(global);}
    if (global.state == GAME) {this->renderGame(global);}
    if (global.state == GAMEOVER) {this->renderGameOver(global);}
    refresh();
}

void		RenderState::renderGame(Global global)
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

void		RenderState::renderMenu(Global global)
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

void		RenderState::renderGameOver(Global global)
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

int		    RenderState::getkey() const
{
	return (getch());
}
