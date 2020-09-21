

#include <common.h>
// safe alloc and malloc

void *safeMalloc(size_t _Size){
	void *ret = malloc(_Size);
	if(ret == NULL){
		fprintf(stderr, "[INTERNAL] Fatal error - cannot allocate memory\n");
		exit(99);
	}
	return ret;
}


void *safeRealloc(void *_Block, size_t _Size){
	void *ret = realloc(_Block, _Size);
	if(ret == NULL){
		fprintf(stderr, "[INTERNAL] Fatal error - cannot allocate memory\n");
		exit(99);
	}
	return ret;
}
