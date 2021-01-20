#pragma once
#include "State.h"
#include "Game.h"
#include "definicje.h"
#include "MenuState.h"

class SplashState : public State
{
public:
	SplashState(Gamedata*);
	virtual void Update();
	virtual void Render();
	virtual void Input();
private:
	Gamedata* data;
	sf::Font font;
	sf::Text text;
	int transparency;
	sf::Clock clock;

};

