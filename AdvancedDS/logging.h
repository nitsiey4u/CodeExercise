#ifndef __LOGGING_H__
#define __LOGGING_H__

#define likely(x)   __builtin_expect(!!(x),1) // for a branch optimization

#define unlikely(x) __builtin_expect(!!(x),0) // for a branch optimization

// Log specific defs
#define LOG_CATEGORY    30
#define LOG_MESSAGE     512
#define LOG_DISABLE     0
#define LOG_ENABLE      1
#define LOG_DEBUG       1
#define LOG_ERROR       2
#define LOG_INFO        3

// Check if logging is allowed
#define allow(curLvl,expLvl) likely(curLvl>=expLvl)

// print log message
#define PRINTMSG(curLvl, expLvl, fmt, args...) { \
    if(allow(curLvl, expLvl)) { \
        char outstr[LOG_MESSAGE]; \
        snprintf(outstr, LOG_MESSAGE, fmt, ##args); \
        printf("\n%s", outstr); \
    }}

// printf message
#define PRINTFMSG(fmt, args...) { \
        char outstr[LOG_MESSAGE]; \
        snprintf(outstr, LOG_MESSAGE, fmt, ##args); \
        printf("\n%s", outstr); \
    }

// log debugging message
#define DINFO(log, fmt, args...) { \
        PRINTMSG(log, LOG_DEBUG, fmt, ##args); \
    }

// log error info message
#define EINFO(log, exp, action, fmt, args...) { \
    if (unlikely(!(exp))) \
    { \
        PRINTMSG(log, LOG_ERROR, fmt, ##args); \
        action; \
    }}

// print info message
#define PINFO(log, fmt, args...) { \
        PRINTMSG(log, LOG_INFO, fmt, ##args); \
    }

#endif // __LOGGING_H__
