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
		m_force = MathDLL::Vector2();//reset
		m_velocity += m_acceleration * deltaTime;
		m_position += m_velocity * deltaTime;
		
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
	void Towards(float x, float y)
	{
		MathDLL::Vector2 v2 = MathDLL::Vector2(x - m_position.x, y - m_position.y);
		v2.normalise();
		v2 *= m_speed;
		m_velocity = v2;
	}
	MathDLL::Vector2 getPos()
	{
		return m_position;
	}
private:

	std::list<IBehaviour *> m_behaviours;

	float m_mass = 1.0f;
	float m_speed = 100.0f;
	MathDLL::Vector2 m_position;
	MathDLL::Vector2 m_velocity;
	MathDLL::Vector2 m_acceleration;
	MathDLL::Vector2 m_force;
};