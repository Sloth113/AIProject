#pragma once
#include "IBehaviour.h"
#include "MathLibDLL.h"
#include "Renderer2D.h"
#include "FiniteStateMachine.h"
#include <list>
#include "Graph.h"

class Agent
{
public:
	Agent() :m_position(0,0), m_velocity(0, 0), m_acceleration(0, 0), m_force(0, 0) {}

	Agent(MathDLL::Vector2 pos) :m_position(pos), m_velocity(0,0), m_acceleration(0,0), m_force(0,0) {}

	virtual void Update(float deltaTime)
	{
		//Out of bounds check
		//Hard coded (Change later)
		if(m_position.x < 0)
		{
			AddForce(MathDLL::Vector2(m_speed, 0));
		}
		else if (m_position.x > 1260)
		{
			AddForce(MathDLL::Vector2(-m_speed, 0));
		}
		if (m_position.y < 0)
		{
			AddForce(MathDLL::Vector2(0, m_speed));
		}
		else if (m_position.y > 1260)
		{
			AddForce(MathDLL::Vector2(0, -m_speed));
		}


		//Move	
		m_acceleration = m_force / m_mass;
		m_velocity += m_acceleration * deltaTime;

		if (m_velocity.getMagSquare() > m_maxVel * m_maxVel)
		{
			//Max speed
			m_velocity.normalise();
			m_velocity *= m_maxVel;
		}
		

		m_position += m_velocity * deltaTime;

		m_force = MathDLL::Vector2();//reset


		//Behaviours
		for (auto iter = m_behaviours.begin(); iter != m_behaviours.end(); iter++)
		{
			(*iter)->Update(this, deltaTime);
		}
		/*
		if(m_fsm.GetCurrentState() != nullptr)
			m_fsm.Update(this);
			*/

	}
	virtual void Draw(aie::Renderer2D * renderer)
	{
		renderer->setRenderColour(1, 1, 1, 1);
		renderer->drawCircle(m_position.x, m_position.y, 10);
		//Accelation

		renderer->setRenderColour(1, 0, 0, 1);
		renderer->drawLine(m_position.x, m_position.y, m_position.x + m_velocity.x, m_position.y + m_velocity.y);

		//node
		renderer->setRenderColour(0, 1, 1, 1);
	//renderer->drawCircle(m_currentNodeData->data.pos.x, m_currentNodeData->data.pos.y, 10);
	}

	void AddForce(MathDLL::Vector2 force)
	{
		m_force += force;
	}
	void AddBehaviour(IBehaviour * behaviour)
	{
		m_behaviours.push_back(behaviour);
	}

	MathDLL::Vector2 GetPos()
	{
		return m_position;
	}
	void PushState(State * s)
	{
		m_fsm.ChangeState(this, s);
	}
	float MaxVel()
	{
		return m_maxVel;
	}
	MathDLL::Vector2 GetVel()
	{
		return m_velocity;
	}
	float GetSpeed()
	{
		return m_speed;
	}
	void SetPos(MathDLL::Vector2 pos)
	{
		m_position = pos;
	}
	bool HasHp()
	{
		return m_hp > 0;
	}
	void SetHp(int hp)
	{
		m_hp = hp;
	}
	int GetHp()
	{
		return m_hp;
	}
	Vertex<PathNode> * GetNode()
	{
		return m_currentNodeData;
	}
	void SetNode(Vertex<PathNode> * data)
	{
		m_currentNodeData = data;
	}
	//Clone used for spawning
	Agent * Clone()
	{
		Agent * clone = new Agent(MathDLL::Vector2(m_position.x, m_position.y));
		for (auto i = m_behaviours.begin(); i != m_behaviours.end(); i++)
			clone->AddBehaviour((*i));
		
		return clone;
	}
private:

	std::list<IBehaviour *> m_behaviours;
	FiniteStateMachine m_fsm;

	float m_maxVel = 70.0f;
	float m_mass = 1.0f;
	float m_speed = 50.0f;
	MathDLL::Vector2 m_position;
	MathDLL::Vector2 m_velocity;
	MathDLL::Vector2 m_acceleration;
	MathDLL::Vector2 m_force;
	int m_hp = 1;
	Vertex<PathNode> * m_currentNodeData;
};