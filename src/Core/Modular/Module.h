#ifndef DANBOORU_CPP_GRABBER_MODULE
#define DANBOORU_CPP_GRABBER_MODULE

#include <stdexcept>
#include <string>

class ModuleException : public std::logic_error {
	public:
		explicit ModuleException(
			std::string const& path,
			std::string const& what_arg) :
			std::logic_error("Module " + path + ": " + what_arg)
		{}
};

class Module {
	private:
		void *handle;
	protected:
		bool wasLoaded;
		std::string path;
	public:
		Module();
		~Module();
	public:
		void load(std::string const& filepath);
		void * sym(std::string const& symname);
};

#endif
