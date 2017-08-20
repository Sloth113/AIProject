#include "AlignmentForce.h"
#include "Agent.h"
AlignmentForce::AlignmentForce(Agent * hood, int size, float dist)
{
	m_neighbourhood = hood;
	m_hoodSize = size;
	m_hoodDist = dist;
	m_weight = 1;
}
MathDLL::Vector2 AlignmentForce::getForce(Agent * agent)
{
	MathDLL::Vector2 alignmentForce = MathDLL::Vector2();

	//CHECK DISTS AND MAKE LOCAL HOOD

	for (int i = 0; i < m_hoodSize; i++)
	{
		alignmentForce += m_neighbourhood[i].getVel();
	}

	alignmentForce /= m_hoodSize;

	return (alignmentForce - agent->getVel()) * m_weight;
}
