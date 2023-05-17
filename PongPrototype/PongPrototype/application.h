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
	// Configuration //
	static const int windowWidth = 1280;
	static const int windowHeight = 720;

	static const int targetFPS = 60;
	const char* windowTitle = "Pong Prototype";
	const char* buildInfo = "Build 0.0.1";

	static const bool enableFullScreen = false;
	static const bool enableAudio = true;
	static const bool canDebug = true;
};