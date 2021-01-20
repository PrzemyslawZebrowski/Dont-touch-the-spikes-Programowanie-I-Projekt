#pragma once
#include "State.h"
#include "Game.h"
#include "GameState.h"
#include <string.h>
#include "ScoreMachine.h"

class GameOverState : public State
{
public:
	GameOverState(Gamedata*, int);

	virtual void Update();
	virtual void Render();
	virtual void Input();
private:
	Gamedata* data;
	int score, bestScore;

	sf::Texture backgroundimg;
	sf::Sprite background;

	sf::Texture boardimg;
	sf::Sprite board;

	sf::Texture gameOverimg;
	sf::Sprite gameOver;
	void loadImg();

	sf::Texture buttonimg;
	sf::Sprite button[2];
	void loadButton();

	sf::Font font;
	sf::Text buttonText[2], bestScoreText, currentScoreText, titleBoard;
	void loadText();


	// mini menu
	void MoveUp();
	void MoveDown();
	void Enter();
	int selectedItemIndex;
};

