// Header(s) //
#pragma once

#include "raylib.h"

#include <iostream>
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
	static const int targetFPS = 60;
	const char* windowTitle = "Pong Prototype";
	const char* buildInfo = "Build 0.0.1 - Debug";

	const float masterVolume = 0.5f;
	const float soundVolume = masterVolume;
	const float musicVolume = masterVolume / 2.0f;

	// Settings //
	int windowWidth = 1280;
	int windowHeight = 720;

	bool canDebug = false;
	bool enableFullScreen = false;
	bool enableAudio = true;
};