#ifndef DCPPG_CORE_OPTIONPARSER_HPP
#define DCPPG_CORE_OPTIONPARSER_HPP

#include <string.h>
#include <vector>
#include <string>
#include <map>
#include <dcppg/data/generic/option.h>
#include <iostream>

class OptionParser {
    private:
	std::map<std::string,std::map<std::string,std::vector<Option> > > optionsmap;
	size_t total_options;

	size_t max_len_descr;
	size_t max_len_short;
	size_t max_len_long;
	size_t max_len_arg;

	size_t term_width;
	size_t padding_before;
	size_t padding_between;
    private:
	std::vector<std::string> wordifier(char const* text);
	std::string gen_help_entry(Option opt);
    public:
	OptionParser() {
	    total_options   = 0;
	    term_width      = 80;
	    padding_before  = 4;
	    padding_between = 4;
	    max_len_descr = max_len_short = max_len_long = max_len_arg = 0;
	}
    public:
	void scanner(std::vector<Option__private__> ao);
	std::string gen_help(bool group = 1, bool name = 1);
};

#endif
