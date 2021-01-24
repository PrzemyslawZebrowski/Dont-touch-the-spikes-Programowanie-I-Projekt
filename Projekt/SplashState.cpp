#include "SplashState.h"


SplashState::SplashState(Gamedata* dane)
{
	data = dane;
	font.loadFromFile("src/Chunk Five Print.otf");
	text.setFont(font);
	transparency = 0;
	text.setFillColor(sf::Color::White);
	text.setString(std::string("Dzien dobry!"));
	text.setOrigin(sf::Vector2f(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2));
	text.setPosition(sf::Vector2f(dane->window.getSize().x / 2, dane->window.getSize().y / 2));
	text.setCharacterSize(30);

}

void SplashState::Update()
{
	// z ka¿da klatka widocznosc napisu zwieksza sie
	if (transparency+1 < 256)transparency += 1;
	text.setFillColor(sf::Color(255, 255, 255, transparency));
	if (clock.getElapsedTime().asSeconds() > SPLASH_TIME)	// po 5 s przechodzimy dalej
	{
		data->machine.addState(new MenuState(data));
	}
}

void SplashState::Render()
{
	data->window.draw(text);
}

void SplashState::Input()
{
	sf::Event event;
	while (data->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			data->window.close();
		if (event.type == sf::Event::KeyPressed)
			data->machine.addState(new MenuState(data));
	}
}
