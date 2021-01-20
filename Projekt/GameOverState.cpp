#include "GameOverState.h"

GameOverState::GameOverState(Gamedata* d, int s)
{
	data = d;
	score = s;
	ScoreMachine* scoreMachine = new ScoreMachine();;
	scoreMachine->loadList();
	scoreMachine->addScore(score);
	scoreMachine->sortList();
	scoreMachine->saveList();
	bestScore = scoreMachine->getTopScore().points;
	delete scoreMachine;
	

	
	loadImg();
	loadText();
	loadButton();
}

void GameOverState::Update()
{
}

void GameOverState::Render()
{
	data->window.draw(background);

	data->window.draw(gameOver);

	data->window.draw(board);
	for (int i = 0; i < 2; i++)
	{
		data->window.draw(button[i]);
		data->window.draw(buttonText[i]);
	}
	data->window.draw(titleBoard);
	data->window.draw(currentScoreText);
	data->window.draw(bestScoreText);
	
}

void GameOverState::Input()
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

void GameOverState::loadImg()
{
	backgroundimg.loadFromFile("src/background.png");
	background.setTexture(backgroundimg);

	gameOverimg.loadFromFile("src/gameover.png");
	gameOver.setTexture(gameOverimg);

	auto lb = gameOver.getLocalBounds();
	gameOver.setOrigin(lb.width / 2, lb.height / 2);
	gameOver.setPosition(WINDOW_WIDTH / 2, 120);
	gameOver.setScale(sf::Vector2f(1.1f, 1.1f));

	boardimg.loadFromFile("src/board.png");
	board.setTexture(boardimg);

	lb = board.getLocalBounds();
	board.setOrigin(lb.width / 2, lb.height / 2);
	board.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 50);
	board.setScale(sf::Vector2f(.5f, .5f));


}

void GameOverState::loadButton()
{
	buttonimg.loadFromFile("src/button_img.png");

	for (int i = 0; i < 2; i++)
	{
		button[i].setTexture(buttonimg);
		auto lb = button[i].getLocalBounds();
		button[i].setOrigin(lb.width / 2, lb.height / 2);
		sf::Vector2f pos(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 200 + 100 *i);
		button[i].setPosition(pos);
		lb = buttonText[i].getLocalBounds();
		buttonText[i].setOrigin(lb.width / 2, lb.height / 2 + 5);
		buttonText[i].setPosition(pos);
	}

}

void GameOverState::loadText()
{
	font.loadFromFile("src/Chunk Five Print.otf");

	buttonText[0].setString("Jeszcze raz?");
	buttonText[1].setString("Wyjdz do menu");
	bestScoreText.setString("Najlepszy: " + std::to_string(bestScore));
	currentScoreText.setString("Aktualny:  " + std::to_string(score));
	titleBoard.setString("Wynik:");

	buttonText[0].setFont(font);
	buttonText[1].setFont(font);
	bestScoreText.setFont(font);
	currentScoreText.setFont(font);
	titleBoard.setFont(font);

	buttonText[0].setFillColor(sf::Color::Yellow);
	buttonText[1].setFillColor(sf::Color::White);
	bestScoreText.setFillColor(sf::Color::White);
	currentScoreText.setFillColor(sf::Color::White);
	titleBoard.setFillColor(sf::Color::White);

	auto gbb = board.getGlobalBounds();
	titleBoard.setPosition(gbb.left + gbb.width / 2, gbb.top + gbb.height / 4);
	currentScoreText.setPosition(gbb.left + gbb.width / 2, gbb.top + gbb.height * 2 / 4);
	bestScoreText.setPosition(gbb.left + gbb.width / 2, gbb.top + gbb.height * 3 / 4);

	titleBoard.setCharacterSize(40);
	currentScoreText.setCharacterSize(40);
	bestScoreText.setCharacterSize(40);

	titleBoard.setOrigin(titleBoard.getLocalBounds().width / 2, 20);
	currentScoreText.setOrigin(currentScoreText.getLocalBounds().width / 2, 20);
	bestScoreText.setOrigin(bestScoreText.getLocalBounds().width / 2, 20);

	
}
void GameOverState::MoveUp()
{
	buttonText[selectedItemIndex].setFillColor(sf::Color::White);
	selectedItemIndex--;
	if (selectedItemIndex < 0) selectedItemIndex = 1;
	buttonText[selectedItemIndex].setFillColor(sf::Color::Yellow);
}

void GameOverState::MoveDown()
{
	buttonText[selectedItemIndex].setFillColor(sf::Color::White);
	selectedItemIndex++;
	if (selectedItemIndex > 1) selectedItemIndex = 0;
	buttonText[selectedItemIndex].setFillColor(sf::Color::Yellow);
}

void GameOverState::Enter()
{
	switch (selectedItemIndex)
	{
	case 0:
		data->machine.addState(new GameState(data));
		break;
	case 1:
		data->machine.removeState();
		break;
	default:
		break;
	}
}