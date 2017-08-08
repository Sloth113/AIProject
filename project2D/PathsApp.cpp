#include "PathsApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

PathsApp::PathsApp()
{

}

PathsApp::~PathsApp()
{

}

bool PathsApp::startup()
{
	m_agent = Agent(MathDLL::Vector2(getWindowWidth() / 2, getWindowHeight() / 2));
	m_ai = Agent(MathDLL::Vector2(100, 100));
	//m_agent.AddBehaviour(new KeyboardController());
	//m_agent.AddBehaviour(new MouseController());
	//m_agent.AddBehaviour(new DrunkModifier());
	//m_agent.AddBehaviour(new SteeringBehaviour(new WanderForce()));

	m_font = new aie::Font("./font/consolas.ttf", 32);
	m_2dRenderer = new aie::Renderer2D();

	// map.createVertex(MathDLL::Vector2(640, 50));
	

	 for (int i = 0; i < 51; i++)
	 {
		 for (int j = 0; j < 29; j++)
		 {
			 arr[i][j] = nullptr;
		 }
	 }
	 int r = 0, c = 0;
	 for (int i = 10, r =0; i < 1270; i += 25, r++)
	 {
		 for (int j = 10, c = 0; j < 710; j += 25, c++)
		 {
			 if (rand() % 3 != 0)
			 {
					 arr[r][c] = map.createVertex(MathDLL::Vector2(i, j));	 
					 if (r > 0 && arr[r - 1][c] != nullptr)
					 {
						 map.addEdge(arr[r][c], arr[r - 1][c], 1);
						 map.addEdge(arr[r - 1][c], arr[r][c], 1);
					 }
					 if (c > 0 && arr[r][c - 1] != nullptr)
					 {
						 map.addEdge(arr[r][c], arr[r][c - 1], 1);
						 map.addEdge(arr[r][c - 1], arr[r][c], 1);
					 }
			 }
		 }
	 }
	 for (auto i = map.m_verts.begin(); i != map.m_verts.end(); i++)
	 {
		 if ((*i)->edges.size() <= 0)
		 {
			 i = map.m_verts.erase(i);
		 }
	 }

	 
	 startSel = map.m_verts.front();
	
	 //m_ai.AddBehaviour(new SteeringBehaviour(new SeekForce(&m_agent)));
	 m_ai.AddBehaviour(new SteeringBehaviour(new ArrivalForce(&m_agent)));
	//m_ai.AddBehaviour(new SteeringBehaviour(new SeekForce(MathDLL::Vector2((*(map.m_verts.begin()))->data.x, (*(map.m_verts.begin()))->data.y))));

	selected = nullptr;
	addEdge = false;
	return true;
}

void PathsApp::shutdown()
{

}

void PathsApp::update(float deltaTime)
{
	// input example
	aie::Input* input = aie::Input::getInstance();

	m_agent.Update(deltaTime);
	m_ai.Update(deltaTime);
	
	//Map creation
	bool nodePress = false;
	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT))
	{
		for (auto i = map.m_verts.begin(); i != map.m_verts.end(); i++)
		{
		
			if (input->getMouseX() > ((*i)->data.x - 12) && input->getMouseX() < ((*i)->data.x + 12) && input->getMouseY() > ((*i)->data.y - 12) && input->getMouseY() < ((*i)->data.y + 12))
				{
					if (addEdge && selected != nullptr && selected != (*i))
					{
						//Add weight
						bool weight = false;
						for (auto j = selected->edges.begin(); j != selected->edges.end(); j++)
						{
							if ((*i) == (*j)->target)
							{
								(*j)->weight++;
								weight = true;
							}
						}
						if(!weight)
							map.addEdge(selected, (*i), 1); //Make it so if already exists it increases weight
						selected = nullptr;
						addEdge = false;
					}
					else
					{
						selected = (*i);
						addEdge = true;
					}
					//CLicked a node
					nodePress = true;
				}
		}
		if (!nodePress)
		{
			
			Vertex<MathDLL::Vector2> * v = map.createVertex(MathDLL::Vector2(input->getMouseX(), input->getMouseY()));
			if (addEdge)
			{
				map.addEdge(selected, v, 1);
				selected = nullptr;
				addEdge = false;
			}

		}
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE) && selected != nullptr)
	{
		//Remembers old path, could just clear or do fancy stuff
		if (m_path.size() > 0)
		{
			startSel = m_path.front();
			m_path.clear();
		}
		//DijkstraThing(map);
		AStarOne(map, startSel, selected);
		//path from selected to origin
		while (selected != selected->parent && selected->parent != nullptr)
		{
			m_path.push_back(selected);
			selected = selected->parent;
		}
		m_path.push_back(selected);
		m_path.reverse();
		m_agent.SetPos(MathDLL::Vector2(m_path.front()->data.x, m_path.front()->data.y));
		selected = false;
		addEdge = false;
		std::cout << "Nodes:" << m_path.size() << std::endl;
	}

	if (m_path.size() > 0)
	{
		MathDLL::Vector2 pos1 = m_ai.GetPos();
		MathDLL::Vector2 pos2 = MathDLL::Vector2(m_path.front()->data.x, m_path.front()->data.y);
		MathDLL::Vector2 dis = pos1 - pos2;
		if (dis.magnitude() < 15)
		{
			//Ai is there move to next
			startSel = m_path.front();
			m_path.pop_front();
			if (m_path.size() > 0)
				m_agent.SetPos(MathDLL::Vector2(m_path.front()->data.x, m_path.front()->data.y));
		}
	}

	if (selected != nullptr && input->wasKeyPressed(aie::INPUT_KEY_C))
	{
		map.removeVertex(selected);
		selected = false;
		addEdge = false;
	}
	if (selected != nullptr && input->wasKeyPressed(aie::INPUT_KEY_S))
	{
		startSel = selected;
		selected = false;
		addEdge = false;
	}
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void PathsApp::draw()
{

	// wipe the screen to the background colour
	clearScreen();

	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(0, 0);

	// begin drawing sprites
	m_2dRenderer->begin();



	m_2dRenderer->setRenderColour(1, 1, 1, 0.5f);
	//Draw map
	m_2dRenderer->setRenderColour(0.5,0.5,0.5, 1);
	

	for (auto i = map.m_verts.begin(); i != map.m_verts.end(); i++)
	{
		if ((*i)->parent != nullptr)
		{
			m_2dRenderer->setRenderColour(1, 0, 1, 0.5f);
		//	m_2dRenderer->drawCircle((*i)->data.x, (*i)->data.y, 5);
		}
		m_2dRenderer->setRenderColour(1, 1, 1, 0.5f);
	//	m_2dRenderer->drawCircle((*i)->data.x, (*i)->data.y, 5);
		m_2dRenderer->drawBox((*i)->data.x, (*i)->data.y, 25, 25);
		for (auto j = (*i)->edges.begin(); j != (*i)->edges.end(); j++)
		{
		//	m_2dRenderer->drawLine((*i)->data.x, (*i)->data.y, (*j)->target->data.x, (*j)->target->data.y, (*j)->weight);
			m_2dRenderer->setRenderColour(0, 0, 1, 0.5f);
		//	m_2dRenderer->drawCircle((*j)->target->data.x, (*j)->target->data.y, 1);
			m_2dRenderer->setRenderColour(1, 1, 1, 0.5f);
		}
	}

	if (m_path.size() > 0)
	{
		m_2dRenderer->setRenderColour(1, 0, 0, 1);
		for(auto i = m_path.begin(); i != m_path.end(); i++)
		{
			m_2dRenderer->drawCircle((*i)->data.x, (*i)->data.y, 5);
		}
	}

	if (selected != nullptr)
	{
		m_2dRenderer->setRenderColour(0, 1, 0);
		m_2dRenderer->drawCircle((selected)->data.x, (selected)->data.y, 10);
	}

	if (startSel != nullptr)
	{
		m_2dRenderer->setRenderColour(0, 1, 1);
		m_2dRenderer->drawCircle((startSel)->data.x, (startSel)->data.y, 10);
	}

	char fps[32];
	sprintf_s(fps, 32, "SPEED: %F", m_ai.GetVel().magnitude());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	
	m_agent.Draw(m_2dRenderer);
	m_ai.Draw(m_2dRenderer);

	// done drawing sprites
	m_2dRenderer->end();
}

void PathsApp::DijkstraThing(Graph<MathDLL::Vector2> & graph)
{
	//Set defaults
	for (auto i = graph.m_verts.begin(); i != graph.m_verts.end(); i++)
	{
		(*i)->gScore = 9999999999; (*i)->parent = nullptr; (*i)->traversed = false;
	}

	auto cmp = [](Vertex<MathDLL::Vector2> * left, Vertex<MathDLL::Vector2> * right)
	{
		return left->gScore > right->gScore;
	};
	std::priority_queue<Vertex<MathDLL::Vector2> *, std::vector<Vertex<MathDLL::Vector2>*>, decltype(cmp)> pQueue(cmp);
	
	
	pQueue.push(*(graph.m_verts.begin()));
	pQueue.top()->gScore = 0;
	pQueue.top()->parent = pQueue.top();

	while (!pQueue.empty())
	{
		Vertex<MathDLL::Vector2> * node = pQueue.top();
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

void PathsApp::AStarOne(Graph<MathDLL::Vector2> & graph, Vertex<MathDLL::Vector2> * start, Vertex<MathDLL::Vector2> * end)
{
	//
	int count = 0;
	int edges = 0;
	//Set defaults
	for (auto i = graph.m_verts.begin(); i != graph.m_verts.end(); i++)
	{
		(*i)->gScore = 9999999999; (*i)->hScore = 9999999999; (*i)->fScore = 9999999999; (*i)->parent = nullptr; (*i)->traversed = false;
	}

	auto cmp = [](Vertex<MathDLL::Vector2> * left, Vertex<MathDLL::Vector2> * right)
	{
		return left->fScore > right->fScore;
	};
	std::priority_queue<Vertex<MathDLL::Vector2> *, std::vector<Vertex<MathDLL::Vector2>*>, decltype(cmp)> pQueue(cmp);
	std::vector<Vertex<MathDLL::Vector2>*> closedList;

	start->gScore = 0;
	MathDLL::Vector2 h = end->data - start->data;
	start->hScore = h.getMagSquare();
	start->fScore = start->hScore;
	start->parent = start;

	pQueue.push(start);


	while (!pQueue.empty())
	{
		Vertex<MathDLL::Vector2> * node = pQueue.top();
		pQueue.pop();
		node->traversed = true;
		closedList.push_back(node);

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
				MathDLL::Vector2 dis = end->data - (*i)->target->data;
				float nextHScore = (dis.getMagSquare());
				std::cout << "H:" << nextHScore << std::endl;
				float nextGScore = node->gScore + (*i)->weight;
				float newScore = node->gScore + (*i)->weight + nextHScore;
				if (newScore < (*i)->target->fScore)
				{
					(*i)->target->parent = node;
					(*i)->target->fScore = newScore;
					(*i)->target->gScore = nextGScore;
					(*i)->target->hScore = nextHScore;
				}
				//ADD TO LIST IF NOT ALREADY THERE
				if (!(std::find(closedList.begin(), closedList.end(), (*i)->target) != closedList.end()))
				{
					pQueue.push((*i)->target);
				}
			}
		}
		std::cout << ":END:" << std::endl;
	}
}
std::list<Vertex<MathDLL::Vector2>> MakePath(Vertex<MathDLL::Vector2> * goal)
{
	std::list<Vertex<MathDLL::Vector2>> path;
	return path;
}
