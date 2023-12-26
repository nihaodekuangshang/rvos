#![no_std]
#![no_main]
#![feature(format_args_nl)]
#![feature(panic_info_message)]
#[macro_use]
mod io;
#[macro_use]
mod log;
mod panic;
mod sbi;
use core::arch::global_asm;
use core::env;

global_asm!(include_str!("entry.s"));

#[no_mangle]
fn main() {
    clear_bss();
    let log_grad = option_env!("LOG").unwrap_or("INFO");
    println!("{:?}", log::max_level());
    println!("{:?}", log::STATIC_MAX_LEVEL);
    println!("{:?}", log::Level::Error > log::Level::Warn);
    println!("{:?}", log::Level::Info < log::Level::Warn);
    info!("This is Info");
    error!("This is Error");
    warn!("This is Warn");
    debug!("This is debug");
    trace!("This is trance");
    panic!("shutdown err");
    loop {}
}
fn clear_bss() {
    extern "C" {
        fn sbss();
        fn ebss();
    }
    (sbss as usize..ebss as usize).for_each(|mem| unsafe {
        (mem as *mut u8).write_volatile(0);
    })
}
