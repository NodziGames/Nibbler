#pragma once

#include "global.hpp"

class Imain
{
	public:
		Imain();
		//Imain(Imain const & src);
		virtual ~Imain();

		virtual void		initgame()=0;
		virtual void		endgame()=0;
		virtual int			checkscreen(Global global, int win_x, int win_y)=0;
		virtual void		render(Global global)=0;
		virtual int			getkey() const =0;
};