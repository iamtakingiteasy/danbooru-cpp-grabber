#include "Core.h"

void Core::hHelp(std::string const& arg, void * usr) {
}

void Core::fillCoreInfo(ModuleInfo & info) {
	info.options.insert(
		Option(
			hHelp,this,"h","help","",
			"Displays this help message"
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
	OptionParser coreopt(pCore->pMod);

	pCore->iCfg["module"]["paths"].push_back("~/.config/dcppg/modules");
	pCore->iCfg["module"]["paths"].push_back("/usr/share/dcppg/modules");

	coreopt.ignoreUnknown(true);
	coreopt.facilize(false);
	coreopt.group(true);
#ifdef HAVE_IOCTL
	struct winsize w;
	ioctl(0,TIOCGWINSZ,&w);
	coreopt.width(w.ws_col);
#endif
	coreopt.collectOpts();

	coreopt.genHelp();
}

void Core::deinit() {
}

ModuleInfo Core::getInfo() {
	return iInfo;
}

void Core::run(int argc, char ** argv) {
	fillCoreInfo(iInfo);
	
	iIO.showFacility(true);
	iIO.showGroups(true);
	iIO.orFlags(
		IO::IOBIT_MESSAGE |
		IO::IOBIT_NOTICE  |
		IO::IOBIT_WARN    |
		IO::IOBIT_ERROR)  ;

	iModule.io(&iIO);
	iModule.pushCore(this);
}
