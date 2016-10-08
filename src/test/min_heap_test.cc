#include <iostream>
#include "min_heap.h"

int main()
{
	int *inserted[1024];
	struct min_heap heap;
	min_heap_ctor(&heap,NULL);
	for (int i = 1023; i >= 0 ; --i) {
		inserted[i] = (int *)malloc(sizeof(int));
		*inserted[i] = i;
		min_heap_push(&heap, inserted[i]);
	}
	while (true)
	{
		int* p = (int *)min_heap_pop(&heap);
		if(!p)
			break;
		printf("%d,", *p);
	}
	for (int i = 0; i < 1024; ++i)
		free(inserted[i]);
	min_heap_dtor(&heap);
	std::cin.get();
	return 0;
}