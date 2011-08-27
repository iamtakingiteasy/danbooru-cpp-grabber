#include "Application.h"

#ifdef HAVE_IOCTL
#    include <sys/ioctl.h>
#endif



void Application::hHelp(std::string const& arg, void * usr) {
	((Application*)usr)->conf.action = GA_HELP;
}

void Application::hHelpFacilize(std::string const& arg, void * usr) {
	((Application*)usr)->conf.action = GA_HELP;
	((Application*)usr)->conf.facilize = true;
}

void Application::hVersion(std::string const& arg, void * usr) {
	((Application*)usr)->conf.action = GA_VERSION;
}


void Application::hModulePath(std::string const& arg, void * usr) {
	((Application*)usr)->conf.modulePaths.push_back(arg);
}

void Application::hModuleRecursion(std::string const& arg, void * usr) {
	int num = atoi(arg.c_str());
	if (num < 0) {
		((Application*)usr)->log.error("Negative recursion depth");
		((Application*)usr)->conf.wasError = true;
		return;
	}
	((Application*)usr)->conf.moduleRecursionDepth = num;
}

void Application::hModuleInterface(std::string const& arg, void * usr) {
	((Application*)usr)->conf.moduleInterface = arg;
}

void Application::hVerbose(std::string const& arg, void * usr) {
	((Application*)usr)->conf.verbose |= VL_DEBUG;	
}

void Application::hVeryVerbose(std::string const& arg, void * usr) {
	((Application*)usr)->conf.debugLevel = 1;
}

void Application::hGuiMode(std::string const& arg, void * usr) {
	((Application*)usr)->conf.action = GA_GUIMODE;
}



void Application::run(int argc, char ** argv) {
	#ifdef HAVE_IOCTL
	struct winsize w;
	ioctl(0,TIOCGWINSZ,&w);
	opt.setTermWidth(w.ws_col);
	#endif
	
	opt.push(Option(this,hHelp,"h","help","",
					"Displays this help",
					"CORE",OT_CORE));

	opt.push(Option(this,hHelpFacilize,"hf","help-facilize","",
					"Displays facilizied version of help",
					"CORE",OT_CORE));
	
	opt.push(Option(this,hVersion,"V","version","",
					"Displays version info",
					"CORE",OT_CORE));
	
	opt.push(Option(this,hModulePath,"mp","module-path","PATH",
					"Specifies additional module search path",
					"CORE",OT_CORE));

	opt.push(Option(this,hModuleRecursion,"mr","module-recursion","DEPTH",
					"Specifies module recursion search depth",
					"CORE",OT_CORE));

	opt.push(Option(this,hModuleInterface,"mi","module-interface","NAME",
					"Specifies interface module name or index",
					"CORE",OT_CORE));

	opt.push(Option(this,hVerbose,"v","verbose","",
					"Enables verbose (debug) printing",
					"CORE",OT_CORE));

	opt.push(Option(this,hVeryVerbose,"vv","very-verbose","",
					"Enables very verbose (debug) printing",
					"CORE",OT_CORE));
	
	opt.push(Option(this,hGuiMode,"gui","gui-mode","",
					"Enables graphical user interface mode (not implemented yet)",
					"CORE",OT_CORE));
		

	opt.parseCoreOptions(argc,argv);
	
	switch (conf.action) {
	case GA_NONE:
		break;
	case GA_HELP:
		opt.genHelp(conf.facilize);
		break;
	case GA_VERSION:
		break;
	case GA_GUIMODE:
		break;
	}
	if (conf.wasError) {
		log.error("Errors detected, exiting");
		return;
	}
}
