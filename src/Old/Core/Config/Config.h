#ifndef DANBOORU_CPP_GRABBER_CONFIG
#define DANBOORU_CPP_GRABBER_CONFIG

#include <danbooru-cpp-grabber/DownloaderInterface.h>

#include <string>
#include <vector>

enum GrabberAction {
	GA_INVALID,
	GA_TAG_SEARCH,
	GA_TAG_DOWNLOAD,
	GA_MODULE_LIST_ALL,
	GA_MODULE_LIST_DOWNLOADERS,
	GA_MODULE_LIST_BOARDS,
	GA_MODULE_LIST_HANDLERS,
	GA_INFO_HELP,
	GA_INFO_VERSION,
	GA_LAST
};

enum SearchOrder {
	SO_INVALID,
	SO_COUNT,
	SO_NAME,
	SO_DATE,
	SO_LAST
};

class Config {
	public:
		std::string progName;
		std::vector<std::string> tags;
		std::vector<std::string> modulePaths;
		GrabberAction action;
		SearchOrder searchOrder;
		bool searchOrderReverse;
		std::string iDownloader;
		std::string iBoard;
		std::string iHandler;
		std::string fileNameFormat;
		std::string workingDirectory;
		std::string username;
		std::string password;
		std::string url;
		unsigned int pageOffset;
		unsigned int searchPageLimit;
		unsigned int downloadPageLimit;
		DownloaderInterface * downloader;
};

#endif
