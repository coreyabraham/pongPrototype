// Header(s) //
#pragma once

#include <iostream>
#include <math.h>

#include "application.h"
#include "common.h"

// Value(s) //
Vector2 logoPos = {
	round(Application::windowWidth / 2 - 128), 
	round(Application::windowHeight / 2 - 128)
};

Color logoBorderColor = BLUE;
Color logoFillColor = SKYBLUE;
Color logoTextColor = WHITE;
const char* introText = "mug";
bool introSoundPlayed = false;

// Variable(s) //
Application::CoreState currentCoreState;
Application::TitleState currentTitleState;

int framesCounter = 0;
int lettersCount = 0;

int topSideRecWidth = 16;
int leftSideRecHeight = 16;

int bottomSideRecWidth = 16;
int rightSideRecHeight = 16;

int state = 0;
float alpha = 1.0f;

ClickButton testButton(Vector2{ 20, 100 }, Vector2{ 80, 40 });
HoverOutline testBtnOutline {testButton, BLUE};

// Function(s) //
void modifyCoreState(Application::CoreState state)
{
	currentCoreState = state;
}

void modifyTitleState(Application::TitleState state)
{
	currentTitleState = state;
}

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
					topSideRecWidth += 4;
					leftSideRecHeight += 4;

					if (topSideRecWidth == 256)
					{
						state = 2;
					}

					break;

				case 2:
					if (Application::enableAudio && !introSoundPlayed)
					{
						std::cout << FileExists("intro.wav") << std::endl;

						Sound introSFX = LoadSound("intro.wav");
						PlaySound(introSFX);
						introSoundPlayed = true;
					}

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
		case Application::Game:

			break;
	}
}

void updateTitleState()
{
	switch (currentTitleState)
	{
	case Application::Main:
		testButton.btnColor = RED;
		testButton.txtColor = WHITE;
		testButton.btnText = "PLAY";

		testButton.Update();

		if (testButton.btnAction)
		{
			std::cout << "Clicked!" << std::endl;
			modifyTitleState(Application::Options);
			
		}

		if (testButton.btnHovering)
		{
			std::cout << "Hovering..." << std::endl;
		}

		break;

	case Application::Options:

		break;

	case Application::Credits:

		break;
	}
}

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
					DrawRectangle(logoPos.x, logoPos.y, 16, 16, logoBorderColor);
				}

				break;

			case 1:
				DrawRectangle(logoPos.x, logoPos.y, topSideRecWidth, 16, logoBorderColor);
				DrawRectangle(logoPos.x, logoPos.y, 16, leftSideRecHeight, logoBorderColor);

				break;

			case 2:
				DrawRectangle(logoPos.x, logoPos.y, topSideRecWidth, 16, logoBorderColor);
				DrawRectangle(logoPos.x, logoPos.y, 16, leftSideRecHeight, logoBorderColor);

				DrawRectangle(logoPos.x + 240, logoPos.y, 16, rightSideRecHeight, logoBorderColor);
				DrawRectangle(logoPos.x, logoPos.y + 240, bottomSideRecWidth, 16, logoBorderColor);

				break;

			case 3:
				DrawRectangle(logoPos.x, logoPos.y, topSideRecWidth, 16, Fade(logoBorderColor, alpha));
				DrawRectangle(logoPos.x, logoPos.y + 16, 16, leftSideRecHeight - 32, Fade(logoBorderColor, alpha));

				DrawRectangle(logoPos.x + 240, logoPos.y + 16, 16, rightSideRecHeight - 32, Fade(logoBorderColor, alpha));
				DrawRectangle(logoPos.x, logoPos.y + 240, bottomSideRecWidth, 16, Fade(logoBorderColor, alpha));

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
	DrawText("Build 0.2.1", 10, GetScreenHeight() - 30, 10, WHITE);

	// State-Specific //
	switch (currentTitleState)
	{
	case Application::Main:
		DrawText("Pong Prototype", 40, 20, 40, WHITE);

		if (testButton.btnHovering)
		{
			testBtnOutline.Draw();
		}

		testButton.Draw();

		break;

	case Application::Options:

		break;

	case Application::Credits:

		break;
	}
}