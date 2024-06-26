#include "include/kalloc.h"
#include "include/addr.h"
#include <stddef.h>
void ekernel();
void* kalloc()
{
	struct free_mem_list* t = kel_mem_man.flist;
	kel_mem_man.flist = t->next;
	return (void*)t;
}
void kfree(void* p)
{
	struct free_mem_list* t = p;
	t->next = kel_mem_man.flist;
	kel_mem_man.flist = t;
	return;
}

void free_mem(void* a,void* e)
{
	uint8_t *p = (uint8_t*)page_up((uint64_t)a);
	for (; p + PAGE_SIZE < (uint8_t*)e; p + PAGE_SIZE) {
		kfree(p);
	}
}
void init_kel_mem()
{
	free_mem(ekernel,(void*)MEM_END);
}
