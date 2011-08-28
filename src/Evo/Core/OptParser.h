#ifndef DANBOORU_CPP_GRABBER_CORE_OPTPARSER
#define DANBOORU_CPP_GRABBER_CORE_OPTPARSER

#include <danbooru-cpp-grabber/Generic/Option.h>

#include <ctype.h>
#include <getopt.h>

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>


class OptParser {
	public:
		OptParser() {
			totalCoreOptions = 0;
			totalOptions     = 0;
			termWidth        = 80;
			paddingBefore    = 4;
			paddingMiddle    = 4;
			shortMaxLen      = 0;
			longMaxLen       = 0;
			argMaxLen        = 0;
			descrMaxLen      = 0;
		}
	public:
		size_t termWidth;
		size_t shortMaxLen;
		size_t longMaxLen;
		size_t argMaxLen;
		size_t descrMaxLen;
		size_t paddingBefore;
		size_t paddingMiddle;
		std::vector<Option> options;
		std::vector<std::string> facilities;
		size_t totalOptions;
		size_t totalCoreOptions;
	private:
		// Unlike strtok() this function is thread-safe and do not requires
		// widechars to operate with like wcstok(). Also this can be implementd
		// with stringstreams, but i chosed to not use them. Just because. XD

		/// String-spliting (into the words) function.
		/// 
		/// \param[in] text split into words to
		/// \return vector of strings(words)
		std::vector<std::string> wordifier(std::string const& text);
		
		/// Fills struct option in generic way
		///
		/// \param[in] name of option
		/// \param[in] argument name
		/// \param[out] option structure to fill
		void fillOptionStructure(
			std::string const& name,
			std::string const& arg,
			struct option * opt
		);

		void genHelpPart(OptionType type, std::string const& facility);
		void parseOptPart(int argc, char ** argv, OptionType type, size_t count);

		static bool optionSorter(Option const& l, Option const& r);
	public:
		void push(Option const& opt);
		void setTermWidth(size_t width);
		void genHelp(bool facilize = false);
		void genHelpFacility(OptionType type, bool facilize = false);
		void parseCoreOptions(int argc, char ** argv);
		void parseOptions(int argc, char ** argv);
};

#endif
