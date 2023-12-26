use core::arch::asm;

//错误码
pub const SBISUCCESS: isize = 0; //顺利完成
pub const SBIERRFAILED: isize = -1; //失败
pub const SBIERRNOTSUPPORTED: isize = -2; //不支持操作
pub const SBIERRINVALIDPARAM: isize = -3; //非法参数
pub const SBIERRDENIED: isize = -4; //拒绝
pub const SBIERRINVALIDADDRESS: isize = -5; //非法地址
pub const SBIERRALREADYAVAILABLE: isize = -6; //（资源）已可用
pub const SBIERRALREADYSTARTED: isize = -7; //（操作）已启动
pub const SBIERRALREADYSHOPPED: isize = -8; //（操作）已停止
pub const SBIERRNOSHMEM: isize = -9; //共享内存不可用

//EID
pub const BASICEXTEND: usize = 0x10; //基本扩展
pub const DEBUGCONSOL: usize = 0x4442434E; // 调试控制台扩展
pub const SYSTEMRESET: usize = 0x53525354; //系统复位扩展 SRST
pub enum BasicFID {
    GetSpecVersion = 0,
    GetImplId = 1,
    GetImplVersion = 2,
    ProbeExtension = 3, //探测 SBI 扩展功能
    //如果给定的 SBI 扩展 ID (EID) 不可用，则返回
    //0；如果可用，返回值应为 1，或为特定 SBI 实现定义的其他非 0 值。
    GetMvendorid = 4, //获取机器供应商标识符
    GetMarchid = 5,   //获取机器体系结构标识符
    GetMimpid = 6,    //获取机器实现标识符 ID
}
pub enum DebugConsoleFID {
    //struct sbiret sbi_debug_console_write(unsigned long num_bytes,   unsigned long base_addr_lo,   unsigned long base_addr_hi)
    DebugConsoleWrite = 0,
    //struct sbiret sbi_debug_console_read(unsigned long num_bytes,   unsigned long base_addr_lo,   unsigned long base_addr_hi
    DebugConsoleRead = 1,
    //struct sbiret sbi_debug_console_write_byte(uint8_t byte)
    DebugConsoleWriteByte = 2,
}
pub enum SRSTFID {
    SystemReset = 0,
}
pub enum ResetType {
    Shutdown = 0,
    ColdBoot = 1,
    HotBoot = 2,
}
pub enum ResetReason {
    NoReason = 0,
    SystemErr = 1,
}
pub fn ecall(eid: usize, fid: usize, arg0: usize, arg1: usize, arg2: usize) -> (usize, usize) {
    let mut ret: usize;
    let mut code: usize;
    unsafe {
        asm!(
            "ecall",
            inlateout("a0") arg0 => code,
            inlateout("a1") arg1 => ret,
            in("a2") arg2,
            in("a6") fid,
            in("a7") eid,
        );
    }
    (code, ret)
}
pub fn shutdown() -> ! {
    ecall(
        SYSTEMRESET,
        SRSTFID::SystemReset as usize,
        ResetType::Shutdown as usize,
        ResetReason::NoReason as usize,
        0,
    );
    loop {}
}
pub fn shutdown_err() -> ! {
    ecall(
        SYSTEMRESET,
        SRSTFID::SystemReset as usize,
        ResetType::Shutdown as usize,
        ResetReason::SystemErr as usize,
        0,
    );
    loop {}
}
