#include "OptParser.h"

std::vector<std::string> OptParser::wordifier(std::string const& text) {
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
void OptParser::fillOptionStructure(
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

bool OptParser::optionSorter(Option const& l, Option const& r) {
	return (l.optShort < r.optShort);
}

void OptParser::setTermWidth(size_t width) {
	termWidth = width;
}

void OptParser::push(Option const& opt) {
	size_t dl = opt.optDescr.length();
	size_t sl = opt.optShort.length();
	size_t ll = opt.optLong.length();
	size_t al = opt.optArg.length();
	
	if (sl) totalOptions++; // we need
	if (ll) totalOptions++; //  both!

	if (opt.type == OT_CORE) {
		if (sl) totalCoreOptions++; // just the
		if (ll) totalCoreOptions++; //  same
	}
	
	if (!opt.optArg.empty()) {
		if (!opt.optShort.empty() && opt.optLong.empty()) {
			sl += 1 + al;
		} else {
			ll += 1 + al;
		}
	}
	
	
	if (sl > shortMaxLen) shortMaxLen = sl;
	if (ll > longMaxLen)  longMaxLen  = ll;
	if (al > argMaxLen)   argMaxLen   = al;
	if (dl > descrMaxLen) descrMaxLen = dl;

	options.push_back(opt);

	std::vector<std::string>::const_iterator it;
	for (it = facilities.begin(); it != facilities.end(); it++) {
		if (*it == opt.facility) return;
	}
	facilities.push_back(opt.facility);
}

void OptParser::genHelpPart(OptionType type, std::string const& facility) {
	std::vector<Option>::const_iterator oit;
	std::vector<std::string>::const_iterator wit;
	bool wasHeader = false;

	for (oit = options.begin(); oit != options.end(); oit++) {
		if (oit->type != type) continue;
		if (!facility.empty()) {
			if (oit->facility != facility) continue;
			else if (!wasHeader) {
				wasHeader = true;
				std::cout << "   *** " << facility << std::endl;
			}
		} 
		std::string const& sn = oit->optShort;
		std::string const& ln = oit->optLong;
		std::string const& an = oit->optArg;
		size_t al = an.length();
		
		std::vector<std::string> const& dnWords = wordifier(oit->optDescr);
		
		std::string prefix;
		
		// +1 for space (short-only with argument) or eq-sign
		if (!an.empty()) { al += 1; }
		
		// Padding before the option
		prefix.resize(paddingBefore,' ');
		
		// if there is short option
		if (!sn.empty()) {
			// make -option literal
			prefix += "-" + sn;
			if (!an.empty() && ln.empty()) {
				// add argument name
				prefix += " " + an;
			}
		} else {
			// balancing '-' sign
			prefix += " ";
		}
		
		// if there long option without short
		if (!ln.empty() && !sn.empty()) {
			prefix += ", ";
		} else {
			prefix += "  ";
		}
		
		// align by longest short option
		prefix.resize(prefix.length() + (shortMaxLen - sn.length()), ' ');
		
		// if there is a long option
		if (!ln.empty()) {
			prefix += "--" + ln;
			// add argument name
			if (!an.empty()) {
				prefix += "=" + an;
			}
		} else {
			// balancing '--' sign
			prefix += "  ";
		}
		
		// align by longest long option and argument name
		prefix.resize(prefix.length() +
					  paddingMiddle - al +
					  (longMaxLen - ln.length()), ' ');
		
		size_t prefixLen = prefix.length() + 1;
		
		wit = dnWords.begin();
		
		// Place description on the same line option is
		for (wit = dnWords.begin();
			 wit != dnWords.end() &&
				 (prefix.length() + wit->length() + 1) <= termWidth;
			 wit++
		) {
			prefix += " " + *wit;
		}
		
		// add part of description that does not fit into
		// the same line option is without exceeding
		// termWidth boundaries
		while (wit != dnWords.end()) {
			std::string longSuffix = "\n";
			longSuffix.resize(prefixLen,' ');
			if ((longSuffix.length() + 1 + wit->length()) >= termWidth) {
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
					  wit->length()) < termWidth;
				 wit++) {
				longSuffix += " " + *wit;
			}
			prefix += longSuffix;
		}
		
		// print option entry
		std::cout << prefix << std::endl;
	}
}

void OptParser::genHelp(bool facilize) {
	std::sort(options.begin(),options.end(),&OptParser::optionSorter);

	std::cout << "*** Core options" << std::endl;
	genHelpFacility(OT_CORE,facilize);
	std::cout << "*** Interfaces options" << std::endl;
	genHelpFacility(OT_INTERFACE,facilize);
	std::cout << "*** Downloaders options" << std::endl;
	genHelpFacility(OT_DOWNLOADER,facilize);
	std::cout << "*** Boards options" << std::endl;
	genHelpFacility(OT_BOARD,facilize);
	std::cout << "*** Handlers options" << std::endl;
	genHelpFacility(OT_HANDLER,facilize);
}

void OptParser::genHelpFacility(OptionType type, bool facilize) {
	std::vector<std::string>::const_iterator it;
	if (facilize) {
		for (it = facilities.begin(); it != facilities.end(); it++) {
			genHelpPart(type,*it);
		}
	} else {
		genHelpPart(type,"");
	}
}

void OptParser::parseOptPart(int argc, char ** argv, OptionType type, size_t count) {
	std::vector<Option>::const_iterator oit;
	size_t index = 0;
	int i = 0;
	struct option * getOptOptions = new struct option[count+1];
	
	for (oit = options.begin(); oit != options.end(); oit++) {
		if (oit->type != type && type != OT_ALL) continue;
		std::string const& sn = oit->optShort;
		std::string const& ln = oit->optLong;
		std::string const& an = oit->optArg;
		
		/// Short options
		if (!sn.empty()) {
			fillOptionStructure(sn,an,&getOptOptions[index]);
			index++;
		}
		/// Long options
		if (!ln.empty()) {
			fillOptionStructure(ln,an,&getOptOptions[index]);
			index++;
		}
		
	}
	// NULL terminator
	getOptOptions[index].name    = 0;
	getOptOptions[index].has_arg = 0;
	getOptOptions[index].flag    = 0;
	getOptOptions[index].val     = 0;

	while (getopt_long_only(argc,argv,"",getOptOptions,&i) != -1) {
		for (oit = options.begin(); oit != options.end(); oit++) {
			std::string o;
			if (getOptOptions[i].name) o = getOptOptions[i].name;
			std::string an;
			if (optarg) an = optarg;
			
			if (o == oit->optShort || o == oit->optLong) {
				oit->optHandler(an,oit->usrPtr);
				break;
			}
		}
	}
	
	delete[] getOptOptions;
}

void OptParser::parseCoreOptions(int argc, char ** argv) {
	opterr = 0;
	parseOptPart(argc,argv,OT_CORE,totalCoreOptions);
}

void OptParser::parseOptions(int argc, char ** argv) {
	opterr = 1;
	parseOptPart(argc,argv,OT_ALL,totalCoreOptions);
}
