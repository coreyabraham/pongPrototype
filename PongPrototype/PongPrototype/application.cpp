// Header(s) //
#include "application.h"
#include "raylib.h"

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
	// Loadables go here!
}

void Application::Unload()
{
	// Unloadables go here!
}

void Application::Update(float deltaTime)
{

}

void Application::Draw()
{
	BeginDrawing();
	ClearBackground(BEIGE);

	if (canDebug)
	{
		DrawFPS(10, 10);
	}

	Vector2 textPos = {20, GetScreenHeight() - 40};
	DrawText("Drawing Test Text", textPos.x, textPos.y, 20, BLUE);

	EndDrawing();
}