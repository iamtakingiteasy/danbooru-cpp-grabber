#include "optionparser.hpp"

void OptionParser::scanner(std::vector<Option__private__> options) {
    total_options = 0;
    std::vector<Option__private__>::const_iterator optit;
    size_t dl,sl,ll,al;

    dl = sl = ll = al = 0;

    max_len_descr = max_len_short = max_len_long = max_len_arg = 0;

    total_options = 0;

    optionsmap.clear();

    for (optit = options.begin(); optit != options.end(); optit++) {
	optionsmap[optit->group][optit->name].push_back(optit->opt);
	dl = strlen(optit->opt.odescr);
	sl = strlen(optit->opt.oshort);
	ll = strlen(optit->opt.olong);
	al = strlen(optit->opt.oarg);

	if (sl) total_options++;
	if (ll) total_options++;

	if (al) {
	    if (sl && !ll) {
		sl += 1 + al;
	    } else {
		ll += 1 + al;
	    }
	}
	if (dl > max_len_descr) max_len_descr = dl;
	if (sl > max_len_short) max_len_short = sl;
	if (ll > max_len_long)  max_len_long  = ll;
	if (al > max_len_arg)   max_len_arg   = al;
    }

}

std::vector<std::string> OptionParser::wordifier(char const* text) {
    std::vector<std::string> result;
    size_t length = strlen(text);
    size_t i = 0;
    bool word_mark = true;
    size_t index = 0;
    while (isspace(text[i]) && i < length) i++;
    for (; i < length; i++) {
	if (isspace(text[i])) {
	    if (word_mark) {
		word_mark = false;
		index++;
	    }
	    continue;
	} else {
	    result.resize(index+1);
	    word_mark = true;
	}
	result[index].push_back(text[i]);
    }
    return result;
}

std::string OptionParser::gen_help_entry(Option opt) {
    std::string result = "";

    std::string sn = opt.oshort;
    std::string ln = opt.olong;
    std::string an = opt.oarg;

    size_t sl = sn.length();
    size_t ll = ln.length();
    size_t al = an.length();
    
    std::vector<std::string> words = wordifier(opt.odescr);
    std::vector<std::string>::const_iterator wit;

    size_t prefix_len = 0;

    // +1 for ' ' or '='
    if (al) {
	al += 1;
    }

    result.resize(padding_before,' ');

    if (sl) {
	result += "-" + sn;
	if (al && !ll) {
	    result += " " + an;
	}
    } else {
	// balancing '-' sign
	result += " ";
    }

    if (ll && sl) {
	result += ", ";
    } else {
	result += "  ";
    }

    result.resize(result.length() + (max_len_short - sl),' ');

    if (ll) {
	result += "--" + ln;
	if (al) {
	    result += "=" + an;
	}
    } else {
	// balancing --' sign
	result += "  ";
    }

    result.resize(result.length() + padding_between - al + (max_len_long - ll), ' ');

    prefix_len = result.length() + 1;

    for (wit = words.begin();
	 wit != words.end() && (result.length() + wit->length() + 1) <= term_width;
	 wit++) {
	result += " " + *wit;
    }

    while (wit != words.end()) {
	std::string long_suffix = "\n";
	long_suffix.resize(prefix_len,' ' );
	if (long_suffix.length() + 1 + wit->length() >= term_width) {
	    long_suffix.clear();
	    while (wit != words.end()) {
		long_suffix += " " + *wit;
		wit++;
	    }
	}
	for (;wit != words.end()
		 && (long_suffix.length() + 1 + wit->length()) < term_width; wit++) {
	    long_suffix += " " + *wit;
	}
	result += long_suffix;
    }
    
    result += '\n';
    return result;
}



std::string OptionParser::gen_help(bool group, bool name) {
    std::string result;
    std::map<std::string
	     ,std::map<std::string,std::vector<Option> > >::const_iterator optit;
    std::map<std::string,std::vector<Option> >::const_iterator grpit;
    std::vector<Option>::const_iterator nmit;
    for (optit = optionsmap.begin(); optit != optionsmap.end(); optit++) {
	if (group) {
	    result += "*** " + optit->first + " options" + "\n";
	}
	for (grpit = optit->second.begin(); grpit != optit->second.end(); grpit++) {
	    if (name) {
		result += "    *** " + grpit->first + " options" + "\n";
	    }
	    for (nmit = grpit->second.begin(); nmit != grpit->second.end(); nmit++) {
		result += gen_help_entry(*nmit);
	    }
	}
    }
    return result;
}
