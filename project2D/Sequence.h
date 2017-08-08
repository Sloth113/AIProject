#pragma once
#include "Composite.h"
class Sequence : public Composite
{
	virtual BehaviourResult Update(Agent *pAgent, float deltaTime)
	{
		for (auto child = children.begin(); child != children.end(); child++)
		{
			if ((*child)->Update(pAgent, deltaTime) == BehaviourResult::Failure)
			{
				return BehaviourResult::Failure;
			}
		}
		return BehaviourResult::Success;
	}
};