#ifndef DCPPG_DATA_HASH_H
#define DCPPG_DATA_HASH_H

#include <string>
#include <vector>
#include <map>

template <class T>
class Hash {
	public:
		enum {
			HASH_EMPTY   = 1<<0,
			HASH_INTEGER = 1<<1,
			HASH_TEXTUAL = 1<<2,
//			HASH_VOID    = 1<<3,
			HASH_VECTOR  = 1<<3,
			HASH_MAP     = 1<<4
		};
	private:
		int               type;
		int               integer;
//		void      *       ptr;
		std::string       textual;
		std::vector<Hash> vectorData;
		std::map<T, Hash> mapData;
	public:
		typedef typename std::map<T,Hash>::iterator map_iterator;
		typedef typename std::map<T,Hash>::const_iterator map_const_iterator;
		typedef typename std::vector<Hash>::iterator vector_iterator;
		typedef typename std::vector<Hash>::const_iterator vector_const_iterator;
	public:
		int getType() const {
			return type;
		}
	public:
		Hash() {
			integer = 0;
			type = HASH_EMPTY;
		}
		Hash(int value) {
			integer = value;
			type |= HASH_INTEGER;
		}
	
		Hash(char const* value) {
			textual = value;
			type |= HASH_TEXTUAL;
		}
//		Hash(void * value) {
//			ptr = value;
//			type |= HASH_VOID;
//		}	
		Hash(std::string const& value) {
			textual = value;
			type |= HASH_TEXTUAL;
		}	
	public:
		Hash & operator=(int value) {
			integer = value;
			type |= HASH_INTEGER;
			return *this;
		}
		Hash & operator=(char const* value) {
			textual = value;
			type |= HASH_TEXTUAL;
			return *this;
		}
//		Hash & operator=(void * value) {
//			ptr = value;
//			type |= HASH_VOID;
//			return *this;
//		}	
		Hash & operator=(std::string const& value) {
			textual = value;
			type |= HASH_TEXTUAL;
			return *this;
		}	
	public:
		void push_back(int value) {
			type |= HASH_VECTOR;
			vectorData.push_back(Hash(value));
		}
		void push_back(char const* value) {
			type |= HASH_VECTOR;
			vectorData.push_back(Hash(value));
		}
//		void push_back(void * value) {
//			type |= HASH_VOID;
//			vectorData.push_back(Hash(value));
//		}
		void push_back(std::string const& value) {
			type |= HASH_VECTOR;
			vectorData.push_back(Hash(value));
		}
	public:
	
//		Hash const& operator[](int index) const {
//			return vectorData[index];
//		}
		Hash const& operator[](char const* name) const {
			return mapData.find(T(name))->second;
		}
//		Hash const& operator[](void const* name) const {
//			return mapData.find(T(name))->second;
//		}
		Hash const& operator[](T const& name) const {
			return mapData.find(name)->second;
		}

//		Hash & operator[](int index) {
//			return vectorData[index];
//		}
		Hash & operator[](char const* name) {
			type |= HASH_MAP;
			return mapData[T(name)];
		}
//		Hash & operator[](void const* name) {
//			type |= HASH_MAP;
//			return mapData[T(name)];
//		}
		Hash & operator[](T const& name) {
			type |= HASH_MAP;
			return mapData[name];
		}
	public:
		operator int() const {
			return integer;
		}
		operator std::string () const {
			return textual;
		}
		operator std::vector<Hash> () const {
			return vectorData;
		}
//		operator void *() const {
//			return ptr;
//		}
		operator std::map<T,Hash> () const {
			return mapData;
		}
	public:
		map_iterator beginMap() {
			return mapData.begin();
		}
		map_const_iterator beginMap() const {
			return mapData.begin();
		}
		map_iterator endMap() {
			return mapData.end();
		}
		map_const_iterator endMap() const {
			return mapData.end();
		}
	public:
		vector_iterator beginVector() {
			return vectorData.begin();
		}
		vector_const_iterator beginVector() const {
			return vectorData.begin();
		}
		vector_iterator endVector() {
			return vectorData.end();
		}
		vector_const_iterator endVector() const {
			return vectorData.end();
		}
};

#endif
