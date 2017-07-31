#include "SeekForce.h"
#include "Agent.h"

SeekForce::SeekForce(Agent * target)
{
	m_agent = target;
}

SeekForce::SeekForce(MathDLL::Vector2 target)
{
	m_target = target;
	m_agent = nullptr;
}

MathDLL::Vector2 SeekForce::getForce(Agent * agent)
{
	if (m_agent != nullptr)
		m_target = m_agent->getPos();
	
		MathDLL::Vector2 vel = (m_target - agent->getPos()) * agent->GetSpeed(); //STILL MAX
		MathDLL::Vector2 force = vel - agent->GetVel();
	
	return force;
}
