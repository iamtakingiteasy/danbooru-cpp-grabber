#ifndef DANBOORU_CPP_GRABBER_MODULAR_GENERIC
#define DANBOORU_CPP_GRABBER_MODULAR_GENERIC

#include "Module.h"
#include <iostream>

class ModuleGeneric {
	protected:
		Module moduleHandle;
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
		std::string const& getName() const;
		std::string const& getDescription() const;
		std::string const& getVersion() const;
		std::string const& getAuthor() const;
};

#endif
