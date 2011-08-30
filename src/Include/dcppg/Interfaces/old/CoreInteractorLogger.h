#ifndef DCPPG_INTERFACE_CORE_INTERACTOR_LOGGER_H
#define DCPPG_INTERFACE_CORE_INTERACTOR_LOGGER_H

class CoreInteractorLogger {
	public:
		CoreInteractorLogger() {}
		virtual ~CoreInteractorLogger() {}
	public:
		virtual void message(std::string const& text) const = 0;
		virtual void notice (std::string const& text) const = 0;
		virtual void warn   (std::string const& text) const = 0;
		virtual void error  (std::string const& text) const = 0;
		virtual void debug  (int level, std::string const& text) const = 0;
};

#endif
