#include "Application.h"

#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <time.h>


int main()
{
	srand((unsigned int)time(NULL));

	try
	{
		Application app;
		app.run();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}

	return(EXIT_SUCCESS);
}
