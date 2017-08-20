#pragma once
#include "IBehaviour.h"
class NotCloseToCondition : public IBehaviour
{
public:
	NotCloseToCondition(float range, Agent * agent);
	virtual BehaviourResult Update(Agent *pAgent, float deltaTime);
private:
	float m_range;
	Agent * m_avoiding;
};