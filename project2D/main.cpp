#include "Application2D.h"
#include "FiniteStateMachTutorial.h"
#include "PathsApp.h"

int main() {
	
	// allocation
	//auto app = new Application2D();
	//auto app = new FiniteStateMachTutorial();
	auto app = new PathsApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);


	
	// deallocation
	delete app;

	return 0;
}