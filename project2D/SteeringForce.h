#pragma once
#include "MathLibDLL.h"
class Agent;
class SteeringForce
{
public:
	virtual MathDLL::Vector2 getForce(Agent * agent) = 0;
};