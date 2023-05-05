// Header(s) //
#pragma once
#include "raylib.h"
#include <string>

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
	static const int windowWidth = 768;
	static const int windowHeight = 576;

	static const int targetFPS = 60;
	const char* windowTitle = "Pong Prototype";

	static const bool enableFullScreen = false;
	static const bool enableAudio = true;

	static const bool canDebug = false;

	// Global Variable(s) / Value(s) //
	enum CoreState { Intro = 1, Title = 2, Game = 3 };
	enum TitleState { Main = 1, Options = 2, Credits = 3 };
};