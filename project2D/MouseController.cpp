#include "MouseController.h"
#include "Agent.h"
#include "Input.h"
BehaviourResult MouseController::Update(Agent * agent, float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();
	agent->SetPos(MathDLL::Vector2(input->getMouseX(), input->getMouseY()));
	return BehaviourResult::Success;
}