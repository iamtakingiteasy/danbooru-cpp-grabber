#ifndef DANBOORU_CPP_GRABBER_CORE_APPLICATION
#define DANBOORU_CPP_GRABBER_CORE_APPLICATION

#include <danbooru-cpp-grabber/Generic/Logger.h>
#include <danbooru-cpp-grabber/Generic/Config.h>

#include <stdlib.h>
#include "OptParser.h"
#include "ModuleManager.h"
#include <string>
#include <map>


class Application {
	private:
		Config conf;
		Logger log;
		OptParser opt;
	public:
		Application() :
			log(&conf,"")
		{}
		~Application() {}
	public:
		static void hHelp(std::string const& arg, void * usr);
		static void hHelpFacilize(std::string const& arg, void * usr);
		static void hVersion(std::string const& arg, void * usr);
		static void hModulePath(std::string const& arg, void * usr);
		static void hModuleRecursion(std::string const& arg, void * usr);
		static void hModuleInterface(std::string const& arg, void * usr);
		static void hVeryVerbose(std::string const& arg, void * usr);
		static void hInterface(std::string const& arg, void * usr);
		static void hVerbose(std::string const& arg, void * usr);
		static void hGuiMode(std::string const& arg, void * usr);
	public:
		void run(int argc, char ** argv);
		Config const* globals() {
			return &conf;
		}
};

#endif
