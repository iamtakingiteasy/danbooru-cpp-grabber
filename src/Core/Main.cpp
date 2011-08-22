#include "Logger/Logger.h"
#include "Config/Config.h"
#include "Modular/Manager.h"

#include <getopt.h>
#include <string.h>
#include <stdlib.h>

Logger log;
Config conf;
ModuleManager modules;

void parseArguments(int argc, char ** argv) {
	int longIndex = 0;

	static const struct option longOpts[] = {
		// long options
		{"help",              no_argument,       NULL, 0},
		{"version",           no_argument,       NULL, 0},
		{"verbose",           no_argument,       NULL, 0},
		{"download",          no_argument,       NULL, 0},
		{"url",               required_argument, NULL, 0},
		{"module-path",       required_argument, NULL, 0},
		{"downloader",        required_argument, NULL, 0},
		{"board",             required_argument, NULL, 0},
		{"handler",           required_argument, NULL, 0},
		{"search-order",      required_argument, NULL, 0},
		{"search-limit",      required_argument, NULL, 0},
		{"download-limit",    required_argument, NULL, 0},
		{"download-page",     required_argument, NULL, 0},
		{"list-all",          no_argument,       NULL, 0},
		{"list-downloaders",  no_argument,       NULL, 0},
		{"list-boards",       no_argument,       NULL, 0},
		{"list-handlers",     no_argument,       NULL, 0},
		{"working-directory", required_argument, NULL, 0},
		// short options
		{"h",  no_argument,       NULL, 0},
		{"V",  no_argument,       NULL, 0},
		{"v",  no_argument,       NULL, 0},
		{"d",  no_argument,       NULL, 0},
		{"u",  required_argument, NULL, 0},
		{"mp", required_argument, NULL, 0},
		{"md", required_argument, NULL, 0},
		{"mb", required_argument, NULL, 0},
		{"mh", required_argument, NULL, 0},
		{"so", required_argument, NULL, 0},
		{"sl", required_argument, NULL, 0},
		{"dl", required_argument, NULL, 0},
		{"dp", required_argument, NULL, 0},
		{"la", no_argument,       NULL, 0},
		{"ld", no_argument,       NULL, 0},
		{"lb", no_argument,       NULL, 0},
		{"lh", no_argument,       NULL, 0},
		{"C",  required_argument, NULL, 0},
		// NULL terminator
		{0, 0, 0, 0}
	};
	while(getopt_long_only(argc,argv,"",longOpts,&longIndex) != -1) {
		char const* opt = longOpts[longIndex].name;

		if (strcmp(opt,"help") == 0 || strcmp(opt,"h") == 0) {
			conf.action = GA_INFO_HELP;
		}
		
		if (strcmp(opt,"version") == 0 || strcmp(opt,"V") == 0) {
			conf.action = GA_INFO_VERSION;
		}

		if (strcmp(opt,"verbose") == 0 || strcmp(opt,"v") == 0) {
			log.orBitmask(LS_DEBUG);
		}

		if (strcmp(opt,"download") == 0 || strcmp(opt,"d") == 0) {
			conf.action = GA_TAG_DOWNLOAD;
		}

		if (strcmp(opt,"url") == 0 || strcmp(opt,"u") == 0) {
			if (optarg) conf.url = optarg;
		}

		if (strcmp(opt,"module-path") == 0 || strcmp(opt,"mp") == 0) {
			if (optarg) conf.modulePaths.push_back(optarg);
		}

		if (strcmp(opt,"downloader") == 0 || strcmp(opt,"md") == 0) {
			if (optarg) conf.iDownloader = optarg;
		}

		if (strcmp(opt,"board") == 0 || strcmp(opt,"mb") == 0) {
			if (optarg) conf.iBoard = optarg;
		}

		if (strcmp(opt,"handler") == 0 || strcmp(opt,"mh") == 0) {
			if (optarg) conf.iHandler = optarg;
		}

		if (strcmp(opt,"search-order") == 0 || strcmp(opt,"so") == 0) {
			if (optarg) {
				if (false) {
				} else if (strcmp(optarg,"count") == 0) {
					conf.searchOrder = SO_COUNT;
				} else if (strcmp(optarg,"name")  == 0) {
					conf.searchOrder = SO_NAME;
				} else if (strcmp(optarg,"date")  == 0) {
					conf.searchOrder = SO_DATE;
				}
			}
		}

		if (strcmp(opt,"search-limit") == 0 || strcmp(opt,"sl") == 0) {
			if (optarg) conf.searchPageLimit = atoi(optarg);
		}		
		
		if (strcmp(opt,"download-limit") == 0 || strcmp(opt,"dl") == 0) {
			if (optarg) conf.downloadPageLimit = atoi(optarg);
		}

		
		
	}

}
void help() {
	log.message(
"USAGE: " + conf.progName + " [OPTIONS] <tag1 [tag2] [...]>\n"
"    -h,   --help                         Print this help message           \n"
"    -V,   --version                      Print version                     \n"
"    -v,   --verbose                      Verbose (debug) printing          \n"
"    -d,   --download                     Actual download the tags          \n"
"    -u,   --url                          URL of danbooru site              \n"
"    -mp   --module-path=DIR              Additiona directory with plugins  \n"
"    -md,  --downloader=MODULE            Downloader module to use. See -ld \n"
"    -mb,  --board=MODULE                 Baord module to use. See -lb      \n"
"    -mh,  --handler=MODULE               Handler module to use. See -lh    \n"
"    -so,  --search-order=ORDER           Tag search result ordering, one of\n"
"                                         'count', 'name', 'date'           \n"
"    -sl,  --search-limit=LIMIT           Search page limit                 \n"
"    -dl,  --download-limit=LIMIT         Download page limit               \n"
"    -dp,  --download-page=PAGE           Download page offset              \n"
"    -la,  --list-all                     List ALL modules                  \n"
"    -ld,  --list-downloaders             List downloader modules           \n"
"    -lb,  --list-boards                  List board modules                \n"
"    -lh,  --list-handlers                List handler modules              \n"
"    -C,   --working-directory=DIR        Change working directory before   \n"
"                                         downloading                       \n"
	);
}

int main(int argc, char ** argv) {
	conf.action = GA_TAG_SEARCH;

	conf.searchOrder = SO_INVALID;
		
	log.orBitmask(LS_MESSAGE | LS_NOTICE | LS_WARNING | LS_ERROR);
	conf.progName = argv[0];
	
	conf.modulePaths.push_back("~/.config/danbooru-cpp-grabber/modules");
	conf.modulePaths.push_back("/usr/lib/danbooru-cpp-grabber/modules");

	parseArguments(argc,argv);

	modules.setPaths(conf.modulePaths);
	modules.loadModules();
	/*
	ModuleManager modules;

	std::vector<std::string> modulePaths;

	modulePaths.push_back("./"); // TODO should be removed from non-dev builds
	modulePaths.push_back("~/.config/danbooru-cpp-grabber/modules");
	modulePaths.push_back("/usr/lib/danbooru-cpp-grabber/modules");

	modules.setPaths(modulePaths);

	modules.loadModules();

	std::vector<ModuleDownloader>::const_iterator it;
	std::vector<ModuleDownloader> downloaderModules = modules.getDownloaders();

	for (it = downloaderModules.begin(); it  != downloaderModules.end(); it++) {
		std::cout << it->getName() << std::endl;
	}
	*/
	return 0;
	
}
