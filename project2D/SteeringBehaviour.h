#pragma once
#include "IBehaviour.h"
#include "SteeringForce.h"
//class SteeringForce;

class SteeringBehaviour : public IBehaviour
{
public:
	SteeringBehaviour(SteeringForce * force);
	virtual BehaviourResult Update(Agent *pAgent, float deltaTime);
private:
	SteeringForce * steerForce;
};