#pragma once
#include "SeekForce.h"

class FollowPath : public SeekForce
{
	virtual MathDLL::Vector2 getForce(Agent * agent);
};