#pragma once
#include "Composite.h"
class Selector : public Composite
{
	virtual bool Update(Agent *pAgent, float deltaTime)
	{
		for (auto child = children.begin(); child != children.end(); child++)
		{
			if ((*child)->Update(pAgent, deltaTime) == true)
			{
				return true;
			}
		}
		return false;
	}
};