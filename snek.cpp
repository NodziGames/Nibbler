#include "snek.hpp"

SnakePart::SnakePart()
{
	this->x = 0;
	this->y = 0;
	this->prevx = 0;
	this->prevy = 0;
	return ;
}

SnakePart::SnakePart(int s_x, int s_y)
{
	this->x = s_x;
	this->y = s_y;
	this->prevx = 0;
	this->prevy = 0;
}

SnakePart::SnakePart(SnakePart const & src)
{
	*this = src;
}

SnakePart::~SnakePart()
{
	return ;
}

SnakePart &       SnakePart::operator=(SnakePart const & rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->prevx = rhs.prevx;
	this->prevy = rhs.prevy;
	return (*this);
}