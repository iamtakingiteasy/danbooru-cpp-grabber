#include "Main.h"

void parseArguments(int argc, char ** argv) {
	core.progName = argv[0];
	
	int longIndex = 0;

	static const struct option longOpts[] = {
		// long options
		{"help",                 no_argument,       NULL, 0},
		{"version",              no_argument,       NULL, 0},
		{"verbose",              no_argument,       NULL, 0},
		{"download",             no_argument,       NULL, 0},
		{"url",                  required_argument, NULL, 0},
		{"module-recursion",     required_argument, NULL, 0},		
		{"module-path",          required_argument, NULL, 0},
		{"downloader",           required_argument, NULL, 0},
		{"board",                required_argument, NULL, 0},
		{"handler",              required_argument, NULL, 0},
		{"search-order",         required_argument, NULL, 0},
		{"search-order-reverse", required_argument, NULL, 0},
		{"search-limit",         required_argument, NULL, 0},
		{"download-limit",       required_argument, NULL, 0},
		{"search-page",          required_argument, NULL, 0},
		{"download-page",        required_argument, NULL, 0},
		{"list-all",             no_argument,       NULL, 0},
		{"list-downloaders",     no_argument,       NULL, 0},
		{"list-boards",          no_argument,       NULL, 0},
		{"list-handlers",        no_argument,       NULL, 0},
		{"working-directory",    required_argument, NULL, 0},
		// short options
		{"h",   no_argument,       NULL, 0},
		{"V",   no_argument,       NULL, 0},
		{"v",   no_argument,       NULL, 0},
		{"d",   no_argument,       NULL, 0},
		{"u",   required_argument, NULL, 0},
		{"mr",  required_argument, NULL, 0},
		{"mp",  required_argument, NULL, 0},
		{"md",  required_argument, NULL, 0},
		{"mb",  required_argument, NULL, 0},
		{"mh",  required_argument, NULL, 0},
		{"so",  required_argument, NULL, 0},
		{"sor", required_argument, NULL, 0},
		{"sl",  required_argument, NULL, 0},
		{"dl",  required_argument, NULL, 0},
		{"sp",  required_argument, NULL, 0},
		{"dp",  required_argument, NULL, 0},
		{"la",  no_argument,       NULL, 0},
		{"ld",  no_argument,       NULL, 0},
		{"lb",  no_argument,       NULL, 0},
		{"lh",  no_argument,       NULL, 0},
		{"C",   required_argument, NULL, 0},
		// NULL terminator
		{0, 0, 0, 0}
	};
	while(getopt_long_only(argc,argv,"",longOpts,&longIndex) != -1) {
		char const* opt = longOpts[longIndex].name;

		if (strcmp(opt,"help") == 0 || strcmp(opt,"h") == 0) {
			core.action = GA_INFO_HELP;
		}

		if (strcmp(opt,"version") == 0 || strcmp(opt,"V") == 0) {
			core.action = GA_INFO_VERSION;
		}

		if (strcmp(opt,"verbose") == 0 || strcmp(opt,"v") == 0) {
			core.loggerFlags |= LS_DEBUG;
		}

		if (strcmp(opt,"download") == 0 || strcmp(opt,"d") == 0) {
			core.action = GA_TAG_DOWNLOAD;
		}

		if (strcmp(opt,"url") == 0 || strcmp(opt,"u") == 0) {
			if (optarg) core.boardURL = optarg;
		}
		
		if (strcmp(opt,"module-recursion") == 0 || strcmp(opt,"mr") == 0) {
			if (optarg) {
				int num = atoi(optarg);
				if (num < 0) {
					core.wasError = true;
					log.error("Recursion depth is negative");
				} else {
					core.moduleRecursionDepth = num;
				}
			}
		}

		if (strcmp(opt,"module-path") == 0 || strcmp(opt,"mp") == 0) {
			if (optarg) core.modulePaths.push_back(optarg);
		}

		if (strcmp(opt,"downloader") == 0 || strcmp(opt,"md") == 0) {
			if (optarg) core.downloaderName = optarg;
		}

		if (strcmp(opt,"board") == 0 || strcmp(opt,"mb") == 0) {
			if (optarg) core.boardName = optarg;
		}

		if (strcmp(opt,"handler") == 0 || strcmp(opt,"mh") == 0) {
			if (optarg) core.handlerName = optarg;
		}

		if (strcmp(opt,"search-order") == 0
			|| strcmp(opt,"so") == 0
			|| strcmp(opt,"search-order-reverse") == 0
			|| strcmp(opt,"sor") == 0) {
			if (optarg) {
				if (false) {
				} else if (strcmp(optarg,"count") == 0) {
					core.searchOrder = SO_COUNT;
				} else if (strcmp(optarg,"name")  == 0) {
					core.searchOrder = SO_NAME;
				} else if (strcmp(optarg,"date")  == 0) {
					core.searchOrder = SO_DATE;
				} else {
					log.warning(
						"Wrong search ordering '"
						+ std::string(optarg)
						+ "'\n");
				}
				if (strcmp(opt,"search-order-reverse") == 0 ||
					strcmp(opt,"sor") == 0) {
					core.searchOrderReverse = true;
				}
			}
		}

		if (strcmp(opt,"search-limit") == 0 || strcmp(opt,"sl") == 0) {
			if (optarg) {
				int num = atoi(optarg);
				if (num < 0) {
					core.wasError = true;
					log.error("Search limit is negative");
				} else {
					core.searchPageLimit = num;
				}
			}
		}

		if (strcmp(opt,"download-limit") == 0 || strcmp(opt,"dl") == 0) {
			if (optarg) {
				int num = atoi(optarg);
				if (num < 0) {
					core.wasError = true;
					log.error("Download limit is negative");
				} else {
					core.downloadPageLimit = num;
				}
			}
		}

		if (strcmp(opt,"search-page") == 0 || strcmp(opt,"sp") == 0) {
			if (optarg) core.searchPageOffset = atoi(optarg);
		}

		if (strcmp(opt,"download-page") == 0 || strcmp(opt,"dp") == 0) {
			if (optarg) core.downloadPageOffset = atoi(optarg);
		}

		if (strcmp(opt,"list-all") == 0 || strcmp(opt,"la") == 0) {
			core.action = GA_MODULE_LIST_ALL;
		}

		if (strcmp(opt,"list-downloaders") == 0 || strcmp(opt,"ld") == 0) {
			core.action = GA_MODULE_LIST_DOWNLOADERS;
		}

		if (strcmp(opt,"list-boards") == 0 || strcmp(opt,"lb") == 0) {
			core.action = GA_MODULE_LIST_BOARDS;
		}

		if (strcmp(opt,"list-handlers") == 0 || strcmp(opt,"lh") == 0) {
			core.action = GA_MODULE_LIST_HANDLERS;
		}

		if (strcmp(opt,"working-directory") == 0 || strcmp(opt,"C") == 0) {
			if (optarg) core.workingDirectory = optarg;
		}
	}
	for (int i = optind; i < argc; i++) {
		core.tags.push_back(argv[i]);
	}

}
