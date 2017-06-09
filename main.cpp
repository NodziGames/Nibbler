#include <curses.h>
#include <iostream>
#include <unistd.h>
#include "snek.hpp"
#include "global.hpp"
#include <vector>
#include <cmath>

#define MENU 1
#define GAME 2
#define GAMEOVER 3
#define ENTERKEY 10

Global global;

void init()
{
    //Reset Variables
    global.t = 0;
    global.xdir = 2;
    global.dir = 2;
    global.ate = false;
    global.score = 0;

    //Init All 4 Default Snek Parts
    global.snek.clear(); //Clears Everything in vector to reset game
    global.snek.push_back(SnakePart(floor(global.max_x / 2) - 2, floor(global.max_y / 2)));
    global.snek.push_back(SnakePart(floor(global.max_x / 2) - 1, floor(global.max_y / 2)));
    global.snek.push_back(SnakePart(floor(global.max_x / 2), floor(global.max_y / 2)));
    global.snek.push_back(SnakePart(floor(global.max_x / 2) + 1, floor(global.max_y / 2)));

    //Place fud fer snek
    srand(time(NULL));
    global.foodx = (rand() % (global.max_x - 2)) + 1;
    global.foody = (rand() % (global.max_y - 2)) + 1;
}

void playerinput()
{
    switch(getch())
    {
        case KEY_LEFT:
            global.xdir = 2;
            break ;
        case KEY_RIGHT:
            global.xdir = 0;
            break ;
        case KEY_UP:
            global.xdir = 1;
            break ;
        case KEY_DOWN:
            global.xdir = 3;
            break ;
    }
}

//Main Render, calls other renders
void render()
{
    //clear();
    if (global.state == MENU) {rendermenu(global);}
    if (global.state == GAME) {rendergame(global);}
    if (global.state == GAMEOVER) {rendergameover(global);}
    refresh();
}

void updategameover()
{
    if (getch() == ENTERKEY)
    {
        global.state = MENU;
    }
}

void updatemenu()
{
    if (getch() == ENTERKEY)
    {
        global.state = GAME;
        init();
    }
}

void updategame()
{
    playerinput();

    //Eat
    if (global.ate == true)
    {
        global.score += 1;
        global.ate = false;
        global.snek.push_back(SnakePart(global.snek[global.snek.size() - 1].x, global.snek[global.snek.size() - 1].y));
        global.t += 8;
    }

    if (global.t % (200 - (global.score * 7)) == 0)
    {
        //Set Dir if Xdir is feasible
        if (global.xdir == 2 && global.dir != 0) {global.dir = 2;}
        if (global.xdir == 0 && global.dir != 2) {global.dir = 0;}
        if (global.xdir == 3 && global.dir != 1) {global.dir = 3;}
        if (global.xdir == 1 && global.dir != 3) {global.dir = 1;}

        //Move The Head First
        global.snek[0].prevx = global.snek[0].x; //We Store The Prev Positions of each part so that the next part in the body knows where it should move
        global.snek[0].prevy = global.snek[0].y;

        if (global.dir == 0) {global.snek[0].x += 1;}
        if (global.dir == 2) {global.snek[0].x -= 1;}
        if (global.dir == 1) {global.snek[0].y -= 1;}
        if (global.dir == 3) {global.snek[0].y += 1;}

        for (size_t i = 1; i < global.snek.size(); i++)
        {
            global.snek[i].prevx = global.snek[i].x;
            global.snek[i].prevy = global.snek[i].y;
            global.snek[i].x = global.snek[i - 1].prevx;
            global.snek[i].y = global.snek[i - 1].prevy;
        }
        if (global.snek[0].x < 1 || global.snek[0].x > global.max_x - 2 || global.snek[0].y < 1 || global.snek[0].y > global.max_y - 2)
        {
            global.state = GAMEOVER;
        }
        //Check if snake rams head up its own ass
        for (size_t i = 1; i < global.snek.size(); i++)
        {
            if (global.snek[0].x == global.snek[i].x && global.snek[0].y == global.snek[i].y)
            {
                global.state = GAMEOVER;
            }
        }
    }

    //Eat Le Froot
    if (global.t % (200 - (global.score * 7)) == 0)
    {
        if ((global.snek[0].x == global.foodx) && (global.snek[0].y == global.foody))
        {
            global.foodx = (rand() % (global.max_x - 2)) + 1;
            global.foody = (rand() % (global.max_y - 2)) + 1;
            global.ate = true;
        }
    }
}

//Main update, calls other updates
void update()
{
    global.t += 1;
    if (global.state == MENU) {updatemenu();}
    if (global.state == GAME) {updategame();}
    if (global.state == GAMEOVER) {updategameover();}
}

int     main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cout << "Please Define A Width And A Height For The Game" << std::endl;
        return (0);
    }
    global.state = MENU;
    int win_x = 0;
    int win_y = 0;
    global.max_x = atoi(argv[1]);
    global.max_y = atoi(argv[2]);
    if (global.max_x < 10 || global.max_y < 10 || global.max_x > 30 || global.max_y > 30)
    {
        std::cout << "Playfield Size Must Be Between 10x10 and 30x30!" << std::endl;
        return (0);
    }

    initscr();
    noecho();
    curs_set(FALSE);
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    while (1)
    {
        clear();
        getmaxyx(stdscr, win_y, win_x);
        if (win_x < global.max_x + 14 || win_y < global.max_y + 10)
        {
            mvprintw(1,1,"Screen too small!");
            usleep(1000);
        }
        else
        {
            update();
            render();
        }
        refresh();
        usleep(1000);
    }
    endwin();
    system("clear");
    return (0);
}