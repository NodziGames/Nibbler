#pragma once

#include "../Imain.hpp"
#include "../global.hpp"
#include <curses.h>
#include <iostream>
#include <unistd.h>

#define MENU 1
#define GAME 2
#define GAMEOVER 3

class RenderState : public Imain
{
	public:
		RenderState();
		RenderState(RenderState const & src);
		virtual ~RenderState();

		//RenderState       operator=(RenderState const & rhs);

		void				initgame();
		void				endgame();
		int					checkscreen(Global global, int win_x, int win_y);
		void				render(Global global);
		void				renderGame(Global global);
		void				renderMenu(Global global);
		void				renderGameOver(Global global);
		int					getkey() const;
};
