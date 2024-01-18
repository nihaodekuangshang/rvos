#include "sbi.h"
const long SBISUCCESS = 0; //顺利完成
const long SBIERRFAILED = -1; //失败
const long SBIERRNOTSUPPORTED = -2; //不支持操作
const long SBIERRINVALIDPARAM = -3; //非法参数
const long SBIERRDENIED = -4; //拒绝
const long SBIERRINVALIDADDRESS = -5; //非法地址
const long SBIERRALREADYAVAILABLE = -6; //（资源）已可用
const long SBIERRALREADYSTARTED = -7; //（操作）已启动
const long SBIERRALREADYSHOPPED = -8; //（操作）已停止
const long SBIERRNOSHMEM = -9; //共享内存不可用
const unsigned long BASICEXTEND = 0x10; //基本扩展
const unsigned long DEBUGCONSOL = 0x4442434E; // 调试控制台扩展
const unsigned long SYSTEMRESET = 0x53525354; //系统复位扩展 SRST
struct Sbiret ecall(
		unsigned long eid, 
		unsigned long fid, 
		unsigned long arg0, 
		unsigned long arg1, 
		unsigned long arg2) {
	register unsigned long a0 __asm__("a0") = arg0;
	register unsigned long a1 __asm__("a1") = arg1;
	register unsigned long a2 __asm__("a2") = arg2;
	register unsigned long a6 __asm__("a6") = fid;
	register unsigned long a7 __asm__("a7") = eid;
        __asm__ __volatile__(
            "ecall"
			:"+r"(a0),"+r"(a1)
			:"r"(a2),"r"(a6),"r"(a7)
			:"cc"
        );
		struct Sbiret  ecr = {a0,a1};
		return ecr;
}
void shutdown()  {

	enum SRSTFID SRST = SystemReset;
	enum ResetReason Reason = NoReason;
	enum ResetType Type = Shutdown;
    ecall(
        SYSTEMRESET,
		SRST,
		Reason,
		Type,
        0
    );
	while (1){}
}
void shutdown_err(){
	enum SRSTFID SRST = SystemReset;
	enum ResetReason Reason = SystemErr;
	enum ResetType Type = Shutdown;
    ecall(
        SYSTEMRESET,
		SRST,
		Type,
        Reason,
        0
    );
	while (1){}
}
