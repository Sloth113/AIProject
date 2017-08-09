#pragma once
#include "SteeringForce.h"

class SeparationForce : public SteeringForce
{
public:
	virtual MathDLL::Vector2 getForce(Agent * agent);
};