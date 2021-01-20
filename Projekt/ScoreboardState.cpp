#include "ScoreboardState.h"

ScoreboardState::ScoreboardState(Gamedata* d)
{
	data = d;

	loadImg();
	loadText();
	loadButton();
	
	auto _scoremachine = new ScoreMachine();
	_scoremachine->loadList();
	_scoremachine->sortList();
	
	sf::Text line;
	line.setFont(font);
	line.setFillColor(sf::Color::White);

	for (int i = 1; i <= 10; i++)
	{
		std::string linetxt(_scoremachine->getScoreLine(i));
		line.setString(linetxt);
		line.setOrigin(line.getGlobalBounds().width / 2, 0);
		line.setPosition(WINDOW_WIDTH / 2, 80 + 50 * i);
		scoreboardLines.push_back(line);
	}
}

void ScoreboardState::Update()
{
}

void ScoreboardState::Render()
{
	data->window.draw(background);

	data->window.draw(board);
	
	data->window.draw(titleBoard);

	data->window.draw(button);

	data->window.draw(buttonText);

	for(auto i : scoreboardLines)
		data->window.draw(i);
}

void ScoreboardState::Input()
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

void ScoreboardState::loadImg()
{
	backgroundimg.loadFromFile("src/background.png");
	background.setTexture(backgroundimg);

	boardimg.loadFromFile("src/board.png");
	board.setTexture(boardimg);

	auto lb = board.getLocalBounds();
	board.setOrigin(lb.width / 2, lb.height / 2);
	board.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 50);
	board.setScale(sf::Vector2f(.8f, .9f));
	board.rotate(90);
}

void ScoreboardState::loadButton()
{
	buttonimg.loadFromFile("src/button_img.png");

	button.setTexture(buttonimg);
	auto lb = button.getLocalBounds();
	button.setOrigin(lb.width / 2, lb.height/2);

	sf::Vector2f pos(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 80);
	button.setPosition(pos);
	lb = buttonText.getLocalBounds();
	buttonText.setOrigin(lb.width / 2, lb.height / 2 + 5);
	buttonText.setPosition(pos);
}

void ScoreboardState::loadText()
{
	font.loadFromFile("src/Chunk Five Print.otf");

	buttonText.setString("Wroc do menu");
	titleBoard.setString("Tabela wynikow");

	buttonText.setFont(font);
	titleBoard.setFont(font);

	buttonText.setFillColor(sf::Color::Yellow);
	titleBoard.setFillColor(sf::Color::White);

	
	titleBoard.setPosition(WINDOW_WIDTH / 2, 80);
	

	titleBoard.setCharacterSize(40);
	titleBoard.setOrigin(titleBoard.getLocalBounds().width / 2, 20);
}

void ScoreboardState::Enter()
{
	data->machine.removeState();
}
