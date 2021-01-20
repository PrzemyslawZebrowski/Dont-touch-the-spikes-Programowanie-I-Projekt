#pragma once
#include "SFML/Graphics.hpp"
class State
{
public:
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Input() = 0;
};

