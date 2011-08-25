#include <ctype.h>
#include <getopt.h>

#include <iostream>
#include <vector>
#include <string>

/// Option parser class, serving the purpose of parsing command-line
/// options and generating --help options listing.
class OptParser {
	private:
		class Option {
			public:
				std::string optShort; ///< short version
				std::string optLong;  ///< long version
				std::string optArg;   ///< argument name
				std::string optDescr; ///< --help description
			public:
				Option(
					std::string const& optShort,
					std::string const& optLong,
					std::string const& optArg,
					std::string const& optDescr
				) :
					optShort(optShort),
					optLong(optLong),
					optArg(optArg),
					optDescr(optDescr)
				{}
		};
	private:
		size_t termWidth;              ///< width of terminal wrap to
		size_t shortMaxLen;            ///< maximum length of short option
		size_t longMaxLen;             ///< maximum length of long option
		size_t argMaxLen;              ///< maximum length of argument name
		size_t descrMaxLen;            ///< maximum length of description
		size_t paddingBefore;          ///< pading before options
		size_t paddingMiddle;          ///< padding between option an description
		std::vector<Option> options;   ///< internal options representation
		size_t totalOptions;           ///< total number of options
		struct option * getOptOptions; ///< set of getopt() options
	private:
		// Unlike strtok() this function is thread-safe and do not requires
		// widechars to operate with like wcstok(). Also this can be implementd
		// with stringstreams, but i chosed to not use them. Just because. XD

		/// String-spliting (into the words) function.
		/// 
		/// \param[in] text split into words to
		/// \return vector of strings(words)
		std::vector<std::string> wordifier(std::string const& text) {
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
		/// Fills struct option in generic way
		///
		/// \param[in] name of option
		/// \param[in] argument name
		/// \param[out] option structure to fill
		void fillOptionStructure(
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
	public:
		OptParser() {
			getOptOptions = NULL;
			totalOptions  = 0;
			termWidth     = 80;
			paddingBefore = 4;
			paddingMiddle = 4;
			shortMaxLen   = 0;
			longMaxLen    = 0;
			argMaxLen     = 0;
			descrMaxLen   = 0;
		}
		~OptParser(){
			delete[] getOptOptions;
		}
	public:
		/// Pushes back option to option list
		///
		/// \param[in] s hort option name
		/// \param[in] l ong optiion name
		/// \param[in] a rgument name
		/// \param[in] d escription of option
		void push_back(
			std::string const& s,
			std::string const& l,
			std::string const& a,
			std::string const& d
		) {
			Option opt(s,l,a,d);
			size_t sl = s.length();
			size_t ll = l.length();
			size_t al = a.length();
			size_t dl = d.length();

			if (sl) totalOptions++; // we need
			if (ll) totalOptions++; //  both!

			if (!a.empty()) {
				if (!s.empty() && l.empty()) {
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
		}
		/// Simple setter
		///
		/// \param[in] width of terminal
		void setTermWidth(size_t width) {
			termWidth = width;
		}
		/// Generates --help dialog
		void genHelp() {
			std::vector<Option>::const_iterator oit;
			std::vector<std::string>::const_iterator wit;
			for (oit = options.begin(); oit != options.end(); oit++) {
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
					if ((longSuffix.length() + 1 + wit->length()) > termWidth) {
						longSuffix.clear();
						while (wit != dnWords.end()) {
							longSuffix += " " + *wit;
							wit++;
						}
					} else {
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
		/// gen getOpt option list from internal structure
		///
		/// \return NULL-terminated array of options
		struct option * genGetOptOptions() {
			std::vector<Option>::const_iterator oit;
			size_t index = 0;
			delete[] getOptOptions;
			getOptOptions = new struct option[totalOptions+1];

			for (oit = options.begin(); oit != options.end(); oit++) {
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
			return getOptOptions;
		}
		
};
