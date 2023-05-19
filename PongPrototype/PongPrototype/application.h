// Header(s) //
#pragma once
#include "raylib.h"
#include <iostream>

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
	const char* buildInfo = "Build 0.0.1 - Debug";

	const float masterVolume = 0.5f;
	const float soundVolume = masterVolume;
	const float musicVolume = masterVolume / 2.0f;

	// Settings //
	bool canDebug = true;
	bool enableAudio = true;
	bool enableFullScreen = false;
};