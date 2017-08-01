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
		m_target = m_agent->GetPos();
	
	MathDLL::Vector2 vel = (m_target - agent->GetPos());
	if (vel.getMagSquare() != 0)
		vel.normalise();
	vel = vel * agent->GetSpeed(); //STILL MAX
	MathDLL::Vector2 force = vel - agent->GetVel();
	
	return force;
}
