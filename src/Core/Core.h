#ifndef DCPPG_CORE_CORE_H
#define DCPPG_CORE_CORE_H

#include "config.h"

#include <dcppg/Interfaces/Module.h>

#include "IO.h"
#include "ModuleManager.h"
#include "OptionParser.h"

#include <string>

#ifdef HAVE_IOCTL
#      include <sys/ioctl.h>
#endif

//void hHelp(std::string const& arg, void * usr) {
//	
///}

class Core : public ModuleInterface {
	private:
		ModuleInfo    iInfo;
		ModuleManager iModule;
		IO            iIO;
	private:
		void fillCoreInfo(ModuleInfo & info);
	private:
		static void hHelp(std::string const& arg, void * usr);
	public:
		void init();
		void runmod();
		ModuleInfo getInfo();
		void deinit();
	public:
		void run(int argc, char ** argv);
		/*
	private:
		IO             iIO;
		ModuleInfo     iInfo;

		CoreInteract * pCore;
		std::map<std::string,ModuleInfo> iMeta;
		
	private:

	public:
		void init();
		void deinit();
		void run(int argc, char ** argv) {

			
		}
		*/










/*
	private:
		IO            iIO;
		MetaData      iMeta;
		ModuleManager iModule;
	public:
		Core() {
			iIO.showFacility(false);
			iIO.showGroups(true);

			iLog.io(&iIO);
			iLog.facility("CORE");

			iModule.io(&iIO);
			iModule.meta(iMeta);

			iOptions.meta(&iMeta);
			iOptions.ignoreUnknown(true);

			initializeCoreOptions();
		}

	private:
		void initializeCoreOptions();
		void scandir(std::string const& path, int recurDepth);
		void loadModules();
	public:
		void run(int argc, char ** argv);
		*/
};

#endif
