#pragma once
#include "IBehaviour.h"
#include "MathLibDLL.h"
#include "Input.h"
class MouseController : public IBehaviour
{
public:
	virtual BehaviourResult Update(Agent * agent, float deltaTime);
};