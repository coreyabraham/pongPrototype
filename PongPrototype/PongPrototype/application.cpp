// Header(s) //
#include "application.h"
#include "states.h"

States StateManager;

// Class(es) //
Application::Application() {  }
Application::~Application() {  }

// Function(s) //
void Application::Run() 
{
	InitWindow(windowWidth, windowHeight, windowTitle);

	if (enableAudio)
	{
		InitAudioDevice();
		SetMasterVolume(masterVolume);
	}
	
	SetTargetFPS(targetFPS);

	if (enableFullScreen)
	{
		ToggleFullscreen();
	}

	Load();

	while (!WindowShouldClose())
	{
		Update(GetFrameTime());
		Draw();
	}

	Unload();
}

void Application::Load()
{
	StateManager.Init();
}

void Application::Unload()
{
	StateManager.Uninit();
}

void Application::Update(float deltaTime)
{
	StateManager.UpdateStates(deltaTime);
}

void Application::Draw()
{
	BeginDrawing();
	ClearBackground(BLACK);

	if (canDebug)
	{
		std::string strFPS = std::to_string(GetFPS());
		std::string strFPS2 = strFPS + " > Frames Per Second";

		char const* framesPerSecond = strFPS2.c_str();

		DrawText(framesPerSecond, 10, 10, 20, GREEN);
		
		std::string strFT = std::to_string(GetFrameTime());
		std::string strFT2 = strFT + " > Delta Time";

		char const* deltaTime = strFT2.c_str();
		
		DrawText(deltaTime, 10, 40, 20, BLUE);

		DrawText(buildInfo, 10, GetScreenHeight() - 20, 10, WHITE);
	}

	StateManager.DrawStates(canDebug);

	EndDrawing();
}