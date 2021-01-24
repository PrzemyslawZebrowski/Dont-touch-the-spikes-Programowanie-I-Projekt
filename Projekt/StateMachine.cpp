#include "StateMachine.h"


StateMachine::StateMachine()
{
	isAdding = false;		// czy jest cos do dodania do stosu
	isRemoving = false;		// czy usunac grorny element stosu
	isReplacing = false;	// czy zamienic gorny element stosu
	_state = nullptr;		// wskaznik na state do dodania do stosu
}

State* StateMachine::getActiveState()
{
	return stack.top();
}

void StateMachine::addState(State* s,bool replace)
{
	_state = s;
	isAdding = true;
	isReplacing = replace;
}

void StateMachine::removeState()
{
	isRemoving = true;
}

void StateMachine::changingProcess()
{
	if (isAdding)
	{
		if (isReplacing)
		{
			delete stack.top();
			stack.pop();
			isReplacing = false;
		}
		stack.push(_state);
		_state = nullptr;
		isAdding = false;
	}
	if (isRemoving)
	{
		delete stack.top();
		stack.pop();
		isRemoving = false;
	}
}
