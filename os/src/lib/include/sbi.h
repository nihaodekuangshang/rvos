#ifndef __SBI_RVOS__HEADER__
#define __SBI_RVOS__HEADER__

#define SBISUCCESS  0 //顺利完成
#define SBIERRFAILED  -1 //失败
#define SBIERRNOTSUPPORTED  -2 //不支持操作
#define SBIERRINVALIDPARAM  -3 //非法参数
#define SBIERRDENIED  -4 //拒绝
#define SBIERRINVALIDADDRESS  -5 //非法地址
#define SBIERRALREADYAVAILABLE  -6 //（资源）已可用
#define SBIERRALREADYSTARTED  -7 //（操作）已启动
#define SBIERRALREADYSHOPPED  -8 //（操作）已停止
#define SBIERRNOSHMEM  -9 //共享内存不可用
#define BASICEXTEND  0x10 //基本扩展
#define DEBUGCONSOL  0x4442434E // 调试控制台扩展
#define SYSTEMRESET  0x53525354 //系统复位扩展 SRST
				//
enum BasicFID {
    GetSpecVersion = 0,
    GetImplId = 1,
    GetImplVersion = 2,
    ProbeExtension = 3, //探测 SBI 扩展功能
    //如果给定的 SBI 扩展 ID (EID) 不可用，则返回
    //0；如果可用，返回值应为 1，或为特定 SBI 实现定义的其他非 0 值。
    GetMvendorid = 4, //获取机器供应商标识符
    GetMarchid = 5,   //获取机器体系结构标识符
    GetMimpid = 6,    //获取机器实现标识符 ID
};
enum DebugConsoleFID {
    //struct sbiret sbi_debug_console_write(unsigned long num_bytes,   unsigned long base_addr_lo,   unsigned long base_addr_hi)
    DebugConsoleWrite = 0,
    //struct sbiret sbi_debug_console_read(unsigned long num_bytes,   unsigned long base_addr_lo,   unsigned long base_addr_hi
    DebugConsoleRead = 1,
    //struct sbiret sbi_debug_console_write_byte(uint8_t byte)
    DebugConsoleWriteByte = 2,
};
enum SRSTFID {
    SystemReset = 0,
};
enum ResetType {
    Shutdown = 0,
    ColdBoot = 1,
    HotBoot = 2,
};
enum ResetReason {
    NoReason = 0,
    SystemErr = 1,
};
struct Sbiret
{
	long error;
	long value;
};

struct Sbiret ecall( unsigned long eid, unsigned long fid, 
		unsigned long arg0, unsigned long arg1, 
		unsigned long arg2);
void shutdown();
void shutdown_err();

#endif
