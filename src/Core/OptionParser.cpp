#include "OptionParser.h"

void OptionParser::fillOptionStructure(
	std::string const& name,
	std::string const& arg,
	struct option * opt
) {
	opt->name = name.c_str();
	if (!arg.empty()) {
		opt->has_arg = required_argument;
	} else {
		opt->has_arg = no_argument;
	}
	opt->flag = NULL;
	opt->val  = 0;
}

void OptionParser::ignoreUnknown(bool value) {
	iIgnoreUnknown = value;
}
void OptionParser::facilize(bool value) {
	iFacilize = value;
}
void OptionParser::group(bool value) {
	iGroup = value;
}


void OptionParser::width(size_t width) {
	iWidth = width;
}

std::vector<std::string> OptionParser::wordifier (std::string const& text) {
	std::vector<std::string> result;
	std::string::const_iterator sit;
	size_t index = 0;
	bool wordMark = true;
	sit = text.begin();
	// skip preceeding whitespaces
	while(isspace(*sit) && sit != text.end()) sit++;
	// so we can safely incriment index here
	for (; sit != text.end(); sit++) {
		if (isspace(*sit)) {
			if (wordMark) {
				wordMark = false;
				index++;
			}
			continue;
		} else {
			result.resize(index+1);
			wordMark = true;
		}
		result[index] += *sit;
	}
	return result;
}

void OptionParser::hScanner(
	OptionParser * that,
	Option const& opt,
	std::string const& group,
	std::string const& facility) {

	size_t dl = opt.optDescr.length();
	size_t sl = opt.optShort.length();
	size_t ll = opt.optLong.length();
	size_t al = opt.optArg.length();
	
	if (sl) that->iTotalOptions++;
	if (ll) that->iTotalOptions++;	

	if (!opt.optArg.empty()) {
		if (!opt.optShort.empty() && opt.optLong.empty()) {
			sl += 1 + al;
		} else {
			ll += 1 + al;
		}
	}
	if (sl > that->iShortMaxLen) that->iShortMaxLen = sl;
	if (ll > that->iLongMaxLen)  that->iLongMaxLen  = ll;
	if (al > that->iArgMaxLen)   that->iArgMaxLen   = al;
	if (dl > that->iDescrMaxLen) that->iDescrMaxLen = dl;

	that->iOptions[group][facility].insert(opt);
}

bool hOutterSort(
	std::map<std::string,Option> left,
	std::map<std::string,Option> right
) {
	return true;
}
void OptionParser::collectOpts() {
	iOptions.clear();
	optionMap(hScanner);
}

void OptionParser::optionMap(void (pred)(
								 OptionParser *,
								 Option const&,
								 std::string const&,
								 std::string const&)) {
	modulemapmap::const_iterator oit;
	modulemap::const_iterator iit;
	std::set<Option>::const_iterator it;

	for (oit = pModules->begin(); oit != pModules->end(); oit++) {
		for (iit = oit->second.begin(); iit != oit->second.end(); iit++) {
			ModuleInfo const& mi = iit->second->getInfo();
			for(it = mi.options.begin(); it != mi.options.end(); it++) {
				pred(this,*it,oit->first,iit->first);
			}
		}
	}
}

std::string OptionParser::genHelpEntry(Option const& opt) {
	std::string result;
	std::vector<std::string>::const_iterator wit;
	std::string const& sn = opt.optShort;
	std::string const& ln = opt.optLong;
	std::string const& an = opt.optArg;
	size_t al = an.length();
	std::vector<std::string> const& dnWords = wordifier(opt.optDescr);	
	
	// +1 for space (short-only with argument) or eq-sign
	if (!an.empty()) { al += 1; }
	
	// Padding before the option
	result.resize(iPaddingBefore,' ');
	
	// if there is short option
	if (!sn.empty()) {
		// make -option literal
		result += "-" + sn;
		if (!an.empty() && ln.empty()) {
			// add argument name
			result += " " + an;
		}
	} else {
		// balancing '-' sign
		result += " ";
	}
	
	// if there long option without short
	if (!ln.empty() && !sn.empty()) {
		result += ", ";
	} else {
		result += "  ";
	}
	
	// align by longest short option
	result.resize(result.length() + (iShortMaxLen - sn.length()), ' ');
	
	// if there is a long option
	if (!ln.empty()) {
		result += "--" + ln;
		// add argument name
		if (!an.empty()) {
			result += "=" + an;
		}
	} else {
		// balancing '--' sign
		result += "  ";
	}
	
	// align by longest long option and argument name
	result.resize(result.length() +
				  iPaddingMiddle - al +
				  (iLongMaxLen - ln.length()), ' ');
	
	size_t prefixLen = result.length() + 1;
		
	wit = dnWords.begin();
	
	// Place description on the same line option is
	for (wit = dnWords.begin();
		 wit != dnWords.end() &&
			 (result.length() + wit->length() + 1) <= iWidth;
		 wit++
	) {
		result += " " + *wit;
	}
	
	// add part of description that does not fit into
	// the same line option is without exceeding
	// termWidth boundaries
	while (wit != dnWords.end()) {
		std::string longSuffix = "\n";
		longSuffix.resize(prefixLen,' ');
		if ((longSuffix.length() + 1 + wit->length()) >= iWidth) {
			longSuffix.clear();
			while (wit != dnWords.end()) {
				longSuffix += " " + *wit;
				wit++;
			}
		}
		for (;
			 wit != dnWords.end() &&
				 (longSuffix.length() +
				  1 +
				  wit->length()) < iWidth;
			 wit++) {
			longSuffix += " " + *wit;
		}
		result += longSuffix;
	}

	return result;
}
	
std::string const& OptionParser::genHelp() {
	std::map<
		std::string,
		std::map<
			std::string,
			std::set<Option,Option> > >::const_iterator git;

	std::map<
		std::string,
		std::set<Option,Option> >::const_iterator fit;

	std::set<Option,Option>::const_iterator it;

	for (git = iOptions.begin(); git != iOptions.end(); git++) {
		if (iGroup) {
			helpResult += "*** " + git->first + " options\n";
		}
		for(fit = git->second.begin(); fit != git->second.end(); fit++) {
			if (iFacilize) {
				helpResult += "    *** " + fit->first + " module\n";
			}
			for (it = fit->second.begin(); it != fit->second.end(); it++) {
				helpResult += genHelpEntry(*it) += "\n";
			}
		}
	}
	std::cout << helpResult;
	return helpResult;
}

void OptionParser::parseOpts(int argc, char ** argv) {
	std::map<
		std::string,
		std::map<
			std::string,
			std::set<Option,Option> > >::const_iterator git;

	std::map<
		std::string,
		std::set<Option,Option> >::const_iterator fit;

	std::set<Option,Option>::const_iterator it;

	struct option * getOptOptions = new struct option[iTotalOptions+1];

	size_t fillIndex = 0;
	int    optIndex  = 0;


	for (git = iOptions.begin(); git != iOptions.end(); git++) {
		for(fit = git->second.begin(); fit != git->second.end(); fit++) {
			for (it = fit->second.begin(); it != fit->second.end(); it++) {
				std::string const& sn = it->optShort;
				std::string const& ln = it->optLong;
				std::string const& an = it->optArg;

				if (!sn.empty())
					fillOptionStructure(sn,an,&getOptOptions[fillIndex++]);
				
				if (!ln.empty())
					fillOptionStructure(ln,an,&getOptOptions[fillIndex++]);
			}
		}
	}
	getOptOptions[fillIndex].name    = 0;
	getOptOptions[fillIndex].has_arg = 0;
	getOptOptions[fillIndex].flag    = 0;
	getOptOptions[fillIndex].val     = 0;

	while(getopt_long_only(argc,argv,"",getOptOptions,&optIndex) != -1) {
		for (git = iOptions.begin(); git != iOptions.end(); git++) {
			for(fit = git->second.begin(); fit != git->second.end(); fit++) {
				for (it = fit->second.begin(); it != fit->second.end(); it++) {
					
				}
			}
		}
	}
	
	delete[] getOptOptions;
}
