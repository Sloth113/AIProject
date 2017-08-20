#include "ArrivalForce.h"
#include "Agent.h"

ArrivalForce::ArrivalForce(Agent * target)
{
	m_agent = target;
}

ArrivalForce::ArrivalForce(float weight)
{
	m_weight = weight;
	m_agent = nullptr;
}

ArrivalForce::ArrivalForce(MathDLL::Vector2 target)
{
	m_target = target;
	m_agent = nullptr;
}

MathDLL::Vector2 ArrivalForce::getForce(Agent * agent)
{
	float slowCircRad = 10.0f;
	if (m_agent != nullptr)
		m_target = m_agent->getPos();
	MathDLL::Vector2 vel;
	if ((m_target - agent->getPos()).getMagSquare() > slowCircRad*slowCircRad)
	{
		vel = (m_target - agent->getPos()).getNormalised() * agent->getSpeed(); //normal speed (seek)
	}
	else
	{
		vel += (m_target - agent->getPos()).getNormalised() * -1 *  ((m_target - agent->getPos()).magnitude() / slowCircRad); //Slow speed
	}
	MathDLL::Vector2 force = vel - agent->getVel();

	return SeekForce::getForce(agent) + force * m_weight;
}

