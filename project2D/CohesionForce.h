#pragma once
#include "SteeringForce.h"

class CohesionForce : public SteeringForce
{
public:
	virtual MathDLL::Vector2 getForce(Agent * agent);
};