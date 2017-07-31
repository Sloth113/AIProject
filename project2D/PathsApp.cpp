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


	m_2dRenderer = new aie::Renderer2D();

	 map.createVertex(MathDLL::Vector2(640, 50));


	 m_ai.AddBehaviour(new SteeringBehaviour(new SeekForce(&m_agent)));
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
		
			if (input->getMouseX() > ((*i)->data.x - 10) && input->getMouseX() < ((*i)->data.x + 10) && input->getMouseY() > ((*i)->data.y - 10) && input->getMouseY() < ((*i)->data.y + 10))
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
		DijkstraThing(map);
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
	}

	if (m_path.size() > 0)
	{
		MathDLL::Vector2 pos1 = m_ai.getPos();
		MathDLL::Vector2 pos2 = MathDLL::Vector2(m_path.front()->data.x, m_path.front()->data.y);
		MathDLL::Vector2 dis = pos1 - pos2;
		if (dis.magnitude() < 5)
		{
			//Ai is there move to next
			m_path.pop_front();
			if(m_path.size() > 0)
				m_agent.SetPos(MathDLL::Vector2(m_path.front()->data.x, m_path.front()->data.y));
		}
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

	m_agent.Draw(m_2dRenderer);
	m_ai.Draw(m_2dRenderer);

	m_2dRenderer->setRenderColour(1, 1, 1, 0.5f);
	//Draw map
	for (auto i = map.m_verts.begin(); i != map.m_verts.end(); i++)
	{
		m_2dRenderer->drawCircle((*i)->data.x, (*i)->data.y, 10);
		for (auto j = (*i)->edges.begin(); j != (*i)->edges.end(); j++)
		{
			m_2dRenderer->drawLine((*i)->data.x, (*i)->data.y, (*j)->target->data.x, (*j)->target->data.y, (*j)->weight);
			m_2dRenderer->setRenderColour(0, 0, 1, 0.5f);
			m_2dRenderer->drawCircle((*j)->target->data.x, (*j)->target->data.y, 3);
			m_2dRenderer->setRenderColour(1, 1, 1, 0.5f);
		}
	}

	if (m_path.size() > 0)
	{
		m_2dRenderer->setRenderColour(1, 0, 0, 1);
		for(auto i = m_path.begin(); i != m_path.end(); i++)
		{
			m_2dRenderer->drawCircle((*i)->data.x, (*i)->data.y, 10);
		}
	}


	// done drawing sprites
	m_2dRenderer->end();
}

void PathsApp::DijkstraThing(Graph<MathDLL::Vector2> & graph)
{
	//Set defaults
	for (auto i = map.m_verts.begin(); i != map.m_verts.end(); i++)
	{
		(*i)->gScore = 9999999999; (*i)->parent = nullptr; (*i)->traversed = false;
	}

	auto cmp = [](Vertex<MathDLL::Vector2> * left, Vertex<MathDLL::Vector2> * right)
	{
		return left->gScore > right->gScore;
	};
	std::priority_queue<Vertex<MathDLL::Vector2> *, std::vector<Vertex<MathDLL::Vector2>*>, decltype(cmp)> pQueue(cmp);
	
	
	pQueue.push(*(map.m_verts.begin()));
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

