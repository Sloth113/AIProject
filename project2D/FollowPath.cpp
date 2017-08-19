#include "FollowPath.h"
#include "Agent.h"
FollowPath::FollowPath(SeekForce * force)
{
	m_force = force;
}
BehaviourResult FollowPath::Update(Agent * agent, float deltaTime)
{
	if (m_path.empty())
	{
		return BehaviourResult::Failure;
	}
	else
	{
		if ((agent->GetPos() - m_goToNode->data.pos).getMagSquare() < m_closeDist * m_closeDist)
		{
			m_goToNode = m_path.back();
			m_path.pop_back();
			m_force->m_target = m_goToNode->data.pos;
		}
		return BehaviourResult::Success;
	}
	return BehaviourResult::Failure;
}

void FollowPath::setPath(std::list<Vertex<PathNode>*> path)
{
	//path.clear();
	m_path = path;
}

PathNode FollowPath::currentNode()
{
	return m_goToNode->data;
}
