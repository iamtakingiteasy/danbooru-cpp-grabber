#include "Core.h"

void Core::hHelp(std::string const& arg, void * usr) {
	((Core*)usr)->pCore->iCfg["action"] = "help";
}

void Core::hHelpFacilize(std::string const& arg, void * usr){
	((Core*)usr)->pCore->iCfg["action"] = "help";
	((Core*)usr)->pCore->pOpt->facilizeSwitch();
	
}
void Core::hHelpGroupped(std::string const& arg, void * usr){
	((Core*)usr)->pCore->iCfg["action"] = "help";
	((Core*)usr)->pCore->pOpt->groupSwitch();
}

void Core::hVersion(std::string const& arg, void * usr) {
	((Core*)usr)->pCore->iCfg["action"] = "version";
}
void Core::hVerbose(std::string const& arg, void * usr) {
	((Core*)usr)->iIO.orFlags(IO::IOBIT_DEBUG);
}
void Core::hVeryVerbose(std::string const& arg, void * usr) {
	((Core*)usr)->iIO.orFlags(IO::IOBIT_DEBUG);
	((Core*)usr)->iIO.incrDebugLevel();
}

void Core::hModulePath(std::string const& arg, void * usr) {
	if (arg.empty()) return;
	((Core*)usr)->pCore->iCfg["module"]["paths"].push_back(arg);
}

void Core::hModuleRecurDepth(std::string const& arg, void * usr) {
	int num = atoi(arg.c_str());
	if (num < 0) {
		((Core*)usr)->pCore->pLog->error("Negative recursion depth");
		return;
	}
	((Core*)usr)->pCore->iCfg["module"]["depth"] = num;
}

void Core::hModuleInterface(std::string const& arg, void * usr) {
	if (arg.empty()) return;
	((Core*)usr)->pCore->iCfg["module"]["interface"] = arg;
}
void Core::hListAll(std::string const& arg, void * usr) {
	((Core*)usr)->pCore->iCfg["action"] = "list-all";	
}
void Core::hListInterfaces(std::string const& arg, void * usr) {
	((Core*)usr)->pCore->iCfg["action"] = "list-interfaces";	
}
void Core::hListDownloaders(std::string const& arg, void * usr) {
	((Core*)usr)->pCore->iCfg["action"] = "list-downloaders";	
}
void Core::hListParsers(std::string const& arg, void * usr) {
	((Core*)usr)->pCore->iCfg["action"] = "list-parsers";	
}
void Core::hListHandlers(std::string const& arg, void * usr) {
	((Core*)usr)->pCore->iCfg["action"] = "list-handlers";
}

void Core::fillCoreInfo(ModuleInfo & info) {
	info.options.insert(
		Option(
			hHelp,this,"h","help","",
			"Displays this help message"
		)
	);
	info.options.insert(
		Option(
			hVersion,this,"V","version","",
			"Displays version info"
		)
	);

	info.options.insert(
		Option(
			hVerbose,this,"v","verbose","",
			"Increases verbosity"
		)
	);

	info.options.insert(
		Option(
			hVeryVerbose,this,"vv","very-verbose","",
			"Increases verbosity even more"
		)
	);

	
	info.options.insert(
		Option(
			hHelpFacilize,this,"hf","help-facilized","",
			"Displays facilized version of help message"
		)
	);

		
	info.options.insert(
		Option(
			hHelpGroupped,this,"hg","help-groupped","",
			"Displays groupped version of help message"
		)
	);

	info.options.insert(
		Option(
			hModulePath,this,"mp","module-path","PATH",
			"Specifies additional module search path"
		)
	);

	info.options.insert(
		Option(
			hModuleRecurDepth,this,"mr","module-recursion","DEPTH",
			"Specifies module search recursion depth"
		)
	);
	
	info.options.insert(
		Option(
			hModuleInterface,this,"mi","module-interface","MODULE",
			"Specifies user interface module to use"
		)
	);

	info.options.insert(
		Option(
			hListAll,this,"la","list-all","",
			"Lists all modules"
		)
	);
	
	info.options.insert(
		Option(
			hListInterfaces,this,"li","list-interfaces","",
			"Lists interface modules"
		)
	);
	
	info.options.insert(
		Option(
			hListDownloaders,this,"ld","list-downloaders","",
			"Lists downloader modules"
		)
	);
	
	info.options.insert(
		Option(
			hListParsers,this,"lp","list-parsers","",
			"Lists parser modules"
		)
	);

	info.options.insert(
		Option(
			hListHandlers,this,"lh","list-handlers","",
			"Lists handler modules"
		)
	);



	info.name    = "Core";
	info.author  = "Alexander <itakingiteasy> Tumin";
	info.version = "1.0";
	info.descr   = "Core module, the application itself";

}


void Core::init() {
	
}

void Core::runmod() {
	pCore->iCfg["module"]["paths"].push_back("~/.config/dcppg/modules");
	pCore->iCfg["module"]["paths"].push_back("/usr/share/dcppg/modules");
	pCore->iCfg["module"]["depth"] = 3;
	pCore->iCfg["action"] = "help";

	pCore->pOpt->ignoreUnknown(true);
	pCore->pOpt->group(true);
	pCore->pOpt->facilize(false);
	pCore->pOpt->collectOpts();
	pCore->pOpt->parseOpts();

	iModule.loadModules();

	if ((std::string)pCore->iCfg["action"] == "help") {
		std::cout << "USAGE: " << pArgv[0] << " [OPTIONS] <Tag1[, Tag2, ..., TagN]>\n";
		std::cout << pCore->pOpt->genHelp();
		return;
	} else if ((std::string)pCore->iCfg["action"] == "version") {
		std::cout << "Modular *booru grabber v." << iInfo.version << std::endl;
		return;
	}
}

void Core::deinit() {
}

ModuleInfo Core::getInfo() {
	return iInfo;
}

void Core::run(int argc, char ** argv) {
	pArgc = argc;
	pArgv = argv;
	fillCoreInfo(iInfo);
	
	iIO.showFacility(true);
	iIO.showGroups(true);
	iIO.orFlags(
		IO::IOBIT_MESSAGE |
		IO::IOBIT_NOTICE  |
		IO::IOBIT_WARN    |
		IO::IOBIT_ERROR)  ;

	iModule.io(&iIO);
	iOpt.modules(iModule.getModules());
#ifdef HAVE_IOCTL
	struct winsize w;
	ioctl(0,TIOCGWINSZ,&w);
	iOpt.width(w.ws_col);
#endif
	iOpt.arguments(argc,argv);

	iModule.pushCore(this,&iOpt);
	runmod();
}
