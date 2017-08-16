#include "CohesionForce.h"
#include "Agent.h"

CohesionForce::CohesionForce(Agent * hood, int size, float dist)
{
	m_neighbourhood = hood;
	m_hoodSize = size;
	m_hoodDist = dist;
	m_weight = 1;
}

MathDLL::Vector2 CohesionForce::getForce(Agent * agent)
{
	MathDLL::Vector2 cohesionForce = MathDLL::Vector2();

	//CHECK DISTS AND MAKE LOCAL HOOD

	for (int i = 0; i < m_hoodSize; i++)
	{
		cohesionForce += m_neighbourhood[i].GetPos() - agent->GetPos();
	}

	cohesionForce /= m_hoodSize;

	return (cohesionForce - agent->GetVel()) * m_weight;
}
