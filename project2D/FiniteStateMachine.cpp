#include "FiniteStateMachine.h"

void FiniteStateMachine::Update(Agent * agent, float deltaTime)
{
	currentState->Update(agent, this);
}

void FiniteStateMachine::ChangeState(Agent * agent, State * newState)
{
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
