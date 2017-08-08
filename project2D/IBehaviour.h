#pragma once
enum BehaviourResult
{
	Success,
	Failure,
	Pending
};
class Agent;
class IBehaviour
{
public:
	virtual BehaviourResult Update(Agent *pAgent, float deltaTime) = 0;
};