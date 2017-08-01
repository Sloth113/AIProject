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
#include "ArrivalForce.h"
#include "WanderForce.h"

#include <functional>
#include <queue>
#include <vector>
#include <algorithm>

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

	aie::Font*			m_font;

	aie::Renderer2D*	m_2dRenderer;
	Agent m_agent;
	Agent m_ai;
	Graph<MathDLL::Vector2> map;

	void DijkstraThing(Graph<MathDLL::Vector2> & graph);
	void AStarOne(Graph<MathDLL::Vector2> & graph, Vertex<MathDLL::Vector2> * start, Vertex<MathDLL::Vector2> * end);
	std::list<Vertex<MathDLL::Vector2>> MakePath(Vertex<MathDLL::Vector2> * goal);
	bool addEdge;
	Vertex<MathDLL::Vector2> * selected;
	Vertex<MathDLL::Vector2> * startSel;

	std::list<Vertex<MathDLL::Vector2>* > m_path;
};