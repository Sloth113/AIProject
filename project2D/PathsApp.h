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
#include "Graph.h"

#include <functional>
#include <queue>
#include <vector>

class PathsApp : public aie::Application
{
public:

	PathsApp();
	virtual ~PathsApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	Agent m_agent;
	Agent m_ai;
	Graph<MathDLL::Vector2> map;

	void DijkstraThing(Graph<MathDLL::Vector2> & graph);
	bool addEdge;
	Vertex<MathDLL::Vector2> * selected;
	std::list<Vertex<MathDLL::Vector2>* > m_path;
};