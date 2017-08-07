#pragma once
class Agent;
class IBehaviour
{
public:
	virtual bool Update(Agent *pAgent, float deltaTime) = 0;
};