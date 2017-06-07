#include "minMax.hpp"
#include <dlfcn.h>
#include <iostream>

int main()
{
	void *handle = dlopen("MinMax.so", RTLD_LAZY);

	if (!handle)
	{
		std::cout << "Failed to open library" << std::endl;
		return (1);
	}

	maxMin *(*create)();
	void (*destroy)(maxMin*);

	create = (maxMin * (*)())dlsym(handle, "create_obj");
	destroy = (void (*) (maxMin *))dlsym(handle, "destroy_obj");
	maxMin *maxmin = create();
	maxmin->printSomething();
	destroy(maxmin);
	return (0);
}