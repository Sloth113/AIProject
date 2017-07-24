#include "DrunkModifier.h"
#include "Agent.h"
#include "Input.h"
#include <math.h>
void DrunkModifier::Update(Agent * agent, float deltaTime)
{
	m_time += deltaTime;
	agent->AddForce(MathDLL::Vector2(sinf(m_time), sinf(m_time)));
}