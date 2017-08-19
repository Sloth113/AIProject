#pragma once
#include "SteeringForce.h"
class ForceStillForce :public SteeringForce
{
public:

	ForceStillForce();
	ForceStillForce(float weight);
	
	virtual MathDLL::Vector2 getForce(Agent * agent);
};