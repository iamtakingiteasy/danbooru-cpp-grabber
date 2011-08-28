#ifndef DANBOORU_CPP_GRABBER_CORE_CONFIG
#define DANBOORU_CPP_GRABBER_CORE_CONFIG


#include <danbooru-cpp-grabber/Generic/Hash.h>
#include <danbooru-cpp-grabber/Generic/Logger.h>

#include <string>
#include <vector>
#include <map>

enum VerboseLevel {
	VL_NONE,
	VL_MESSAGE,
	VL_NOTICE,
	VL_WARN,
	VL_ERROR,
	VL_DEBUG
};

enum GrabberAction {
	GA_NONE,
	GA_HELP,
	GA_VERSION,
	GA_GUIMODE
};

class Config {
	public:
		GrabberAction action;
		std::vector<std::string> modulePaths;
		bool wasError;
		bool facilize;
		int verbose;
		int debugLevel;
		int moduleRecursionDepth;

		std::string moduleInterface;
		std::string moduleDownloader;
		std::string moduleBoard;
		std::string moduleHandler;
	public:
		Config(){
			moduleInterface  = "1";
			moduleDownloader = "1";
			moduleBoard      = "1";
			moduleHandler    = "1";
			wasError = false;
			facilize = false;
			action = GA_HELP;
			verbose = VL_MESSAGE | VL_NOTICE | VL_WARN | VL_ERROR;
			debugLevel = 0;
			moduleRecursionDepth = 3;
		}
};

#endif
