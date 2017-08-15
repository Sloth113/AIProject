#include "ProjectApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <time.h>


ProjectApp::ProjectApp()
{

}

ProjectApp::~ProjectApp()
{

}

bool ProjectApp::startup()
{
	srand(time(NULL));
	//Textures
	m_floorT = new aie::Texture("./textures/floor1.png");
	m_roughT = new aie::Texture("./textures/rubble1.png");
	m_spikesT = new aie::Texture("./textures/spike1.png");





	m_mainAgent = Agent(MathDLL::Vector2(getWindowWidth() / 2, getWindowHeight() / 2));
	m_spawnerAgent = Agent(MathDLL::Vector2(100, 100));
	//m_agent.AddBehaviour(new KeyboardController());
	//m_agent.AddBehaviour(new MouseController());
	//m_agent.AddBehaviour(new DrunkModifier());
	//m_agent.AddBehaviour(new SteeringBehaviour(new WanderForce()));




	m_font = new aie::Font("./font/consolas.ttf", 32);
	m_2dRenderer = new aie::Renderer2D();

	int ran =  rand() % 20;
	//MAKE THE GRID
	for (int i = 0; i < GRID_X; i++)
	{
		for (int j = 0; j < GRID_Y; j++)
		{
			ran = rand() % 20;
			if(ran > 7)
				arr[i][j] = m_map.createVertex(PathNode{ MathDLL::Vector2((i)*GRID_SPACE + GRID_SPACE/2 +5,(j)*GRID_SPACE + GRID_SPACE/2 +5),{PathNode::Type::clear, 1}});
			if (ran <= 7 && ran >= 3)
				arr[i][j] = m_map.createVertex(PathNode{ MathDLL::Vector2((i)*GRID_SPACE + GRID_SPACE/2 +5,(j)*GRID_SPACE + GRID_SPACE/2 +5),{PathNode::Type::rough, 25} });
			if (ran < 3)
				arr[i][j] = m_map.createVertex(PathNode{ MathDLL::Vector2((i)*GRID_SPACE + GRID_SPACE/2 +5,(j)*GRID_SPACE + GRID_SPACE/2 +5),{PathNode::Type::solid, 100} });

			//ADD THE EDGES
			if (i > 0)
			{
				m_map.addEdge(arr[i][j], arr[i - 1][j], (arr[i][j]->data.info.weight > arr[i - 1][j]->data.info.weight) ? (arr[i][j]->data.info.weight) : (arr[i - 1][j]->data.info.weight));
				m_map.addEdge(arr[i - 1][j], arr[i][j], (arr[i][j]->data.info.weight > arr[i - 1][j]->data.info.weight) ? (arr[i][j]->data.info.weight) : (arr[i - 1][j]->data.info.weight));
			}
			if (j > 0)
			{
				m_map.addEdge(arr[i][j], arr[i][j - 1], (arr[i][j]->data.info.weight > arr[i][j - 1]->data.info.weight) ? (arr[i][j]->data.info.weight) : (arr[i][j - 1]->data.info.weight));
				m_map.addEdge(arr[i][j - 1], arr[i][j], (arr[i][j]->data.info.weight > arr[i][j - 1]->data.info.weight) ? (arr[i][j]->data.info.weight) : (arr[i][j - 1]->data.info.weight));
			}
			//Diags
			if (i > 0 && j > 0)
			{
				m_map.addEdge(arr[i][j], arr[i- 1][j - 1], (arr[i][j]->data.info.weight > arr[i - 1][j - 1]->data.info.weight) ? (arr[i][j]->data.info.weight) : (arr[i - 1][j - 1]->data.info.weight) * 1.4f);
				m_map.addEdge(arr[i- 1][j - 1], arr[i][j], (arr[i][j]->data.info.weight > arr[i - 1][j - 1]->data.info.weight) ? (arr[i][j]->data.info.weight) : (arr[i - 1][j - 1]->data.info.weight) * 1.4f);
			}
			if (i > 0 && j < GRID_Y-1)
			{
				m_map.addEdge(arr[i][j], arr[i - 1][j + 1], (arr[i][j]->data.info.weight > arr[i - 1][j + 1]->data.info.weight) ? (arr[i][j]->data.info.weight) : (arr[i - 1][j + 1]->data.info.weight) * 1.4f);
				m_map.addEdge(arr[i - 1][j + 1], arr[i][j], (arr[i][j]->data.info.weight > arr[i - 1][j + 1]->data.info.weight) ? (arr[i][j]->data.info.weight) : (arr[i - 1][j + 1]->data.info.weight) * 1.4f);
			}
		}
	}



	/*
	//Behaviour tree
	//Wander but avoid sequence
	Sequence * closeFlee = new Sequence();
	closeFlee->children.push_back(new CloseToCondition(100, &m_agent));
	closeFlee->children.push_back(new SteeringBehaviour(new FleeForce(&m_agent)));

	Selector * wanderFlee = new Selector();
	wanderFlee->children.push_back(closeFlee);
	wanderFlee->children.push_back(new SteeringBehaviour(new WanderForce()));

	m_ai.AddBehaviour(wanderFlee);
	*/


	//m_ai.AddBehaviour(new SteeringBehaviour(new SeekForce(&m_agent)));
	//m_ai.AddBehaviour(new SteeringBehaviour(new FleeForce(&m_agent)));
	//m_ai.AddBehaviour(new SteeringBehaviour(new WanderForce()));
	//m_ai.AddBehaviour(new SteeringBehaviour(new ArrivalForce(&m_agent)));
	//m_ai.AddBehaviour(new SteeringBehaviour(new SeekForce(MathDLL::Vector2((*(map.m_verts.begin()))->data.x, (*(map.m_verts.begin()))->data.y))));

	/*
	//Flock
	flockSize = 10;
	float flockDist = 100;
	m_flock = new Agent[flockSize];
	for (int i = 0; i < flockSize - 1; i++)
	{
		m_flock[i] = Agent(MathDLL::Vector2(rand() % 1280, rand() % 720));
		m_flock[i].AddBehaviour(new SteeringBehaviour(new SeparationForce(m_flock, flockSize, flockDist)));
		m_flock[i].AddBehaviour(new SteeringBehaviour(new CohesionForce(m_flock, flockSize, flockDist)));
		m_flock[i].AddBehaviour(new SteeringBehaviour(new AlignmentForce(m_flock, flockSize, flockDist)));


	}
	m_flock[9] = m_ai;

	*/
	return true;
}

void ProjectApp::shutdown()
{
}

void ProjectApp::update(float deltaTime)
{
	// input example
	aie::Input* input = aie::Input::getInstance();

	m_mainAgent.Update(deltaTime);
	//	m_ai.Update(deltaTime);

	for (int i = 0; i < m_currentSwamSize; i++)
	{
		m_spawn[i].Update(deltaTime);
	}

	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
	{
		//Remembers old path, could just clear or do fancy stuff
		if (m_path.size() > 0)
		{
			m_path.clear();
		}
		//AStarOne(m_map, m_map.m_verts.front(), m_map.m_verts.back());
		//m_path = MakePath(m_map.m_verts.front(), m_map.m_verts.back());
		auto eh = []()
		{
		};
		m_path = AStar(m_map, m_map.m_verts.front(), m_map.m_verts.back(), eh);
	}

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void ProjectApp::draw()
{

	// wipe the screen to the background colour
	clearScreen();

	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(0, 0);

	// begin drawing sprites
	m_2dRenderer->begin();


	//char fps[32];
	//sprintf_s(fps, 32, "SPEED: %F", m_spawnerAgent.GetVel().magnitude());
	//m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	
	
	//DRAW MAP
	for (auto i = m_map.m_verts.begin(); i != m_map.m_verts.end(); i++)
	{
		if ((*i)->parent != nullptr)
		{
			m_2dRenderer->setRenderColour(1, 0, 1, 0.5f);
			m_2dRenderer->drawCircle((*i)->data.pos.x, (*i)->data.pos.y, 5);
		}
		m_2dRenderer->setRenderColour(1, 1, 1, 0.5f);
		if ((*i)->data.info.state == PathNode::Type::clear)
			//m_2dRenderer->setRenderColour(1, 0, 0, 0.5f);
			m_2dRenderer->drawSprite(m_floorT, (*i)->data.pos.x, (*i)->data.pos.y, GRID_SPACE, GRID_SPACE);
		if ((*i)->data.info.state == PathNode::Type::rough)
			//m_2dRenderer->setRenderColour(0, 1, 0, 0.5f);
			m_2dRenderer->drawSprite(m_roughT, (*i)->data.pos.x, (*i)->data.pos.y, GRID_SPACE, GRID_SPACE);
		if ((*i)->data.info.state == PathNode::Type::solid)
			//m_2dRenderer->setRenderColour(0, 0, 1, 0.5f);
			m_2dRenderer->drawSprite(m_spikesT, (*i)->data.pos.x, (*i)->data.pos.y, GRID_SPACE, GRID_SPACE);

		//m_2dRenderer->drawCircle((*i)->data.pos.x, (*i)->data.pos.y, 5);
		
		for (auto j = (*i)->edges.begin(); j != (*i)->edges.end(); j++)
		{
		//	m_2dRenderer->setRenderColour(1, 1, 1, 0.5f);
		//	m_2dRenderer->drawLine((*i)->data.pos.x, (*i)->data.pos.y, (*j)->target->data.pos.x, (*j)->target->data.pos.y, (*j)->weight);
		//	m_2dRenderer->setRenderColour(0, 0, 1, 0.5f);
		//	m_2dRenderer->drawCircle((*j)->target->data.pos.x, (*j)->target->data.pos.y, 1);
		
		}
	}

	if (m_path.size() > 0)
	{
		m_2dRenderer->setRenderColour(1, 0, 0, 1);
		for (auto i = m_path.begin(); i != m_path.end(); i++)
		{
			m_2dRenderer->drawCircle((*i)->data.pos.x, (*i)->data.pos.y, 5);
		}
	}


	m_mainAgent.Draw(m_2dRenderer);
	//	m_ai.Draw(m_2dRenderer);
	for (int i = 0; i < m_currentSwamSize; i++)
	{
		m_spawn[i].Draw(m_2dRenderer);
	}
	// done drawing sprites
	m_2dRenderer->end();
}

void ProjectApp::DijkstraThing(Graph<PathNode> & graph)
{
	//Set defaults
	for (auto i = graph.m_verts.begin(); i != graph.m_verts.end(); i++)
	{
		(*i)->gScore = 9999999999; (*i)->parent = nullptr; (*i)->traversed = false;
	}

	auto cmp = [](Vertex<PathNode> * left, Vertex<PathNode> * right)
	{
		return left->gScore > right->gScore;
	};
	std::priority_queue<Vertex<PathNode> *, std::vector<Vertex<PathNode>*>, decltype(cmp)> pQueue(cmp);


	pQueue.push(*(graph.m_verts.begin()));
	pQueue.top()->gScore = 0;
	pQueue.top()->parent = pQueue.top();

	while (!pQueue.empty())
	{
		Vertex<PathNode> * node = pQueue.top();
		pQueue.pop();
		node->traversed = true;
		for (auto i = node->edges.begin(); i != node->edges.end(); i++)
		{
			if (!(*i)->target->traversed)
			{
				float gScore = node->gScore + (*i)->weight;
				if ((*i)->target->gScore > gScore)
				{
					(*i)->target->gScore = gScore;
					(*i)->target->parent = node;
				}
				//ADD TO LIST IF NOT ALREADY THERE
				pQueue.push((*i)->target);
			}
		}
	}


}

void ProjectApp::AStarOne(Graph<PathNode> & graph, Vertex<PathNode> * start, Vertex<PathNode> * end)
{
	//
	int count = 0;
	int edges = 0;
	//Set defaults
	for (auto i = graph.m_verts.begin(); i != graph.m_verts.end(); i++)
	{
		(*i)->gScore = 9999999999; (*i)->hScore = 9999999999; (*i)->fScore = 9999999999; (*i)->parent = nullptr; (*i)->traversed = false;
	}

	auto cmp = [](Vertex<PathNode> * left, Vertex<PathNode> * right)
	{
		return left->fScore < right->fScore;
	};
	//std::priority_queue<Vertex<PathNode> *, std::vector<Vertex<PathNode>*>, decltype(cmp)> pQueue(cmp);
	std::list<Vertex<PathNode>*> openList;
	std::list<Vertex<PathNode>*> closedList;
	
	//H
	MathDLL::Vector2 h = end->data.pos - start->data.pos;
	start->hScore = h.magnitude()/25.0f;
	//defaults
	start->gScore = 0;
	start->fScore = start->hScore;
	start->parent = start;

	openList.push_back(start);


	while (!openList.empty())
	{
		openList.sort(cmp);
		//std::cout << "BREAK1" << std::endl;
		Vertex<PathNode> * node = openList.front();
		openList.pop_front();
		node->traversed = true;
		closedList.push_back(node);
		//std::cout << "BREAK2" << std::endl;
		if (node == end)
		{
			break;
			//Make path
		}

		for (auto i = node->edges.begin(); i != node->edges.end(); i++)
		{
			edges++;
			if (!(*i)->target->traversed)
			{
				//H
				MathDLL::Vector2 dis = end->data.pos - (*i)->target->data.pos;
				float nextHScore = (dis.magnitude()/25.0f);
				std::cout << "H:" << nextHScore << std::endl;
				float nextGScore = node->gScore + (*i)->weight;
				float newScore = node->gScore + (*i)->weight + nextHScore;
				std::cout << "H:" << nextHScore << "G:" << nextGScore << "F:" << newScore << std::endl;
				//std::cout << "BREAK3" << std::endl;

				if (newScore < (*i)->target->fScore)
				{
					//std::cout << "BREAK4" << std::endl;
					(*i)->target->parent = node;
					(*i)->target->fScore = newScore;
					(*i)->target->gScore = nextGScore;
					(*i)->target->hScore = nextHScore;
				}
				//std::cout << "BREAK5" << std::endl;
				//ADD TO LIST IF NOT ALREADY THERE
				if (!(std::find(closedList.begin(), closedList.end(), (*i)->target) != closedList.end()) && !((std::find(openList.begin(), openList.end(), (*i)->target)) != openList.end()) )
				{
					//std::cout << "BREAK6" << std::endl;
					openList.push_back((*i)->target);
				}
				//std::cout << "BREAK7" << std::endl;
			}
		}
		std::cout << ":END:" << std::endl;
	}
}

std::list<Vertex<PathNode>*> ProjectApp::AStar(Graph<PathNode>& graph, Vertex<PathNode>* start, Vertex<PathNode>* end, std::function<void()> heuristic)
{
	//Lamba and list
	auto cmp = [](Vertex<PathNode> * left, Vertex<PathNode> * right)
	{
		return left->fScore < right->fScore;
	};
	//std::priority_queue<Vertex<PathNode> *, std::vector<Vertex<PathNode>*>, decltype(cmp)> pQueue(cmp);
	std::list<Vertex<PathNode>*> pQueue;
	
	//Set defaults
	for (auto i = graph.m_verts.begin(); i != graph.m_verts.end(); i++)
	{
		(*i)->gScore = FLT_MAX; (*i)->hScore = FLT_MAX; (*i)->fScore = FLT_MAX; (*i)->parent = nullptr; (*i)->traversed = false;
	}
	//Initial
	start->parent = start;
	start->gScore = 0;
	/*
	//Heuristic
	MathDLL::Vector2 h = end->data.pos - start->data.pos;
	start->hScore = h.magnitude() / 25.0f;
	start->fScore = start->hScore + start->gScore;
	*/
	pQueue.push_front(start);
	//Find path
	while (!pQueue.empty())
	{
		pQueue.sort(cmp);
		Vertex<PathNode> * node = pQueue.front();
		pQueue.pop_front();
		node->traversed = true;
		
		if (node == end)
		{
			return MakePath(start, end);
		}
		//edges
		for (auto i = node->edges.begin(); i != node->edges.end(); i++)
		{
			if (!(*i)->target->traversed)
			{
				node->gScore = node->parent->gScore + (*i)->weight;
				MathDLL::Vector2 dis = end->data.pos - (*i)->target->data.pos;
				float nextHScore = (dis.magnitude() / GRID_SPACE);
				float newFScore = node->gScore + nextHScore;
				//
				std::cout << newFScore << " < " << (*i)->target->fScore << std::endl;
				if (newFScore < (*i)->target->fScore)
				{
					
					(*i)->target->parent = node;
					(*i)->target->gScore = (node->gScore + (*i)->weight);
					(*i)->target->hScore = (end->data.pos - (*i)->target->data.pos).magnitude();
					//(*i)->target->fScore = newFScore;
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
	return MakePath(start, end);
}



std::list<Vertex<PathNode> *> ProjectApp::MakePath(Vertex<PathNode> * start, Vertex<PathNode> * end)
{
	std::list<Vertex<PathNode> *> path;
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