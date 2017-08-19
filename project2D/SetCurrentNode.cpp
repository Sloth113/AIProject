#include "SetCurrentNode.h"
#include "Agent.h"
SetCurrentNode::SetCurrentNode(Graph<PathNode> *  map)
{
	m_map = map;
}

BehaviourResult SetCurrentNode::Update(Agent * agent, float deltaTime)
{
	Vertex<PathNode> * node = m_map->m_verts.front();
	for (auto i = m_map->m_verts.begin(); i != m_map->m_verts.end(); i++)
	{
		if (((*i)->data.pos - agent->GetPos()).getMagSquare() < (node->data.pos - agent->GetPos()).getMagSquare())
		{
			node = (*i);
		}
	}
	agent->SetNode(node);
	return BehaviourResult::Success;
}
