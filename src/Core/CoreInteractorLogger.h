#ifndef DCCPG_CORE_CORE_INTERACTOR_LOGGER_H
#define DCCPG_CORE_CORE_INTERACTOR_LOGGER_H

class CoreInteractorLogger {
	private:
		Logger * log;
	public:
		CoreInteractor(Logger * l) :
			log(l)
		{}
	public:
		void message(std::string const& text);
		void notice (std::string const& text);
		void warn   (std::string const& text);
		void error  (std::string const& text);
		void debug  (int level, std::string const& text);
};

#endif
