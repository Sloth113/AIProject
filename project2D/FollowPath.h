#pragma once
#include "IBehaviour.h"
#include "Graph.h"
#include "ArrivalForce.h"
class FollowPath : public IBehaviour
{
public:
	FollowPath(ArrivalForce * force, float dis);
	virtual BehaviourResult Update(Agent * agent, float deltaTime);
	void setPath(std::list<Vertex<PathNode>*>  path);
	PathNode currentNode();

private:
	std::list< Vertex<PathNode>*>  m_path;
	Vertex<PathNode> * m_goToNode;
	ArrivalForce * m_force;
	float m_closeDist =1;

};