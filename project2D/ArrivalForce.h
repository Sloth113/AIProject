#pragma once
#pragma once
#include "SteeringForce.h"
class ArrivalForce :public SteeringForce
{
public:
	ArrivalForce(Agent * target);
	ArrivalForce(MathDLL::Vector2 target);
	virtual MathDLL::Vector2 getForce(Agent * agent);

private:
	Agent * m_agent;
	MathDLL::Vector2 m_target;
};