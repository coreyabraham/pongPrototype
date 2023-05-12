// Header(s) //
#pragma once
#include "application.h"

// Function(s) //
inline int floatToInt(float value) 
{ 
	return static_cast<int>(value); 
}

// Struct(s) //
struct ClickButton
{
private:
	bool outlineApplicable = false;
	Color highlightColor = WHITE;
	float highlightThickness = 5.0f;

	Rectangle outline = {  };

public:
	// Constructor(s) //
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
	}

	void Draw()
	{
		DrawRectangleRec(coreButton, btnColor);
		DrawText(btnText, floatToInt(coreButton.x), floatToInt(coreButton.y), floatToInt(coreButton.height - 10), txtColor);
	}

	// Outline Function(s) //
	void DrawOutline()
	{
		if (outlineApplicable)
		{
			DrawRectangleRec(outline, highlightColor);
		}
	}
};

struct Player
{
private:
	// Default(s) //
	float PaddleWidth = 10.0f;
	float PaddleHeight = 100.0f;

	float PaddleY = (Application::windowHeight / 2) - PaddleHeight;
	float defaultY = PaddleY;

	KeyboardKey PaddleUP = KEY_UP;
	KeyboardKey PaddleDOWN = KEY_DOWN;
	KeyboardKey PaddleSLOW = KEY_SPACE;

	float maxSpeed = 500.0f;
	float currentSpeed = maxSpeed;
	float halfSpeed = maxSpeed / 2.0f;
	
	float PaddleX = 50.0f;
	Color PaddleColor = WHITE;

public:
	// Constructor(s) //
	Player() {};
	~Player() {};

	Player(float X, KeyboardKey Up, KeyboardKey Down, KeyboardKey Slow)
	{
		PaddleX = X;
		PaddleUP = Up;
		PaddleDOWN = Down;
		PaddleSLOW = Slow;
	};

	Player(float X, KeyboardKey Up, KeyboardKey Down, KeyboardKey Slow, Color color)
	{
		PaddleX = X;
		PaddleUP = Up;
		PaddleDOWN = Down;
		PaddleSLOW = Slow;
		PaddleColor = color;
	};
	
	// Value(s) and Variable(s) //
	Rectangle Paddle { PaddleX, PaddleY, PaddleWidth, PaddleHeight };

	void Update()
	{
		float deltaTime = GetFrameTime();

		if (IsKeyDown(PaddleSLOW))
		{
			if (currentSpeed != halfSpeed)
				currentSpeed = halfSpeed;
		}

		else
		{
			if (currentSpeed != maxSpeed)
				currentSpeed = maxSpeed;
		}

		if (IsKeyDown(PaddleUP))
		{
			Paddle.y -= currentSpeed * deltaTime;
		}

		if (IsKeyDown(PaddleDOWN))
		{
			Paddle.y += currentSpeed * deltaTime;
		}
	}

	void Draw()
	{
		DrawRectangleRec(Paddle, PaddleColor);
	}

	void Reset()
	{
		 Paddle.y = defaultY;
	}
};