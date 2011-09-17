#include "grabber.hpp"
#include <stdlib.h>

void Grabber::push_option(ModuleType group, char const* domain, Option opt) {
    Option__private__ optpriv;
    optpriv.opt = opt;
    optpriv.name = domain;
    switch (group) {
    case MT_NONE:
	optpriv.group = "MALICIOUS";
	break;
    case MT_CORE:
	optpriv.group = "Core";
	break;
    case MT_DOWNLOADER:
	optpriv.group = "Downloaders";
	break;
    case MT_PARSER:
	optpriv.group = "Parsers";
	break;
    case MT_HANDLER:
	optpriv.group = "Handlers";
	break;
    }
    
    modules_options.push_back(optpriv);
}

int Grabber::set_action(void * context, void * value) {
    Grabber * g = (Grabber*)context;
    int v = *(int*)value;
    g->action = v;
    return 1;
}
int Grabber::or_verbosity(void * context, void * value) {
    Grabber * g = (Grabber*)context;
    int v = *(int*)value;
    g->verbosity |= v;
    return 1;
}
int Grabber::push_module_path(void * context, void * value) {
    Grabber * g = (Grabber*)context;
    char const* path = (char const*)value;
    g->modules_paths.push_back(path);
    return 1;
}
int Grabber::set_recutsion_depth(void * context, void * value) {
    Grabber * g = (Grabber*)context;
    int v = atoi((char const*)value);
    if (v < 0) return 0;
    g->recursion_depth = v;
    return 1;
}

void Grabber::grabber_init(int ac, char ** av) {
    argc = ac;
    for (int i = 0; i < ac; i++) {
	argv.push_back(av[i]);
    }
    action = GA_HELP;
    verbosity = VL_MESSAGE | VL_NOTICE | VL_WARN | VL_ERROR;

    modules_paths.push_back("~/.config/dcppg/modules");
    modules_paths.push_back("/usr/lib/dcppg/modules");

    ModuleInfo core_info = CPPModuleInfo(
	ML_CPP,
	MT_CORE,
	"Core",
	"Grabber core",
	"1.0",
	"Alexander <itakingiteasy> Tumin"
    ).get();
    
    modules_info.push_back(core_info);
    push_option(core_info.type, core_info.name, CPPOption(
		    "Displays this help message",
		    "h","help","",this,GA_HELP,
		    set_action).get());
    push_option(core_info.type, core_info.name, CPPOption(
		    "Displays version info",
		    "v","version","",this,GA_VERSION,
		    set_action).get());

    push_option(core_info.type, core_info.name, CPPOption(
		    "Lists all modules",
		    "la","list-all","",this,GA_LIST_ALL,
		    set_action).get());
    push_option(core_info.type, core_info.name, CPPOption(
		    "Lists downloader modules",
		    "ld","list-downloaders","",this,GA_LIST_DOWNLOADERS,
		    set_action).get());
    push_option(core_info.type, core_info.name, CPPOption(
		    "Lists parser modules",
		    "lp","list-parsers","",this,GA_LIST_PARSERS,
		    set_action).get());
    push_option(core_info.type, core_info.name, CPPOption(
		    "Lists handler modules",
		    "lh","list-handlers","",this,GA_LIST_HANDLERS,
		    set_action).get());

    push_option(core_info.type, core_info.name, CPPOption(
		    "Increases verbosity level",
		    "v","verbose","",this,VL_DEBUG1,
		    or_verbosity).get());
    push_option(core_info.type, core_info.name, CPPOption(
		    "Increases verbosity level more",
		    "vv","very-verbose","",this,VL_DEBUG2,
		    or_verbosity).get());
    push_option(core_info.type, core_info.name, CPPOption(
		    "Increases verbosity level even more",
		    "vvv","very-very-verbose","",this,VL_DEBUG3,
		    or_verbosity).get());

    push_option(core_info.type, core_info.name, CPPOption(
		    "Specified additional module search path",
		    "mp","module-path","",this,0,
		    push_module_path).get());
    push_option(core_info.type, core_info.name, CPPOption(
		    "Specifies module search recursion depth",
		    "mr","module-recursion","",this,0,
		    set_recutsion_depth).get());
}
