#include <dlfcn.h>
#include <iostream>
int main()
{
	void *handle = dlopen("../minMaxLib.dylib", 1);

	if (!handle)
	{
		std::cout << "Failed to open library" << std::endl;
		return (0);
	}
	return (0);
}