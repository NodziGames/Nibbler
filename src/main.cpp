#include "minMax.hpp"
#include <dlfcn.h>
#include <iostream>

int main()
{
	void *handle = dlopen("../MinMax.so", RTLD_LAZY);

	if (!handle)
	{
		std::cout << "Failed to open library" << std::endl;
		return (1);
	}

	maxMin *(*create)();
	void (*destroy)(maxMin*);

	create = (maxMin * (*)())dlsym(handle, "create_obj");
	destroy = (void (*) (maxMin *))dlsym(handle, "destroy_obj");
	std::cout << "Wut" << std::endl;
	maxMin *maxmin = create();
	std::cout << "the" << std::endl;
	maxmin->printSomething();

	std::cout << "fuck" << std::endl;

	std::cout << "Successfully opened the library" << std::endl;
	destroy(maxmin);
	return (0);
}