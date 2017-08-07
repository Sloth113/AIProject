#include "SteeringBehaviour.h"
#include "Agent.h"
SteeringBehaviour::SteeringBehaviour(SteeringForce * force)
{
	steerForce = force;
}
bool SteeringBehaviour::Update(Agent * pAgent, float deltaTime)
{
	pAgent->AddForce(steerForce->getForce(pAgent));
	return true;
}
