#ifndef DCPPG_CORE_GRABBER_HPP
#define DCPPG_CORE_GRABBER_HPP

#include <string>
#include <vector>

#include <dcppg/data/generic/module_info.h>
#include <dcppg/data/cppspecific/dlinked.hpp>
#include <dcppg/data/cppspecific/option.hpp>

enum {
    GA_HELP,
    GA_VERSION,
    GA_LIST_ALL,
    GA_LIST_DOWNLOADERS,
    GA_LIST_PARSERS,
    GA_LIST_HANDLERS
};

enum {
    VL_MESSAGE = 1<<1,
    VL_NOTICE  = 1<<2,
    VL_WARN    = 1<<3,
    VL_ERROR   = 1<<4,
    VL_DEBUG1  = 1<<5,
    VL_DEBUG2  = 1<<5 | 1<<6,
    VL_DEBUG3  = 1<<5 | 1<<6 | 1<<7
};

class Grabber {
    private:
	int argc;
	DLinkedWrapper argv;

	int action;
	int verbosity;

	int recurse_level;
	
	DLinkedWrapper modules_paths;
	DLinkedWrapper modules_info;
	DLinkedWrapper modules_options;

	int module_downloader;
	int module_parser;
	int module_handler;
    private:
	void grabber_init();
	void push_option(char const* domain, Option opt);
	void gen_help(int oargc, DLinked oargv, DLinked options);
    public:
	void run(int oargc, char ** oargv);
    public:
	static char set_action(void*, void*);
	static char or_verbose(void*, void*);
	static char push_module_path(void*, void*);
	static char set_recursion_depth(void*, void*);
};

#endif
