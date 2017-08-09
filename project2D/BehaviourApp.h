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
#include "FleeForce.h"
#include "CloseToCondition.h"
#include "Sequence.h"
#include "Selector.h"
//Flocking
#include "SeparationForce.h"
#include "CohesionForce.h"
#include "AlignmentForce.h"



#include <functional>
#include <queue>
#include <vector>
#include <algorithm>

class BehaviourApp : public aie::Application
{
public:

	BehaviourApp();
	virtual ~BehaviourApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Font*			m_font;

	aie::Renderer2D*	m_2dRenderer;
	Agent m_agent;
	Agent m_ai;
	Agent * m_flock;
	int flockSize;
	Graph<MathDLL::Vector2> map;

	void DijkstraThing(Graph<MathDLL::Vector2> & graph);
	void AStarOne(Graph<MathDLL::Vector2> & graph, Vertex<MathDLL::Vector2> * start, Vertex<MathDLL::Vector2> * end);
	bool addEdge;
	Vertex<MathDLL::Vector2> * selected;
	Vertex<MathDLL::Vector2> * startSel;
	Vertex<MathDLL::Vector2> * arr[51][29];

	std::list<Vertex<MathDLL::Vector2>* > m_path;
};