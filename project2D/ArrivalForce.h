#pragma once
#pragma once
#include "SteeringForce.h"
#include "SeekForce.h"
class ArrivalForce :public SeekForce
{
public:
	ArrivalForce(Agent * target);
	ArrivalForce(float weight);
	ArrivalForce(MathDLL::Vector2 target);
	virtual MathDLL::Vector2 getForce(Agent * agent);

//	Agent * m_agent;
//	MathDLL::Vector2 m_target;
};