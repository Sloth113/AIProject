#pragma once
#include "IBehaviour.h"
#include "Graph.h"
#include "SeekForce.h"
class FollowPath : public IBehaviour
{
public:
	FollowPath(SeekForce * force);
	virtual BehaviourResult Update(Agent * agent, float deltaTime);
	void setPath(std::list<Vertex<PathNode>*>  path);
	PathNode currentNode();

private:
	std::list< Vertex<PathNode>*>  m_path;
	Vertex<PathNode> * m_goToNode;
	SeekForce * m_force;
	float m_closeDist;

};