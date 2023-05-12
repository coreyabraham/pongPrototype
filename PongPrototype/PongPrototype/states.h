// Header(s) //
#pragma once

#include <iostream>
#include "application.h"
#include "common.h"

// Value(s) //
// Intro
int logoPosX = floatToInt(Application::windowWidth / 2 - 128);
int logoPosY = floatToInt(Application::windowHeight / 2 - 128);

Color logoBorderColor = BLUE;
Color logoFillColor = SKYBLUE;
Color logoTextColor = WHITE;
const char* introText = "Monke";
bool introSoundPlayed = false;

// Variable(s) //
Application::CoreState currentCoreState;
Application::TitleState currentTitleState;
Application::GameState currentGameState;

int framesCounter = 0;
int lettersCount = 0;

int topSideRecWidth = 16;
int leftSideRecHeight = 16;

int bottomSideRecWidth = 16;
int rightSideRecHeight = 16;

int state = 0;
float alpha = 1.0f;

// Game - Generic
bool gameStarted = false;
int frameOnStart = 0;
int hideTextOnFrame = 100;

int leftScore = 0;
int rightScore = 0;

Player player1 = { 50.0f, KEY_W, KEY_S, KEY_SPACE, BLUE };
Player player2 = { 100.0f, KEY_UP, KEY_DOWN, KEY_RIGHT_CONTROL, RED };

// Button(s) //
// Shared
ClickButton returnBtn = { Vector2{ 20, Application::windowHeight - 90 }, Vector2{ 130, 40 }, "RETURN", RED, WHITE, true, 2.5f};

// "Main"
ClickButton playBtn = { Vector2{ 20, 200 }, Vector2{ 70, 40 }, "Play", BLACK, WHITE, true, 2.5f };
ClickButton optsBtn = { Vector2{ 20, 280 }, Vector2{ 120, 40 }, "Options", BLACK, WHITE, true, 2.5f };
ClickButton cdsBtn = { Vector2{ 20, 360 }, Vector2{ 120, 40 }, "Credits", BLACK, WHITE, true, 2.5f };
ClickButton exitBtn = { Vector2{ 20, 440 }, Vector2{ 70, 40 }, "Exit", BLACK, WHITE, true, 2.5f };

// "Modes"
ClickButton genBtn = { Vector2{ 20, 200 }, Vector2{ 210, 40 }, "Generic Mode", BLACK, WHITE, true, 2.5f };
ClickButton sglBtn = { Vector2{ 20, 280 }, Vector2{ 210, 40 }, "Singleplayer Mode", BLACK, WHITE, true, 2.5f };

Sound click;
Sound back;
Sound start;
Sound begin;
Sound error;
Sound onExit;

Music titleBGM;

// Core Function(s) //
void loadLocalData()
{
	click = LoadSound("resources\\audio\\click.wav");
	back = LoadSound("resources\\audio\\back.wav");
	start = LoadSound("resources\\audio\\start.wav");
	begin = LoadSound("resources\\audio\\begin.wav");
	error = LoadSound("resources\\audio\\error.wav");
	onExit = LoadSound("resources\\audio\\exit.wav");

	titleBGM = LoadMusicStream("resources\\audio\\titleBGM.mp3");
	SetMusicVolume(titleBGM, 0.25f);
}

void localUnloadData()
{
	UnloadSound(click);
	UnloadSound(back);
	UnloadSound(start);
	UnloadSound(begin);
	UnloadSound(error);
	UnloadSound(onExit);

	UnloadMusicStream(titleBGM);
}

void modifyCoreState(Application::CoreState state)
{
	currentCoreState = state;
}

void modifyTitleState(Application::TitleState state)
{
	currentTitleState = state;
}

void modifyGameState(Application::GameState state)
{
	currentGameState = state;
}

// Update Function(s)
void updateCoreState()
{
	switch (currentCoreState)
	{
		case Application::Intro:
			switch (state)
			{
				case 0:
					framesCounter++;

					if (framesCounter == 120)
					{
						state = 1;
						framesCounter = 0;
					}

					break;

				case 1:
					if (Application::enableAudio && !introSoundPlayed)
					{
						Sound introSfx = LoadSound("resources\\audio\\intro.wav");
						PlaySound(introSfx);
						introSoundPlayed = true;
					}

					topSideRecWidth += 4;
					leftSideRecHeight += 4;

					if (topSideRecWidth == 256)
					{
						state = 2;
					}

					break;

				case 2:
					bottomSideRecWidth += 4;
					rightSideRecHeight += 4;

					if (bottomSideRecWidth == 256)
					{
						state = 3;
					}

					break;

				case 3:
					framesCounter++;

					if (framesCounter / 12)
					{
						lettersCount++;
						framesCounter = 0;
					}

					if (lettersCount >= 10)
					{
						alpha -= 0.02f;

						if (alpha <= 0.0f)
						{
							alpha = 0.0f;
							state = 0;

							modifyCoreState(Application::Title);
							modifyTitleState(Application::Main);
						}
					}

					break;
			}

			if (Application::canDebug)
			{
				std::cout << "CurrentIntroState: " << state << std::endl;
				std::cout << "CurrentFrameCount: " << framesCounter << std::endl;
			}

			break;

		case Application::Title:
			if (!IsMusicStreamPlaying(titleBGM))
				PlayMusicStream(titleBGM);

			UpdateMusicStream(titleBGM);

			break;

		case Application::Game:
			// Add Data Here!
			
			break;
	}
}

void updateTitleState()
{
	switch (currentTitleState)
	{
	case Application::Main:
		playBtn.Update();
		optsBtn.Update();
		cdsBtn.Update();
		exitBtn.Update();

		if (playBtn.btnAction)
		{
			if (Application::enableAudio)
				PlaySound(click);

			modifyTitleState(Application::Modes);
		}

		if (optsBtn.btnAction)
		{
			if (Application::enableAudio)
				PlaySound(click);

			modifyTitleState(Application::Options);
		}

		if (cdsBtn.btnAction)
		{
			if (Application::enableAudio)
				PlaySound(click);

			modifyTitleState(Application::Credits);
		}

		if (exitBtn.btnAction)
		{
			if (Application::enableAudio)
			{
				PlaySound(onExit);
				SetWindowOpacity(0.0f);
				while (IsSoundPlaying(onExit)) { }
				CloseWindow();
			}
		}

		break;

	case Application::Modes:
		genBtn.Update();
		sglBtn.Update();
		returnBtn.Update();

		if (genBtn.btnAction)
		{
			if (Application::enableAudio)
				PlaySound(start);

			modifyCoreState(Application::Game);
			modifyTitleState(Application::Empty);
			modifyGameState(Application::Generic);
		}

		if (sglBtn.btnAction)
		{
			if (Application::enableAudio)
				PlaySound(start);

			modifyCoreState(Application::Game);
			modifyTitleState(Application::Empty);
			modifyGameState(Application::Solo);
		}

		if (returnBtn.btnAction)
		{
			if (Application::enableAudio)
				PlaySound(back);

			modifyTitleState(Application::Main);
		}

		break;

	case Application::Options:
		returnBtn.Update();

		if (returnBtn.btnAction)
		{
			if (Application::enableAudio)
				PlaySound(back);

			modifyTitleState(Application::Main);
		}

		break;

	case Application::Credits:
		returnBtn.Update();

		if (returnBtn.btnAction)
		{
			if (Application::enableAudio)
				PlaySound(back);

			modifyTitleState(Application::Main);
		}

		break;
	}
}

void updateGameState()
{
	switch (currentGameState)
	{
		case Application::Generic:
			if (!gameStarted && IsKeyPressed(KEY_ENTER))
			{
				gameStarted = true;
				PlaySound(begin);
			}

			if (gameStarted && IsKeyPressed(KEY_BACKSPACE))
			{
				PlaySound(error);

				player1.Reset();
				player2.Reset();
				// Clear Logic Here!

				modifyGameState(Application::Null);
				modifyCoreState(Application::Title);
				modifyTitleState(Application::Modes);
				
				gameStarted = false;
			}

			if (gameStarted)
			{
				player1.Update();
				player2.Update();
			}

			break;

		case Application::Solo:
			// Insert Execution Here!

			break;
	}
}

// Draw Function(s) //
void drawCoreState()
{
	switch (currentCoreState)
	{
	case Application::Intro:
		switch (state)
		{
			case 0:
				if ((framesCounter / 15) % 2)
				{
					DrawRectangle(logoPosX, logoPosY, 16, 16, logoBorderColor);
				}

				break;

			case 1:
				DrawRectangle(logoPosX, logoPosY, topSideRecWidth, 16, logoBorderColor);
				DrawRectangle(logoPosX, logoPosY, 16, leftSideRecHeight, logoBorderColor);

				break;

			case 2:
				DrawRectangle(logoPosX, logoPosY, topSideRecWidth, 16, logoBorderColor);
				DrawRectangle(logoPosX, logoPosY, 16, leftSideRecHeight, logoBorderColor);

				DrawRectangle(logoPosX + 240, logoPosY, 16, rightSideRecHeight, logoBorderColor);
				DrawRectangle(logoPosX, logoPosY + 240, bottomSideRecWidth, 16, logoBorderColor);

				break;

			case 3:
				DrawRectangle(logoPosX, logoPosY, topSideRecWidth, 16, Fade(logoBorderColor, alpha));
				DrawRectangle(logoPosX, logoPosY + 16, 16, leftSideRecHeight - 32, Fade(logoBorderColor, alpha));

				DrawRectangle(logoPosX + 240, logoPosY + 16, 16, rightSideRecHeight - 32, Fade(logoBorderColor, alpha));
				DrawRectangle(logoPosX, logoPosY + 240, bottomSideRecWidth, 16, Fade(logoBorderColor, alpha));

				DrawRectangle(GetScreenWidth() / 2 - 112, GetScreenHeight() / 2 - 112, 224, 224, Fade(logoFillColor, alpha));
				DrawText(TextSubtext(introText, 0, lettersCount), GetScreenWidth() / 2 - 88, GetScreenHeight() / 2 + 48, 50, Fade(logoTextColor, alpha));

				break;
		}

		break;
	case Application::Game:

		break;
	}
}

void drawTitleState()
{
	// Shared //
	const Vector2 pos = { 40, 20 };
	const int size = 40;
	const Color color = WHITE;
	const char* text = "";

	switch (currentTitleState)
	{
		case Application::Main:
			text = "Pong Prototype | Main Menu";
			break;

		case Application::Modes:
			text = "Pong Prototype | Gamemodes";
			break;

		case Application::Options:
			text = "Pong Prototype | Options";
			break;

		case Application::Credits:
			text = "Pong Prototype | Credits";
			break;
	}

	if (Application::canDebug)
	{
		Application app;
		DrawText(app.buildInfo, 10, GetScreenHeight() - 20, 10, WHITE);
	}

	DrawText(text, static_cast<int>(pos.x), static_cast<int>(pos.y), size, color);

	int genericTextScale = 20;

	// State-Specific //
	switch (currentTitleState)
	{
	case Application::Main:

		if (playBtn.btnHovering)
			playBtn.DrawOutline();

		if (optsBtn.btnHovering)
			optsBtn.DrawOutline();

		if (cdsBtn.btnHovering)
			cdsBtn.DrawOutline();

		if (exitBtn.btnHovering)
			exitBtn.DrawOutline();

		playBtn.Draw();
		optsBtn.Draw();
		cdsBtn.Draw();
		exitBtn.Draw();

		break;

	case Application::Modes:
		DrawText("Selectable Modes: ", (GetScreenWidth() / 2) / genericTextScale, 160, genericTextScale, color);
		
		DrawText(
			"> Your Generic (Standard) Pong Game, Requires Two Players to Play!", 
			(GetScreenWidth() / 2) / genericTextScale, 
			floatToInt(genBtn.coreButton.y) + genericTextScale * 2 + 5,
			genericTextScale, 
			color
		);

		DrawText(
			"> A Singleplayer Pong Game, bounce the ball against a wall and see how long you can go!",
			(GetScreenWidth() / 2) / genericTextScale,
			floatToInt(sglBtn.coreButton.y) + genericTextScale * 2 + 5,
			genericTextScale - 2,
			color
		);

		if (genBtn.btnHovering)
			genBtn.DrawOutline();

		if (sglBtn.btnHovering)
			sglBtn.DrawOutline();

		if (returnBtn.btnHovering)
			returnBtn.DrawOutline();

		genBtn.Draw();
		sglBtn.Draw();
		returnBtn.Draw();
		break;

	case Application::Options:
		DrawText("To be introduced.", (GetScreenWidth() / 2) / genericTextScale, 160, genericTextScale, color);

		if (returnBtn.btnHovering)
			returnBtn.DrawOutline();

		returnBtn.Draw();
		break;

	case Application::Credits:
		DrawText("Prototype Developed by Corey Abraham.", (GetScreenWidth() / 2) / genericTextScale, 160, genericTextScale, color);
		DrawText("Developed as a prototype for AIE, distrubution requires permission.", (GetScreenWidth() / 2) / genericTextScale, 180, genericTextScale, color);

		if (returnBtn.btnHovering)
			returnBtn.DrawOutline();

		returnBtn.Draw();
		break;
	}
}

void drawGameState()
{
	int genericTextScale = 20;

	switch (currentGameState)
	{
	case Application::Generic:
		if (!gameStarted)
		{
			if (frameOnStart != 0)
			{
				frameOnStart = 0;
			}

			DrawText("Press ENTER to Start!", (GetScreenWidth() / 2) / genericTextScale, 80, genericTextScale, WHITE);
		}

		else
		{
			if (frameOnStart < hideTextOnFrame)
			{
				DrawText("Game started!", (GetScreenWidth() / 2) / genericTextScale, 80, genericTextScale, WHITE);
			}

			frameOnStart += 1;
		}
		
		player1.Draw();
		player2.Draw();

		break;

	case Application::Solo:
		// Insert Drawing Here!
		
		break;
	}
}