#pragma once
#include "SteeringForce.h"
class FleeForce :public SteeringForce
{
public:
	FleeForce();
	FleeForce(Agent * target);
	FleeForce(MathDLL::Vector2 target);
	virtual MathDLL::Vector2 getForce(Agent * agent);

protected:
	Agent * m_agent;
	MathDLL::Vector2 m_target;
};