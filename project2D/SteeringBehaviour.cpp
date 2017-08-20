#include "SteeringBehaviour.h"
#include "Agent.h"
SteeringBehaviour::SteeringBehaviour(SteeringForce * force)
{
	steerForce = force;
}
BehaviourResult SteeringBehaviour::Update(Agent * pAgent, float deltaTime)
{
	pAgent->addForce(steerForce->getForce(pAgent));
	return BehaviourResult::Success;
}
