#pragma once
class Agent;
class IBehaviour
{
public:
	virtual void Update(Agent *pAgent, float deltaTime) = 0;
};