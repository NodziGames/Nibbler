#include "global.hpp"

Global::Global()
{
	this->quit = false;
	return ;
}

Global::Global(Global const & src)
{
	*this = src;
}

Global::~Global()
{
	return ;
}

Global &      Global::operator=(Global const & rhs)
{
	this->state = rhs.state;
	this->t = rhs.t;
	this->xdir = rhs.xdir;
	this->dir = rhs.dir;
	this->score = rhs.score;
	this->max_x = rhs.max_x;
	this->max_y = rhs.max_y;
	this->foodx = rhs.foodx;
	this->foody = rhs.foody;
	this->ate = rhs.ate;
	this->quit = rhs.quit;
	this->snek = rhs.snek;
	return (*this);
}