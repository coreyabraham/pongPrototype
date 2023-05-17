// Header(s) //
#include "raylib.h"
#include "states.h"
#include "common.h"

#include <iostream>
#include <string>

// Global Variable(s) //
int logoPosX = floatToInt(Application::windowWidth / 2 - 128);
int logoPosY = floatToInt(Application::windowHeight / 2 - 128);

Color logoBorderColor = BLUE;
Color logoFillColor = SKYBLUE;
Color logoTextColor = WHITE;
const char* introText = "Monke";
bool introSoundPlayed = false;

States::CoreState currentCoreState;
States::TitleState currentTitleState;
States::GameState currentGameState;

int framesCounter = 0;
int lettersCount = 0;

int topSideRecWidth = 16;
int leftSideRecHeight = 16;

int bottomSideRecWidth = 16;
int rightSideRecHeight = 16;

int state = 0;
float alpha = 1.0f;

bool gameStarted = false;
bool gamePaused = false;
bool gameHalted = false;

int maxScoreCount = 3;
bool playerWon = false;

int plr1Score = 0;
int plr2Score = 0;

const char* pointWinner = "";
const char* gameWinner = "";

int frameOnStart = 0;
int hideTextOnFrame = 100;

Player player1 = { 50.0f, KEY_Q, KEY_A, KEY_LEFT_ALT, BLUE };
Player player2 = { Application::windowWidth - 75.0f, KEY_P, KEY_L, KEY_RIGHT_ALT, RED };
Ball ball = {  };

ClickButton returnBtn = { Vector2{ 20, Application::windowHeight - 90 }, Vector2{ 130, 40 }, "RETURN", RED, WHITE, true, 2.5f };

ClickButton playBtn = { Vector2{ 20, 200 }, Vector2{ 70, 40 }, "Play", BLACK, WHITE, true, 2.5f };
ClickButton optsBtn = { Vector2{ 20, 280 }, Vector2{ 120, 40 }, "Options", BLACK, WHITE, true, 2.5f };
ClickButton cdsBtn = { Vector2{ 20, 360 }, Vector2{ 120, 40 }, "Credits", BLACK, WHITE, true, 2.5f };
ClickButton exitBtn = { Vector2{ 20, 440 }, Vector2{ 70, 40 }, "Exit", BLACK, WHITE, true, 2.5f };

ClickButton genBtn = { Vector2{ 20, 200 }, Vector2{ 210, 40 }, "Generic Mode", BLACK, WHITE, true, 2.5f };
ClickButton sglBtn = { Vector2{ 20, 280 }, Vector2{ 280, 40 }, "Singleplayer Mode", BLACK, WHITE, true, 2.5f };

Sound click;
Sound back;
Sound start;
Sound begin;
Sound error;
Sound onExit;

Sound paused;
Sound unpaused;

Sound ballCollision;
Sound ballHit;
Sound matchPoint;
Sound matchWin;

Music titleBGM;

// Class(es) //
States::States() {  }
States::~States() {  }

// Class Function(s) //
void States::Init()
{
	click = LoadSound("resources\\audio\\sounds\\click.wav");
	back = LoadSound("resources\\audio\\sounds\\back.wav");
	start = LoadSound("resources\\audio\\sounds\\start.wav");
	begin = LoadSound("resources\\audio\\sounds\\begin.wav");
	error = LoadSound("resources\\audio\\sounds\\error.wav");
	onExit = LoadSound("resources\\audio\\sounds\\exit.wav");

	paused = LoadSound("resources\\audio\\sounds\\gamePause.wav");
	unpaused = LoadSound("resources\\audio\\sounds\\gameUnpause.wav");

	ballCollision = LoadSound("resources\\audio\\sounds\\ballCollision.wav");
	ballHit = LoadSound("resources\\audio\\sounds\\ballHit.wav");
	matchPoint = LoadSound("resources\\audio\\sounds\\matchPoint.wav");
	matchWin = LoadSound("resources\\audio\\sounds\\matchWin.wav");

	titleBGM = LoadMusicStream("resources\\audio\\music\\titleBGM.mp3");
	SetMusicVolume(titleBGM, 0.25f);

	currentCoreState = CoreState::Intro;
}

void States::Uninit()
{
	UnloadSound(click);
	UnloadSound(back);
	UnloadSound(start);
	UnloadSound(begin);
	UnloadSound(error);
	UnloadSound(onExit);

	UnloadSound(paused);
	UnloadSound(unpaused);

	UnloadSound(ballCollision);
	UnloadSound(ballHit);
	UnloadSound(matchPoint);
	UnloadSound(matchWin);

	UnloadMusicStream(titleBGM);
}

void States::UpdateStates()
{
	// Core
	switch (currentCoreState)
	{
	case CoreState::Intro:
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
				Sound introSfx = LoadSound("resources\\audio\\sounds\\intro.wav");
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

					currentCoreState = CoreState::Title;
					currentTitleState = TitleState::Main;
				}
			}

			break;
		}

		//if (Application::canDebug)
		//{
		//	std::cout << "CurrentFrameCount: " << framesCounter << std::endl;
		//}

		break;

	case CoreState::Title:
		if (!IsMusicStreamPlaying(titleBGM))
			PlayMusicStream(titleBGM);

		UpdateMusicStream(titleBGM);

		break;

	case CoreState::Game:
		// Add Data Here!

		break;
	}

	// Title
	switch (currentTitleState)
	{
	case TitleState::Main:
		playBtn.Update();
		optsBtn.Update();
		cdsBtn.Update();
		exitBtn.Update();

		if (playBtn.btnAction)
		{
			if (Application::enableAudio)
				PlaySound(click);

			currentTitleState = TitleState::Modes;
		}

		if (optsBtn.btnAction)
		{
			if (Application::enableAudio)
				PlaySound(click);

			currentTitleState = TitleState::Options;
		}

		if (cdsBtn.btnAction)
		{
			if (Application::enableAudio)
				PlaySound(click);

			currentTitleState = TitleState::Credits;
		}

		if (exitBtn.btnAction)
		{
			if (Application::enableAudio)
			{
				PlaySound(onExit);
				SetWindowOpacity(0.0f);
				while (IsSoundPlaying(onExit)) {}
				CloseWindow();
			}
		}

		break;

	case TitleState::Modes:
		genBtn.Update();
		sglBtn.Update();
		returnBtn.Update();

		if (genBtn.btnAction)
		{
			if (Application::enableAudio)
				PlaySound(start);

			currentCoreState = CoreState::Game;
			currentTitleState = TitleState::Empty;
			currentGameState = GameState::Generic;
		}

		if (sglBtn.btnAction)
		{
			if (Application::enableAudio)
				PlaySound(start);

			currentCoreState = CoreState::Game;
			currentTitleState = TitleState::Empty;
			currentGameState = GameState::Solo;
		}

		if (returnBtn.btnAction)
		{
			if (Application::enableAudio)
				PlaySound(back);

			currentTitleState = TitleState::Main;
		}

		break;

	case TitleState::Options:
		returnBtn.Update();

		if (returnBtn.btnAction)
		{
			if (Application::enableAudio)
				PlaySound(back);

			currentTitleState = TitleState::Main;
		}

		break;

	case TitleState::Credits:
		returnBtn.Update();

		if (returnBtn.btnAction)
		{
			if (Application::enableAudio)
				PlaySound(back);

			currentTitleState = TitleState::Main;
		}

		break;
	}

	// Game
	switch (currentGameState)
	{
	case GameState::Generic:
		if (!gameStarted && IsKeyPressed(KEY_ENTER))
		{
			PlaySound(begin);
			gameStarted = true;
		}

		if (gameStarted)
		{
			if (gamePaused && !gameHalted && IsKeyPressed(KEY_BACKSPACE))
			{
				PlaySound(error);

				ball.Reset();
				player1.Reset();
				player2.Reset();

				playerWon = false;
				gameWinner = "";
				pointWinner = "";

				plr1Score = 0;
				plr2Score = 0;

				gameStarted = false;
				gamePaused = false;
				gameHalted = false;

				currentCoreState = CoreState::Title;
				currentTitleState = TitleState::Modes;
				currentGameState = GameState::Null;
			}

			if (!gamePaused && !gameHalted)
			{
				ball.Update();
				player1.Update();
				player2.Update();

				if (CheckCollisionCircleRec(ball.ballPosition, ball.ballRadius, player2.Paddle))
				{
					ball.ballSpeed.x *= -1.1f;
					ball.ballSpeed.y = (ball.ballPosition.y - player2.Paddle.y) / (player2.Paddle.height / 2) * ball.ballSpeed.x;

					ball.ballColor = player2.PaddleColor;
					PlaySound(ballHit);
				}

				if (CheckCollisionCircleRec(ball.ballPosition, ball.ballRadius, player1.Paddle))
				{
					ball.ballSpeed.x *= -1.1f;
					ball.ballSpeed.y = (ball.ballPosition.y - player1.Paddle.y) / (player1.Paddle.height / 2) * ball.ballSpeed.x;

					ball.ballColor = player1.PaddleColor;
					PlaySound(ballHit);
				}

				if (ball.ballCollided)
				{
					PlaySound(ballCollision);
				}

				if (ball.ballPosition.x < 0 - ball.ballRadius)
				{
					gameHalted = true;
					plr2Score += 1;

					if (plr2Score < maxScoreCount)
					{
						pointWinner = "Player 2 Scored a Point!";
						PlaySound(matchPoint);
					}

					else
					{
						gameWinner = "Player 2 Wins!";
						playerWon = true;
						PlaySound(matchWin);
					}
				}

				if (ball.ballPosition.x > GetScreenWidth() + ball.ballRadius)
				{
					gameHalted = true;
					plr1Score += 1;

					if (plr1Score < maxScoreCount)
					{
						pointWinner = "Player 1 Scored a Point!";
						PlaySound(matchPoint);
					}

					else
					{
						gameWinner = "Player 1 Wins!";
						playerWon = true;
						PlaySound(matchWin);
					}
				}
			}

			if (!gameHalted)
			{
				if (IsKeyPressed(KEY_TAB))
				{
					if (!gamePaused)
					{
						PlaySound(paused);
						gamePaused = true;
					}

					else
					{
						PlaySound(unpaused);
						gamePaused = false;
					}
				}
			}

			else
			{
				if (!playerWon && IsKeyPressed(KEY_ENTER))
				{
					ball.Reset();
					player1.Reset();
					player2.Reset();

					gameHalted = false;
				}
			}
		}

		break;

	case GameState::Solo:
		// Insert Execution Here!

		break;
	}
}

void States::DrawStates()
{
	// Core
	switch (currentCoreState)
	{
	case CoreState::Intro:
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
	}

	// Title
	const Vector2 pos = { 40, 20 };
	const int size = 40;
	const Color color = WHITE;
	const char* text = "";

	switch (currentTitleState)
	{
	case TitleState::Main:
		text = "Pong Prototype | Main Menu";
		break;

	case TitleState::Modes:
		text = "Pong Prototype | Gamemodes";
		break;

	case TitleState::Options:
		text = "Pong Prototype | Options";
		break;

	case TitleState::Credits:
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

	switch (currentTitleState)
	{
	case TitleState::Main:

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

	case TitleState::Modes:
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

	case TitleState::Options:
		DrawText("To be introduced.", (GetScreenWidth() / 2) / genericTextScale, 160, genericTextScale, color);

		if (returnBtn.btnHovering)
			returnBtn.DrawOutline();

		returnBtn.Draw();
		break;

	case TitleState::Credits:
		DrawText("Prototype Developed by Corey Abraham.", (GetScreenWidth() / 2) / genericTextScale, 160, genericTextScale, color);
		DrawText("Developed as a prototype for AIE, distrubution requires permission.", (GetScreenWidth() / 2) / genericTextScale, 180, genericTextScale, color);

		if (returnBtn.btnHovering)
			returnBtn.DrawOutline();

		returnBtn.Draw();
		break;
	}

	// Game
	switch (currentGameState)
	{
	case GameState::Generic:
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
			std::string str = std::to_string(plr1Score);
			char const* p1Score = str.c_str();

			std::string str2 = std::to_string(plr2Score);
			char const* p2Score = str2.c_str();

			int textPosX = (int)GetScreenWidth() / 2;
			int textPosY = 120;
			int textSize = 40;

			DrawText(p1Score, textPosX, textPosY, 20, player1.PaddleColor);
			DrawText("|", textPosX + textSize, textPosY, 20, WHITE);
			DrawText(p2Score, textPosX + (textSize * 2), textPosY, 20, player2.PaddleColor);

			if (frameOnStart < hideTextOnFrame)
			{
				DrawText("Game started!", (GetScreenWidth() / 2) / genericTextScale, 80, genericTextScale, WHITE);
			}

			frameOnStart += 1;
		}

		ball.Draw();
		player1.Draw();
		player2.Draw();

		if (gamePaused)
		{
			DrawText("Game Paused! Press 'TAB' to Unpause or Press 'BACKSPACE' to Exit!", (GetScreenWidth() / 2) / genericTextScale, GetScreenHeight() - genericTextScale * 2, genericTextScale, WHITE);
		}

		if (gameHalted)
		{
			if (!playerWon)
			{
				int fontSize = 30;
				int textWidth = MeasureText(pointWinner, fontSize);
				DrawText(pointWinner, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - fontSize, fontSize, ORANGE);
			}

			else
			{
				int fontSize = 50;
				int textWidth = MeasureText(gameWinner, fontSize);
				DrawText(gameWinner, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - fontSize, fontSize, YELLOW);

				const char* text = "Press 'BACKSPACE' to Exit Mode, Press 'ENTER' to do a Rematch!";
				int fontSize2 = fontSize / 2;
				int textWidth2 = MeasureText(text, fontSize2);
				DrawText(text, GetScreenWidth() / 2 - textWidth2 / 2, GetScreenHeight() / 2 - fontSize2 + fontSize, fontSize2, WHITE);
			}
		}

		break;

	case GameState::Solo:
		// Insert Drawing Here!

		break;
	}
}