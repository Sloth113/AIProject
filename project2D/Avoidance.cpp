#include "Avoidance.h"
#include "Agent.h"

const float SEE_AHEAD = 20;
MathDLL::Vector2 Avoidance::getForce(Agent * agent)
{
	MathDLL::Vector2 ahead = agent->GetPos() + (agent->GetVel().getNormalised()) * SEE_AHEAD;
	MathDLL::Vector2 ahead2 = agent->GetPos() + (agent->GetVel().getNormalised()) * SEE_AHEAD * 0.5f;

	MathDLL::Vector2 object = whatToAvoid();
	MathDLL::Vector2 avoidance = MathDLL::Vector2();

	if (object != MathDLL::Vector2(-100, -100))
	{

	}
	else
	{
		return MathDLL::Vector2();
	}

	return MathDLL::Vector2();
}
//Going to use this to avoid edges
MathDLL::Vector2 Avoidance::whatToAvoid()
{
	return MathDLL::Vector2();
}
