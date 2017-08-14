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
	MathDLL::Vector2 m_wandPos;
	MathDLL::Vector2 m_tinyForce = MathDLL::Vector2(0.01f, 0.01f);
	float m_wanderAngle = 1;
	MathDLL::Vector2 m_cirCenter;
	MathDLL::Vector2 m_displacement;

	float timer;
};