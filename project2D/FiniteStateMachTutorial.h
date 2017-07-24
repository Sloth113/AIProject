#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Audio.h"
#include "MathLibDLL.h"
#include "Agent.h"
#include "KeyboardController.h"
#include "DrunkModifier.h"

class FiniteStateMachTutorial : public aie::Application
{
public:

	FiniteStateMachTutorial();
	virtual ~FiniteStateMachTutorial();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Texture*		m_texture;
	aie::Texture*		m_shipTexture;
	aie::Font*			m_font;
	aie::Audio*			m_audio;


	Agent m_agent;

	float m_cameraX, m_cameraY;
	float m_timer;
};