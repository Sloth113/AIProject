#include "SeekForce.h"
#include "Agent.h"

SeekForce::SeekForce(Agent * target)
{
	m_target = target;
}

MathDLL::Vector2 SeekForce::getForce(Agent * agent)
{
	MathDLL::Vector2 vel = (m_target->getPos() - agent->getPos()) * agent->GetSpeed(); //STILL MAX
	MathDLL::Vector2 force = vel - agent->GetVel();
	return force;
}
