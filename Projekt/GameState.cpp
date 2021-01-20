#include "GameState.h"


GameState::GameState(Gamedata* x)
{
	this->data = x;

	isOver = false;

	// Ustawiamy ptaka
	loadBird();

	// Kolor
	activeColor = sf::Color(128, 128, 128);
	
	// Mapa
	loadMap();

	// Kolce
	loadSpikes();
	
	// Do punktow
	loadPointsDisplay();

	// Dzwieki
	loadSound();
	
}

void GameState::Update()
{
	birdSpeed.y = birdSpeed.y + 0.2f;	// Grawitacja
	bird.move(birdSpeed);				// Przesuwamy ptaka

	moveSpikes();						// Animacja kolcy
	
	if (!isOver)
	{
		if (bird.getGlobalBounds().intersects(rightBar.getGlobalBounds()) || bird.getGlobalBounds().intersects(leftBar.getGlobalBounds()))
		{
			// Jezeli ptak udezy w sciane

			wallHitSound.play();

			bird.setScale(-bird.getScale().x, bird.getScale().y);		// obracamy go
			birdSpeed.x = -birdSpeed.x;									// odbija sie od œciany
			points += 1;												// gracz zdobywa punkt
			
			if (!(points % 5))LevelUp();								// co 5 punktow lvl up, kazdy lvl to mo¿liwy dodatkowy kolec na boku

			if (birdSpeed.x < 0)					// jezeli leci w lewo to:
				randLeftSpikes();					// losujemy kolce na lewej œcianie
			else									// jak nie to 
				randRightSpikes();					// losujemy na prawej
		}

		// Ponizej sprawdzamy czy ptak uderzyl w jakis kolec
		for (auto& spike : upperSpikes)
		{
			if (bird.getGlobalBounds().intersects(spike.getGlobalBounds()))
				gameOver();
		}
		for (auto& spike : bottomSpikes)
		{
			if (bird.getGlobalBounds().intersects(spike.getGlobalBounds()))
				gameOver();
		}
		for (auto& spike : leftSpikes)
		{
			if (bird.getGlobalBounds().intersects(spike.getGlobalBounds()))
				gameOver();
		}
		for (auto& spike : rightSpikes)
		{
			if (bird.getGlobalBounds().intersects(spike.getGlobalBounds()))
				gameOver();
		}

		// wysrodkowanie i aktualizacja naszego wyswietlacza punktow
		setPointsDisplay();
	}
	else
	{
		birdSpeed.x *= 0.90; // jesli udezy w kolec to jego predkosc jest w stopniowo wygaszana
		if (clock.getElapsedTime().asSeconds() > 3)
		{
			data->machine.addState(new GameOverState(data, points));
		}
			
	}
}

void GameState::Render()		// tu wszystko wyrzucamy na ekran
{
	data->window.clear(sf::Color::White);
	
	data->window.draw(upperBar);
	data->window.draw(bottomBar);
	data->window.draw(leftBar);
	data->window.draw(rightBar);
	// PUNKTY
	data->window.draw(pointsDisplayBackground);
	data->window.draw(pointsDisplay);
	// KOLCE
	for (auto &spike : upperSpikes)
	{
		data->window.draw(spike);
	}
	for (auto& spike : bottomSpikes)
	{
		data->window.draw(spike);
	}
	for (auto& spike : leftSpikes)
	{
		data->window.draw(spike);
	}
	for (auto& spike : rightSpikes)
	{
		data->window.draw(spike);
	}
	
	// PTAK
	data->window.draw(bird);
}

void GameState::Input()	// Obsluga wejscia
{
	sf::Event event;
	while (data->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			data->window.close();
		if (!isOver)
		{
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
				Jump();																				// jak spacja to ptak skacze
		}		
	}
}

void GameState::gameOver()			// koniec gry
{
	Jump();							// skok dla efektu jak w mario
	isOver = true;
	bgMusic.stop();
	birdDiesSound.play();
	clock.restart();				// zaczynamy mierzyc czas
}

void GameState::Jump()
{
	birdSpeed.y = -6;
}

void GameState::loadBird()
{
	birdimg.loadFromFile("src/bird.png");

	bird.setTexture(birdimg);
	bird.setOrigin(bird.getLocalBounds().width / 2, bird.getLocalBounds().height / 2);
	bird.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	birdSpeed = sf::Vector2f(4, 0);
}

void GameState::loadMap()
{
	// Paski góra/dó³

	upperBar = sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH, 75));
	bottomBar = sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH, 75));

	upperBar.setFillColor(activeColor);
	bottomBar.setFillColor(activeColor);

	bottomBar.move(0, WINDOW_HEIGHT - 75);

	// Paski lewo/prawo
	leftBar = sf::RectangleShape(sf::Vector2f(25, WINDOW_HEIGHT));
	rightBar = sf::RectangleShape(sf::Vector2f(25, WINDOW_HEIGHT));

	leftBar.setFillColor(activeColor);
	rightBar.setFillColor(activeColor);

	rightBar.move(WINDOW_WIDTH - 25, 0);
}

void GameState::ChangeColor()		// zmieniamy kolor mapy
{
	do
	{
		activeColor = sf::Color(rand() % 256, rand() % 256, rand() % 256);
	} while (activeColor.r > 230 && activeColor.g > 230 && activeColor.b > 230);		// nie mo¿e byæ za jansy bo nic nie widaæ

	pointsDisplayBackground.setFillColor(activeColor);
	leftBar.setFillColor(activeColor);
	rightBar.setFillColor(activeColor);
	upperBar.setFillColor(activeColor);
	bottomBar.setFillColor(activeColor);

	for (auto &spike : upperSpikes)
	{
		spike.setFillColor(activeColor);
	}
	for (auto& spike : bottomSpikes)
	{
		spike.setFillColor(activeColor);
	}
	for (auto& spike : leftSpikes)
	{
		spike.setFillColor(activeColor);
	}
	for (auto& spike : rightSpikes)
	{
		spike.setFillColor(activeColor);
	}
}

void GameState::loadSpikes()
{
	int p1{};
	for (int i = 0; i < 7; i++)
	{
		upperSpikes.push_back(sf::ConvexShape());
		upperSpikes.at(i).setPointCount(3);
		p1 = i * 50 + 25 + 19 + i * 7;
		upperSpikes.at(i).setPoint(0, sf::Vector2f(p1, 75.f));
		upperSpikes.at(i).setPoint(1, sf::Vector2f(p1 + 50.f, 75.f));
		upperSpikes.at(i).setPoint(2, sf::Vector2f(p1 + 25.f, 100.f));
		upperSpikes.at(i).setFillColor(activeColor);
	}
	for (int i = 0; i < 7; i++)
	{
		bottomSpikes.push_back(sf::ConvexShape());
		bottomSpikes.at(i).setPointCount(3);
		p1 = i * 50 + 25 + 19 + i * 7;
		bottomSpikes.at(i).setPoint(0, sf::Vector2f(p1, WINDOW_HEIGHT - 75.f));
		bottomSpikes.at(i).setPoint(1, sf::Vector2f(p1 + 50.f, WINDOW_HEIGHT - 75.f));
		bottomSpikes.at(i).setPoint(2, sf::Vector2f(p1 + 25.f, WINDOW_HEIGHT - 100.f));
		bottomSpikes.at(i).setFillColor(activeColor);
	}
}

void GameState::randLeftSpikes()
{
	leftSpikes.clear();
	int p{}, j{};
	for (int i = 0; i < level+1; i++)
	{
		j = rand() % 10;
		leftSpikes.push_back(sf::ConvexShape());
		leftSpikes.at(i).setPointCount(3);
		p = j * 50 + 75 + 17 + j * 7;
		leftSpikes.at(i).setPoint(0, sf::Vector2f(0, p));
		leftSpikes.at(i).setPoint(1, sf::Vector2f(0, p+50.f));
		leftSpikes.at(i).setPoint(2, sf::Vector2f(25.f, p+25.f));

		leftSpikes.at(i).setFillColor(activeColor);
	}
}

void GameState::randRightSpikes()
{
	rightSpikes.clear();
	int p{}, j{};
	for (int i = 0; i < level + 1; i++)
	{
		j = rand() % 10;
		rightSpikes.push_back(sf::ConvexShape());
		rightSpikes.at(i).setPointCount(3);
		p = j * 50 + 75 + 17 + j * 7;
		rightSpikes.at(i).setPoint(0, sf::Vector2f(WINDOW_WIDTH, p));
		rightSpikes.at(i).setPoint(1, sf::Vector2f(WINDOW_WIDTH, p + 50.f));
		rightSpikes.at(i).setPoint(2, sf::Vector2f(WINDOW_WIDTH - 25.f, p + 25.f));

		rightSpikes.at(i).setFillColor(activeColor);
	}
}

void GameState::moveSpikes()
{
	if (leftSpikes.size() > 0)
	{
		if (birdSpeed.x < 0)
		{
			if (leftSpikes.front().getPosition().x + 1 <= 25)
			{
				for (auto& spike : leftSpikes)
				{
					spike.move(1, 0);
				}
			}
		}
		else
		{
			if (leftSpikes.front().getPosition().x - 1 >= 0)
			{
				for (auto& spike : leftSpikes)
				{
					spike.move(-1, 0);
				}
			}
		}
	}
	if (rightSpikes.size() > 0)
	{	
		if (birdSpeed.x < 0)
		{
			if (rightSpikes.front().getPosition().x + 1 <= 0)
			{
				for (auto& spike : rightSpikes)
				{
					spike.move(1, 0);
				}
			}
		}
		else
		{
			if (rightSpikes.front().getPosition().x - 1 >= -25)
			{
				for (auto& spike : rightSpikes)
				{
					spike.move(-1, 0);
				}
			}
		}
	}
}

void GameState::setPointsDisplay()
{
	pointsDisplay.setString(std::to_string(points));
	pointsDisplay.setOrigin(pointsDisplay.getLocalBounds().width / 2, pointsDisplay.getLocalBounds().height / 2);
	pointsDisplay.setPosition(pointsDisplayBackground.getPosition());
}

void GameState::loadPointsDisplay()
{
	points = 0;
	level = 0;

	font.loadFromFile("src/Chunk Five Print.otf");
	pointsDisplay.setFont(font);
	pointsDisplay.setFillColor(sf::Color(255, 255, 255, 128));
	pointsDisplay.setCharacterSize(50);

	pointsDisplayBackground = sf::CircleShape(75);
	pointsDisplayBackground.setOrigin(75, 65);
	pointsDisplayBackground.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	pointsDisplayBackground.setFillColor(activeColor);
}

void GameState::LevelUp()
{
	ChangeColor();
	level++;
}

void GameState::loadSound()
{
	wallHitBuffer.loadFromFile("src/wall_hit.wav");
	wallHitSound.setBuffer(wallHitBuffer);
	wallHitSound.setVolume(20);

	birdDiesBuffer.loadFromFile("src/bird_dies _sound _effect.wav");
	birdDiesSound.setBuffer(birdDiesBuffer);
	birdDiesSound.setVolume(20);

	bgMusic.openFromFile("src/background_music.wav");
	bgMusic.setLoop(true);
	bgMusic.setVolume(5);
	bgMusic.play();
}
