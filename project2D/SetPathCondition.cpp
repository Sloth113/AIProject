#include "SetPathCondition.h"
#include "Agent.h"
SetPathCondition::SetPathCondition(Graph<PathNode> * map, FollowPath * pathBehav)
{
	m_map = map;
	m_target = nullptr;
}

SetPathCondition::SetPathCondition(Graph<PathNode> * map, Agent * agent, FollowPath * pathBehav)
{
	m_map = map;
	m_target = agent;
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
		
		m_followPathBehav->setPath(m_map->aStar(agent->GetNode(), (*i), eh));
		//Random node
	}
	else
	{
		m_followPathBehav->setPath(m_map->aStar(agent->GetNode(), m_target->GetNode(), eh));
	}
	return BehaviourResult();
}
