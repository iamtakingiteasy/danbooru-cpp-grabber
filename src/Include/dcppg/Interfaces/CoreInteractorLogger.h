#ifndef DCPPG_INTERFACE_CORE_INTERACTOR_LOGGER_H
#define DCPPG_INTERFACE_CORE_INTERACTOR_LOGGER_H

class CoreInteractorLoggerInterface{
	public:
		CoreInteractorLoggerInterface() {}
		virtual ~CoreInteractorLoggerInterface() {}
	public:
		virtual void message(std::string const& text);
		virtual void notice (std::string const& text);
		virtual void warn   (std::string const& text);
		virtual void error  (std::string const& text);
		virtual void debug  (int level, std::string const& text);
};

#endif
