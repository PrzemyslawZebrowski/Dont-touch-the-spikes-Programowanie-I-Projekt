#pragma once
#include "definitions.h"
#include "State.h"
#include <stack>

class StateMachine
{
public:
	StateMachine();
	State* getActiveState();
	void addState(State*,bool replace = true);
	void removeState();
	void changingProcess();

	
private:
	std::stack<State*> stack;

	State* _state;
	bool isAdding;
	bool isRemoving;
	bool isReplacing;
};

