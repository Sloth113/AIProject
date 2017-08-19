#include "SpawnAction.h"
#include "Agent.h"
SpawnAction::SpawnAction(Agent * spawnTemplate)
{
	m_spawn = spawnTemplate;
}

BehaviourResult SpawnAction::Update(Agent *pAgent, float deltaTime)
{
	m_spawnThing = true;
	return BehaviourResult::Success;
}

Agent * SpawnAction::GetSpawn()
{
	m_spawnThing = false;
	return m_spawn->Clone();
}

bool SpawnAction::SpawnReady()
{
	return m_spawnThing;
}

