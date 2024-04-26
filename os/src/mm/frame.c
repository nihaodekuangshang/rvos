
#include "include/frame.h"
#include "include/addr.h"
#include <stdint.h>
#include <stdio.h>
void __init_stack_frame(struct stack_frame_stuct* this,ppn_t l , ppn_t p)
{
	this->cur = l;
	this->end = p;
}
ppn_t __frame_alloc(struct stack_frame_stuct* sf)
{
	ppn_t t = sf->rec->pop(sf->rec);
	if (t != 0) {
		return t;
	}else {
		if (sf->cur == sf->end) {
			return 0;
		}else {
			sf->cur++;
			return sf->cur-1;
		}
	
	}
}
void __frame_dealloc(struct stack_frame_stuct* sf,ppn_t p)
{
	if (p >= sf->cur || sf->rec->find(sf->rec,p)) {
		panic("frame ppn %lx is not alloced",p);
		return;
	}
	sf->rec->push(sf->rec,p);
}
bool __find_in_frame_vec(struct frame_link_vec* fl,ppn_t p)
{
	for (uint64_t i = fl->cur; i < MAX_PAGE_NUM+fl->cur-1;i++) {
		uint64_t t = i % MAX_PAGE_NUM;
		if (fl->value[i] == p) {
			return true;
		}
	}
	return false;
}

ppn_t __pop_in_frame(struct frame_link_vec* fl)
{

  if (fl->cur == 0){
    panic("[ERROR] no rec page");
  }
  ppn_t t = fl->value[--fl->cur];
  return t;
}
void __push_in_frame(struct frame_link_vec* fl,ppn_t p)
{
  if (fl->cur >= MAX_PAGE_NUM){
    panic("[ERROR] more rec page");
  }
  fl->value[fl->cur] = p;
  fl->cur++;
}
void init_frame()
{
	fvec.cur = 0;
	fvec.end = MAX_PAGE_NUM;
	for (int i = 0; i < MAX_PAGE_NUM;i++) {
		fvec.value[i] = 0;
	}
	fvec.find = &__find_in_frame_vec;
	fvec.pop = &__pop_in_frame;
	fvec.push = &__push_in_frame;
	stack_frame.cur = 0;
	stack_frame.end = 0;
	stack_frame.rec = &fvec;
	stack_frame.init = &__init_stack_frame;
	stack_frame.alloc = &__frame_alloc;
	stack_frame.dealloc = &__frame_dealloc;


	stack_frame.init(&stack_frame,page_up((uint64_t)ekernel),page_down(MEM_END));
}
ppn_t frame_alloc()
{
  ppn_t p = stack_frame.alloc(&stack_frame);
  //TODO
  return p;
}
void frame_dealloc(ppn_t p)
{
  stack_frame.dealloc(&stack_frame,p);
}
