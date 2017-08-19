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
//AI
#include "SpawnAction.h"
#include "SpawnTimerCondition.h"
#include "FollowPath.h"
#include "SetCurrentNode.h"
#include "SetPathCondition.h"




#include <functional>
#include <queue>
#include <vector>
#include <algorithm>

const int GRID_X = 25;
const int GRID_Y = 14;
const int GRID_SPACE = 50;



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

	aie::Texture * m_floorT;
	aie::Texture * m_roughT;
	aie::Texture * m_spikesT;
	
	
	Agent  m_mainAgent;

	Agent  m_spawnerAgent;
	SpawnAction * m_spawnAction;


	Agent spawnPrototype;
	std::list<Agent *> m_swarm;
	int m_currentSwamSize;

	Graph<PathNode> m_map;

	void DijkstraThing(Graph<PathNode> & graph);
//	void AStarOne(Graph<PathNode> & graph, Vertex<PathNode> * start, Vertex<PathNode> * end);
//	std::list<Vertex<PathNode>*> AStar(Graph<PathNode> & graph, Vertex<PathNode> * start, Vertex<PathNode> * end, std::function<void()> heuristic);
//	std::list<Vertex<PathNode>*>  MakePath(Vertex<PathNode> * start, Vertex<PathNode> * end);
	//For map building
	Vertex<PathNode> * arr[GRID_X][GRID_Y];

	//Used path
	std::list<Vertex<PathNode>* > m_path;
};