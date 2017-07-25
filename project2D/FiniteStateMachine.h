#pragma once
#include "State.h"
class Agent;
class FiniteStateMachine
{
public:
	FiniteStateMachine();
	FiniteStateMachine(State * startState);
	void Update(Agent * agent);
	void ChangeState(Agent * agent, State * newState);
	State* GetCurrentState();
	State* GetPreviousState();

	State * currentState;
	State * prevState;
};