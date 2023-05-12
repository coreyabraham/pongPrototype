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

	// Original Resolution: 768 x 576
	static const int windowWidth = 800;
	static const int windowHeight = 800;

	static const int targetFPS = 60;
	const char* windowTitle = "Pong Prototype";
	const char* buildInfo = "Build 0.0.1";

	static const bool enableFullScreen = false;
	static const bool enableAudio = true;
	static const bool canDebug = true;

	// Global Variable(s) / Value(s) //
	enum CoreState { Intro = 1, Title = 2, Game = 3, None = 4 };
	enum TitleState { Main = 1, Modes = 2, Options = 3, Credits = 4, Empty = 5 };
	enum GameState { Generic = 1, Solo = 2, Null = 3 };
};