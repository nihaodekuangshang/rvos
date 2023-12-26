use crate::sbi;
use core::fmt::{self, Write};
use core::format_args_nl;

struct Stdout;
impl Write for Stdout {
    fn write_str(&mut self, s: &str) -> fmt::Result {
        _print_str(s);
        Ok(())
    }
}
fn _print_c(c: char) {
    sbi::ecall(
        sbi::DEBUGCONSOL,
        sbi::DebugConsoleFID::DebugConsoleWriteByte as usize,
        c as usize,
        0,
        0,
    );
}
fn _print_str(str: &str) {
    let addr_lb = str.as_ptr() as usize;
    sbi::ecall(
        sbi::DEBUGCONSOL,
        sbi::DebugConsoleFID::DebugConsoleWrite as usize,
        str.len(),
        addr_lb,
        0,
    );
}
pub fn _print(arg: fmt::Arguments) {
    Stdout.write_fmt(arg);
}
#[macro_export]
macro_rules! print {
    ($($arg:tt)*) => {{
        $crate::io::_print(format_args!($($arg)*));
    }};
}
#[macro_export]
macro_rules! println {
    () => {
        $crate::io::print!("\n")
    };
    ($($arg:tt)*) => {{
        $crate::io::_print(format_args_nl!($($arg)*));
    }};
}
