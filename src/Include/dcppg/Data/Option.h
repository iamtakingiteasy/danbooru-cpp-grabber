#ifndef DCPPG_DATA_OPTION_H
#define DCPPG_DATA_OPTION_H

#include <string>

typedef void optionHandler(std::string const& optArg, void *userPtr);

class Option  {
	public:
		optionHandler * optHandler;
		void * usrPtr;
		std::string optShort;
		std::string optLong;
		std::string optArg;
		std::string optDescr;
	public:
		Option() {
			optHandler = NULL;
			usrPtr     = NULL;
		}
		Option(
			optionHandler * optHandler,
			void * usrPtr,
			std::string const& optShort,
			std::string const& optLong,
			std::string const& optArg,
			std::string const& optDescr
		) :
			optHandler(optHandler),
			usrPtr(usrPtr),
			optShort(optShort),
			optLong(optLong),
			optArg(optArg),
			optDescr(optDescr)
		{}
	public:
		class comparator {
			public:
				bool operator()(Option const& a, Option const& b) const {
					return (a.optShort   != b.optShort   ||
							a.optLong    != b.optLong    ||
							a.optHandler != b.optHandler ||
							a.optArg     != b.optArg);
				}
		};
};


#endif
