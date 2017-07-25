#pragma once
#include "SteeringForce.h"
class SeekForce :public SteeringForce
{
public:
	SeekForce(Agent * target);
	virtual MathDLL::Vector2 getForce(Agent * agent);

private:
	Agent * m_target;
};