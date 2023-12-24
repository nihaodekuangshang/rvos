use core::panic::PanicInfo;
#[panic_handler]
fn panic_handler(_pa: &PanicInfo) -> ! {
    loop {}
}
