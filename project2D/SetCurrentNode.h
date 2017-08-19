#pragma once
#include "IBehaviour.h"
#include "Graph.h"
//Sets the current node on the agent to closest node on map
class SetCurrentNode : public IBehaviour
{
public:
	SetCurrentNode(Graph<PathNode> * map);
	virtual BehaviourResult Update(Agent * agent, float deltaTime);
private:
	Graph<PathNode> * m_map;
};