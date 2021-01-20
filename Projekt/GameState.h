#pragma once
#include "State.h"
#include "Game.h"
#include <string>
#include "GameOverState.h"

class GameState : public State
{
public:
	GameState(Gamedata*);
	virtual void Update();
	virtual void Render();
	virtual void Input();
private:
	Gamedata* data;
	
	void gameOver();
	bool isOver;

	//Zwiazane z Ptakiem

	sf::Sprite bird;
	sf::Texture birdimg;
	sf::Vector2f birdSpeed;
	void Jump();
	void loadBird();

	// Mapa
	sf::Color activeColor;
	sf::RectangleShape bottomBar, upperBar, leftBar, rightBar;
	void loadMap();
	void ChangeColor();

	//Kolce
	std::vector<sf::ConvexShape> upperSpikes;
	std::vector<sf::ConvexShape> bottomSpikes;
	std::vector<sf::ConvexShape> leftSpikes;
	std::vector<sf::ConvexShape> rightSpikes;

	void loadSpikes();
	void randLeftSpikes();
	void randRightSpikes();

	void moveSpikes();

	// Punkty
	int points;
	sf::Font font;
	sf::Text pointsDisplay;
	sf::CircleShape pointsDisplayBackground;
	void setPointsDisplay();
	void loadPointsDisplay();
	
	// Poziom Trudnosci
	int level;
	void LevelUp();

	// Dzwieki
	void loadSound();
	sf::SoundBuffer wallHitBuffer, birdDiesBuffer;
	sf::Sound wallHitSound, birdDiesSound;
	sf::Music bgMusic;

	// Do mierzenia czasu 
	sf::Clock clock;
};

