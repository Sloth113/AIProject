#pragma once
#include "IBehaviour.h"
#include "MathLibDLL.h"
#include "Input.h"
class DrunkModifier : public IBehaviour
{
public:
	virtual void Update(Agent * agent, float deltaTime);
private:
	float m_time;
};