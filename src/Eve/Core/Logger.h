#ifndef DCPPG_CORE_LOGGER_H
#define DCPPG_CORE_LOGGER_H

#include <string>
#include <iostream>

enum VerboseLevel {
	VL_NONE,
	VL_MESSAGE,
	VL_NOTICE,
	VL_WARN,
	VL_ERROR,
	VL_DEBUG
};


class Logger {
	private:
		int flags;
		int debugLevel;
		bool showGroups;
		bool showFacilities;
	public:
		Logger();
		~Logger() {}
	public:
		void orFlags(VerboseLevel f);
		void incrDebugLevel();
		void toggleShowFacilities();
		void toggleShowGroups();
	public:
		void message(std::string const& facility, std::string const& text) const;
		void notice (std::string const& facility, std::string const& text) const;
		void warn   (std::string const& facility, std::string const& text) const;
		void error  (std::string const& facility, std::string const& text) const;
		void debug  (
			std::string const& facility,
			int level,
			std::string const& text) const;
};

#endif
