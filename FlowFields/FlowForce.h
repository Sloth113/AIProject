#pragma once
#include "SteeringForce.h"

//class FlowForce : public SteeringForce
//{
//public:
//	FlowForce() {};
//	virtual ~FlowForce() {};
//
//	void setFlowField(Vector2 * flowfield, int rows, int cols, int cellSize)
//	{
//	m_flowfield = flowfield;
//	m_rows = rows;
//	m_cols = cols; 
//	m_cellSize = cellSize;
//	}
//	//calculate the force that should be applied to GameObject 
//	virtual Force getForce(GameObject* gameObject) const;
//
//protected:
//	int m_rows, m_cols;
//	float m_cellSize;
//	Vector2 * m_flowfield = nullptr;
//};