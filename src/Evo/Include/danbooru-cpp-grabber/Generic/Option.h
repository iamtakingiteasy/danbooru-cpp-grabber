#ifndef DANBOORU_CPP_GRABBER_GENERIC_OPTION
#define DANBOORU_CPP_GRABBER_GENERIC_OPTION

#include <string>

typedef void optionHandler(std::string const& optArg, void *userPtr);

enum OptionType {
	OT_MALICIOUS ,
	OT_CORE,
	OT_INTERFACE,
	OT_DOWNLOADER,
	OT_BOARD,
	OT_HANDLER,
	OT_ALL
};

class Option {
	public:
		void * usrPtr;
		optionHandler * optHandler;
		std::string optShort;
		std::string optLong;
		std::string optArg;
		std::string optDescr;
		std::string facility;
		OptionType type;
	public:
		Option(
			void * usrPtr,
			optionHandler optHandler,
			std::string const& optShort,
			std::string const& optLong,
			std::string const& optArg,
			std::string const& optDescr,
			std::string const& facility = "MALICIOUS",
			OptionType type = OT_MALICIOUS
		) :
			usrPtr(usrPtr),
			optHandler(optHandler),
			optShort(optShort),
			optLong(optLong),
			optArg(optArg),
			optDescr(optDescr),
			facility(facility),
			type(type)
		{}
};

#endif
