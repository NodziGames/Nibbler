#pragma once

#include <iostream>

class maxMin
{
	public:

		maxMin();
		virtual ~maxMin();

		virtual int    newMin(int a, int b);
		virtual int    newMax(int a, int b);

		virtual void   printSomething();

	private:

};