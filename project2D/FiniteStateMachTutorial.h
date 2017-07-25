#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Audio.h"
#include "MathLibDLL.h"
#include "Agent.h"
#include "KeyboardController.h"
#include "DrunkModifier.h"
#include "MouseController.h"
#include "SeekForce.h"
#include "SteeringBehaviour.h"

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
	Agent m_agent;
	Agent m_ai;

};