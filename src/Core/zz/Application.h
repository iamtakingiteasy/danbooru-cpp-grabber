#ifndef DANBOORU_CPP_GRABBER_CORE
#define DANBOORU_CPP_GRABBER_CORE

class Core;

#include "Config.h"
#include "Logger.h"
#include "ModuleManager.h"
#include "Interactor.h"

class Core {
	public:
		Config conf;
		Logger log;
		Interactor & interact;
		ModuleManager modules;
	public:
		Core(Interactor & i) :
			log(conf),
			interact(i),
			modules(conf,log)
		{}
	public:
		void run(int argc, char ** argv) {
			
		}

};

#endif
