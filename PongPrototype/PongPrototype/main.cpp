// Header(s) //
#include "application.h"

using namespace std;

// Function(s) //
int main(int argc, char* argv[])
{
	Application app;

	bool runGame = true;
	bool clearOutputAfterGame = false;

	if (argc > 1)
	{
		for (int i = 1; i < argc; ++i)
		{
			//std::cout << argv[i] << " | " << i << std::endl;

			// Console Arguments //
			if (argv[i] == string("version"))
			{
				cout << "Version: " << app.buildInfo << endl;
				runGame = false;
			}

			if (argv[i] == string("preclear"))
				system("cls");

			if (argv[i] == string("postclear"))
				clearOutputAfterGame = true;

			// Raylib and or Project Arguments //
			if (argv[i] == string("enabledebug"))
				app.canDebug = true;

			if (argv[i] == string("disableaudio"))
				app.enableAudio = false;

			if (argv[i] == string("fullscreen"))
			{
				int monitor = GetCurrentMonitor();
				int moniX = GetMonitorWidth(monitor);
				int moniY = GetMonitorHeight(monitor);

				app.windowWidth = moniX;
				app.windowHeight = moniY;
				
				app.enableFullScreen = true;
			}
		}
	}

	if (runGame)
		app.Run();

	if (clearOutputAfterGame)
		system("cls");
}