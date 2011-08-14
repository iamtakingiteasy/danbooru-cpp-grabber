#ifndef DANBOORU_CPP_GRABBER_MODULE
#define DANBOORU_CPP_GRABBER_MODULE

#include <stdexcept>
#include <string>

namespace Generic {
	class Module {
		private:
			void *handle;
		protected:
			bool wasLoaded;
			std::string path;
			std::string name;
			std::string description;
			std::string version;
			std::string author;
		protected:
			void* sym(std::string const& symname) {
				void* fooptr = NULL;
#ifdef _WIN32
				fooptr = (void *)(intptr_t)GetProcAddress(
					(HINSTANCE__*)moduleHandle,
					symname.c_str());
#else
				fooptr = dlsym(moduleHandle,symname.c_str());
#endif
				if (!fooptr) {
					throw std::logic_error(
						"Module " + path + " @ symbol " + symname + " cant be loaded");
				}
			}
		public:
			Module() {
				handle = NULL;
				wasLoaded = false;
			}
			~Module() {
				if (wasLoaded) {
#ifdef _WIN32
					FreeLibrary((HINSTANCE__*)handle);
#else
					dlclose(handle);
#endif				
				}
			}
		public:
			void load(std::string const& filepath) {
				if (wasLoaded) {
					throw std::logic_error("Module " + path + " was already loaded");
				}

				path = filepath;
				
#ifdef _WIN32
				handle = LoadLibrary(path.c_str());
#else
				handle = dlopen(path.c_str(),RTLD_LAZY);
#endif
				if (!handle) {
					throw std::logic_error("Module " + path + " can't be loaded");
				}

				wasLoaded = true
			}
			
	};
}

#endif
