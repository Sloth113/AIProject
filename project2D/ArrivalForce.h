#pragma once
#pragma once
#include "SteeringForce.h"
class ArrivalForce :public SteeringForce
{
public:
	ArrivalForce(Agent * target);
	ArrivalForce(float weight);
	ArrivalForce(MathDLL::Vector2 target);
	virtual MathDLL::Vector2 getForce(Agent * agent);

	Agent * m_agent;
	MathDLL::Vector2 m_target;
};