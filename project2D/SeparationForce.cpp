#include "SeparationForce.h"
#include "Agent.h"
SeparationForce::SeparationForce(Agent * hood, int size, float dist)
{
	m_neighbourhood = hood;
	m_hoodSize = size;
	m_hoodDist = dist;
	m_weight = 1;
}
MathDLL::Vector2 SeparationForce::getForce(Agent * agent)
{
	MathDLL::Vector2 separtionForce = MathDLL::Vector2();

	//CHECK DISTS AND MAKE LOCAL HOOD

	for (int i = 0; i < m_hoodSize; i++)
	{
		separtionForce += agent->GetPos() - m_neighbourhood[i].GetPos();
	}

	separtionForce /= m_hoodSize;

	return (separtionForce - agent->GetVel()) * m_weight;
}
