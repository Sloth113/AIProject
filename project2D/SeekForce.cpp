#include "SeekForce.h"
#include "Agent.h"

SeekForce::SeekForce()
{
	m_weight = 1;
	m_target = MathDLL::Vector2();
	m_agent = nullptr;
}
SeekForce::SeekForce(float weight)
{
	m_weight = weight;
	m_target = MathDLL::Vector2();
	m_agent = nullptr;
}

SeekForce::SeekForce(Agent * target)
{
	m_weight = 1;
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
	
	MathDLL::Vector2 vel = (m_target - agent->getPos());
	if (vel.getMagSquare() != 0)
		vel.normalise();
	vel = vel * agent->getSpeed(); //
	MathDLL::Vector2 force = vel - agent->getVel();
	return force * m_weight;
}
