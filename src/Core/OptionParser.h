#ifndef DCPPG_CORE_OPTION_PARSER_H
#define DCPPG_CORE_OPTION_PARSER_H

#include "config.h"

#include <ctype.h>
#include <getopt.h>

#include <dcppg/Data/ModuleInfo.h>
#include <dcppg/CoreInteract/CoreModule.h>
#include <dcppg/CoreInteract/CoreOption.h>

#include <vector>
#include <iostream>
#include <set>
#include <string>

class OptionParser : public CoreOption {
	private:
		int     pArgc;
		char ** pArgv;
		size_t  iWidth;
		size_t  iShortMaxLen;
		size_t  iLongMaxLen;
		size_t  iArgMaxLen;
		size_t  iDescrMaxLen;
		size_t  iPaddingBefore;
		size_t  iPaddingMiddle;
		size_t  iTotalOptions;

		modulemapmap const* pModules;
		bool iIgnoreUnknown;
		bool iFacilize;
		bool iGroup;
		
		std::map<
			std::string,
			std::map<
				std::string,
				std::set<Option,Option::comparator> > > iOptions;

		
		std::set<Option,Option::comparator> iPlainOptions;
		std::string helpResult;
	public:
		OptionParser() {
			pModules       = NULL;
			iTotalOptions  = 0;
			iWidth         = 80;
			iPaddingBefore = 4;
			iPaddingMiddle = 4;
			iShortMaxLen   = 0;
			iLongMaxLen    = 0;
			iArgMaxLen     = 0;
			iDescrMaxLen   = 0;
			iIgnoreUnknown = false;
			iFacilize      = false;
			iGroup         = true;
		}
		virtual ~OptionParser() {}
	private:
		void fillOptionStructure(
			std::string const& name,
			std::string const& arg,
			struct option * opt
		);
		std::vector<std::string> wordifier (std::string const& text);
		void optionMap(void (pred)(
						   OptionParser *,
						   Option const&,
						   std::string const&,
						   std::string const&));
		static void hScanner(
			OptionParser * that,
			Option const& opt,
			std::string const& group,
			std::string const& facility);
		std::string genHelpEntry(Option const& opt);
		
	public:
		void ignoreUnknown(bool value);
		void facilize(bool value);
		void group(bool value);
		void facilizeSwitch();
		void groupSwitch();
		void width(size_t width);
		void modules(modulemapmap const* p);
		void arguments(int argc, char ** argv);
	public:
		void collectOpts();
		std::string const& genHelp();
		void parseOpts();
};

#endif
