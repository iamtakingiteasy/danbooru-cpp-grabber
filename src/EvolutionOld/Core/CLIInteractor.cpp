#include "Grabber.h"

#ifdef HAVE_IOCTL
#    include <sys/ioctl.h>
#endif


void Grabber::Interactor::hHelp(std::string const& arg, void * usr) {
	((Interactor*)usr)->core.conf.action = Config::GA_HELP;
}

void Grabber::Interactor::hVersion(std::string const& arg, void * usr) {
	((Interactor*)usr)->core.conf.action = Config::GA_VERSION;
}

void Grabber::Interactor::hVerbose(std::string const& arg, void * usr) {
	((Interactor*)usr)->core.conf.loggerFlags |= Logger::LT_DEBUG;
}

void Grabber::Interactor::hVeryVerbose(std::string const& arg, void * usr) {
	((Interactor*)usr)->core.conf.loggerDebugLevel++;
}

void Grabber::Interactor::hDownload(std::string const& arg, void * usr) {
	((Interactor*)usr)->core.conf.action = Config::GA_DOWNLOAD;
}

void Grabber::Interactor::hURL(std::string const& arg, void * usr) {
	((Interactor*)usr)->core.conf.boardURL = arg;
}

void Grabber::Interactor::hModulePath(std::string const& arg, void * usr) {
	((Interactor*)usr)->core.conf.moduleDirs.push_back(arg);
}

void Grabber::Interactor::hModuleRecursion(std::string const& arg, void * usr) {
	int num = atoi(arg.c_str());
	if (num < 0) {
		((Interactor*)usr)->core.conf.wasError = true;
		((Interactor*)usr)->core.log.error("Recursin depth is negative");
	} else {
		((Interactor*)usr)->core.conf.moduleSearchRecursionDepth = num;
	}
}

void Grabber::Interactor::hModuleDownloader(std::string const& arg, void * usr) {
	((Interactor*)usr)->core.conf.selectedDownloader = arg;
}

void Grabber::Interactor::hModuleBoard(std::string const& arg, void * usr) {
	((Interactor*)usr)->core.conf.selectedBoard = arg;
}

void Grabber::Interactor::hModuleHandler(std::string const& arg, void * usr) {
	((Interactor*)usr)->core.conf.selectedHandler = arg;
}

void Grabber::Interactor::hListAll(std::string const& arg, void * usr) {
	((Interactor*)usr)->core.conf.action = Config::GA_LIST_ALL;
}

void Grabber::Interactor::hListDownloaders(std::string const& arg, void * usr) {
	((Interactor*)usr)->core.conf.action = Config::GA_LIST_DOWNLOADERS;
}

void Grabber::Interactor::hListBoards(std::string const& arg, void * usr) {
	((Interactor*)usr)->core.conf.action = Config::GA_LIST_BOARDS;
}

void Grabber::Interactor::hListHandlers(std::string const& arg, void * usr) {
	((Interactor*)usr)->core.conf.action = Config::GA_LIST_HANDLERS;
}

void Grabber::Interactor::hWorkingDirectory(std::string const& arg, void * usr) {
	((Interactor*)usr)->core.conf.workingDirectory = arg;
}

void Grabber::Interactor::push_option(Option const& o) {
	modOpt.push_back(o);
}

Grabber::Interactor::Interactor(Grabber & c) : core(c) {
	#ifdef HAVE_IOCTL
	struct winsize w;
	ioctl(0,TIOCGWINSZ,&w);
	opt.setTermWidth(w.ws_col);
	modOpt.setTermWidth(w.ws_col);
	#endif
	opt.push_back(Option("h", "help", "",
						 "This help message"
						 ,hHelp,this));

	opt.push_back(Option("V", "version", "",
						 "Prints version info"
						 ,hVersion,this));

	opt.push_back(Option("v", "verbose", "",
						 "Prints verbose (debug) info"
						 ,hVerbose,this));

	opt.push_back(Option("vv", "very-verbose", "",
						 "Prints even more debug info"
						 ,hVeryVerbose,this));

	opt.push_back(Option("d", "download", "",
						 "Download selected tags"
						 ,hDownload,this));

	opt.push_back(Option("u", "url", "",
						 "Specify URL of booru site"
						 ,hURL,this));

	opt.push_back(Option("mp","module-path", "DIR",
						 "Additional directory with plugins"
						 ,hModulePath,this));

	opt.push_back(Option("mr","module-recursion", "DEPTH",
						 "Depth of recursion when searching modules"
						 ,hModuleRecursion,this));
	
	opt.push_back(Option("md","module-downloader","MODULE",
						 "Downloader module name or index"
						 ,hModuleDownloader,this));

	opt.push_back(Option("mb","module-board", "MODULE",
						 "Board module name or index"
						 ,hModuleBoard,this));
	
	opt.push_back(Option("mh","module-handler", "MODULE",
						 "Handler module name or index"
						 ,hModuleHandler,this));	

	opt.push_back(Option("la","list-all","",
						 "List ALL modules"
						 ,hListAll,this));
		
	opt.push_back(Option("ld","list-downloaders","",
						 "List downloader modules"
						 ,hListDownloaders,this));
	
	opt.push_back(Option("lb","list-boards","",
						 "List board modules"
						 ,hListBoards,this));

	opt.push_back(Option("lh","list-handlers","",
						 "List handler modules"
						 ,hListHandlers,this));
	
	opt.push_back(Option("C","working-directory","DIR",
						 "Change working directory before downloading"
						 ,hWorkingDirectory,this));

	
	/*

	opt.push_back("so","search-order", "ORDER",
				  "Tag search resultsordering, one of 'count', 'name' or 'date'");
	
	opt.push_back("pl","page-limit","LIMIT",
				  "Page size limit");
	
	opt.push_back("po","page-offset","OFFSET",
				  "Page offset");

	*/
}

void Grabber::Interactor::version() {
	std::cout
		<< "danbooru-cpp-grabber ver. "
		<< DANBOORU_CPP_GRABBER_VERSION
		<< std::endl;
}

void Grabber::Interactor::help() {
	std::cout
		<< "USAGE: "
		<< core.conf.progName
		<< " [OPTIONS] <Tag1[, Tag2, ...]>"
		<< std::endl;
	opt.genHelp();
	std::cout << "*** Module options" << std::endl;
	modOpt.genHelp();
}

void Grabber::Interactor::parse(int argc, char ** argv) {
	opt.parseOptions(argc,argv);
	modOpt.parseOptions(argc,argv);
	while (optind < argc) {
		std::cout << argv[optind++] << std::endl;
	}
}
