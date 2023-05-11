// Header(s) //
#pragma once
#include "application.h"

// Struct(s) //
class ClickButton
{
public:
	// Constructor(s) and Deconstructor(s) //

	ClickButton() {};
	~ClickButton() {};

	ClickButton(Vector2 Position, Vector2 Size)
	{
		coreButton.x = Position.x;
		coreButton.y = Position.y;

		coreButton.width = Size.x;
		coreButton.height = Size.y;
	};

	// Value(s) and Variable(s) //
	Rectangle coreButton = { 20, 20, 80, 40 };

	bool btnAction = false;
	bool btnHovering = false;

	const char* btnText = "BtnTextHere";

	Color btnColor = WHITE;
	Color txtColor = BLACK;

	// Function(s) //
	void Update()
	{
		if (CheckCollisionPointRec(GetMousePosition(), coreButton))
		{
			btnHovering = true;
			btnAction = false;

			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
				btnAction = true;
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
		DrawText(btnText, coreButton.x, coreButton.y, coreButton.height - 10, txtColor);
	}
};

class HoverOutline
{
private:
	// Default(s) //
	float thickness = 5.0f;

public:
	// Constructor(s) and Deconstructor(s) //
	HoverOutline(ClickButton targetButton)
	{
		outline.x = targetButton.coreButton.x;
		outline.y = targetButton.coreButton.y;

		outline.width = targetButton.coreButton.width + thickness;
		outline.height = targetButton.coreButton.height + thickness / 2;
	};

	HoverOutline(ClickButton targetButton, float Thickness)
	{
		outline.x = targetButton.coreButton.x;
		outline.y = targetButton.coreButton.y;

		outline.width = targetButton.coreButton.width + Thickness;
		outline.height = targetButton.coreButton.height + Thickness / 2;
	};

	HoverOutline(ClickButton targetButton, Color color)
	{
		outline.x = targetButton.coreButton.x;
		outline.y = targetButton.coreButton.y;

		outline.width = targetButton.coreButton.width + thickness;
		outline.height = targetButton.coreButton.height + thickness / 2;

		outlineColor = color;
	};

	HoverOutline(ClickButton targetButton, float Thickness, Color color)
	{
		outline.x = targetButton.coreButton.x;
		outline.y = targetButton.coreButton.y;

		outline.width = targetButton.coreButton.width + Thickness;
		outline.height = targetButton.coreButton.height + Thickness / 2;

		outlineColor = color;
	};

	~HoverOutline() {};

	// Value(s) and Variable(s) //
	Rectangle outline = {  }; // Requires Constructor in order to execute!
	Color outlineColor = WHITE;

	// Function(s) //
	void Draw()
	{
		DrawRectangleRec(outline, outlineColor);
	}
};