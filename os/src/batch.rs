#![no_std]
#![feature(c_variadic)]
use core::ffi::{c_char, c_int, CStr, VaList};

#[link(name = "k", kind = "static")]
extern "C" {
    fn printf(fmt: *const c_char, ...) -> c_int;
    fn putchar(c: c_int) -> c_int;
    fn puts(s: *const c_char) -> c_int;
    fn sprintf(buf: *mut c_char, fmt: *const c_char, ...) -> c_int;
    fn vsprintf(buf: *mut c_char, fmt: *const c_char, args: VaList) -> c_int;
}
#[link(name = "lang_item", kind = "static")]
extern crate lang_item;
pub const USER_STACK_SIZE: usize = 4096 * 2;
pub const KERNEL_STACK_SIZE: usize = 4096 * 2;
pub const MAX_APP_NUM: usize = 16;
pub const APP_BASE_ADDRESS: usize = 0x80400000;
pub const APP_SIZE_LIMIT: usize = 0x20000;

extern "C" fn test_c() -> () {}
#[repr(C)]
pub struct AppManager {
    num: usize,
    cur: usize,
    ads: [usize; MAX_APP_NUM + 1],
}
impl AppManager {
    #[no_mangle]
    pub extern "C" fn new() -> Self {
        AppManager {
            num: 0,
            cur: 0,
            ads: [0; MAX_APP_NUM + 1],
        }
    }
}
#[repr(align(4096))]
pub struct KernelStack {
    data: [u8; KERNEL_STACK_SIZE],
}
impl KernelStack {
    #[no_mangle]
    pub extern "C" fn get_kl_sp(&self) -> usize {
        self.data.as_ptr() as usize + KERNEL_STACK_SIZE
    }
}
#[repr(align(4096))]
pub struct UserStack {
    data: [u8; USER_STACK_SIZE],
}
impl UserStack {
    #[no_mangle]
    pub extern "C" fn get_us_sp(&self) -> usize {
        self.data.as_ptr() as usize + USER_STACK_SIZE
    }
}
#[no_mangle]
pub static mut APP_MAN: AppManager = AppManager {
    num: 0,
    cur: 0,
    ads: [0; MAX_APP_NUM + 1],
};

#[no_mangle]
pub static KERNEL_STACK: KernelStack = KernelStack {
    data: [0; KERNEL_STACK_SIZE],
};
#[no_mangle]
pub static USER_STACK: UserStack = UserStack {
    data: [0; USER_STACK_SIZE],
};
#[no_mangle]
pub extern "C" fn init_app_man() {
    extern "C" {
        fn _num_app();
    }
    unsafe {
        printf(CStr::from_bytes_with_nul(b"start ok \n").unwrap().as_ptr());
    }
    unsafe {
        let num_app_ptr = _num_app as usize as *const usize;
        let num = num_app_ptr.read_volatile();
        let cur: usize = 0;
        let addr = core::slice::from_raw_parts(num_app_ptr.add(1), num + 1);
        let mut ads: [usize; MAX_APP_NUM + 1] = [0; MAX_APP_NUM + 1];
        ads[..=num].copy_from_slice(addr);
        let am = AppManager {
            num: num,
            cur: cur,
            ads: ads,
        };
        APP_MAN = am;
    }
}
