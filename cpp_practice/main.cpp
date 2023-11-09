#include "Container.h"
#include "Object.h"

#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

int main()
{
	Equation a(1, 2, '+', "Sum");

	std::cout << a.toString();

	_CrtDumpMemoryLeaks();
	return 0;
}