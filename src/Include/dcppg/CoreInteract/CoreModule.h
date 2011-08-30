#ifndef DCPPG_CORE_INTERACT_MODULE_H
#define DCPPG_CORE_INTERACT_MODULE_H

#include <dcppg/Data/ModuleInfo.h>
#include <map>

class CoreModule {
	public:
		virtual ~CoreModule() {}
	public:
		virtual ModuleInfo const& getInfo() const = 0;
		virtual void load() = 0;
		virtual void reload() = 0;
		virtual void unload() = 0;
};

template <class K,class V>
class constMap {
	private:
		std::map<K,V> data;
	public:
		typedef typename std::map<K,V>::iterator iterator;
		typedef typename std::map<K,V>::const_iterator const_iterator;
	public:

		V const& operator[](K const& key) const {
			return data.find(key)->second;
		}
		V const& operator[](void const* key) const {
			return data.find(K(key))->second;
		}
		V const& operator[](char const* key) const {
			return data.find(K(key))->second;
		}

		
		V & operator[](K const& key) {
			return data[key];
		}
		V & operator[](void const* key) {
			return data[K(key)];
		}
		V & operator[](char const* key) {
			return data[K(key)];
		}
	public:
		
		iterator begin() {
			return data.begin();
		}
		const_iterator begin() const {
			return data.begin();
		}
		iterator end() {
			return data.end();
		}
		const_iterator end() const {
			return data.end();
		}
};

typedef constMap<std::string,CoreModule*> modulemap;
typedef constMap<std::string,modulemap> modulemapmap;


#endif
