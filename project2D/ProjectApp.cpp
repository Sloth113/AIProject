#include "ProjectApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <time.h>

//AI PROJECT
//3 Types of agents
//Main paths to the spawner then stops till it gets some distance away 
//Spawner makes sure the player isnt close, runs away to random point on map using path finding a star.
//	If there /idle itll spawn a seeker every 3 seconds
//Seeker seek the main agent with wander.
//Scott Hart

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

	//Spawn location
	m_mainAgent = Agent(MathDLL::Vector2(0,0));
	m_spawnerAgent = Agent(MathDLL::Vector2(100, 100));
	
	//Seeker agent
	Sequence * mainUpdatePathOrMove = new Sequence();
	ArrivalForce * mainArriveForce = new ArrivalForce(0.3f);
	FollowPath * mainFollowPath = new FollowPath(mainArriveForce, 20);
	mainUpdatePathOrMove->children.push_back(mainFollowPath);
	mainUpdatePathOrMove->children.push_back(new SteeringBehaviour(mainArriveForce));

	Sequence * notCloseFindPathTo = new Sequence();
	notCloseFindPathTo->children.push_back(new NotCloseToCondition(100, &m_spawnerAgent));
	notCloseFindPathTo->children.push_back(new SetPathCondition(&m_map, &m_spawnerAgent, mainFollowPath));


	Selector * pathOrDistCheck = new Selector();
	pathOrDistCheck->children.push_back(mainUpdatePathOrMove);
	pathOrDistCheck->children.push_back(notCloseFindPathTo);

	Selector * standStillandWait = new Selector();
	standStillandWait->children.push_back(pathOrDistCheck);
	standStillandWait->children.push_back(new SteeringBehaviour(new ForceStillForce(1.0f)));

	m_mainAgent.addBehaviour(standStillandWait);
	m_mainAgent.addBehaviour(new SetCurrentNode(&m_map));

	//Spawn
	spawnPrototype = Agent(MathDLL::Vector2(0, 0));
	spawnPrototype.addBehaviour(new SteeringBehaviour(new WanderForce(0.5f)));
	spawnPrototype.addBehaviour(new SteeringBehaviour(new SeekForce(&m_mainAgent)));
	spawnPrototype.addBehaviour(new SetCurrentNode(&m_map));
	
	//Spawner
	Sequence * updatePathOrMove = new Sequence();
	ArrivalForce * followPathForce = new ArrivalForce(1.0f);
	FollowPath * followPath = new FollowPath(followPathForce, 20);
	updatePathOrMove->children.push_back(followPath);
	updatePathOrMove->children.push_back(new SteeringBehaviour(followPathForce));
	
	Sequence * closeSetMove = new Sequence();
	closeSetMove->children.push_back(new CloseToCondition(100, &m_mainAgent));
	closeSetMove->children.push_back(new SetPathCondition(&m_map, followPath));

	Selector * movePathOrCheckClose = new Selector();
	movePathOrCheckClose->children.push_back(updatePathOrMove);
	movePathOrCheckClose->children.push_back(closeSetMove);

	Sequence * spawnOnTimer = new Sequence();
	m_spawnAction = new SpawnAction(&spawnPrototype);
	spawnOnTimer->children.push_back(new SpawnTimerCondition(3.0f));
	spawnOnTimer->children.push_back(m_spawnAction);

	Selector * standStillAndSpawn = new Selector();
	standStillAndSpawn->children.push_back(spawnOnTimer);
	standStillAndSpawn->children.push_back(new SteeringBehaviour(new ForceStillForce(1.0f)));

	Selector * moveOrSpawn = new Selector();
	moveOrSpawn->children.push_back(movePathOrCheckClose);
	moveOrSpawn->children.push_back(standStillAndSpawn);

	m_spawnerAgent.addBehaviour(moveOrSpawn);
	m_spawnerAgent.addBehaviour(new SetCurrentNode(&m_map));


	//Map
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
				arr[i][j] = m_map.createVertex(PathNode{ MathDLL::Vector2((i)*GRID_SPACE + GRID_SPACE/2 +5,(j)*GRID_SPACE + GRID_SPACE/2 +5),{PathNode::Type::rough, 50} });
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



	//Set defaults 
	m_spawnerAgent.setColour(0, 0, 1);
	m_spawnerAgent.setRenderSize(20);
	m_spawnerAgent.setNode(m_map.m_verts.front());

	
	m_mainAgent.setNode(m_map.m_verts.front());

	spawnPrototype.setColour(0, 1, 0);
	spawnPrototype.setRenderSize(5);
	spawnPrototype.setNode(m_map.m_verts.front());
	return true;
}

void ProjectApp::shutdown()
{
}

void ProjectApp::update(float deltaTime)
{
	// input example
	aie::Input* input = aie::Input::getInstance();

	m_mainAgent.update(deltaTime);

	m_spawnerAgent.update(deltaTime);

	//spawned dudes
	for (auto i = m_swarm.begin(); i != m_swarm.end(); i++)
	{
		(*i)->update(deltaTime);
	}
	//Clone more 
	if (m_spawnAction->SpawnReady())
	{
		Agent * clone = m_spawnAction->GetSpawn();
		clone->addBehaviour(new SteeringBehaviour(new WanderForce(0.5f)));
		clone->addBehaviour(new SteeringBehaviour(new SeekForce(&m_mainAgent)));
		clone->addBehaviour(new SetCurrentNode(&m_map));
		clone->setPos(MathDLL::Vector2(m_spawnerAgent.getPos().x, m_spawnerAgent.getPos().y));
		clone->setNode(m_spawnerAgent.getNode());

		m_swarm.push_back(clone);
	}

	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
	{
		m_swarm.clear();//Space to clear swarm
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
	
	//DRAW MAP
	for (auto i = m_map.m_verts.begin(); i != m_map.m_verts.end(); i++)
	{
		m_2dRenderer->setRenderColour(1, 1, 1, 0.5f);
		if ((*i)->data.info.state == PathNode::Type::clear)
			m_2dRenderer->drawSprite(m_floorT, (*i)->data.pos.x, (*i)->data.pos.y, GRID_SPACE, GRID_SPACE);
		if ((*i)->data.info.state == PathNode::Type::rough)
			m_2dRenderer->drawSprite(m_roughT, (*i)->data.pos.x, (*i)->data.pos.y, GRID_SPACE, GRID_SPACE);
		if ((*i)->data.info.state == PathNode::Type::solid)
			m_2dRenderer->drawSprite(m_spikesT, (*i)->data.pos.x, (*i)->data.pos.y, GRID_SPACE, GRID_SPACE);
	}

	if (m_path.size() > 0)
	{
		m_2dRenderer->setRenderColour(1, 0, 0, 1);
		for (auto i = m_path.begin(); i != m_path.end(); i++)
		{
			m_2dRenderer->drawCircle((*i)->data.pos.x, (*i)->data.pos.y, 5);
		}
	}

	//Draw agents
	m_mainAgent.draw(m_2dRenderer);

	m_spawnerAgent.draw(m_2dRenderer);

	for (auto i = m_swarm.begin(); i != m_swarm.end(); i++)
	{
		(*i)->draw(m_2dRenderer);
	}
	// done drawing 
	m_2dRenderer->end();
}

//void ProjectApp::DijkstraThing(Graph<PathNode> & graph)
//{
//	//Set defaults
//	for (auto i = graph.m_verts.begin(); i != graph.m_verts.end(); i++)
//	{
//		(*i)->gScore = 9999999999; (*i)->parent = nullptr; (*i)->traversed = false;
//	}
//
//	auto cmp = [](Vertex<PathNode> * left, Vertex<PathNode> * right)
//	{
//		return left->gScore > right->gScore;
//	};
//	std::priority_queue<Vertex<PathNode> *, std::vector<Vertex<PathNode>*>, decltype(cmp)> pQueue(cmp);
//
//
//	pQueue.push(*(graph.m_verts.begin()));
//	pQueue.top()->gScore = 0;
//	pQueue.top()->parent = pQueue.top();
//
//	while (!pQueue.empty())
//	{
//		Vertex<PathNode> * node = pQueue.top();
//		pQueue.pop();
//		node->traversed = true;
//		for (auto i = node->edges.begin(); i != node->edges.end(); i++)
//		{
//			if (!(*i)->target->traversed)
//			{
//				float gScore = node->gScore + (*i)->weight;
//				if ((*i)->target->gScore > gScore)
//				{
//					(*i)->target->gScore = gScore;
//					(*i)->target->parent = node;
//				}
//				//ADD TO LIST IF NOT ALREADY THERE
//				pQueue.push((*i)->target);
//			}
//		}
//	}
//
//
//}

//void ProjectApp::AStarOne(Graph<PathNode> & graph, Vertex<PathNode> * start, Vertex<PathNode> * end)
//{
//	//
//	int count = 0;
//	int edges = 0;
//	//Set defaults
//	for (auto i = graph.m_verts.begin(); i != graph.m_verts.end(); i++)
//	{
//		(*i)->gScore = 9999999999; (*i)->hScore = 9999999999; (*i)->fScore = 9999999999; (*i)->parent = nullptr; (*i)->traversed = false;
//	}
//
//	auto cmp = [](Vertex<PathNode> * left, Vertex<PathNode> * right)
//	{
//		return left->fScore < right->fScore;
//	};
//	//std::priority_queue<Vertex<PathNode> *, std::vector<Vertex<PathNode>*>, decltype(cmp)> pQueue(cmp);
//	std::list<Vertex<PathNode>*> openList;
//	std::list<Vertex<PathNode>*> closedList;
//	
//	//H
//	MathDLL::Vector2 h = end->data.pos - start->data.pos;
//	start->hScore = h.magnitude()/25.0f;
//	//defaults
//	start->gScore = 0;
//	start->fScore = start->hScore;
//	start->parent = start;
//
//	openList.push_back(start);
//
//
//	while (!openList.empty())
//	{
//		openList.sort(cmp);
//		//std::cout << "BREAK1" << std::endl;
//		Vertex<PathNode> * node = openList.front();
//		openList.pop_front();
//		node->traversed = true;
//		closedList.push_back(node);
//		//std::cout << "BREAK2" << std::endl;
//		if (node == end)
//		{
//			break;
//			//Make path
//		}
//
//		for (auto i = node->edges.begin(); i != node->edges.end(); i++)
//		{
//			edges++;
//			if (!(*i)->target->traversed)
//			{
//				//H
//				MathDLL::Vector2 dis = end->data.pos - (*i)->target->data.pos;
//				float nextHScore = (dis.magnitude()/25.0f);
//				std::cout << "H:" << nextHScore << std::endl;
//				float nextGScore = node->gScore + (*i)->weight;
//				float newScore = node->gScore + (*i)->weight + nextHScore;
//				std::cout << "H:" << nextHScore << "G:" << nextGScore << "F:" << newScore << std::endl;
//				//std::cout << "BREAK3" << std::endl;
//
//				if (newScore < (*i)->target->fScore)
//				{
//					//std::cout << "BREAK4" << std::endl;
//					(*i)->target->parent = node;
//					(*i)->target->fScore = newScore;
//					(*i)->target->gScore = nextGScore;
//					(*i)->target->hScore = nextHScore;
//				}
//				//std::cout << "BREAK5" << std::endl;
//				//ADD TO LIST IF NOT ALREADY THERE
//				if (!(std::find(closedList.begin(), closedList.end(), (*i)->target) != closedList.end()) && !((std::find(openList.begin(), openList.end(), (*i)->target)) != openList.end()) )
//				{
//					//std::cout << "BREAK6" << std::endl;
//					openList.push_back((*i)->target);
//				}
//				//std::cout << "BREAK7" << std::endl;
//			}
//		}
//		std::cout << ":END:" << std::endl;
//	}
//}

//std::list<Vertex<PathNode>*> ProjectApp::AStar(Graph<PathNode>& graph, Vertex<PathNode>* start, Vertex<PathNode>* end, std::function<void()> heuristic)
//{
//	//Lamba and list
//	auto cmp = [](Vertex<PathNode> * left, Vertex<PathNode> * right)
//	{
//		return left->fScore < right->fScore;
//	};
//	//std::priority_queue<Vertex<PathNode> *, std::vector<Vertex<PathNode>*>, decltype(cmp)> pQueue(cmp);
//	std::list<Vertex<PathNode>*> pQueue;
//	
//	//Set defaults
//	for (auto i = graph.m_verts.begin(); i != graph.m_verts.end(); i++)
//	{
//		(*i)->gScore = FLT_MAX; (*i)->hScore = FLT_MAX; (*i)->fScore = FLT_MAX; (*i)->parent = nullptr; (*i)->traversed = false;
//	}
//	//Initial
//	start->parent = start;
//	start->gScore = 0;
//	/*
//	//Heuristic
//	MathDLL::Vector2 h = end->data.pos - start->data.pos;
//	start->hScore = h.magnitude() / 25.0f;
//	start->fScore = start->hScore + start->gScore;
//	*/
//	pQueue.push_front(start);
//	//Find path
//	while (!pQueue.empty())
//	{
//		pQueue.sort(cmp);
//		Vertex<PathNode> * node = pQueue.front();
//		pQueue.pop_front();
//		node->traversed = true;
//		
//		if (node == end)
//		{
//			return MakePath(start, end);
//		}
//		//edges
//		for (auto i = node->edges.begin(); i != node->edges.end(); i++)
//		{
//			if (!(*i)->target->traversed)
//			{
//				node->gScore = node->parent->gScore + (*i)->weight;
//				MathDLL::Vector2 dis = end->data.pos - (*i)->target->data.pos;
//				float nextHScore = (dis.magnitude() / GRID_SPACE);
//				float newFScore = node->gScore + nextHScore;
//				//
//				std::cout << newFScore << " < " << (*i)->target->fScore << std::endl;
//				if (newFScore < (*i)->target->fScore)
//				{
//					
//					(*i)->target->parent = node;
//					(*i)->target->gScore = (node->gScore + (*i)->weight);
//					(*i)->target->hScore = (end->data.pos - (*i)->target->data.pos).magnitude();
//					//(*i)->target->fScore = newFScore;
//					(*i)->target->fScore = (*i)->target->gScore + (*i)->target->hScore;
//					//Not already in there
//					if (std::find(pQueue.begin(), pQueue.end(), (*i)->target) == pQueue.end() && !(*i)->target->traversed)
//					{
//						pQueue.push_front((*i)->target);
//					}
//				}
//			}
//		}
//	}
//	return MakePath(start, end);
//}
//
//
//
//std::list<Vertex<PathNode> *> ProjectApp::MakePath(Vertex<PathNode> * start, Vertex<PathNode> * end)
//{
//	std::list<Vertex<PathNode> *> path;
//	//path from selected to origin
//	while (end != end->parent && end->parent != nullptr)
//	{
//		path.push_back(end);
//		end = end->parent;
//	}
//	path.push_back(end);
//	path.reverse();
//	return path;
//}