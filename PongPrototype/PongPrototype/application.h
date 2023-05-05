// Header(s) //
#pragma once
#include "raylib.h"

// Class(es) //
class Application
{
public:
	Application();
	~Application();

	void Run();

private:
	void Load();
	void Unload();
	
	void Update(float deltaTime);
	void Draw();

public:
	static const int windowWidth = 768;
	static const int windowHeight = 576;

	static const int targetFPS = 120;
	const char* windowTitle = "Pong Prototype";
	static const bool enableFullScreen = false;

	static const bool canDebug = true;
};