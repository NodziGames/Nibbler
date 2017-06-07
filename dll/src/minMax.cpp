#include "../includes/minMax.hpp"

#include <iostream>

extern "C" maxMin *create_obj()
{
	return (new maxMin);
}

extern "C" void destroy_obj(maxMin *object)
{
	delete object;
}

maxMin::maxMin()
{
	return ;
}

maxMin::~maxMin()
{
	return ;
}

int maxMin::newMin(int a, int b)
{
	return ((a < b) ? a : b);
}

int maxMin::newMax(int a, int b)
{
	return ((a > b) ? a : b);
}

void maxMin::printSomething()
{
	std::cout << "This is something!" << std::endl;
}