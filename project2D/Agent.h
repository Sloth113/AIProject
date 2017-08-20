#pragma once
#include "IBehaviour.h"
#include "MathLibDLL.h"
#include "Renderer2D.h"
#include "FiniteStateMachine.h"
#include <list>
#include "Graph.h"
//Game object 
//Should put into cpp
class Agent
{
public:
	Agent() :m_position(0,0), m_velocity(0, 0), m_acceleration(0, 0), m_force(0, 0) {
		m_currentNodeData = nullptr;
	}

	Agent(MathDLL::Vector2 pos) :m_position(pos), m_velocity(0,0), m_acceleration(0,0), m_force(0,0) {
		m_currentNodeData = nullptr;
	}

	virtual void update(float deltaTime)
	{
		//Out of bounds check
		//Hard coded (Change later)
		if(m_position.x < 0)
		{
			addForce(MathDLL::Vector2(m_speed, 0));
		}
		else if (m_position.x > 1260)
		{
			addForce(MathDLL::Vector2(-m_speed, 0));
		}
		if (m_position.y < 0)
		{
			addForce(MathDLL::Vector2(0, m_speed));
		}
		else if (m_position.y > 1260)
		{
			addForce(MathDLL::Vector2(0, -m_speed));
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
	}

	virtual void draw(aie::Renderer2D * renderer)
	{
		renderer->setRenderColour(m_r, m_g, m_b, 1);
		renderer->drawCircle(m_position.x, m_position.y, m_radi);
		//Accelation

		renderer->setRenderColour(1, 0, 0, 1);
		renderer->drawLine(m_position.x, m_position.y, m_position.x + m_velocity.x, m_position.y + m_velocity.y);

		//Draw closest node
		//if (m_currentNodeData != nullptr)
		//{
		//	renderer->setRenderColour(0, 1, 1, 1);
		//	renderer->drawCircle(m_currentNodeData->data.pos.x, m_currentNodeData->data.pos.y, 10);
		//}
	}

	void addForce(MathDLL::Vector2 force)
	{
		m_force += force;
	}
	void addBehaviour(IBehaviour * behaviour)
	{
		m_behaviours.push_back(behaviour);
	}

	MathDLL::Vector2 getPos()
	{
		return m_position;
	}
	void pushState(State * s)
	{
		m_fsm.ChangeState(this, s);
	}
	float maxVel()
	{
		return m_maxVel;
	}
	MathDLL::Vector2 getVel()
	{
		return m_velocity;
	}
	float getSpeed()
	{
		return m_speed;
	}
	void setPos(MathDLL::Vector2 pos)
	{
		m_position = pos;
	}
	bool hasHp()
	{
		return m_hp > 0;
	}
	void setHp(int hp)
	{
		m_hp = hp;
	}
	int getHp()
	{
		return m_hp;
	}
	Vertex<PathNode> * getNode()
	{
		return m_currentNodeData;
	}
	void setNode(Vertex<PathNode> * data)
	{
		m_currentNodeData = data;
	}
	//Clone used for spawning
	Agent * clone()
	{
		Agent * clone = new Agent(MathDLL::Vector2(m_position.x, m_position.y));

		//Set clones values
		clone->m_maxVel = m_maxVel;
		clone->m_mass = m_mass;
		clone->m_speed = m_speed;
		
		clone->m_position = m_position;
		clone->m_velocity = m_velocity;
		clone->m_acceleration = m_acceleration;
		clone->m_force = m_force;
		
		clone->m_radi = m_radi;
		clone->m_r = m_r;
		clone->m_g = m_g;
		clone->m_b = m_b;

		return clone;
	}

	//For renderering 
	void setColour(float r, float g, float b)
	{
		m_r = r;
		m_g = g;
		m_b = b;
	}
	void setRenderSize(float radi)
	{
		m_radi = radi;
	}


protected:

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

	//For render
	float m_radi = 10;
	float m_r =1, m_g =1, m_b =1;
};