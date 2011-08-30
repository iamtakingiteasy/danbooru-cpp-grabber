#ifndef DCCPG_CORE_CORE_H
#define DCPPG_CORE_CORE_H

#include <map>
#include <vector>
#include <string>

class Logger  {
	private:
		int flags;
		
};

typedef void optionHandler(std::string const& optArg, void *userPtr);

class Option  {
	public:
		optionHandler * optHandler;
		void * usrPtr;
		std::string optShort;
		std::string optLong;
		std::string optArg;
		std::string optDescr;
	public:
		Option(
			optionHandler optHandler,
			void * usrPtr,
			std::string const& optShort,
			std::string const& optLong,
			std::string const& optArg,
			std::string const& optDescr,
		) :
			optHandler(optHandler),
			usrPtr(usrPtr),
			optShort(optShort),
			optLong(optLong),
			optArg(optArg),
			optDescr(optDescr)
		{}
};


class Options {};


class ModuleInfo {
	public:
		std::string name;
		std::string author;
		std::string version;
		std::string descr;
		std::vector<Option> options;
	public:
		ModuleInfo(
			std::string const& name,
			std::string const& author,
			std::string const& version,
			std::string const& descr,
			std::vector<Option> options
		) :
			name(name),
			author(author),
			version(version),
			descr(descr),
			options(options)
		{}
};

class Modular {
		
};

class CoreInteractor {
	private:
		Logger * log;
	public:
		CoreInteractor() {
			log = NULL;
		}
	public:
		void setLog(Logger * l) {
			log = l;
		}
	public:
		
};


template<class I, class C, class D>
class ModuleLoader {
	privete:
		std::string path;
		Modular handle;
		ModuleInfo info;
		CoreInteractor icore;
		
		I * instance;
		C * create;
		D * destroy;
	public:
		ModuleLoader() {
			instance = NULL;
			crate    = NULL;
			destroy  = NULL;
			log      = NULL;
		}
		~ModuleLoader() {
			unload();
		}
	public:
		
	public:
		void load(std::string const& p, Logger * l) {
			if (instance) return;
			if (path.empty()) path = p;
			if (path.empty()) return;
			if (l != NULL) icore.setLog(l);
			handle.load(path);
			create  = (C*)(intptr_t)handle.sym("create");
			destroy = (D*)(intptr_t)handle.sym("destroy");
			instance = create();
			info = instance->getInfo();
			instance->setCore(&icore);
		}
		void unload() {
			if (instance) {
				destroy(instance);
			}
			handle.unload();
		}
		void reload() {
			unload();
			load(path,NULL);
		}
};

class ModuleBase {};

class ModuleInterface  : public ModuleBase {};
typedef ModuleInterface * interface_create_t();
typedef void interface_destroy_t(ModuleInterface *);

class ModuleDownloader : public ModuleBase {};
typedef ModuleDownloader * downloader_create_t();
typedef void downloader_destroy_t(ModuleDownloader *);

class ModuleParser     : public ModuleBase {};
typedef ModuleParser * parser_create_t();
typedef void parser_destroy_t(ModuleParser *);

class ModuleHandler    : public ModuleBase {};
typedef ModuleHandler * handler_create_t();
typedef void handler_destroy_t(ModuleHandler *);




class Core {
	private:
		Logger  ilog;
		Options iopt;

		std::map<
			std::string,
			ModuleLoader<
				ModuleInterface,
				interface_create_t,
				interface_destroy_t>
			> interfaces;

		std::map<
			std::string,
			ModuleLoader<
				ModuleDownloader,
				downloader_create_t,
				downloader_destroy_t>
			> downloaders;

		std::map<
			std::string,
			ModuleLoader<
				ModuleParser,
				parser_create_t,
				parser_destroy_t>
			> parsers;

		std::map<
			std::string,
			ModuleLoader<
				ModuleHandler,
				handler_create_t,
				handler_destroy_t>
			> handlers;
		
	public:
		void run(int argc, char ** argv);
		// init options
		// parse core options
		// load modules
		// parse options again, now with modules'
		// switch action
		//// A_HELP
		//// A_HELPFACIL
		//// A_VERSION
		//// A_CONTINUE
		// execute interface
		//// interfaces decides which downloader, board and handler to use
		//// and with which options
		

};

#endif
