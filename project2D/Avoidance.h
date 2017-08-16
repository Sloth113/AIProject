#pragma once
#include "SteeringForce.h"

class Avoidance : public SteeringForce
{
public:
	virtual MathDLL::Vector2 getForce(Agent * agent);
private:
	MathDLL::Vector2 whatToAvoid();
};