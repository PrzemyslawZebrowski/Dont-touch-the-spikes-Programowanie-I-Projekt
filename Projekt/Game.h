#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <stack>
#include "State.h"
#include "StateMachine.h"

struct Gamedata
{
	sf::RenderWindow window;
	StateMachine machine;
};

class Game
{
public:
	Game(int, int, std::string);
	void run();
private:
	Gamedata* data = new Gamedata;
};
