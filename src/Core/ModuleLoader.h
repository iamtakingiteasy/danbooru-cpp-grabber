#ifndef DANBOORU_CPP_GRABBER_CORE_MODULE_LOADER
#define DANBOORU_CPP_GRABBER_CORE_MODULE_LOADER

#include "Modular.h"

template <class Interface, class Create, class Destroy>
class ModuleLoader {
	protected:
		Modular handle;
	protected:
		std::string name;
		std::string author;
		std::string version;
		std::string descr;
		Create    * createPtr;
		Destroy   * destroyPtr;
		Interface * instance;
	public:
		ModuleLoader() {
			createPtr    = NULL;
			destroyPtr   = NULL;
			instance     = NULL;
		}
		~ModuleLoader() {
			if (instance) {
				destroyPtr(instance);
			}
		}
	public:
		void load(std::string const& filepath) {
			handle.load(filepath);
			name    = *(std::string *)handle.sym("moduleName");
			author  = *(std::string *)handle.sym("moduleAuthor");
			version = *(std::string *)handle.sym("moduleVersion");
			descr   = *(std::string *)handle.sym("moduleDescr");

			createPtr  = (Create  *)(intptr_t)handle.sym("create");
			destroyPtr = (Destroy *)(intptr_t)handle.sym("destroy");

			instance = createPtr();
		}
	public:
		bool isLoaded() const {
			return handle.isLoaded();
		}
		Interface * getInstance()       const {
			return instance;
		}
		std::string const& getName()    const {
			return name;
		}
		std::string const& getAuthor()  const {
			return author;
		}
		std::string const& getVersion() const {
			return version;
		}
		std::string const& getDescr()   const {
			return descr;
		}
};


#endif
