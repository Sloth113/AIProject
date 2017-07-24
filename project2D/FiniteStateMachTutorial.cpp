#include "FiniteStateMachTutorial.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

FiniteStateMachTutorial::FiniteStateMachTutorial()
{

}

FiniteStateMachTutorial::~FiniteStateMachTutorial()
{

}

bool FiniteStateMachTutorial::startup()
{
	m_agent = Agent(MathDLL::Vector2(getWindowWidth()/2, getWindowHeight()/2));
	m_agent.AddBehaviour(new KeyboardController());
//	m_agent.AddBehaviour(new MouseController());
	m_agent.AddBehaviour(new DrunkModifier());
	m_2dRenderer = new aie::Renderer2D();

	return true;
}

void FiniteStateMachTutorial::shutdown()
{

}

void FiniteStateMachTutorial::update(float deltaTime)
{
	// input example
	aie::Input* input = aie::Input::getInstance();

	m_agent.Update(deltaTime);

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void FiniteStateMachTutorial::draw()
{

	// wipe the screen to the background colour
	clearScreen();

	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(0, 0);

	// begin drawing sprites
	m_2dRenderer->begin();

	m_agent.Draw(m_2dRenderer);

	// done drawing sprites
	m_2dRenderer->end();
}