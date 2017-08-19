#pragma once
#include "SteeringForce.h"
class SeekForce :public SteeringForce
{
public:

	SeekForce();
	SeekForce(float weight);
	SeekForce(Agent * target);
	SeekForce(MathDLL::Vector2 target);
	virtual MathDLL::Vector2 getForce(Agent * agent);


	Agent * m_agent;
	MathDLL::Vector2 m_target;
};