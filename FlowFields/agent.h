#pragma once
#include "IBehaviour.h"
#include "MathLibDLL.h"
#include "Renderer2D.h"
#include <list>

class Agent
{
public:
	Agent() {}

	Agent(MathDLL::Vector2 pos) :m_position(pos) {}

	virtual void Update(float deltaTime)
	{
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
	virtual void Draw(aie::Renderer2D * renderer)
	{
		renderer->setRenderColour(1, 1, 1, 1);
		renderer->drawCircle(m_position.x, m_position.y, 10);
		//Accelation

		renderer->setRenderColour(1, 0, 0, 1);
		renderer->drawLine(m_position.x, m_position.y, m_position.x + m_velocity.x, m_position.y + m_velocity.y);
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
private:

	std::list<IBehaviour *> m_behaviours;

	float m_maxVel = 70.0f;
	float m_mass = 1.0f;
	float m_speed = 50.0f;
	MathDLL::Vector2 m_position;
	MathDLL::Vector2 m_velocity;
	MathDLL::Vector2 m_acceleration;
	MathDLL::Vector2 m_force;
};