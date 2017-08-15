#include "FlowFieldsApp.h"

int main() {
	
	auto app = new FlowFieldsApp();
	app->run("AIE", 1280, 720, false);
	delete app;

	return 0;
}