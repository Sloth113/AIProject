#pragma once
class FiniteStateMachine;
class Agent;
class State
{
public:
	virtual void Update(Agent * agent, FiniteStateMachine * sm) = 0;
	virtual void Init(Agent * agent) = 0;
	virtual void Exit(Agent * agent) = 0;
};