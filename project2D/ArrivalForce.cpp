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
	float slowCircRad = 15;
	if (m_agent != nullptr)
		m_target = m_agent->GetPos();
	MathDLL::Vector2 vel;
	
	if ((m_target - agent->GetPos()).getMagSquare() > slowCircRad*slowCircRad)
	{
		vel = (m_target - agent->GetPos()).getNormalised() * agent->GetSpeed(); //normal speed (seek)
	}
	else
	{
		vel = (m_target - agent->GetPos()).getNormalised() * -1 *  ((m_target - agent->GetPos()).magnitude() / slowCircRad); //Slow speed
	}
	MathDLL::Vector2 force = vel - agent->GetVel();

	return force;
}

