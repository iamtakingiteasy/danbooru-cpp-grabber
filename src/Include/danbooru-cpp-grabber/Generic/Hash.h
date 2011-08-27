#ifndef DANBOORU_CPP_GRABBER_GENERIC_HASH
#define DANBOORU_CPP_GRABBER_GENERIC_HASH

#include <string>
#include <map>

class HashNode {
	private:
		int valueInt;
		std::string valueString;
	public:
		HashNode() {
			valueInt = 0;
		}
		HashNode(int value) {
			valueInt = value;
		}
		HashNode(char const* value){
			valueString = value;
		}
		HashNode(std::string const& value){
			valueString = value;
		}
	public:
		HashNode & operator=(int value) {
			valueInt = value;
			return * this;
		}
		HashNode & operator=(char const* value) {
			valueString = value;
			return *this;
		}
		HashNode & operator=(std::string const& value) {
			valueString = value;
			return *this;
		}
	public:
		operator int() const {
			return valueInt;
		}
		operator std::string const& () const {
			return valueString;
		}
};


class Hash {
	private:
		std::map<std::string,HashNode> values;
	public:
		Hash() {}
	public:
		HashNode & operator[] (std::string const& name) {
			return values[name];
		}
};


#endif
