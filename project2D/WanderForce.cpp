#include "WanderForce.h"
#include "Agent.h"



WanderForce::WanderForce()
{
	m_agent = nullptr;
}

MathDLL::Vector2 WanderForce::getForce(Agent * agent)
{
	if (m_prevTarget.getMagSquare() == 0 || (m_target - agent->GetPos()).getMagSquare() < 10)
	{
		m_prevTarget = MathDLL::Vector2(rand() % 1281,rand() % 721);
	}
	m_target = m_prevTarget;

	/*
	float wanderAngle;

	MathDLL::Vector2 cirCenter = agent->GetVel();
	if(cirCenter.getMagSquare() != 0)
		cirCenter.normalise();
	cirCenter = cirCenter * CIRCLE_DIST;

	MathDLL::Vector2 displacement = MathDLL::Vector2(0, 0); //YAXIS ALIGN
	displacement = displacement * CIRCLE_RAD;

	//CHANGE ANGLE
	wanderAngle = rand() % 11 -5 ;
	displacement.x += wanderAngle;

	wanderAngle = rand() % 11 - 5;
	displacement.y += wanderAngle;

	if(displacement.getMagSquare() != 0)
		displacement.normalise();
	displacement = displacement * CIRCLE_RAD;

	//DIS = dis - r * tan (wanderangle);
	//Dis.normalise
	//dis = dis * circRad;

	//MathDLL::Vector2 force;
	*/
	return SeekForce::getForce(agent);
}
