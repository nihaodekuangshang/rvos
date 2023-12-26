use core::file;
use core::fmt;
use core::line;
use core::module_path;
use core::stringify;

pub fn log(
    args: fmt::Arguments,
    level: Level,
    &(target, module_path, file): &(&str, &'static str, &'static str),
    line: u32,
) {
    match level {
        Level::Info => println!("\x1b[36m[Info][0] {}\x1b[0m", args),
        Level::Warn => println!("\x1b[33m[Warn][0] {}\x1b[0m", args),
        Level::Error => println!("\x1b[31m[Error][0] {}\x1b[0m", args),
        Level::Debug => println!("\x1b[32m[Debug][0] {}\x1b[0m", args),
        Level::Trace => println!("\x1b[34m[Trace][0] {}\x1b[0m", args),
        _ => println!("\x1b[34m{}\x1b[0m", args),
    }
}

pub const STATIC_MAX_LEVEL: Level = Level::Trace;
#[repr(usize)]
#[derive(Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Debug, Hash)]
pub enum Level {
    Error = 1,
    Warn,
    Info,
    Debug,
    Trace,
}
pub fn max_level() -> Level {
    let log_grad = option_env!("LOG").unwrap_or("INFO");
    match log_grad {
        "INFO" => return Level::Info,
        "WARN" => return Level::Warn,
        "ERROR" => return Level::Error,
        "TRACE" => return Level::Trace,
        "DEBUG" => return Level::Debug,
        _ => return Level::Info,
    }
}
#[macro_export]
macro_rules! info {
    // info!(target: "my_target", key1 = 42, key2 = true; "a {} event", "log")
    // info!(target: "my_target", "a {} event", "log")
    (target: $target:expr, $($arg:tt)+) => ($crate::log::log!(target: $target, $crate::log::Level::Info, $($arg)+));

    // info!("a {} event", "log")
    ($($arg:tt)+) => ($crate::log!($crate::log::Level::Info, $($arg)+))
}

#[macro_export]
macro_rules! debug {
    // debug!(target: "my_target", key1 = 42, key2 = true; "a {} event", "log")
    // debug!(target: "my_target", "a {} event", "log")
    (target: $target:expr, $($arg:tt)+) => ($crate::log::log!(target: $target, $crate::log::Level::Debug, $($arg)+));

    // debug!("a {} event", "log")
    ($($arg:tt)+) => ($crate::log!($crate::log::Level::Debug, $($arg)+))
}

#[macro_export]
macro_rules! error {
    // error!(target: "my_target", key1 = 42, key2 = true; "a {} event", "log")
    // error!(target: "my_target", "a {} event", "log")
    (target: $target:expr, $($arg:tt)+) => ($crate::log!(target: $target, $crate::Level::Error, $($arg)+));

    // error!("a {} event", "log")
    ($($arg:tt)+) => ($crate::log!($crate::log::Level::Error, $($arg)+))
}

#[macro_export]
macro_rules! trace {
    // trace!(target: "my_target", key1 = 42, key2 = true; "a {} event", "log")
    // trace!(target: "my_target", "a {} event", "log")
    (target: $target:expr, $($arg:tt)+) => ($crate::log!(target: $target, $crate::log::Level::Trace, $($arg)+));

    // trace!("a {} event", "log")
    ($($arg:tt)+) => ($crate::log!($crate::log::Level::Trace, $($arg)+))
}

#[macro_export]
macro_rules! warn {
    // warn!(target: "my_target", key1 = 42, key2 = true; "a {} event", "log")
    // warn!(target: "my_target", "a {} event", "log")
    (target: $target:expr, $($arg:tt)+) => ($crate::log!(target: $target, $crate::log::Level::Warn, $($arg)+));

    // warn!("a {} event", "log")
    ($($arg:tt)+) => ($crate::log!($crate::log::Level::Warn, $($arg)+))
}
#[macro_export]
macro_rules! log {
    // log!(target: "my_target", Level::Info, "a {} event", "log");
    (target: $target:expr, $lvl:expr, $($arg:tt)+) => ({
        let lvl = $lvl;
        if lvl <= $crate::log::STATIC_MAX_LEVEL && lvl <= $crate::log::max_level() {
            $crate::log::log(
                format_args!($($arg)+),
                lvl,
                &($target, module_path!(), file!()),
                line!(),
            );
        }
    });

    // log!(Level::Info, "a log event")
    ($lvl:expr, $($arg:tt)+) => ($crate::log!(target: module_path!(), $lvl, $($arg)+));
    ( $($arg:tt)+) => ($crate::log!(target: module_path!(), $crate::log::Level::Info, $($arg)+));
}
#[macro_export]
macro_rules! __log_key {
    // key1 = 42
    ($($args:ident)*) => {
        stringify!($($args)*)
    };
    // "key1" = 42
    ($($args:expr)*) => {
        $($args)*
    };
}
