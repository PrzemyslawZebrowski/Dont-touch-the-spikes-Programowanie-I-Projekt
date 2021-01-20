#include "MenuState.h"


MenuState::MenuState(Gamedata* dane)
{
	this->data = dane;

	loadBackground();
	loadButtons();
	loadTitle();

}

void MenuState::Update()
{
	;
}

void MenuState::Render()
{
	data->window.draw(background);
	for (int i = 0; i < size; i++)
		data->window.draw(buttons[i]);
	for (int i=0; i < size; i++)
		data->window.draw(text[i]);
	for (int i = 0; i < 2; i++)
		data->window.draw(title[i]);
	
}

void MenuState::Input()
{
	sf::Event event;
	while (data->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			data->window.close();
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W)
			MoveUp();
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
			MoveDown();
		if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Space))
			Enter();
	}
}

void MenuState::loadBackground()
{
	backgroundimg.loadFromFile("src/background.png");
	background.setTexture(backgroundimg);
}

void MenuState::loadButtons()
{
	font.loadFromFile("src/Chunk Five Print.otf");

	buttonimg.loadFromFile("src/button_img.png");

	for (int i{}; i < size; i++)
	{
		text[i].setFont(font);
		text[i].setFillColor(sf::Color::White);
		text[i].setString(textInside[i]);
		text[i].setOrigin(sf::Vector2f(text[i].getLocalBounds().width / 2, text[i].getLocalBounds().height / 2));
		text[i].setPosition(sf::Vector2f((WINDOW_WIDTH / 2), 200 + (WINDOW_HEIGHT / 7) * (i + 1)));

		buttons[i].setTexture(buttonimg);
		buttons[i].setOrigin(sf::Vector2f(buttons[i].getLocalBounds().width / 2, buttons[i].getLocalBounds().height / 2));
		buttons[i].setPosition(text[i].getPosition().x, text[i].getPosition().y + 5);

	}

	text[0].setFillColor(sf::Color::Yellow);
	selectedItemIndex = 0;
}

void MenuState::loadTitle()
{
	titleTexture[0].loadFromFile("src/title_1.png");
	titleTexture[1].loadFromFile("src/title_2.png");
	for (int i = 0; i < 2; i++)
	{
		title[i].setTexture(titleTexture[i]);
		auto _lb = title[i].getLocalBounds();
		title[i].setOrigin(_lb.width / 2, _lb.height / 2);
		title[i].setPosition(WINDOW_WIDTH / 2-7, (i==0)? (_lb.height / 2 + 40) : (1.2 * _lb.height + 40));
	}
}

void MenuState::MoveUp()
{
	text[selectedItemIndex].setFillColor(sf::Color::White);
	selectedItemIndex--;
	if (selectedItemIndex < 0) selectedItemIndex = size-1;
	text[selectedItemIndex].setFillColor(sf::Color::Yellow);
}

void MenuState::MoveDown()
{
	text[selectedItemIndex].setFillColor(sf::Color::White);
	selectedItemIndex++;
	if (selectedItemIndex > size-1) selectedItemIndex = 0;
	text[selectedItemIndex].setFillColor(sf::Color::Yellow);
}

void MenuState::Enter()
{
	switch (selectedItemIndex)
	{
	case 0:
		data->machine.addState(new GameState(data),false);
		break;
	case 1:
		data->machine.addState(new ScoreboardState(data), false);
		break;
	case 2:
		data->machine.addState(new RulesState(data), false);
		break;
	case 3:
		data->window.close();
		break;
	default:
		break;
	}
}

