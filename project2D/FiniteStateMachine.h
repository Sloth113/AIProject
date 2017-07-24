#pragma once
#include "State.h"
class Agent;
class FiniteStateMachine
{
public:
	void Update(Agent * agent, float deltaTime);
	void ChangeState(Agent * agent, State * newState);
	State* GetCurrentState();
	State* GetPreviousState();

	State * currentState;
	State * prevState;
};