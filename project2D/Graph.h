#pragma once
#include <list>
#include <functional>
#include "MathLibDLL.h"
//My own Graph class not used 
struct PathNode
{
	enum Type
	{
		clear,
		rough,
		solid
	};
	struct Data
	{
		Type state;
		int weight;
	};

	MathDLL::Vector2 pos;
	Data info;
};


template<class T>
class Vertex;

template<class T>
class Edge
{
public:
	Edge(Vertex<T>* t = nullptr, float w = 0)
	{
		target = t;
		weight = w;
	};

	virtual ~Edge() {}

	Vertex<T> * target;

	float weight;
};

template <class T>
class Vertex
{
public:
	Vertex(T value) : data(value) {}
	virtual ~Vertex() {}

	std::list<Edge<T>*> edges;

	//For pathfinding
	float gScore;
	float hScore;
	float fScore;
	Vertex * parent;
	bool traversed;
	//

	T data;
};

template<class T>
class Graph
{
public:
	Vertex<T>* createVertex(T value)
	{
		Vertex<T> * v = new Vertex<T>(value);
		m_verts.push_back(v);
		return v;
	}

	void removeVertex(Vertex<T> * v)
	{
		for (auto i = m_verts.begin(); i != m_verts.end(); i++)
		{
			for (auto j = (*i)->edges.begin(); j != (*i)->edges.end();)
			{
				if ((*j)->target == v)
				{
					removeEdge(*i, v); //Go through other nodes and remove edges to this node
					j = (*i)->edges.begin(); //BAD but works
				}
				else
					j++;
			}
		}
		m_verts.remove_if([v](Vertex<T> * vert) { return vert == v; });
	}

	void addEdge(Vertex<T> * v1, Vertex<T> * v2, float weight)
	{
		v1->edges.push_back(new Edge<T>(v2, weight));
	}

	void removeEdge(Vertex<T> * v1, Vertex<T> * v2)
	{
		v1->edges.remove_if([v2](Edge<T> * edge) { return edge->target == v2; });
	}
	//PATH FINDING
	std::list<Vertex<T>*> aStar(Vertex<T>* start, Vertex<T>* end, std::function<float(Vertex<T>*, Vertex<T>*)> heuristic)
	{
		//Lamba and list
		auto cmp = [](Vertex<T> * left, Vertex<T> * right)
		{
			return left->fScore < right->fScore;
		};
		std::list<Vertex<T>*> pQueue;

		//Set defaults
		for (auto i = m_verts.begin(); i != m_verts.end(); i++)
		{
			(*i)->gScore = FLT_MAX; (*i)->hScore = FLT_MAX; (*i)->fScore = FLT_MAX; (*i)->parent = nullptr; (*i)->traversed = false;
		}
		//Initial
		start->parent = start;
		start->gScore = 0;
		/*
		//Heuristic
		start->hScore =  heuristic(start, end);
		start->fScore = start->hScore + start->gScore;
		*/
		pQueue.push_front(start);
		//Find path
		while (!pQueue.empty())
		{
			pQueue.sort(cmp);
			Vertex<T> * node = pQueue.front();
			pQueue.pop_front();
			node->traversed = true;

			if (node == end)
			{
				return makePath(start, end);
			}
			//edges
			for (auto i = node->edges.begin(); i != node->edges.end(); i++)
			{
				if (!(*i)->target->traversed)
				{
					node->gScore = node->parent->gScore + (*i)->weight;

					float nextHScore = heuristic((*i)->target, end);
					float newFScore = node->gScore + nextHScore;
					
					if (newFScore < (*i)->target->fScore)
					{

						(*i)->target->parent = node;
						(*i)->target->gScore = (node->gScore + (*i)->weight);
						(*i)->target->hScore = heuristic((*i)->target, end);
						
						(*i)->target->fScore = (*i)->target->gScore + (*i)->target->hScore;
						//Not already in there
						if (std::find(pQueue.begin(), pQueue.end(), (*i)->target) == pQueue.end() && !(*i)->target->traversed)
						{
							pQueue.push_front((*i)->target);
						}
					}
				}
			}
		}
		return makePath(start, end);
	}

	std::list<Vertex<T> *> makePath(Vertex<T> * start, Vertex<T> * end)
	{
		std::list<Vertex<T> *> path;
		//path from selected to origin
		while (end != end->parent && end->parent != nullptr)
		{
			path.push_back(end);
			end = end->parent;
		}
		path.push_back(end);
		path.reverse();
		return path;
	}

	std::list<Vertex<T> *> m_verts;
};