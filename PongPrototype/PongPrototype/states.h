// Header(s) //
#pragma once

// Class(es) //
class States
{
public:
	States();
	~States();

	void Init();
	void Uninit();

	void UpdateStates(float deltaTime);
	void DrawStates(bool canDebug);

	enum CoreState { Intro = 1, Title = 2, Game = 3, CNULL = 4 };
	enum TitleState { Main = 1, Modes = 2, Credits = 3, TNULL = 4 };
	enum GameState { Generic = 1, Solo = 2, GNULL = 3 };
};