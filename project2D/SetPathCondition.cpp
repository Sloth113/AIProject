#include "SetPathCondition.h"
#include "Agent.h"
//Makes the path and sets it on another behaviour
SetPathCondition::SetPathCondition(Graph<PathNode> * map, FollowPath * pathBehav)
{
	m_map = map;
	m_target = nullptr;
	m_followPathBehav = pathBehav;
}

SetPathCondition::SetPathCondition(Graph<PathNode> * map, Agent * agent, FollowPath * pathBehav)
{
	m_map = map;
	m_target = agent;
	m_followPathBehav = pathBehav;
}

BehaviourResult SetPathCondition::Update(Agent * agent, float deltaTime)
{
	auto eh = [](Vertex<PathNode> * current, Vertex<PathNode> * end) -> float
	{

		MathDLL::Vector2 dis = end->data.pos - current->data.pos;
		return (dis.magnitude() / 25);
	};
	if (m_target == nullptr)
	{
		int r = rand() % (25 * 14);
		auto i = m_map->m_verts.begin();
		for (; r != 0; r--)
		{
			i++;
		}
		
		m_followPathBehav->setPath(m_map->aStar(  (*i), agent->getNode(), eh));
		//Random node
	}
	else
	{
		m_followPathBehav->setPath(m_map->aStar( m_target->getNode(), agent->getNode(), eh));
	}
	return BehaviourResult();
}
