#include "MouseController.h"
#include "Agent.h"
#include "Input.h"
void MouseController::Update(Agent * agent, float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();
	agent->Towards(input->getMouseX(), input->getMouseY());
}