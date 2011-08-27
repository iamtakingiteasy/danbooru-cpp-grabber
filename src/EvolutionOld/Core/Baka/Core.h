#ifndef DANBOORU_CPP_GRABBER_CORE_CONFIG
#define DANBOORU_CPP_GRABBER_CORE_CONFIG

#include <danbooru-cpp-grabber/DownloaderInterface.h>
//#include <danbooru-cpp-grabber/BoardInterface.h>
//#include <danbooru-cpp-grabber/HandlerInterface.h>

#include "ModuleSpecificDownloader.h"
//#include "ModuleSpecificBoard.h"
//#include "ModuleSpecificHandler.h"


#include <string>
#include <map>
#include <vector>

enum GrabberAction {
	GA_TAG_SEARCH,
	GA_TAG_DOWNLOAD,
	GA_MODULE_LIST_ALL,
	GA_MODULE_LIST_DOWNLOADERS,
	GA_MODULE_LIST_BOARDS,
	GA_MODULE_LIST_HANDLERS,
	GA_INFO_HELP,
	GA_INFO_VERSION
};

enum SearchOrder {
	SO_COUNT,
	SO_NAME,
	SO_DATE
};

enum LoggerState {
	LS_MESSAGE = 1<<0,
	LS_NOTICE  = 1<<1,
	LS_WARNING = 1<<2,
	LS_ERROR   = 1<<3,
	LS_DEBUG   = 1<<4
};


struct Core {
	public:
		Core() {
			wasError = false;
			loggerFlags = LS_MESSAGE | LS_NOTICE | LS_WARNING | LS_ERROR;
			action = GA_TAG_SEARCH;
			searchOrder = SO_COUNT;
			searchOrderReverse = true;
			modulePaths.push_back("~/.config/danbooru-cpp-grabber/modules");
			modulePaths.push_back("/usr/lib/danbooru-cpp-grabber/modules");

			moduleRecursionDepth = 10;

			downloadPageOffset = 0;
			downloadPageLimit = 100;
			searchPageOffset = 0;
			searchPageLimit = 100;

			downloaderName = "1";
			boardName = "1";
			handlerName = "1";
			
		}
	public:
		bool wasError;
		
		std::string progName;
		std::string filenameFormat;
		std::string workingDirectory;
		std::string username;
		std::string password;
		std::string boardURL;

		std::vector<std::string> tags;
		std::vector<std::string> modulePaths;

		int moduleRecursionDepth;

		GrabberAction action;
		SearchOrder searchOrder;

		bool searchOrderReverse;

		int downloadPageOffset;
		int downloadPageLimit;
		int searchPageOffset;
		int searchPageLimit;

		int loggerFlags;

		std::string downloaderName;
		std::string boardName;
		std::string handlerName;

		std::map<std::string,ModuleSpecificDownloader> downloaders;
//		std::vector<ModuleSpecificBoard> boards;
//		std::vector<ModuleSpecificHandler> handlers;

		std::vector<std::string> downloadersIndex;
		std::vector<std::string> boardsIndex;
		std::vector<std::string> handlersIndex;

		
		DownloaderInterface * downloaderInstance;
//		BoardInterface * boardInstance;
//		HandlerInterface * handlerInstance;
		
};

#endif
