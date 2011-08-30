#ifndef DCPPG_CORE_INTERACT_LOGGER_H
#define DCPPG_CORE_INTERACT_LOGGER_H

#include <string>

class CoreLogger {
	public:
		virtual void message(std::string const& text) const = 0;
		virtual void notice (std::string const& text) const = 0;
		virtual void warn   (std::string const& text) const = 0;
		virtual void error  (std::string const& text) const = 0;
		virtual void debug  (int level, std::string const& text) const = 0;
};

#endif
