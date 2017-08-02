#pragma once
#include "SeekForce.h"
class WanderForce :public SeekForce
{
public:
	WanderForce();
	virtual MathDLL::Vector2 getForce(Agent * agent);
private:
	MathDLL::Vector2 m_prevTarget;
	//const float TIMER = 5;
	//const float   = 20;
};