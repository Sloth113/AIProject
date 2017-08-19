#pragma once
#include "IBehaviour.h"

class SpawnTimerCondition : public IBehaviour
{
public:
	SpawnTimerCondition(float timer);
	virtual BehaviourResult Update(Agent *pAgent, float deltaTime);
private:
	float m_timer = 0;
	float m_spawnTime = 0;
};