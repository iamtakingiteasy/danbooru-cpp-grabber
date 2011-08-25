#ifndef DANBOORU_CPP_GRABBER_CORE_GRABBER
#define DANBOORU_CPP_GRABBER_CORE_GRABBER

#include "config.h"

#include "Loaders/Downloader.h"
#include <danbooru-cpp-grabber/DownloaderInterface.h>

#include <danbooru-cpp-grabber/Generic/OptParser.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>

class Grabber {
	private:
		class Logger {
			public:
				enum type {
					LT_MESSAGE = 1<<0,
					LT_NOTICE  = 1<<1,
					LT_WARNING = 1<<2,
					LT_ERROR   = 1<<3,
					LT_DEBUG   = 1<<4
				};
				void multi(int bits, std::string const& text) const;
				void message(std::string const& text) const;
				void notice(std::string const& text)  const;
				void warning(std::string const& text) const;
				void error(std::string const& text)   const;
				void debug(std::string const& text)   const;
		};
		class Interactor {
			private:
				OptParser opt;
			public:
				Interactor();
			public:
				void help();
				void parse(int argc, char ** argv);
				void validate();
		};
		class Config {
			public:
				Config() {
					wasError = false;

					loggerFlags =
						Logger::LT_MESSAGE |
						Logger::LT_NOTICE  |
						Logger::LT_WARNING |
						Logger::LT_ERROR   ;
					
					progName = "danbooru-cpp-grabber";
					workingDirectory = ".";

					//username
					//password

					//boardURL

					//tags
					
					moduleDirs.push_back("~/.config/danbooru-cpp-grabber/modules");
					moduleDirs.push_back("/usr/lib/danbooru-cpp-grabber/modules");

					moduleSearchRecursionDepth = 3;

					pageOffset = 0;
					pageSize = 100;

					selectedDownloader = "0";
					selectedBoard = "0";
					selectedHandler = "0";

					loaderDownloader = NULL;
					//loaderBoard = NULL;
					//loaderHandler = NULL;

					downloader = NULL;
					//board = NULL;
					//handler = NULL;
				};
			public:
				bool wasError;

				int loggerFlags;

				std::string progName;
				std::string workingDirectory;
				std::string username;
				std::string password;
				std::string boardURL;

				std::vector<std::string> tags;
				std::vector<std::string> moduleDirs;

				int moduleSearchRecursionDepth;

				int pageOffset;
				int pageSize;

				std::string selectedDownloader;
				std::string selectedBoard;
				std::string selectedHandler;

				DownloaderLoader * loaderDownloader;
				//BoardLoader * loaderBoard;
				//HanlerLoader * loaderHandler;

				DownloaderInterface * downloader;
				//BoardInterface * board;
				//HandlerInterface * handler;				
		};
		class ModuleCollection {
			private:
				std::map<std::string,DownloaderLoader> loadersDownloader;
				//std::map<std::string,DownloaderBoard> loadersBoard;
				//std::map<std::string,DownloaderHandle> loadersHandler;
				std::vector<std::string> loaderIndexDownloader;
				//std::vector<std::string> loaderIndexBoard;
				//std::vector<std::string> loaderIndexHandler;
			public:
				void loadModules();
				void installModules();
				DownloaderLoader * lookupDownloader(std::string const& nameOrIndex);
				//void lookupBoard(std::string const& nameOrIndex);
				//void lookupHandler(std::string const& nameOrIndex);
		};
	private:
		Config conf;
	public:
		Interactor interact;
		Logger log;
		ModuleCollection modules;
};

extern Grabber core; // to be declared into Main.cpp

#endif
