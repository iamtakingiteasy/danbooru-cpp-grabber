#ifndef DCPPG_CORE_GRABBER_HPP
#define DCPPG_CORE_GRABBER_HPP

#include <iostream>
#include <vector>
#include <string>

#include <dcppg/data/cppspecific/option.hpp>
#include <dcppg/data/cppspecific/module_info.hpp>

#include "optionparser.hpp"

enum {
    GA_HELP,
    GA_VERSION,
    GA_LIST_ALL,
    GA_LIST_DOWNLOADERS,
    GA_LIST_PARSERS,
    GA_LIST_HANDLERS,
    GA_MANAGE
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
	std::vector<std::string> argv;

	int action;
	int verbosity;

	int recursion_depth;

	OptionParser option_parser;

	std::vector<std::string>       modules_paths;
	std::vector<ModuleInfo>        modules_info;
	std::vector<Option__private__> modules_options;

	int module_manager;
	int module_downloader;
	int module_parser;
	int module_handler;
    private:
	void grabber_init(int ac, char ** av);
	void push_option(ModuleType type, char const* domain, Option opt);
    public:
	void run(int ac, char ** av);
    public:
	static int set_action(void * context, void * value);
	static int or_verbosity(void * context, void * value);
	static int push_module_path(void * context, void * value);
	static int set_recutsion_depth(void * context, void * value);
};

#endif
