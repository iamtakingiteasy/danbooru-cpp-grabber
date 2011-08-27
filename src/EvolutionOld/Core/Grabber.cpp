#include "Grabber.h"

void Grabber::run(int argc, char ** argv) {
	core.conf.progName = argv[0];
	core.interact.parse(argc,argv);
	if (core.conf.wasError) return;
	core.modules.loadModules();
	
	switch (conf.action) {
	case Config::GA_SEARCH:
		break;
	case Config::GA_DOWNLOAD:
		break;
	case Config::GA_HELP:
		core.interact.help();
		break;
	case Config::GA_VERSION:
		core.interact.version();
		break;
	case Config::GA_LIST_ALL:
		break;
	case Config::GA_LIST_DOWNLOADERS:
		break;
	case Config::GA_LIST_BOARDS:
		break;
	case Config::GA_LIST_HANDLERS:
		break;
	}
}
