// Header(s) //
#include "application.h"

// Function(s) //
int main(int argc, char* argv[])
{
	Application app;

	bool runGame = true;
	bool attemptFullscreen = false;
	bool clearOutputAfterGame = false;

	if (argc > 1)
	{
		for (int i = 1; i < argc; ++i)
		{
			// Console Arguments //
			if (argv[i] == std::string("version"))
			{
				std::cout << "Build Version: " << app.buildInfo << std::endl;
				runGame = false;
			}

			if (argv[i] == std::string("postclear"))
				clearOutputAfterGame = true;

			if (argv[i] == std::string("preclear"))
				system("cls");

			// Raylib and or Project Arguments //
			if (argv[i] == std::string("enabledebug"))
				app.canDebug = true;

			if (argv[i] == std::string("disableaudio"))
				app.enableAudio = false;

			if (argv[i] == std::string("fullscreen"))
				attemptFullscreen = true;
		}
	}

	if (runGame)
	{
		if (attemptFullscreen)
		{
			int monitor = GetCurrentMonitor();
			int moniX = GetMonitorWidth(monitor);
			int moniY = GetMonitorHeight(monitor);

			if (app.windowWidth != moniX)
				app.windowWidth = moniX;

			if (app.windowHeight != moniY)
				app.windowHeight = moniY;

			app.enableFullScreen = true;
		}

		app.Run();

		if (clearOutputAfterGame)
			system("cls");
	}
}