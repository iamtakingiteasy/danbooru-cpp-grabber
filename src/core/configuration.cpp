#include "grabber.hpp"

char Grabber::set_action(void * context, void * input) {
    Grabber * g = (Grabber*)context;
    int act = *(int*)input;
    g->action = act;
    return 1;
}

char Grabber::or_verbose(void * context, void * input) {
    Grabber * g = (Grabber*)context;
    int lev = *(int*)input;
    g->verbosity |= lev;
    return 1;
}

char Grabber::push_module_path(void * context, void * input) {
    Grabber * g = (Grabber*)context;
    char const* str = (char const*)input;
    g->modules_paths.push_back(str);
    return 1;
}

char Grabber::set_recursion_depth(void * context, void * input) {
    Grabber * g = (Grabber*)context;
    int lev = atoi((char *)input);
    if (lev < 0) return 0;
    g->recurse_level = lev;
    return 1;
}


void Grabber::push_option(char const* domain, Option opt) {
    opt.domain = domain;
    modules_options.push_back(&opt,sizeof(Option));    
}

void Grabber::grabber_init() {
    recurse_level = 3;

    modules_paths.push_back("~/.config/dcppg/modules");
    modules_paths.push_back("/usr/lib/dcppg/modules");
    

    action = GA_HELP;
    verbosity = VL_MESSAGE | VL_NOTICE | VL_WARN | VL_ERROR;

    ModuleInfo core_info;
    core_info.type    = MT_CORE;
    core_info.name    = "Core";
    core_info.descr   = "Grabber Core";
    core_info.version = "1.0";
    core_info.author  = "Alexander <itakingiteasy> Tumin";

    modules_info.push_back(&core_info,sizeof(ModuleInfo));

    push_option(core_info.name,OptionWrapper(
		    "Displays this help message",
		    "h","help","",this,GA_HELP,set_action).get_opt());
    push_option(core_info.name,OptionWrapper(
		    "Displays version info",
		    "V","version","",this,GA_VERSION,set_action).get_opt());

    push_option(core_info.name,OptionWrapper(
		    "Lists all modules",
		    "la","list-all","",this,GA_LIST_ALL,set_action).get_opt());
    push_option(core_info.name,OptionWrapper(
		    "Lists downloaders modules",
		    "ld","list-downloaders","",this,GA_LIST_DOWNLOADERS,
		    set_action).get_opt());
    push_option(core_info.name,OptionWrapper(
		    "Lists parser modules",
		    "lp","list-parsers","",this,GA_LIST_PARSERS,
		    set_action).get_opt());
    push_option(core_info.name,OptionWrapper(
		    "Lists handlers modules",
		    "lh","list-handlers","",this,GA_LIST_HANDLERS,
		    set_action).get_opt());

    push_option(core_info.name,OptionWrapper(
		    "Increases verbosity level",
		    "v","verbose","",this,VL_DEBUG1,or_verbose).get_opt());
    push_option(core_info.name,OptionWrapper(
		    "Increases verbosity level more",
		    "vv","very-verbose","",this,VL_DEBUG2,or_verbose).get_opt());
    push_option(core_info.name,OptionWrapper(
		    "Increases verbosity level even more",
		    "vvv","very-very-verbose","",this,VL_DEBUG3,or_verbose).get_opt());

    push_option(core_info.name,OptionWrapper(
		    "Specifies additional search path",
		    "mp","module-path","DIR",this,0,push_module_path).get_opt());
    push_option(core_info.name,OptionWrapper(
		    "Specifies module search recursion depth",
		    "mr","module-recursion","DEPTH",this,0,
		    set_recursion_depth).get_opt());

    module_downloader = -1;
    module_parser     = -1;
    module_handler    = -1;
}
