#include "FollowPath.h"
#include "Agent.h"
//Check that its not at the node and follow path until empty
FollowPath::FollowPath(ArrivalForce * force, float dis)
{
	m_force = force;
	m_closeDist = dis;
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
	m_path.clear();
	m_path = path;
	m_goToNode = m_path.back();
	m_force->m_target = m_goToNode->data.pos;
}

PathNode FollowPath::currentNode()
{
	return m_goToNode->data;
}
