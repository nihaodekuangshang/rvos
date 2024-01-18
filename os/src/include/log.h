#ifndef __LOG__RVOS_H
#define __LOG__RVOS_H

extern const enum Level STATIC_MAX_LEVEL =  Trace; //最大等级
extern const char* LOG_GRAD ; //log等级
enum Level {
    Error = 1,
    Warn,
    Info,
    Debug,
    Trace,
};
#endif
