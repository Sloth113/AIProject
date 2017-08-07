#pragma once
#include "Composite.h"
class Sequence : public Composite
{
	virtual bool Update(Agent *pAgent, float deltaTime)
	{
		for (auto child = children.begin(); child != children.end(); child++)
		{
			if ((*child)->Update(pAgent, deltaTime) == false)
			{
				return false;
			}
		}
		return true;
	}
};