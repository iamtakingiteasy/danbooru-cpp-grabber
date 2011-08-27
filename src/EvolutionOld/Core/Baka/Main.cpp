#include "Main.h"

Logger log;
Core core;
ModuleManager modules;

int main(int argc, char ** argv) {
	parseArguments(argc,argv);
	modules.loadModules();
	makeInstances();

	
	return 0;
}
