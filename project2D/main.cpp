#include "Application2D.h"
#include "FiniteStateMachTutorial.h"
#include "PathsApp.h"
#include "BehaviourApp.h"

int main() {
	
	// allocation
	//auto app = new Application2D();
	//auto app = new FiniteStateMachTutorial();
	//auto app = new PathsApp();
	auto app = new BehaviourApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);


	
	// deallocation
	delete app;

	return 0;
}