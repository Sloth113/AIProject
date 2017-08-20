#include "CloseToCondition.h"
#include "Agent.h"
CloseToCondition::CloseToCondition(float range, Agent * agent)
{
	m_range = range;
	m_avoiding = agent;
}

BehaviourResult CloseToCondition::Update(Agent * pAgent, float deltaTime)
{
	MathDLL::Vector2 dis = m_avoiding->getPos() - pAgent->getPos();
	if (dis.getMagSquare() < m_range * m_range)
	{
		return BehaviourResult::Success;
	}
	return BehaviourResult::Failure;
}
