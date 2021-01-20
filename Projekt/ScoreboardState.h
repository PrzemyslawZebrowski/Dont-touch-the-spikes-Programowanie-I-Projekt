#pragma once
#include "State.h"
#include "GameState.h"
#include "ScoreMachine.h"
#include <vector>
#include <iostream>

class ScoreboardState :
    public State
{
public:
	ScoreboardState(Gamedata*);
	virtual void Update();
	virtual void Render();
	virtual void Input();
private:
	Gamedata* data;

	sf::Texture backgroundimg;
	sf::Sprite background;

	sf::Texture boardimg;
	sf::Sprite board;

	void loadImg();

	sf::Texture buttonimg;
	sf::Sprite button;
	void loadButton();

	sf::Font font;
	sf::Text buttonText, titleBoard;
	void loadText();

	std::vector<sf::Text> scoreboardLines;

	void Enter();
};

