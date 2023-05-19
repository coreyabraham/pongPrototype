// Header(s) //
#include "raylib.h"
#include "states.h"

#include <iostream>
#include <string>

// Setup //
States::CoreState currentCoreState = States::CoreState::Intro;
States::TitleState currentTitleState = States::TitleState::TNULL;
States::GameState currentGameState = States::GameState::GNULL;
#include "common.h"

// Global Variable(s) //
int logoPosX = floatToInt(Application::windowWidth / 2 - 128);
int logoPosY = floatToInt(Application::windowHeight / 2 - 128);

Color logoBorderColor = BLUE;
Color logoFillColor = SKYBLUE;
Color logoTextColor = WHITE;
const char* introText = "Monke";
bool introSoundPlayed = false;

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
bool p1Success = false;

int plr1Score = 0;
int plr2Score = 0;

const char* pointWinner = "";
const char* gameWinner = "";

int frameOnStart = 0;
int hideTextOnFrame = 100;

Player player1 = { 50.0f, KEY_Q, KEY_A, KEY_LEFT_ALT };
Player player2 = { Application::windowWidth - 75.0f, KEY_P, KEY_L, KEY_RIGHT_ALT };

Ball ball = {  };
Rectangle sglPlrPaddle = { Application::windowWidth - 75.0f, (Application::windowHeight / 2) - 250.0f, 10.0f, 500.0f };

ClickButton returnBtn = { Vector2{ 20, Application::windowHeight - 90 }, Vector2{ 130, 40 }, "RETURN", RED, WHITE, true, 2.5f };

ClickButton playBtn = { Vector2{ 20, 200 }, Vector2{ 70, 40 }, "Play", BLACK, WHITE, true, 2.5f };
ClickButton optsBtn = { Vector2{ 20, 280 }, Vector2{ 120, 40 }, "Options", BLACK, WHITE, true, 2.5f };
ClickButton cdsBtn = { Vector2{ 20, 360 }, Vector2{ 120, 40 }, "Credits", BLACK, WHITE, true, 2.5f };
ClickButton exitBtn = { Vector2{ 20, 440 }, Vector2{ 70, 40 }, "Exit", BLACK, WHITE, true, 2.5f };

ClickButton genBtn = { Vector2{ 20, 200 }, Vector2{ 210, 40 }, "Generic Mode", BLACK, WHITE, true, 2.5f };
ClickButton sglBtn = { Vector2{ 20, 280 }, Vector2{ 280, 40 }, "Singleplayer Mode", BLACK, WHITE, true, 2.5f };

ClickButton fsBtn = { Vector2{ 20, 200 }, Vector2{ 285, 40 }, "Toggle Fullscreen", BLACK, WHITE, true, 2.5f };

Sound click;
Sound back;
Sound hover;
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
Music gameBGM;

// Class(es) //
States::States() {  }
States::~States() {  }

// Class Function(s) //
void States::Init()
{
	Application app;
	
	if (app.enableAudio)
	{

		player1.PaddleColor = generateCustomColor();
		player2.PaddleColor = generateCustomColor();

		click = LoadSound("resources\\audio\\sounds\\click.wav");
		SetSoundVolume(click, app.soundVolume);

		back = LoadSound("resources\\audio\\sounds\\back.wav");
		SetSoundVolume(back, app.soundVolume);

		hover = LoadSound("resources\\audio\\sounds\\hover.wav");
		SetSoundVolume(hover, app.soundVolume);

		start = LoadSound("resources\\audio\\sounds\\start.wav");
		SetSoundVolume(start, app.soundVolume);

		begin = LoadSound("resources\\audio\\sounds\\begin.wav");
		SetSoundVolume(begin, app.soundVolume);

		error = LoadSound("resources\\audio\\sounds\\error.wav");
		SetSoundVolume(error, app.soundVolume);

		onExit = LoadSound("resources\\audio\\sounds\\exit.wav");
		SetSoundVolume(onExit, app.soundVolume);

		paused = LoadSound("resources\\audio\\sounds\\gamePause.wav");
		SetSoundVolume(paused, app.soundVolume);

		unpaused = LoadSound("resources\\audio\\sounds\\gameUnpause.wav");
		SetSoundVolume(unpaused, app.soundVolume);

		ballCollision = LoadSound("resources\\audio\\sounds\\ballCollision.wav");
		SetSoundVolume(ballCollision, app.soundVolume);

		ballHit = LoadSound("resources\\audio\\sounds\\ballHit.wav");
		SetSoundVolume(ballHit, app.soundVolume);

		matchPoint = LoadSound("resources\\audio\\sounds\\matchPoint.wav");
		SetSoundVolume(matchPoint, app.soundVolume);

		matchWin = LoadSound("resources\\audio\\sounds\\matchWin.wav");
		SetSoundVolume(matchWin, app.soundVolume);

		titleBGM = LoadMusicStream("resources\\audio\\music\\titleBGM.mp3");
		SetMusicVolume(titleBGM, app.musicVolume);

		gameBGM = LoadMusicStream("resources\\audio\\music\\gameBGM.mp3");
		SetMusicVolume(gameBGM, app.musicVolume);
	}
}

void States::Uninit()
{
	Application app;

	if (app.enableAudio)
	{
		UnloadSound(click);
		UnloadSound(back);
		UnloadSound(hover);
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
		UnloadMusicStream(gameBGM);
	}
}

void States::UpdateStates()
{
	Application app;
	
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

			if (app.enableAudio && !introSoundPlayed)
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

		break;

	case CoreState::Title:
		if (!IsMusicStreamPlaying(titleBGM))
			PlayMusicStream(titleBGM);

		UpdateMusicStream(titleBGM);

		break;

	case CoreState::Game:
		if (!IsMusicStreamPlaying(gameBGM))
			PlayMusicStream(gameBGM);

		if (!gamePaused)
		{
			UpdateMusicStream(gameBGM);
		}

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

		playBtn.HandleSound(hover);	
		optsBtn.HandleSound(hover);	
		cdsBtn.HandleSound(hover);	
		exitBtn.HandleSound(hover);	

		playBtn.HandleClick(click, true, Title, Modes, GNULL);
		optsBtn.HandleClick(click, true, Title, Options, GNULL);
		cdsBtn.HandleClick(click, true, Title, Credits, GNULL);

		// Custom Button Logic is ued for the Exit Button!
		if (exitBtn.btnAction)
		{
			if (app.enableAudio)
			{
				PlaySound(onExit);
				SetWindowOpacity(0.0f);
				while (IsSoundPlaying(onExit)) {}
			}

			CloseWindow();
		}

		break;

	case TitleState::Modes:
		genBtn.Update();
		sglBtn.Update();
		returnBtn.Update();

		genBtn.HandleSound(hover);
		sglBtn.HandleSound(hover);
		returnBtn.HandleSound(hover);

		// Fix having to use "TitleState::None" to fool notation!
		genBtn.HandleClick(click, true, Game, TNULL, Generic);
		sglBtn.HandleClick(click, true, Game, TNULL, Solo);
		returnBtn.HandleClick(click, true, Title, Main, GNULL);

		break;

	case TitleState::Options:
		returnBtn.Update();
		returnBtn.HandleSound(hover);
		returnBtn.HandleClick(click, true, Title, Main, GNULL);

		fsBtn.Update();
		fsBtn.HandleSound(hover);
		
		if (fsBtn.btnAction)
			ToggleFullscreen();

		break;

	case TitleState::Credits:
		returnBtn.Update();
		returnBtn.HandleSound(hover);
		returnBtn.HandleClick(click, true, Title, Main, GNULL);

		break;
	}

	if (gameStarted && !gameHalted)
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
				ball.Reset();
				player1.Reset();
				player2.Reset();

				playerWon = false;
				p1Success = false;

				gameWinner = "";
				pointWinner = "";

				plr1Score = 0;
				plr2Score = 0;

				gameStarted = false;
				gamePaused = false;
				gameHalted = false;

				PlaySound(error);
				currentCoreState = CoreState::Title;
				currentTitleState = TitleState::Modes;
				currentGameState = GameState::GNULL;
			}

			if (!gamePaused && !gameHalted)
			{
				ball.Update();
				player1.Update();
				player2.Update();

				if (ball.ballCollided)
				{
					PlaySound(ballCollision);
				}

				if (CheckCollisionCircleRec(ball.ballPosition, ball.ballRadius, player2.Paddle) && player2.canHitBall)
				{
					ball.ballSpeed.x *= -1.1f;
					ball.ballSpeed.y = (ball.ballPosition.y - player2.Paddle.y) / (player2.Paddle.height / 2) * ball.ballSpeed.x;

					ball.ballColor = player2.PaddleColor;
					PlaySound(ballHit);
				}

				if (CheckCollisionCircleRec(ball.ballPosition, ball.ballRadius, player1.Paddle) && player1.canHitBall)
				{
					ball.ballSpeed.x *= -1.1f;
					ball.ballSpeed.y = (ball.ballPosition.y - player1.Paddle.y) / (player1.Paddle.height / 2) * ball.ballSpeed.x;

					ball.ballColor = player1.PaddleColor;
					PlaySound(ballHit);
				}

				if (ball.ballPosition.x > GetScreenWidth() + ball.ballRadius)
				{
					gameHalted = true;
					plr1Score += 1;

					if (plr1Score < maxScoreCount)
					{
						p1Success = true;
						pointWinner = "Player 1 Scored a Point!";
						PlaySound(matchPoint);
					}

					else
					{
						p1Success = true;
						playerWon = true;
						gameWinner = "Player 1 Wins!";
						PlaySound(matchWin);
					}
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
			}

			else if (!gamePaused && gameHalted)
			{
				if (IsKeyPressed(KEY_ENTER))
				{
					if (!playerWon)
					{
						ball.Reset();
						player1.Reset();
						player2.Reset();

						gameHalted = false;
						p1Success = false;
					}

					else
					{
						ball.Reset();
						player1.Reset();
						player2.Reset();

						playerWon = false;
						p1Success = false;

						gameWinner = "";
						pointWinner = "";

						plr1Score = 0;
						plr2Score = 0;

						gameStarted = false;
						gamePaused = false;
						gameHalted = false;
					}
				}

				if (IsKeyPressed(KEY_BACKSPACE) && playerWon)
				{
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

					PlaySound(error);
					currentCoreState = CoreState::Title;
					currentTitleState = TitleState::Modes;
					currentGameState = GameState::GNULL;
				}
			}
		}

		break;

	case GameState::Solo:
		if (!gameStarted && IsKeyPressed(KEY_ENTER))
		{
			PlaySound(begin);
			gameStarted = true;
		}

		if (gameStarted)
		{
			if (gamePaused && !gameHalted && IsKeyPressed(KEY_BACKSPACE))
			{
				ball.Reset();
				player1.Reset();
				plr1Score = 0;

				gameStarted = false;
				gameHalted = false;
				gamePaused = false;

				PlaySound(error);
				currentCoreState = CoreState::Title;
				currentTitleState = TitleState::Modes;
				currentGameState = GameState::GNULL;
			}

			if (!gamePaused && !gameHalted)
			{
				ball.Update();
				player1.Update();

				if (ball.ballCollided)
				{
					PlaySound(ballCollision);
				}

				if (CheckCollisionCircleRec(ball.ballPosition, ball.ballRadius, player1.Paddle) && player1.canHitBall)
				{
					ball.ballSpeed.x *= -1.1f;
					ball.ballSpeed.y = (ball.ballPosition.y - player1.Paddle.y) / (player1.Paddle.height / 2) * ball.ballSpeed.x;

					ball.ballColor = player1.PaddleColor;
					
					PlaySound(ballHit);
				}

				if (CheckCollisionCircleRec(ball.ballPosition, ball.ballRadius, sglPlrPaddle))
				{
					if (!player1.canHitBall)
					{
						player1.canHitBall = true;
						ball.ballSpeed.y /= 1.1f;
					}

					ball.ballSpeed.x *= -1.1f;

					plr1Score += 1;
					
					PlaySound(ballHit);
					PlaySound(matchPoint);
				}

				if (ball.ballPosition.x > GetScreenWidth() + ball.ballRadius)
				{
					player1.canHitBall = false;
					
					ball.ballPosition.x = 0;
					ball.ballSpeed.y *= 1.1f;

					plr1Score += 2;

					PlaySound(matchWin);
				}

				if (ball.ballPosition.x < 0 - ball.ballRadius)
				{
					PlaySound(onExit);
					gameHalted = true;
				}
			}

			else if (gameHalted)
			{
				if (IsKeyPressed(KEY_ENTER))
				{
					ball.Reset();
					player1.Reset();
					plr1Score = 0;

					gameStarted = false;
					gameHalted = false;
					gamePaused = false;
				}

				if (IsKeyPressed(KEY_BACKSPACE))
				{
					ball.Reset();
					player1.Reset();
					plr1Score = 0;

					gameStarted = false;
					gameHalted = false;
					gamePaused = false;

					PlaySound(error);
					currentCoreState = CoreState::Title;
					currentTitleState = TitleState::Modes;
					currentGameState = GameState::GNULL;
				}
			}
		}

		break;
	}
}

void States::DrawStates()
{
	Application app;

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
	const char* text = "";
	const int size = 40;
	const Color color = WHITE;

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

	if (app.canDebug)
	{
		Application app;
		DrawText(app.buildInfo, 10, GetScreenHeight() - 20, 10, WHITE);
	}

	int titleWidth = MeasureText(text, size);
	DrawText(text, floatToInt(GetScreenWidth() / 2 - titleWidth / 2), size, size, color);

	int genericTextScale = 20;

	switch (currentTitleState)
	{
	case TitleState::Main:
		playBtn.DrawOutline();
		optsBtn.DrawOutline();
		cdsBtn.DrawOutline();
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

		genBtn.DrawOutline();
		sglBtn.DrawOutline();
		returnBtn.DrawOutline();

		genBtn.Draw();
		sglBtn.Draw();
		returnBtn.Draw();
		break;

	case TitleState::Options:
		fsBtn.DrawOutline();
		fsBtn.Draw();

		returnBtn.DrawOutline();
		returnBtn.Draw();

		break;

	case TitleState::Credits:
		DrawText("Prototype Developed by Corey Abraham.", (GetScreenWidth() / 2) / genericTextScale, 160, genericTextScale, color);
		DrawText("Developed as a prototype for AIE, distrubution requires permission.", (GetScreenWidth() / 2) / genericTextScale, 180, genericTextScale, color);
		DrawText("Finalize Date: 18/05/2023 (DEV NOTE: UPDATE THIS WITH THE ACTUAL FINAL DATE!)", (GetScreenWidth() / 2) / genericTextScale, 200, genericTextScale, color);

		returnBtn.DrawOutline();
		returnBtn.Draw();

		break;
	}

	if (gamePaused)
	{
		DrawText("Game Paused! Press 'TAB' to Unpause or Press 'BACKSPACE' to Exit!", (GetScreenWidth() / 2) / genericTextScale, GetScreenHeight() - genericTextScale * 4, genericTextScale, WHITE);
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
			if (frameOnStart < hideTextOnFrame)
			{
				DrawText("Game started!", (GetScreenWidth() / 2) / genericTextScale, 80, genericTextScale, WHITE);
			}

			frameOnStart += 1;

			std::string str = std::to_string(plr1Score);
			char const* p1Score = str.c_str();

			std::string str2 = std::to_string(plr2Score);
			char const* p2Score = str2.c_str();

			int textSize = 40;
			int textWidth = MeasureText("000", textSize);

			int textPosX = (int)GetScreenWidth() / 2 - textWidth / 2;
			int textPosY = 120;

			DrawText(p1Score, textPosX - (textSize * 2), textPosY, textSize, player1.PaddleColor);
			DrawText(p2Score, textPosX + (textSize * 2), textPosY, textSize, player2.PaddleColor);
			DrawText("|", textPosX, textPosY, textSize, WHITE);
		}

		ball.Draw();
		player1.Draw();
		player2.Draw();

		if (gameHalted)
		{
			if (!playerWon)
			{
				Color plrColor = player2.PaddleColor;
				if (p1Success)
				{
					plrColor = player1.PaddleColor;
				}

				int fontSize = 30;
				int textWidth = MeasureText(pointWinner, fontSize);
				DrawText(pointWinner, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - fontSize, fontSize, plrColor);

				const char* text = "Press 'ENTER' to Continue...";
				int fontSize2 = fontSize - 10;
				int textWidth2 = MeasureText(text, fontSize2);
				DrawText(text, GetScreenWidth() / 2 - textWidth2 / 2, GetScreenHeight() / 2 - fontSize2 + fontSize, fontSize2, WHITE);
			}

			else
			{
				Color plrColor = player2.PaddleColor;
				if (p1Success)
				{
					plrColor = player1.PaddleColor;
				}

				int fontSize = 50;
				int textWidth = MeasureText(gameWinner, fontSize);
				DrawText(gameWinner, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - fontSize, fontSize, plrColor);

				const char* text = "Press 'BACKSPACE' to Exit Mode, Press 'ENTER' to do a Rematch!";
				int fontSize2 = fontSize / 2;
				int textWidth2 = MeasureText(text, fontSize2);
				DrawText(text, GetScreenWidth() / 2 - textWidth2 / 2, GetScreenHeight() / 2 - fontSize2 + fontSize, fontSize2, WHITE);
			}
		}

		break;

	case GameState::Solo:
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

			std::string str = std::to_string(plr1Score);
			char const* p1Score = str.c_str();
			if (plr1Score > 99)
			{
				p1Score = "...how?";
				ball.Reset();
			}

			int textSize = 40;
			int textWidth = MeasureText("000", textSize);

			int textPosX = (int)GetScreenWidth() / 2 - textWidth / 2;
			int textPosY = 120;

			DrawText(p1Score, textPosX, textPosY, textSize, player1.PaddleColor);
		}

		if (gameHalted)
		{
			int fontSize = 50;
			const char* plrText = "Oh noes! You missed the ball!";

			int textWidth = MeasureText(plrText, fontSize);
			DrawText(plrText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - fontSize, fontSize, RED);

			const char* text = "Press 'BACKSPACE' to Exit Mode, Press 'ENTER' to Reset Field!";
			int fontSize2 = fontSize / 2;
			int textWidth2 = MeasureText(text, fontSize2);
			DrawText(text, GetScreenWidth() / 2 - textWidth2 / 2, GetScreenHeight() / 2 - fontSize2 + fontSize, fontSize2, WHITE);
		}

		ball.Draw();
		player1.Draw();
		DrawRectangleRec(sglPlrPaddle, WHITE);

		break;
	}
}