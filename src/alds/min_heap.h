//////////////////////////////////////////////////////////////////////////
//
// Copyright(C)	2016, gjm_kevin.  All rights reserved.
// Author	:	gjm_kevin@163.com
//
//////////////////////////////////////////////////////////////////////////

#ifndef CALM_ALDS_MINHEAP_H_
#define CALM_ALDS_MINHEAP_H_

// Á¬ÐøÄÚ´æ´æ´¢


#include <malloc.h>

#define GET_LEFT_CHILD(i)   ((i<<1)+1)
#define GET_RIGHT_CHILD(i)  ((i<<1)+2)
#define GET_PARENT(i) ((i-1)>>1)

typedef struct min_heap
{
	void** value;
	unsigned size;   // num of heap
	unsigned capacity; 
	int(*compare_func)(void*, void*);
} min_heap_t;

typedef int(*comp_func)(void*, void*);

static inline void	min_heap_ctor(min_heap_t* s, comp_func func);
static inline void	min_heap_dtor(min_heap_t* s);
static inline int	min_heap_push(min_heap_t* s, void* ele);
static inline int	min_heap_reserve(min_heap_t* s, unsigned n);
static inline void	min_heap_shift_up_(min_heap_t* s, unsigned hole_index, void* e);

int compare_int_keys(register void* key1, register void* key2) {
	// Cast them as int* and read them in
	register int key1_v = *((int*)key1);
	register int key2_v = *((int*)key2);
	// Perform the comparison
	if (key1_v < key2_v)
		return -1;
	else if (key1_v == key2_v)
		return 0;
	else
		return 1;
}


int min_heap_elem_greater(min_heap_t *s,void *lhs, void *rhs)
{
	return s->compare_func(lhs,rhs) == 1;
}

void min_heap_ctor(min_heap_t* s, comp_func func) 
{ 
	s->value = 0;
	s->size = 0;
	s->capacity = 0;
	if (func == NULL)
		s->compare_func = compare_int_keys;
}

void min_heap_dtor(min_heap_t* s) { if (s->value) free(s->value); }

int min_heap_push(min_heap_t* s, void* ele)
{
	if (min_heap_reserve(s, s->size + 1))
		return -1;
	min_heap_shift_up_(s, s->size++, ele);
	return 0;
}
int	min_heap_reserve(min_heap_t* s, unsigned n)
{
	if (s->capacity < n)
	{
		void ** p;
		unsigned capacity = s->capacity ? s->capacity * 2 : 8;
		if (capacity < n)
			capacity = n;
		if (!(p = (void**)realloc(s->value, capacity * sizeof(p))))
			return -1;
		s->value = p;
		s->capacity = capacity;
	}
	return 0;
}

void min_heap_shift_up_(min_heap_t* s, unsigned hole_index, void* e)
{
	//unsigned parent = (hole_index - 1) / 2;
	unsigned parent =GET_PARENT(hole_index);
	while (hole_index && min_heap_elem_greater(s,s->value[parent], e))
	{
		(s->p[hole_index] = s->p[parent])->ev_timeout_pos.min_heap_idx = hole_index;
		hole_index = parent;
		parent = (hole_index - 1) / 2;
	}
	(s->p[hole_index] = e)->ev_timeout_pos.min_heap_idx = hole_index;
}

#endif //CALM_ALDS_MINHEAP_H_

