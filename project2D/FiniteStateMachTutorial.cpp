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
	m_agent.AddBehaviour(new DrunkModifier());
	m_2dRenderer = new aie::Renderer2D();

	m_texture = new aie::Texture("./textures/numbered_grid.tga");
	m_shipTexture = new aie::Texture("./textures/ship.png");

	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_audio = new aie::Audio("./audio/powerup.wav");

	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;

	return true;
}

void FiniteStateMachTutorial::shutdown()
{

	delete m_audio;
	delete m_font;
	delete m_texture;
	delete m_shipTexture;
	delete m_2dRenderer;
}

void FiniteStateMachTutorial::update(float deltaTime)
{

	m_timer += deltaTime;

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
	m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);

	// begin drawing sprites
	m_2dRenderer->begin();

	m_agent.Draw(m_2dRenderer);
	
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Press Space for sound!", 0, 720 - 64);

	// done drawing sprites
	m_2dRenderer->end();
}