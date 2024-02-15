
#include "include/task.h"
#include "include/taskContext.h"
#include "include/switch.h"
#include "loader.h"
#include <stdio.h>

struct task_manager task_man;

void init_task()
{
	task_man.num = get_num_app();
	task_man.cur = 0;
	for(int8_t i = 0; i<=12;++i){
		zero_init(&task_man.tasks[i].cont);
		task_man.tasks[i].status = task_unInit;
	}
	for(int8_t i = 0; i<=12;++i){
		goto_restore(&task_man.tasks[i].cont,init_app_ct(i));
		task_man.tasks[i].status = task_ready;
	}
}
void mark_sus(struct task_manager *tm)
{
	tm->tasks[tm->cur].status = task_ready;
	//printf("mark sus  cur : %lx,Status:%lx\n",tm->cur,tm->tasks[tm->cur].status);
}
void mark_exit(struct task_manager *tm)
{
	tm->tasks[tm->cur].status = task_exited;
}
uint64_t  find_next_task(struct task_manager *tm) 
{


	usize cur = tm->cur;
	uint64_t num = tm->num;
	for (uint64_t i = cur + 1; i<= tm->num + 1 + cur ; ++i){
		uint64_t id= i%num;
		if(tm->tasks[id].status == task_ready)
		{
			return id;
		}
	}
	return tm->num;
}
void  run_next_task(struct task_manager *tm)
{
	uint64_t ne = find_next_task(tm);
	//for (int i =0 ; i < tm->num;++i){
		//printf("cur:%lx , i: %lx , status: %lx\n",tm->cur,i,tm->tasks[i].status);
	//}
	//printf("ne: %lx,Status:%lx\n",ne,tm->tasks[ne].status);
	//printf("ne ra : %lx,\n",tm->tasks[ne].cont.ra);
	if(ne >=0 && ne <tm->num){
		usize cur = tm->cur;
		tm->tasks[ne].status = task_running;
		tm->cur = ne;
		__switch(&tm->tasks[cur].cont,&tm->tasks[ne].cont);
	} else {
		 panic("All applications completed!");
        }

}



//暂停当前进程
void suspend_task(struct task_manager *tm)
{
	mark_sus(tm);
	run_next_task(tm);
}
void exit_task(struct task_manager *tm)
{
	mark_exit(tm);
	run_next_task(tm);
}
void  run_first_task(struct task_manager *tm)
{


	struct task_control_block *t0 =  &tm->tasks[0];
	t0->status = task_running;
	struct task_context *tc = &t0->cont;
	struct task_context tmp;
	zero_init(&tmp);
	__switch(&tmp,tc);
	panic("unreachable in run_first_task!");

}
