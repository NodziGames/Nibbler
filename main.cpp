#include <dlfcn.h>
#include <iostream>
#include <unistd.h>
#include "snek.hpp"
#include "global.hpp"
#include "Imain.hpp"
#include <vector>
#include <cmath>

#define MENU 1
#define GAME 2
#define GAMEOVER 3
#define ENTERKEY 10
#define ESCAPEKEY 27
#define DIGITKEY_1 49
#define DIGITKEY_2 50
#define DIGITKEY_3 51
#define KEY_LEFT 0404
#define KEY_RIGHT 0405
#define KEY_UP 0403
#define KEY_DOWN 0402

Global global;

void *handle = dlopen("red.so", RTLD_NOW | RTLD_LOCAL);

void init()
{
	//Reset Variables
	global.t = 0;
	global.xdir = 2;
	global.dir = 2;
	global.ate = false;
	global.score = 0;
	global.quit = false;

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

void playerinput(Imain *renderState)
{
	switch(renderState->getkey())
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
		case ESCAPEKEY:
			global.quit = true;
			break ;
		case ENTERKEY:
			if (global.state == MENU)
			{
				init();
				global.state = GAME;
			}
			else if (global.state == GAMEOVER)
				global.state = MENU;
			break ;
		case DIGITKEY_1:
			if (handle)
				dlclose(handle);
			handle = dlopen("red.so", RTLD_NOW | RTLD_LAZY);
			if (!handle)
				global.quit = true;
			break ;
		case DIGITKEY_2:
			if (handle)
				dlclose(handle);
			handle = dlopen("green.so", RTLD_NOW | RTLD_LAZY);
			if (!handle)
				global.quit = true;
			break ;
		case DIGITKEY_3:
			if (handle)
				dlclose(handle);
			handle = dlopen("blue.so", RTLD_NOW | RTLD_LAZY);
			if (!handle)
				global.quit = true;
			break ;
	}
}

//Main update, calls other updates
void update()
{
	global.t += 1;
	//Eat

	if (global.state == GAME)
	{
		if (global.ate == true)
		{
			global.score += 1;
			global.ate = false;
			global.snek.push_back(SnakePart(global.snek[global.snek.size() - 1].x, global.snek[global.snek.size() - 1].y));
			global.t += 8;
		}

		if (global.t % (std::max(200 - (global.score * 7), 20)) == 0)
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
			//Eat Le Froot
			if (global.t % (std::max(200 - (global.score * 7), 20)) == 0)
			{
				if ((global.snek[0].x == global.foodx) && (global.snek[0].y == global.foody))
				{
					global.foodx = (rand() % (global.max_x - 2)) + 1;
					global.foody = (rand() % (global.max_y - 2)) + 1;
					global.ate = true;
				}
			}
		}
	}
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
	if (global.max_x < 10 || global.max_y < 10 || global.max_x > 100 || global.max_y > 50)
	{
		std::cout << "Playfield Size Must Be Between 10x10 and 100x50!" << std::endl;
		return (0);
	}
	// Initialize to default library
	Imain *renderState;
	Imain *(*createRenderState)();
	void (*destroyRenderState)(Imain *);
	if (!handle)
	{
		std::cout << "Library not found." << std::endl;
		return (0);
	}
	
	createRenderState = (Imain *(*)())dlsym(handle, "createRenderState");
	destroyRenderState = (void (*)(Imain *))dlsym(handle,"destroyRenderState");
	renderState = createRenderState();
	
	renderState->initgame();
	while (!global.quit)
	{
		if (handle)
		{
			createRenderState = (Imain *(*)())dlsym(handle, "createRenderState");
			destroyRenderState = (void (*)(Imain *))dlsym(handle, "deleteRenderState");
			if (!createRenderState || !destroyRenderState)
			{
				std::cout << "States failed" << std::endl;
				return (0);
			}
			renderState = createRenderState();
			if (renderState->checkscreen(global, win_x, win_y))
			{
				update();
				renderState->render(global);
			}
			playerinput(renderState);
			usleep(1000);
		}
	}
	global.snek.clear();
	if (handle)
	{
		renderState->endgame();
		destroyRenderState(renderState);
		dlclose(handle);
	}
	system("clear");
	return (0);
}
