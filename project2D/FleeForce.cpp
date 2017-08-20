#include "FleeForce.h"
#include "Agent.h"

FleeForce::FleeForce()
{
	m_target = MathDLL::Vector2();
	m_agent = nullptr;
}

FleeForce::FleeForce(Agent * target)
{
	m_agent = target;
}

FleeForce::FleeForce(MathDLL::Vector2 target)
{
	m_target = target;
	m_agent = nullptr;
}

MathDLL::Vector2 FleeForce::getForce(Agent * agent)
{
	if (m_agent != nullptr)
		m_target = m_agent->getPos();

	MathDLL::Vector2 vel =  (agent->getPos()- (m_target));
	if (vel.getMagSquare() != 0)
		vel.normalise();
	vel = vel * agent->getSpeed(); //
	MathDLL::Vector2 force = vel - agent->getVel();

	return force;
}
