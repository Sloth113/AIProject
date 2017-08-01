#include "ArrivalForce.h"
#include "Agent.h"

ArrivalForce::ArrivalForce(Agent * target)
{
	m_agent = target;
}

ArrivalForce::ArrivalForce(MathDLL::Vector2 target)
{
	m_target = target;
	m_agent = nullptr;
}

MathDLL::Vector2 ArrivalForce::getForce(Agent * agent)
{
	float slowCircRad = 10;
	if (m_agent != nullptr)
		m_target = m_agent->GetPos();
	MathDLL::Vector2 vel;
	if ((m_target - agent->GetPos()).getMagSquare() > slowCircRad*slowCircRad)
	{
		vel = (m_target - agent->GetPos()).getNormalised() * agent->GetSpeed(); //STILL MAX
	}
	else
	{
		vel = (m_target - agent->GetPos()).getNormalised() * -1 *  ((m_target - agent->GetPos()).magnitude() / slowCircRad);
	}
	MathDLL::Vector2 force = vel - agent->GetVel();

	return force;
}

