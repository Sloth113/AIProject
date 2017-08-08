#pragma once
#include "IBehaviour.h"
#include <list>
class Composite : public IBehaviour
{
public:
	virtual BehaviourResult Update(Agent *pAgent, float deltaTime) = 0;
protected:
	std::list<IBehaviour *> children;
};