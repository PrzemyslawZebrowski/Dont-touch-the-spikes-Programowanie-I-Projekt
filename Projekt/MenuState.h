#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include "definitions.h"
#include "State.h"
#include "game.h"
#include "GameState.h"
#include "ScoreboardState.h"
#include "RulesState.h"

class MenuState : public State
{
public:
	 static const int size = 4;

	 
	 MenuState(Gamedata*);
	 void MoveUp();
	 void MoveDown();
	 void Enter();
	 virtual void Update();
	 virtual void Render();
	 virtual void Input();

private:
	
	
	// tlo
	sf::Texture backgroundimg; 
	sf::Sprite background;

	void loadBackground();
	
	// przyciski
	sf::Texture buttonimg;
	sf::Sprite buttons[size];
	std::string textInside[size]{ "Graj!","Tabela wynikow","Jak grac?","Wyjdz" };
	int selectedItemIndex;
	sf::Font font;
	sf::Text text[size];

	void loadButtons();

	// tytul
	sf::Texture titleTexture[2];
	sf::Sprite title[2];

	void loadTitle();
	
	Gamedata* data;
};

