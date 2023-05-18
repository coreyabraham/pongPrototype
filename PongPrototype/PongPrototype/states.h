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

	void UpdateStates();
	void DrawStates();

	enum CoreState { Intro = 1, Title = 2, Game = 3, CNULL = 4 };
	enum TitleState { Main = 1, Modes = 2, Options = 3, Credits = 4, TNULL = 5 };
	enum GameState { Generic = 1, Solo = 2, GNULL = 3 };
};