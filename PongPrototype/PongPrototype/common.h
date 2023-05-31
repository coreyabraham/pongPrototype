// Header(s) //
#include "application.h"

// Function(s) //
inline int floatToInt(float value) 
{ 
	return static_cast<int>(value); 
}

Color generateCustomColor()
{
	int random = GetRandomValue(1, 22);

	switch (random)
	{
		case 1:
			return LIGHTGRAY;

		case 2:
			return GRAY;

		case 3:
			return DARKGRAY;

		case 4:
			return YELLOW;

		case 5:
			return GOLD;

		case 6:
			return ORANGE;

		case 7:
			return PINK;

		case 8:
			return RED;

		case 9:
			return MAROON;

		case 10:
			return GREEN;

		case 11:
			return LIME;

		case 12:
			return DARKGREEN;

		case 13:
			return SKYBLUE;

		case 14:
			return BLUE;

		case 15:
			return DARKBLUE;

		case 16:
			return PURPLE;

		case 17:
			return VIOLET;

		case 18:
			return DARKPURPLE;

		case 19:
			return BEIGE;

		case 20:
			return BROWN;

		case 21:
			return DARKBROWN;

		case 22:
			return MAGENTA;

		default:
			return WHITE;
	}
}

// Struct(s) //
struct ClickButton
{
	Application app;

private:
	bool outlineApplicable = false;
	Color highlightColor = WHITE;
	float highlightThickness = 5.0f;

	Rectangle outline = {  };

public:
	// Constructor(s) //
	ClickButton() {};
	~ClickButton() {};

	ClickButton(Vector2 Position, Vector2 Size)
	{
		coreButton.x = Position.x;
		coreButton.y = Position.y;

		coreButton.width = Size.x;
		coreButton.height = Size.y;
	}

	ClickButton(Vector2 Position, Vector2 Size, const char* text)
	{
		coreButton.x = Position.x;
		coreButton.y = Position.y;

		coreButton.width = Size.x;
		coreButton.height = Size.y;

		btnText = text;
	}

	ClickButton(Vector2 Position, Vector2 Size, const char* text, Color bgColor)
	{
		coreButton.x = Position.x;
		coreButton.y = Position.y;

		coreButton.width = Size.x;
		coreButton.height = Size.y;

		btnText = text;
		btnColor = bgColor;
	}

	ClickButton(Vector2 Position, Vector2 Size, const char* text, Color bgColor, Color fgColor)
	{
		coreButton.x = Position.x;
		coreButton.y = Position.y;

		coreButton.width = Size.x;
		coreButton.height = Size.y;

		btnText = text;
		btnColor = bgColor;
		txtColor = fgColor;
	}

	ClickButton(Vector2 Position, Vector2 Size, const char* text, Color bgColor, Color fgColor, 
		bool showOutline)
	{
		coreButton.x = Position.x;
		coreButton.y = Position.y;

		coreButton.width = Size.x;
		coreButton.height = Size.y;

		btnText = text;
		btnColor = bgColor;
		txtColor = fgColor;

		outlineApplicable = true;

		outline.x = coreButton.x;
		outline.y = coreButton.y;

		outline.width = coreButton.width + highlightThickness;
		outline.height = coreButton.height + highlightThickness;
	}

	ClickButton(Vector2 Position, Vector2 Size, const char* text, Color bgColor, Color fgColor, 
		bool showOutline, float outlineThickness)
	{
		coreButton.x = Position.x;
		coreButton.y = Position.y;

		coreButton.width = Size.x;
		coreButton.height = Size.y;

		btnText = text;
		btnColor = bgColor;
		txtColor = fgColor;

		outlineApplicable = true;

		outline.x = coreButton.x;
		outline.y = coreButton.y;

		outline.width = coreButton.width + outlineThickness;
		outline.height = coreButton.height + outlineThickness;
	}

	ClickButton(Vector2 Position, Vector2 Size, const char* text, Color bgColor, Color fgColor, 
		bool showOutline, float outlineThickness, Color outlineColor)
	{
		coreButton.x = Position.x;
		coreButton.y = Position.y;

		coreButton.width = Size.x;
		coreButton.height = Size.y;

		btnText = text;
		btnColor = bgColor;
		txtColor = fgColor;

		outlineApplicable = true;
		highlightColor = outlineColor;

		outline.x = coreButton.x;
		outline.y = coreButton.y;

		outline.width = coreButton.width + outlineThickness;
		outline.height = coreButton.height + outlineThickness;
	}

	// Value(s) and Variable(s) //
	Rectangle coreButton = { 20, 20, 80, 40 };

	bool btnAction = false;
	bool btnHovering = false;
	bool btnHoverSFXPlayed = false;

	const char* btnText = "BtnTextHere";

	Color btnColor = WHITE;
	Color txtColor = BLACK;

	// Core Function(s) //
	void Update()
	{
		if (CheckCollisionPointRec(GetMousePosition(), coreButton))
		{
			btnHovering = true;
			btnAction = false;

			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				btnHovering = false;
				btnAction = true;
			}

			else
				btnAction = false;
		}

		else
		{
			btnAction = false;
			btnHovering = false;
		}

		if (outlineApplicable && btnHovering)
		{
			if (outline.x != coreButton.x)
				outline.x = coreButton.x;

			if (outline.y != coreButton.y)
				outline.y = coreButton.y;
		}
	}

	void Draw()
	{
		if (outlineApplicable && btnHovering)
		{
			DrawRectangleRec(outline, highlightColor);
		}

		DrawRectangleRec(coreButton, btnColor);
		DrawText(btnText, floatToInt(coreButton.x), floatToInt(coreButton.y), floatToInt(coreButton.height - 10), txtColor);
	}

	// Other Function(s) //
	void HandleClick(Sound playbackSound, bool useStates, 
		States::CoreState coreState, States::TitleState titleState, States::GameState gameState)
	{
		if (btnAction)
		{
			if (app.enableAudio)
				PlaySound(playbackSound);

			if (useStates)
			{
				currentCoreState = coreState;
				currentTitleState = titleState;
				currentGameState = gameState;
			}
		}
	}

	void HandleSound(Sound playbackSound)
	{
		if (btnHovering)
		{
			if (app.enableAudio && !btnHoverSFXPlayed)
			{
				PlaySound(playbackSound);
				btnHoverSFXPlayed = true;
			}
		}

		else
		{
			if (app.enableAudio && btnHoverSFXPlayed)
				btnHoverSFXPlayed = false;
		}
	}
};

struct Player
{
private:
	// Default(s) //
	float PaddleWidth = 10.0f;
	float PaddleHeight = 100.0f;

	float DefaultPaddleX = 50.0f;
	float PaddleY = (GetScreenHeight() / 2) - PaddleHeight;

	KeyboardKey PaddleUP = KEY_UP;
	KeyboardKey PaddleDOWN = KEY_DOWN;
	KeyboardKey PaddleFAST = KEY_SPACE;

	float maxSpeed = 1000.0f;
	float standardSpeed = maxSpeed / 2;
	float currentSpeed = standardSpeed;

public:
	// Constructor(s) //
	Player() {};
	~Player() {};

	Player(float X, KeyboardKey Up, KeyboardKey Down, KeyboardKey Slow)
	{
		Paddle.x = X;
		PaddleUP = Up;
		PaddleDOWN = Down;
		PaddleFAST = Slow;
	};

	Player(float X, KeyboardKey Up, KeyboardKey Down, KeyboardKey Slow, Color color)
	{
		Paddle.x = X;
		PaddleUP = Up;
		PaddleDOWN = Down;
		PaddleFAST = Slow;
		PaddleColor = color;
	};
	
	// Value(s) and Variable(s) //
	Rectangle Paddle { DefaultPaddleX, PaddleY, PaddleWidth, PaddleHeight };
	Color PaddleColor = WHITE;
	bool canHitBall = true;

	// Core Function(s) //
	void Update()
	{
		float deltaTime = GetFrameTime();

		if (IsKeyDown(PaddleFAST))
		{
			if (currentSpeed != maxSpeed)
				currentSpeed = maxSpeed;
		}

		else
		{
			if (currentSpeed != standardSpeed)
				currentSpeed = standardSpeed;
		}

		if (IsKeyDown(PaddleUP))
		{
			Paddle.y -= currentSpeed * deltaTime;

			if (Paddle.y < 0 - Paddle.height)
				Paddle.y = GetScreenHeight();
		}

		if (IsKeyDown(PaddleDOWN))
		{
			Paddle.y += currentSpeed * deltaTime;

			if (Paddle.y > GetScreenHeight())
				Paddle.y = -Paddle.height;
		}
	}

	void Draw()
	{
		DrawRectangleRec(Paddle, PaddleColor);
	}

	void Reset()
	{
		Paddle.y = PaddleY;

		if (!canHitBall)
		{
			canHitBall = true;
		}
	}

	// Other Function(s) //
	void DrawDebug(int xPos, int textSize)
	{	
		std::string a = std::to_string(Paddle.x);
		std::string b = std::to_string(Paddle.y);
		std::string c = std::to_string(Paddle.width);
		std::string d = std::to_string(Paddle.height);
		std::string e = std::to_string(currentSpeed);

		std::string f = std::to_string(canHitBall);
		
		if (f == std::string("1"))
			f = std::string("true");
		else
			f = std::string("false");

		char const* z = a.c_str();
		char const* y = b.c_str();
		char const* x = c.c_str();
		char const* w = d.c_str();
		char const* v = e.c_str();
		char const* u = f.c_str();

		int startingPoint = floatToInt(GetScreenHeight() / 2 - Paddle.height);

		DrawText(z, xPos, startingPoint, textSize, PaddleColor);
		DrawText(y, xPos, startingPoint + textSize, textSize, PaddleColor);
		DrawText(x, xPos, startingPoint + (textSize * 2), textSize, PaddleColor);
		DrawText(w, xPos, startingPoint + (textSize * 3), textSize, PaddleColor);
		DrawText(v, xPos, startingPoint + (textSize * 4), textSize, PaddleColor);
		DrawText(u, xPos, startingPoint + (textSize * 5), textSize, PaddleColor);
	}
};

struct Ball
{
private:
	// Default(s) //
	Vector2 defaultBallPosition = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};
	Vector2 defaultBallSpeed = { 300.0f, 300.0f };
	Color defaultBallColor = WHITE;

public:
	// Constructor(s) //
	Ball() {};
	~Ball() {};

	Ball(Color color)
	{
		ballColor = color;
	}

	Ball(Color color, float radius)
	{
		ballColor = color;
		ballRadius = radius;
	}

	// Value(s) and Variable(s) //
	Vector2 ballPosition = defaultBallPosition;
	Vector2 ballSpeed = defaultBallSpeed;
	Color ballColor = defaultBallColor;
	float ballRadius = 5.0f;
	bool ballCollided = false;

	// Core Function(s) //
	void Update()
	{
		ballPosition.x += ballSpeed.x * GetFrameTime();
		ballPosition.y += ballSpeed.y * GetFrameTime();

		ballCollided = false;

		if (ballPosition.y < 0)
		{
			ballPosition.y = 0;
			ballSpeed.y *= -1;

			ballCollided = true;
		}

		if (ballPosition.y > GetScreenHeight())
		{
			ballPosition.y = GetScreenHeight();
			ballSpeed.y *= -1;

			ballCollided = true;
		}
	}

	void Draw()
	{
		DrawCircleV(ballPosition, ballRadius, ballColor);
	}

	void Reset()
	{
		ballPosition = defaultBallPosition;
		ballSpeed = defaultBallSpeed;
		ballColor = defaultBallColor;
	}

	// Other Function(s) //
	void DrawDebug(int xPos, int textSize)
	{
		std::string a = std::to_string(ballPosition.x);
		std::string b = std::to_string(ballPosition.y);
		std::string c = std::to_string(ballSpeed.x);
		std::string d = std::to_string(ballSpeed.y);
		std::string e = std::to_string(ballRadius);
		
		std::string f = std::to_string(ballCollided);

		if (f == std::string("1"))
			f = std::string("true");
		else
			f = std::string("false");

		char const* z = a.c_str();
		char const* y = b.c_str();
		char const* x = c.c_str();
		char const* w = d.c_str();
		char const* v = e.c_str();
		char const* u = f.c_str();

		int startingPoint = floatToInt(GetScreenHeight() - (textSize * 6));

		DrawText(z, xPos, startingPoint, textSize, ballColor);
		DrawText(y, xPos, startingPoint + textSize, textSize, ballColor);
		DrawText(x, xPos, startingPoint + (textSize * 2), textSize, ballColor);
		DrawText(w, xPos, startingPoint + (textSize * 3), textSize, ballColor);
		DrawText(v, xPos, startingPoint + (textSize * 4), textSize, ballColor);
		DrawText(u, xPos, startingPoint + (textSize * 5), textSize, ballColor);
	}
};