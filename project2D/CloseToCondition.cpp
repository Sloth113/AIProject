#include "CloseToCondition.h"
#include "Agent.h"
CloseToCondition::CloseToCondition(float range, Agent * agent)
{
	m_range = range;
	m_avoiding = agent;
}

BehaviourResult CloseToCondition::Update(Agent * pAgent, float deltaTime)
{
	std::cout << "Close CHECK\n";
	MathDLL::Vector2 dis = m_avoiding->GetPos() - pAgent->GetPos();
	if (dis.getMagSquare() < m_range * m_range)
	{
		return BehaviourResult::Success;
	}
	return BehaviourResult::Failure;
}
