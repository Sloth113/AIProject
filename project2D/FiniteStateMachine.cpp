#include "FiniteStateMachine.h"

FiniteStateMachine::FiniteStateMachine()
{
	currentState = nullptr;
	prevState = nullptr;
}

FiniteStateMachine::FiniteStateMachine(State * startState)
{
	currentState = startState;
	prevState = nullptr;
}

void FiniteStateMachine::Update(Agent * agent)
{
	if(currentState!= nullptr)
	currentState->Update(agent, this);
}

void FiniteStateMachine::ChangeState(Agent * agent, State * newState)
{
	if(currentState!= nullptr)
		currentState->Exit(agent);
	newState->Init(agent);
	prevState = currentState;
	currentState = newState;
}

State* FiniteStateMachine::GetCurrentState()
{
	return currentState;
}

State * FiniteStateMachine::GetPreviousState()
{
	return prevState;
}
