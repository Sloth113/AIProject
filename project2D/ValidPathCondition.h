#pragma once
#include "IBehaviour.h"
#include "MathLibDLL.h"
#include "Graph.h"
#include <list>

class ValidPathCondition : public IBehaviour
{
public:
	ValidPathCondition(std::list<Vertex<MathDLL::Vector2>*> * path, Agent * agent);
	virtual BehaviourResult Update(Agent *pAgent, float deltaTime);
private:
	float m_range;
	std::list<Vertex<MathDLL::Vector2>* > m_path;
};