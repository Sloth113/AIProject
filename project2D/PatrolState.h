#pragma once
#include "State.h"
#include "MathLibDLL.h"
struct PatrolPoint
{
	MathDLL::Vector2 pos;
	PatrolPoint * next;
};
class PatrolState :public State
{
public:
	virtual void Update(Agent * agent, FiniteStateMachine * sm);
	virtual void Init(Agent * agent);
	virtual void Exit(Agent * agent);
private:
	PatrolPoint * points;
	int numOfPoints;
	PatrolPoint currentPoint;
};