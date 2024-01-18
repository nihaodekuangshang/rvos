#include "io.h"
#include "log.h"
 void log(
    va_list args,
    enum Level level,
    unsigned int line
) 
{
	 switch (level) {
		case Info: print("\x1b[36m[Info][0] {}\x1b[0m", args);
			   break;
		case Warn : print("\x1b[33m[Warn][0] {}\x1b[0m", args);
			    break;
		case Error : print("\x1b[31m[Error][0] {}\x1b[0m", args);
			     break;
		case Debug : print("\x1b[32m[Debug][0] {}\x1b[0m", args);
			     break;
		case Trace : print("\x1b[34m[Trace][0] {}\x1b[0m", args);
			     break;
		default : print("\x1b[34m{}\x1b[0m", args);
	 };
}

const enum Level STATIC_MAX_LEVEL =  Trace; //最大等级
const char* LOG_GRAD ; //log等级
enum Level  max_level() 
{
	if(LOG_GRAD == "INFO"){
		return Info;
	}else if(LOG_GRAD == "WARN"){
		return Warn;
	} else if(LOG_GRAD == "ERROR"){
		return Error;
	} else if(LOG_GRAD == "TRACE"){
		return Trace;
	} else if(LOG_GRAD == "DEBUG"){
		return Debug;
	}else{
		return Info;
	}
}
//#[macro_export]
//macro_rules! info {
//    // info!(target: "my_target", key1 = 42, key2 = true; "a {} event", "log")
//    // info!(target: "my_target", "a {} event", "log")
//    (target: $target:expr, $($arg:tt)+) => ($crate::log::log!(target: $target, $crate::log::Level::Info, $($arg)+));
//
//    // info!("a {} event", "log")
//    ($($arg:tt)+) => ($crate::log!($crate::log::Level::Info, $($arg)+))
//}
//
//#[macro_export]
//macro_rules! debug {
//    // debug!(target: "my_target", key1 = 42, key2 = true; "a {} event", "log")
//    // debug!(target: "my_target", "a {} event", "log")
//    (target: $target:expr, $($arg:tt)+) => ($crate::log::log!(target: $target, $crate::log::Level::Debug, $($arg)+));
//
//    // debug!("a {} event", "log")
//    ($($arg:tt)+) => ($crate::log!($crate::log::Level::Debug, $($arg)+))
//}
//
//#[macro_export]
//macro_rules! error {
//    // error!(target: "my_target", key1 = 42, key2 = true; "a {} event", "log")
//    // error!(target: "my_target", "a {} event", "log")
//    (target: $target:expr, $($arg:tt)+) => ($crate::log!(target: $target, $crate::Level::Error, $($arg)+));
//
//    // error!("a {} event", "log")
//    ($($arg:tt)+) => ($crate::log!($crate::log::Level::Error, $($arg)+))
//}
//
//#[macro_export]
//macro_rules! trace {
//    // trace!(target: "my_target", key1 = 42, key2 = true; "a {} event", "log")
//    // trace!(target: "my_target", "a {} event", "log")
//    (target: $target:expr, $($arg:tt)+) => ($crate::log!(target: $target, $crate::log::Level::Trace, $($arg)+));
//
//    // trace!("a {} event", "log")
//    ($($arg:tt)+) => ($crate::log!($crate::log::Level::Trace, $($arg)+))
//}
//
//#[macro_export]
//macro_rules! warn {
//    // warn!(target: "my_target", key1 = 42, key2 = true; "a {} event", "log")
//    // warn!(target: "my_target", "a {} event", "log")
//    (target: $target:expr, $($arg:tt)+) => ($crate::log!(target: $target, $crate::log::Level::Warn, $($arg)+));
//
//    // warn!("a {} event", "log")
//    ($($arg:tt)+) => ($crate::log!($crate::log::Level::Warn, $($arg)+))
//}
//#[macro_export]
//macro_rules! log {
//    // log!(target: "my_target", Level::Info, "a {} event", "log");
//    (target: $target:expr, $lvl:expr, $($arg:tt)+) => ({
//        let lvl = $lvl;
//        if lvl <= $crate::log::STATIC_MAX_LEVEL && lvl <= $crate::log::max_level() {
//            $crate::log::log(
//                format_args!($($arg)+),
//                lvl,
//                &($target, module_path!(), file!()),
//                line!(),
//            );
//        }
//    });
//
//    // log!(Level::Info, "a log event")
//    ($lvl:expr, $($arg:tt)+) => ($crate::log!(target: module_path!(), $lvl, $($arg)+));
//    ( $($arg:tt)+) => ($crate::log!(target: module_path!(), $crate::log::Level::Info, $($arg)+));
//}
//#[macro_export]
//macro_rules! __log_key {
//    // key1 = 42
//    ($($args:ident)*) => {
//        stringify!($($args)*)
//    };
//    // "key1" = 42
//    ($($args:expr)*) => {
//        $($args)*
//    };
//}
