// Header(s) //
#include "states.h"
#include <string>

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
		SetMasterVolume(0.5f);
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
	//modifyTitleState(Main);
	loadLocalData();
}

void Application::Unload()
{
	// Add Data Here!
}

void Application::Update(float deltaTime)
{
	updateCoreState();
	updateTitleState();
	updateGameState();
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
	drawGameState();

	EndDrawing();
}