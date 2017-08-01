#include "WanderForce.h"
#include "Agent.h"



MathDLL::Vector2 WanderForce::getForce(Agent * agent)
{
	const float CIRCLE_DIST = 10;
	const float CIRCLE_RAD = 30;

	float wanderAngle;

	MathDLL::Vector2 cirCenter = agent->GetVel();
	if(cirCenter.getMagSquare() != 0)
		cirCenter.normalise();
	cirCenter = cirCenter * CIRCLE_DIST;

	MathDLL::Vector2 displacement = MathDLL::Vector2(0, -1); //YAXIS ALIGN
	displacement = displacement * CIRCLE_RAD;

	//CHANGE ANGLE
	wanderAngle = rand() % 31 - 15;
	displacement.x += wanderAngle;

	wanderAngle = rand() % 31 - 15;
	displacement.y += wanderAngle;
	if(displacement.getMagSquare() != 0)
		displacement.normalise();
	displacement = displacement * CIRCLE_RAD;

	//DIS = dis - r * tan (wanderangle);
	//Dis.normalise
	//dis = dis * circRad;

	//MathDLL::Vector2 force;

	return displacement - agent->GetVel();
}
