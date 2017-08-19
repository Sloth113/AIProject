#include "ForceStillForce.h"
#include "Agent.h"
ForceStillForce::ForceStillForce()
{
}
ForceStillForce::ForceStillForce(float weight)
{
	m_weight = weight;
}
MathDLL::Vector2 ForceStillForce::getForce(Agent * agent)
{
	MathDLL::Vector2 force = agent->GetVel() * -1;
	return force * m_weight;
}
