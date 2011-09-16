#include <dcppg/data/cppspecific/dlinked.hpp>
#include <string.h>

void rebuild(DLinked * l) {
    size_t i;
    DLinkedNode * n;
    for (i = 0; i < l->used; i++) {
        n = &l->nodes[i];
        if (n->prev) {
            n->prev = &l->nodes[n->prev_index];
        }
        if (n->next) {
            n->next = &l->nodes[n->next_index];
        }
    }
    l->first = &l->nodes[l->first_index];
    l->last  = &l->nodes[l->last_index];
}
void rebuild_map(DLinked * l) {
    DLinkedNode * n;
    size_t index = 0;
    for (n = l->first; n != NULL; n = n->next) {
        l->nodemap[index++] = n;
    }
}

void DLinkedImpl::init(DLinked * l, void (*destructor)(void*), char mapps) {
    l->default_destructor = destructor;
    l->used  = 0;
    l->power = 1;
    l->nodes = (DLinkedNode*)calloc(l->power,sizeof(DLinkedNode));
    if (mapps) {
        l->nodemap = (DLinkedNode**)calloc(l->power,sizeof(DLinkedNode*));
    } else{
        l->nodemap = NULL;
    }
    l->first_index = 0;
    l->last_index  = 0;
    l->first = &l->nodes[l->first_index];
    l->last  = &l->nodes[l->last_index];
}

void DLinkedImpl::deinit(DLinked * l) {
    for (size_t index = 0; index < l->used; index++) {
        if (l->nodes[index].destructor) {
            l->nodes[index].destructor(l->nodes[index].data);
        }
    }
    if (l->nodes) {
	free(l->nodes);
    }
    l->used  = 0;
    l->power = 1;
    l->nodes = NULL;
    if (l->nodemap) {
        free(l->nodemap);
	l->nodemap = NULL;
    }
}

DLinkedNode * DLinkedImpl::push_back(DLinked * l
				     , void * node
				     , void (*destructor)(void*)) {
    DLinkedNode * n;
    DLinkedNode * maybe_ptr;
    DLinkedNode ** maybe_map_ptr;
    size_t projected = l->used + 1;
    if (projected > l->power) {
        while (projected > l->power) {
            l->power <<= 1;
        }
        maybe_ptr = (DLinkedNode*)realloc(l->nodes,sizeof(DLinkedNode) * l->power);
        if (!maybe_ptr) return NULL;
        l->nodes = maybe_ptr;
        memset(&l->nodes[l->used],0,sizeof(DLinkedNode) * (l->power - l->used));

        rebuild(l);

        if (l->nodemap) {
            maybe_map_ptr = (DLinkedNode**)realloc(l->nodemap
						   ,sizeof(DLinkedNode*) * l->power);
            if (!maybe_map_ptr) return NULL;
            l->nodemap = maybe_map_ptr;
            memset(&l->nodemap[l->used],0,sizeof(DLinkedNode*) * (l->power - l->used));
        }
    }
    n = l->last;

    while (n->next) {
        n = n->next;
    }

    if (n->data) {
        n->next_index = l->used;
        n->next = &l->nodes[l->used];
        n->next->prev_index = n->index;
        n->next->prev =  n;

        n = n->next;
    }

    n->next_index = 0;
    n->next = NULL;

    n->index = l->used;
    n->master = l;
    n->data = node;

    l->last_index = l->used;
    l->last = n;

    if (destructor) {
        n->destructor = destructor;
    } else {
        n->destructor = l->default_destructor;
    }

    l->used += 1;

    if (l->nodemap) {
        rebuild_map(l);
    }
    return n;
}

DLinkedNode * DLinkedImpl::push_back_copy(DLinked * l, void const* node, size_t size) {
    void * data = malloc(size);
    memmove(data,node,size);
    return push_back(l,data,free);
}
DLinkedNode * DLinkedImpl::push_back_string(DLinked * l, char const* str) {
    return push_back_copy(l,str,strlen(str)+1);
}

void DLinkedImpl::delete_node(DLinkedNode * n) {
    DLinked * l  = n->master;
    size_t index = n->index;
    DLinkedNode * last_ptr = NULL;

    l->used -= 1;

    if (n->destructor) {
        n->destructor(n->data);
    }

    last_ptr = &l->nodes[l->used];

    if (n->next && n->prev) {
        n->prev->next       = n->next;
        n->prev->next_index = n->next_index;

        n->next->prev       = n->prev;
        n->next->prev_index = n->prev_index;
    } else if (n->next || n->prev) {
        if (n->next) {
            n->next->prev  = NULL;
            l->first       = n->next;
            l->first_index = n->next_index;
        }
        if (n->prev) {
            n->prev->next = NULL;
            l->last       = n->prev;
            l->last_index = n->prev_index;
        }
    } else {
        l->last        = &l->nodes[0];
        l->last_index  = 0;
        l->first       = &l->nodes[0];
        l->first_index = 0;
    }

    if (l->last_index == l->used) {
        l->last       = n;
        l->last_index = index;
    }

    if (l->first_index == l->used) {
        l->first       = n;
        l->first_index = index;
    }

    if (index != l->used) {
        if (last_ptr->prev) {
            last_ptr->prev->next       = n;
            last_ptr->prev->next_index = index;
        }
        if (last_ptr->next) {
            last_ptr->next->prev       = n;
            last_ptr->next->prev_index = index;
        }
    }

    *n = *last_ptr;
    n->index = index;

    memset(last_ptr, 0, sizeof(DLinkedNode));

    l->first->prev       = NULL;
    l->first->prev_index = 0;

    l->last->next       = NULL;
    l->last->next_index = 0;

    if (l->nodemap) {
        rebuild_map(l);
    }
}

void swap(DLinkedNode * nodea, DLinkedNode * nodeb) {
    void * tmpdata = nodea->data;
    void (*tmpdestructor)(void *) = nodea->destructor;

    nodea->data       = nodeb->data;
    nodea->destructor = nodeb->destructor;
    nodeb->data       = tmpdata;
    nodeb->destructor = tmpdestructor;
}


void DLinkedImpl::sort(DLinked * l
		       , size_t begin
		       , size_t end
		       , char (*pred)(void *, void *)) {
    
    DLinkedNode * pivot;
    size_t left;
    size_t right;
    if (begin >= end) return;

    pivot = l->nodemap[begin];

    left  = begin;
    right = end;

    while (left < right) {
        while (pred(l->nodemap[left]->data,pivot->data) && left < end)
            left++;
        while (!pred(l->nodemap[right]->data,pivot->data) && right > begin)
            right--;
        if (left < right) {
            swap(l->nodemap[left],l->nodemap[right]);
        }
    }
    swap(l->nodemap[begin],l->nodemap[right]);
    if (right < end)
        sort(l, right + 1, end, pred);
    if (right > 0)
        sort(l, begin, right - 1, pred);
}

DLinkedSymbols DLinkedImpl::symbols() {
    DLinkedSymbols syms;
    syms.init           = init;
    syms.deinit         = deinit;
    syms.push_back      = push_back;
    syms.push_back_copy = push_back_copy;
    syms.sort           = sort;
    return syms;
}
