#include "KeyboardController.h"
#include "Agent.h"
#include "Input.h"
BehaviourResult KeyboardController::Update(Agent * agent, float deltaTime)
{

	aie::Input* input = aie::Input::getInstance();
		if (input->isKeyDown(aie::INPUT_KEY_W))
		{
			agent->AddForce(MathDLL::Vector2(0, 10));
		}
		if (input->isKeyDown(aie::INPUT_KEY_S))
		{
			agent->AddForce(MathDLL::Vector2(0, -10));
		}
		if (input->isKeyDown(aie::INPUT_KEY_A))
		{
			agent->AddForce(MathDLL::Vector2(-10, 0));
		}
		if (input->isKeyDown(aie::INPUT_KEY_D))
		{
			agent->AddForce(MathDLL::Vector2(10, 0));
		}
		return BehaviourResult::Success;
}
