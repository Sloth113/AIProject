#pragma once
#include "IBehaviour.h"
class CloseToCondition : public IBehaviour
{
public:
	CloseToCondition(float range, Agent * agent);
	virtual BehaviourResult Update(Agent *pAgent, float deltaTime);
private:
	float m_range;
	Agent * m_avoiding;
};