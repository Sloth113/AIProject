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

const int GRID_X = 50;
const int GRID_Y = 28;
const int GRID_SPACE = 25;

struct PathNode
{
	enum Type
	{
		clear,
		rough,
		solid
	};

	MathDLL::Vector2 pos;
	Type state;
};

class ProjectApp : public aie::Application
{
public:

	ProjectApp();
	virtual ~ProjectApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Font*			m_font;

	aie::Renderer2D*	m_2dRenderer;
	
	
	Agent m_mainAgent;

	Agent m_spawnerAgent;
	Agent * m_spawn;
	int m_currentSwamSize;

	Graph<PathNode> m_map;

	void DijkstraThing(Graph<PathNode> & graph);
	void AStarOne(Graph<PathNode> & graph, Vertex<PathNode> * start, Vertex<PathNode> * end);
	
	//For map building
	Vertex<PathNode> * arr[GRID_X][GRID_Y];

	//Used path
	std::list<Vertex<PathNode>* > m_path;
};