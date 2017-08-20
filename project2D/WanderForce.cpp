#include "WanderForce.h"
#include "Agent.h"
#define _USE_MATH_DEFINES
#include <math.h>

const float CIRCLE_DIST = 50;
const float CIRCLE_RAD = 85;
const float ANGLE_CHANGE = 7.0f / 180.0f * M_PI;

WanderForce::WanderForce(float weight)
{
	m_weight = weight;
	m_agent = nullptr;
}

MathDLL::Vector2 WanderForce::getForce(Agent * agent)
{
	/*
	Old random location wander
	if (m_prevTarget.getMagSquare() == 0 || (m_target - agent->GetPos()).getMagSquare() < 10)
	{
		m_prevTarget = MathDLL::Vector2(rand() % 1281,rand() % 721);
	}
	m_target = m_prevTarget;
	*/

	//Set the seek target
	m_cirCenter = agent->getVel();
	float length = m_wandPos.magnitude();

	if (length == 0)
	{
		m_cirCenter = m_tinyForce;
	}

	m_cirCenter.normalise();
	m_cirCenter *= CIRCLE_DIST;
	m_cirCenter += agent->getPos();

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
}
