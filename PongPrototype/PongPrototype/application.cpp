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
	StateManager.UpdateStates();
}

void Application::Draw()
{
	BeginDrawing();
	ClearBackground(BLACK);

	if (canDebug)
	{
		DrawFPS(10, 10);
	}

	StateManager.DrawStates();

	EndDrawing();
}