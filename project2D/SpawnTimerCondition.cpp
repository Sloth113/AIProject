#include "SpawnTimerCondition.h"

SpawnTimerCondition::SpawnTimerCondition(float timer)
{
	m_spawnTime = timer;
}

BehaviourResult SpawnTimerCondition::Update(Agent *pAgent, float deltaTime)
{
	if (m_timer > m_spawnTime)
	{
		m_timer = 0;
		return BehaviourResult::Success;
	}
	m_timer += deltaTime;
	return BehaviourResult::Failure;
}
