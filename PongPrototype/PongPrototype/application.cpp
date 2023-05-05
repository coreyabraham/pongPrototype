// Header(s) //
#include "common.h"

// Class(es) //
Application::Application()
{

}

Application::~Application()
{

}

// Function(s) //
void Application::Run() 
{
	InitWindow(windowWidth, windowHeight, windowTitle);

	if (enableAudio)
	{
		InitAudioDevice();
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
	modifyCoreState(Intro);
}

void Application::Unload()
{
	// Add unloadables here!
}

void Application::Update(float deltaTime)
{
	updateCoreState();
	updateTitleState();
}

void Application::Draw()
{
	BeginDrawing();
	ClearBackground(BLACK);

	if (canDebug)
	{
		DrawFPS(10, 10);
	}

	drawCoreState();
	drawTitleState();

	EndDrawing();
}