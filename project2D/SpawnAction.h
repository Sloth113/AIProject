#pragma once
#include "IBehaviour.h"
class SpawnAction : public IBehaviour
{
public:
	SpawnAction(Agent * spawnTemplate);
	virtual BehaviourResult Update(Agent *pAgent, float deltaTime);
	Agent * GetSpawn();
	bool SpawnReady();
private:
	Agent * m_spawn;
	bool m_spawnThing = false;
};