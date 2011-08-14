#ifndef DANBOORU_CPP_GRABBER_MODULE
#define DANBOORU_CPP_GRABBER_MODULE

#include <stdexcept>
#include <string>

namespace Generic {
	class Module {
		private:
			void *moduleHandle;
			std::string path;
		private:
			void moduleOpen();
			void moduleClose();
		public:
			Module(std::string const& filepath) {
				path = filepath;
				moduleHandle = NULL;
				moduleOpen();
				if (!moduleHandle) {
					throw std::logic_error("Failed to open module \"" + path + "\"");
				}
			}
			~Module() {
				if (moduleHandle) {
					moduleClose();
					moduleHandle = NULL;
				}
			}
		public:
			Module& operator=(Module const& r) {
				if (this == &r)
					return *this;
				moduleHandle = r.moduleHandle;
				path = r.path;
				return *this;
			}
		public:
			void* moduleSym(std::string const& symname);
	};
}

#endif
