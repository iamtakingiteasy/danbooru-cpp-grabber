#ifndef DANBOORU_CPP_GRABBER_CORE_MODULE_GENERIC
#define DANBOORU_CPP_GRABBER_CORE_MODULE_GENERIC

#include "ModuleLoader.h"
#include <iostream>

class ModuleGeneric {
	protected:
		ModuleLoader moduleHandle;
	protected:
		std::string name;
		std::string description;
		std::string version;
		std::string author;
	public:
		ModuleGeneric() {
		}
		virtual ~ModuleGeneric() {}
	public:
		void loadBasic(std::string const& filepath);
	public:
		bool isLoaded() const;
		std::string const& getName() const;
		std::string const& getDescription() const;
		std::string const& getVersion() const;
		std::string const& getAuthor() const;
};


#endif

