#ifndef DCPPG_CORE_LOGGER_H
#define DCPPG_CORE_LOGGER_H

#include "config.h"

#include <dcppg/CoreInteract/CoreLogger.h>

#include "IO.h"

#include <string>

class Logger : public CoreLogger {
	private:
		IO const* iIO;
		std::string iFacility;
	private:
		Logger & operator=(Logger const& r) {
			return *this;
		}
		Logger(Logger const& r) {}
	public:
		Logger() {
			iIO = NULL;
		}
		virtual ~Logger() {}
	public:
		void io(IO const* iio);
		void facility(std::string const& facility);
	public:
		void message(std::string const& text) const;
		void notice (std::string const& text) const;
		void warn   (std::string const& text) const;
		void error  (std::string const& text) const;
		void debug  (int level, std::string const& text) const;
};

#endif
