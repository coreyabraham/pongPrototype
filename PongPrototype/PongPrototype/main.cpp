// Header(s) //
#include "application.h"

// Function(s) //
int main(int argc, char* argv[])
{
	Application app;
	bool runGame = true;

	if (argc > 1)
	{
		for (int i = 1; i < argc; ++i)
		{
			//std::cout << argv[i] << " | " << i << std::endl;

			if (argv[i] == std::string("version"))
			{
				std::cout << "Version: " << app.buildInfo << std::endl;
				runGame = false;
			}
		}
	}

	if (runGame)
	{
		app.Run();
	}
}