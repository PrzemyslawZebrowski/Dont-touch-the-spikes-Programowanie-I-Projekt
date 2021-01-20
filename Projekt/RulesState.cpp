#include "RulesState.h"

RulesState::RulesState(Gamedata* d)
{
	data = d;

	backgroundimg.loadFromFile("src/rules.png");
	background.setTexture(backgroundimg);

	font.loadFromFile("src/Chunk Five Print.otf");

	buttonText.setString("Wroc do menu");

	buttonText.setFont(font);

	buttonText.setFillColor(sf::Color::Yellow);

	buttonimg.loadFromFile("src/button_img.png");

	button.setTexture(buttonimg);
	auto lb = button.getLocalBounds();
	button.setOrigin(lb.width / 2, lb.height / 2);

	sf::Vector2f pos(SZERKOKOSC_OKNA / 2, WYSKOKOSC_OKNA - 80);
	button.setPosition(pos);
	lb = buttonText.getLocalBounds();
	buttonText.setOrigin(lb.width / 2, lb.height / 2 + 5);
	buttonText.setPosition(pos);
}

void RulesState::Update()
{
}

void RulesState::Render()
{
	data->window.draw(background);

	data->window.draw(button);

	data->window.draw(buttonText);

}

void RulesState::Input()
{
	sf::Event event;
	while (data->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			data->window.close();
		if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Space))
			Enter();
	}
}

void RulesState::Enter()
{
	data->machine.removeState();
}
