#pragma once
#include "SteeringForce.h"
class WanderForce :public SteeringForce
{
public:
	virtual MathDLL::Vector2 getForce(Agent * agent);
};