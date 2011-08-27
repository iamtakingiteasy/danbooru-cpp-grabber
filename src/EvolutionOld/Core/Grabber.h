#ifndef DANBOORU_CPP_GRABBER_CORE_GRABBER
#define DANBOORU_CPP_GRABBER_CORE_GRABBER

#include "config.h"

#include "Loaders/Modular.h"
#include "Loaders/Downloader.h"
#include <danbooru-cpp-grabber/DownloaderInterface.h>

#include <danbooru-cpp-grabber/Generic/OptParser.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>

class Grabber {
	private:
		class Config {
			public:
				enum grabberAction {
					GA_SEARCH,
					GA_DOWNLOAD,
					GA_HELP,
					GA_VERSION,
					GA_LIST_ALL,
					GA_LIST_DOWNLOADERS,
					GA_LIST_BOARDS,
					GA_LIST_HANDLERS
				};
				Config() {
					wasError = false;

					action = GA_SEARCH;

					loggerDebugLevel = 0;
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

					//searchOrder

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

				grabberAction action;

				int loggerDebugLevel;
				int loggerFlags;

				std::string progName;
				std::string workingDirectory;
				std::string username;
				std::string password;
				std::string boardURL;

				std::string searchOrder;

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
		class Logger {
			private:
				Grabber & core;
			public:
				Logger(Grabber & c);
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
				void debug(int level, std::string const& text)   const;
		};
		class Interactor {
			private:
				OptParser opt;
				OptParser modOpt;
				Grabber & core;
			public:
				Interactor(Grabber & c);
			public:
				static void hHelp(std::string const& arg, void * usr);
				static void hVersion(std::string const& arg, void * usr);
				static void hVerbose(std::string const& arg, void * usr);
				static void hVeryVerbose(std::string const& arg, void * usr);
				static void hDownload(std::string const& arg, void * usr);
				static void hURL(std::string const& arg, void * usr);
				static void hModulePath(std::string const& arg, void * usr);
				static void hModuleRecursion(std::string const& arg, void * usr);
				static void hModuleDownloader(std::string const& arg, void * usr);
				static void hModuleBoard(std::string const& arg, void * usr);
				static void hModuleHandler(std::string const& arg, void * usr);
				static void hListAll(std::string const& arg, void * usr);
				static void hListDownloaders(std::string const& arg, void * usr);
				static void hListBoards(std::string const& arg, void * usr);
				static void hListHandlers(std::string const& arg, void * usr);
				static void hWorkingDirectory(std::string const& arg, void * usr);
			public:
				void help();
				void version();
				void parse(int argc, char ** argv);
				void validate();
				void push_option(Option const& o);
		};
		class ModuleCollection {
			private:
				std::map<std::string,DownloaderLoader> loadersDownloader;
				//std::map<std::string,DownloaderBoard> loadersBoard;
				//std::map<std::string,DownloaderHandle> loadersHandler;
				std::vector<std::string> loadersIndexDownloader;
				//std::vector<std::string> loaderIndexBoard;
				//std::vector<std::string> loaderIndexHandler;
				Grabber & core;
			private:
				void scandir(std::string const& path, int depth);
			public:
				ModuleCollection(Grabber & c);
			public:
				void loadModules();
				void installModules();
				DownloaderLoader * lookupDownloader(std::string const& nameOrIndex);
				//void lookupBoard(std::string const& nameOrIndex);
				//void lookupHandler(std::string const& nameOrIndex);
		};
	public:
		void run(int argc, char ** argv);
		Grabber() :
			core(*this),
			interact(*this),
			log(*this),
			modules(*this)
		{}
	private:
		Config conf;
	public:
		Grabber & core;
		Interactor interact;
		Logger log;
		ModuleCollection modules;
};

#endif
