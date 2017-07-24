#include "Application2D.h"
#include "FiniteStateMachTutorial.h"

int main() {
	
	// allocation
	//auto app = new Application2D();
	auto app = new FiniteStateMachTutorial();

	// initialise and loop
	app->run("AIE", 1280, 720, false);


	
	// deallocation
	delete app;

	return 0;
}