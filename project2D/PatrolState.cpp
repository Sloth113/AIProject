#include "PatrolState.h"
#include "Agent.h"
void PatrolState::Update(Agent * agent, FiniteStateMachine * sm)
{
	if ((agent->GetPos() - currentPoint.pos).getMagSquare() > 5)
	{
		currentPoint = *(currentPoint.next);
	}
	//if(getPlayer().getPos()-agent->getPos()).getMagSquare() > 10))
	//{
	//	sm->ChangeState(agent,new AttackState());
	//}

}
