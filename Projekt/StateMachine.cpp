#include "StateMachine.h"


StateMachine::StateMachine()
{
	isAdding = false;
	isRemoving = false;
	isReplacing = false;
	_state = nullptr;
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
