#ifndef __KALLOC_RVOS_H
#define __KALLOC_RVOS_H 1
#include "addr.h"
#define MEM_END 0x80800000
#define page_up(a) ((a+PAGE_SIZE-1)&~(PAGE_SIZE-1))
#define page_down(a) ((a)&~(PAGE_SIZE-1))
struct free_mem_list{
	struct free_mem_list* next;
};
//内核内存管理
struct{
	struct free_mem_list* flist;
}kel_mem_man;
void init_kel_mem();
void* kalloc();
void kfree(void* p);
#endif
