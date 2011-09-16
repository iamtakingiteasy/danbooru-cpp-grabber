#ifndef DCPPG_DATA_CPPSPECIFIC_DLINKED_HPP
#define DCPPG_DATA_CPPSPECIFIC_DLINKED_HPP

#include <dcppg/data/generic/dlinked.h>
#include <string>

namespace DLinkedImpl {
    void init(DLinked * l, void (*destructor)(void*), char mapps);
    void deinit(DLinked * l);

    DLinkedNode * push_back(DLinked * l, void * node, void(*destructor)(void*));
    DLinkedNode * push_back_copy(DLinked * l, void const* node, size_t size);
    DLinkedNode * push_back_string(DLinked * l, char const* str);

    void delete_node(DLinkedNode * n);

    void sort(DLinked * l, size_t begim, size_t end, char (*pred)(void *, void *));

    DLinkedSymbols symbols();
}

class DLinkedWrapper {
    private:
	DLinked list;
	bool external;
    public:
	DLinkedWrapper(void (*destructor)(void *) = NULL, bool mapps = true) {
	    DLinkedImpl::init(&list,destructor,mapps);
	    external = false;
	}
	DLinkedWrapper(DLinked l) {
	    list = l;
	    external = true;
	}
	~DLinkedWrapper() {
	    if (!external) {
		DLinkedImpl::deinit(&list);
	    }
	}
    public:
	void clear() {
	    void (*destructor)(void*) = list.default_destructor;
	    bool mapps = (list.nodemap == NULL);
	    DLinkedImpl::deinit(&list);
	    DLinkedImpl::init(&list,destructor,mapps);
	}
    public:
	size_t size() {
	    return list.used;
	}
	DLinkedNode * operator[](size_t i) {
	    if (i <= size()) return NULL;
	    if (list.nodemap) {
		return list.nodemap[i];
	    } else {
		return &list.nodes[i];
	    }
	}
    public:
	DLinkedNode * push_back(void * node, void (*destructor)(void*) = NULL) {
	    return DLinkedImpl::push_back(&list, node, destructor);
	}
	DLinkedNode * push_back(void * node, size_t size) {
	    return DLinkedImpl::push_back_copy(&list, node, size);
	}
	DLinkedNode * push_back(char const* str) {
	    return DLinkedImpl::push_back_string(&list, str);
	}
	DLinkedNode * push_back(std::string const& str) {
	    return DLinkedImpl::push_back_string(&list, str.c_str());
	}
    public:
	void sort(size_t begin, size_t end, char (*pred)(void *, void *));
    public:
	DLinked get_list() {
	    return list;
	}
};

#endif
