#pragma once
#include "State.h"
#include "Game.h"
class RulesState :
    public State
{
public:
    RulesState(Gamedata*);
    virtual void Update();
    virtual void Render();
    virtual void Input();
private:
    sf::Texture backgroundimg;
    sf::Sprite background;

    sf::Texture buttonimg;
    sf::Sprite button;

    sf::Font font;
    sf::Text buttonText;

    void Enter();
    Gamedata* data;
};

