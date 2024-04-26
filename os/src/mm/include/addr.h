#ifndef __ADDR_RVOS_H
#define __ADDR_RVOS_H 1
#include <stddef.h>
#define PA_WIDTH_SV39 56
#define PAGE_SIZE_BITS 12
#define PAGE_SIZE 4096
#define PPN_WIDTH_SV39 ((PA_WIDTH_SV39) - (PAGE_SIZE_BITS))

/*
 * 标志位
 *   
 */
#define PTE_V (1L << 0)     // valid
#define PTE_R (1L << 1)
#define PTE_W (1L << 2)
#define PTE_X (1L << 3)
#define PTE_U (1L << 4)     // 1 -> user can access
#define PTE_G (1L << 5)     
#define PTE_A (1L << 6)     // 处理器记录自从页表项上的这一位被清零之后，页表项的对应虚拟页面是否被访问过
#define PTE_D (1L << 7)     // 处理器记录自从页表项上的这一位被清零之后，页表项的对应虚拟页面是否被修改过


//PhysAddr
typedef usize pa_t ;
//VirtAddr
typedef usize va_t ;
//PhysPageNum
typedef usize ppn_t ;
//VirtPageNum
typedef usize vpn_t ;
//PageTableEntry
typedef usize pte_t ;



//从usize转化成pa_t
#define pa_fromu(v) (v & ( (1 << PA_WIDTH_SV39) - 1 )) 
//从usize转化成ppn_t
#define ppn_fromu(v) (v & ( (1 << PPN_WIDTH_SV39) - 1 ))
//从pa转化成ppn_t,失败返回-1
#define ppn_from_pa(v) ((v&(PAGE_SIZE-1))==0?(-1):(__add_floor(v)))
//从ppn转化成pa
#define pa_from_ppn(v) (v<<PAGE_SIZE_BITS)

//p PhysPageNum ; f : page_flag
#define pte_from_ppn(p,f)  ((p<<10)|f)
#define ppn_from_pte(p)    ((p>>10)&((1<<44)-1))


//down page number
#define  __add_floor(v) (v / PAGE_SIZE)
//up page number
#define  __add_ceil(v)  (v==0?0:((v-1+PAGE_SIZE)/PAGE_SIZE))
#endif
