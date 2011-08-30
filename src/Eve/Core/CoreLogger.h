#ifndef DCPPG_CORE_CORE_LOGGER_H
#define DCPPG_CORE_CORE_LOGGER_H

#include "Logger.h"
#include <dcppg/Interfaces/CoreInteractorLogger.h>

class CoreLogger : public CoreInteractorLogger {
	private:
		Logger const* log;
		std::string facility;
	public:
		CoreLogger() {
			log = NULL;
		}
	public:
		void setFacility(std::string const& f);
		void setRealLogger(Logger const* l);
	public:
		void message(std::string const& text) const;
		void notice (std::string const& text) const;
		void warn   (std::string const& text) const;
		void error  (std::string const& text) const;
		void debug  (int level, std::string const& text) const;
};

#endif
