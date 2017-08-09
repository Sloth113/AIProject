#include "BehaviourApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

BehaviourApp::BehaviourApp()
{

}

BehaviourApp::~BehaviourApp()
{

}

bool BehaviourApp::startup()
{
	m_agent = Agent(MathDLL::Vector2(getWindowWidth() / 2, getWindowHeight() / 2));
	m_ai = Agent(MathDLL::Vector2(100, 100));
	//m_agent.AddBehaviour(new KeyboardController());
	m_agent.AddBehaviour(new MouseController());
	//m_agent.AddBehaviour(new DrunkModifier());
	//m_agent.AddBehaviour(new SteeringBehaviour(new WanderForce()));

	


	m_font = new aie::Font("./font/consolas.ttf", 32);
	m_2dRenderer = new aie::Renderer2D();


	//Behaviour tree
	//Wander but avoid sequence
	Sequence * closeFlee = new Sequence();
	closeFlee->children.push_back(new CloseToCondition(100, &m_agent));
	closeFlee->children.push_back(new SteeringBehaviour(new FleeForce(&m_agent)));

	Selector * wanderFlee = new Selector();
	wanderFlee->children.push_back(closeFlee);
	wanderFlee->children.push_back(new SteeringBehaviour(new WanderForce()));

	m_ai.AddBehaviour(wanderFlee);
	
	//m_ai.AddBehaviour(new SteeringBehaviour(new SeekForce(&m_agent)));
	//m_ai.AddBehaviour(new SteeringBehaviour(new FleeForce(&m_agent)));
	//m_ai.AddBehaviour(new SteeringBehaviour(new WanderForce()));
	//m_ai.AddBehaviour(new SteeringBehaviour(new ArrivalForce(&m_agent)));
	//m_ai.AddBehaviour(new SteeringBehaviour(new SeekForce(MathDLL::Vector2((*(map.m_verts.begin()))->data.x, (*(map.m_verts.begin()))->data.y))));


	//Flock
	flockSize = 10;
	m_flock = new Agent[flockSize];
	for (int i = 0; i < flockSize; i++)
	{
		m_flock[i] = Agent(MathDLL::Vector2(rand() % 1280, rand() % 720));
		m_flock[i].AddBehaviour(new SteeringBehaviour(new SeparationForce()));
		m_flock[i].AddBehaviour(new SteeringBehaviour(new CohesionForce()));
		m_flock[i].AddBehaviour(new SteeringBehaviour(new AlignmentForce()));
			
	}



	selected = nullptr;
	addEdge = false;
	return true;
}

void BehaviourApp::shutdown()
{
	delete[] m_flock;
}

void BehaviourApp::update(float deltaTime)
{
	// input example
	aie::Input* input = aie::Input::getInstance();

	m_agent.Update(deltaTime);
	m_ai.Update(deltaTime);

	for (int i = 0; i < flockSize; i++)
	{
		m_flock[i].Update(deltaTime);
	}

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void BehaviourApp::draw()
{

	// wipe the screen to the background colour
	clearScreen();

	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(0, 0);

	// begin drawing sprites
	m_2dRenderer->begin();


	char fps[32];
	sprintf_s(fps, 32, "SPEED: %F", m_ai.GetVel().magnitude());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);

	m_agent.Draw(m_2dRenderer);
	m_ai.Draw(m_2dRenderer);
	for (int i = 0; i < flockSize; i++)
	{
		m_flock[i].Draw(m_2dRenderer);
	}
	// done drawing sprites
	m_2dRenderer->end();
}

void BehaviourApp::DijkstraThing(Graph<MathDLL::Vector2> & graph)
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

void BehaviourApp::AStarOne(Graph<MathDLL::Vector2> & graph, Vertex<MathDLL::Vector2> * start, Vertex<MathDLL::Vector2> * end)
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
