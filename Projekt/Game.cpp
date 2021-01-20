#include "Game.h"
#include "MenuState.h"
#include "SplashState.h"

Game::Game(int h, int w, std::string n)
{
	data->window.create(sf::VideoMode(h, w), n);
    data->window.setFramerateLimit(60);
    data->machine.addState(new SplashState(data),false);
    this->run();
}

void Game::run()
{
    while (data->window.isOpen())
    {
        data->machine.changingProcess();
        data->machine.getActiveState()->Input();
        data->machine.getActiveState()->Update();
        data->window.clear();
        data->machine.getActiveState()->Render();
        data->window.display();
    }
}
