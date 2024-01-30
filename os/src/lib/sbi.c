#include "sbi.h"
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
