#pragma once
#include "IBehaviour.h"
#include "Graph.h"
#include "FollowPath.h"
class SetPathCondition : public IBehaviour
{
public:
	SetPathCondition(Graph<PathNode> * map, FollowPath * pathBehav);
	SetPathCondition(Graph<PathNode> * map, Agent * agent, FollowPath * pathBehav);
	virtual BehaviourResult Update(Agent * agent, float deltaTime);

private:
	Agent * m_target;
	FollowPath * m_followPathBehav;
	Graph<PathNode> * m_map;

};