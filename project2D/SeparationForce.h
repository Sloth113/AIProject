#pragma once
#include "SteeringForce.h"

class SeparationForce : public SteeringForce
{
public:
	SeparationForce(Agent * hood, int size, float dist);
	virtual MathDLL::Vector2 getForce(Agent * agent);
private:
	Agent * m_neighbourhood;
	int m_hoodSize;
	float m_hoodDist;
//	float m_weight;
};