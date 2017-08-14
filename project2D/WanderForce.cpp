#include "WanderForce.h"
#include "Agent.h"
#define _USE_MATH_DEFINES
#include <math.h>

const float CIRCLE_DIST = 50;
const float CIRCLE_RAD = 85;
const float ANGLE_CHANGE = 7.0f / 180.0f * M_PI;

WanderForce::WanderForce()
{
	m_agent = nullptr;
}

MathDLL::Vector2 WanderForce::getForce(Agent * agent)
{
	/*
	if (m_prevTarget.getMagSquare() == 0 || (m_target - agent->GetPos()).getMagSquare() < 10)
	{
		m_prevTarget = MathDLL::Vector2(rand() % 1281,rand() % 721);
	}
	m_target = m_prevTarget;
	*/

	m_cirCenter = agent->GetVel();
	float length = m_wandPos.magnitude();

	if (length == 0)
	{
		m_cirCenter = m_tinyForce;
	}

	m_cirCenter.normalise();
	m_cirCenter *= CIRCLE_DIST;
	m_cirCenter += agent->GetPos();

	//random number between -1 and 1
	float randNum = (((float)rand() / (float)RAND_MAX) - 0.5f) * 2.0f;

	m_wanderAngle += ANGLE_CHANGE * randNum;
	
	m_displacement = m_cirCenter.getNormalised();

	m_displacement *= CIRCLE_RAD;

	//ROTATION MATRIX
	MathDLL::Matrix2 rot = MathDLL::Matrix2(cos(m_wanderAngle), sin(m_wanderAngle), -sin(m_wanderAngle), cos(m_wanderAngle));
	m_displacement = rot * m_displacement;


	m_wandPos = m_displacement + m_cirCenter;

	m_target = m_wandPos;
	return SeekForce::getForce(agent);

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
