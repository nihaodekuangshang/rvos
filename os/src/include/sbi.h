#ifndef __SBI_RVOS__HEADER__
#define __SBI_RVOS__HEADER__
extern const long SBISUCCESS; //顺利完成
extern const long SBIERRFAILED; //失败
extern const long SBIERRNOTSUPPORTED; //不支持操作
extern const long SBIERRINVALIDPARAM; //非法参数
extern const long SBIERRDENIED; //拒绝
extern const long SBIERRINVALIDADDRESS; //非法地址
extern const long SBIERRALREADYAVAILABLE; //（资源）已可用
extern const long SBIERRALREADYSTARTED; //（操作）已启动
extern const long SBIERRALREADYSHOPPED; //（操作）已停止
extern const long SBIERRNOSHMEM; //共享内存不可用
extern const unsigned long BASICEXTEND; //基本扩展
extern const unsigned long DEBUGCONSOL; // 调试控制台扩展
extern const unsigned long SYSTEMRESET; //系统复位扩展 SRST
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

struct Sbiret ecall(
		unsigned long eid, 
		unsigned long fid, 
		unsigned long arg0, 
		unsigned long arg1, 
		unsigned long arg2);
void shutdown();
void shutdown_err();

#endif
