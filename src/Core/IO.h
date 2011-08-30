#ifndef DCPPG_CORE_IO_H
#define DCPPG_CORE_IO_H

#include "config.h"

#include <iostream>
#include <string>

class IO {
	public:
		enum IOFlag {
			IOBIT_MESSAGE = 1<<1,
			IOBIT_NOTICE  = 1<<2,
			IOBIT_WARN    = 1<<3,
			IOBIT_ERROR   = 1<<4,
			IOBIT_DEBUG   = 1<<5
		};
	private:
		bool iShowFacility;
		bool iShowGroups;
		int  iFlags;
		int  iDebugLevel;
	public:
		IO() {
			iShowFacility = false;
			iShowGroups   = true;
			iFlags = IOBIT_MESSAGE | IOBIT_NOTICE | IOBIT_WARN | IOBIT_ERROR;
			iDebugLevel = 0;
		}
	public:
		void incrDebugLevel();
		void showFacility(bool value);
		void showGroups(bool value);
		void orFlags(int flags);
	public:
		void message(std::string const& facility, std::string const& text) const;
		void notice (std::string const& facility, std::string const& text) const;
		void warn   (std::string const& facility, std::string const& text) const;
		void error  (std::string const& facility, std::string const& text) const;
		void debug  (std::string const& facility, int level, std::string const& text)
			const;
};

#endif
