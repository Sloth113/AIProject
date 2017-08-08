#pragma once
#include "Composite.h"
class Selector : public Composite
{
	virtual BehaviourResult Update(Agent *pAgent, float deltaTime)
	{
		for (auto child = children.begin(); child != children.end(); child++)
		{
			if ((*child)->Update(pAgent, deltaTime) == BehaviourResult::Success)
			{
				return BehaviourResult::Success;
			}
		}
		return BehaviourResult::Failure;
	}
};