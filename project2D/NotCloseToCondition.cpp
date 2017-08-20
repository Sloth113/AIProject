#include "NotCloseToCondition.h"

#include "Agent.h"
NotCloseToCondition::NotCloseToCondition(float range, Agent * agent)
{
	m_range = range;
	m_avoiding = agent;
}

BehaviourResult NotCloseToCondition::Update(Agent * pAgent, float deltaTime)
{
	MathDLL::Vector2 dis = m_avoiding->getPos() - pAgent->getPos();
	if (dis.getMagSquare() < m_range * m_range)
	{
		return BehaviourResult::Failure;
	}
	return BehaviourResult::Success;
}
