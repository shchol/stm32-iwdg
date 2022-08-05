/*
 * defs.h
 *
 *  Created on: 30 мая 2022 г.
 *      Author: user
 */

#ifndef SRC_INC_DEFS_H_
#define SRC_INC_DEFS_H_


#ifndef __ASSEMBLY__
#include <stddef.h>
#endif

//#if !defined(__linux__) && !defined(_WIN32)
//#include <../hal/system.h>
//#endif
//#include "../hal/system.h"


//#if !defined(__LITTLE_ENDIAN__) && !defined(__BIG_ENDIAN__)
//#if defined(_WIN32)
//#define __LITTLE_ENDIAN__
//#elif defined(__linux__)
//#include <endian.h>
//#if __BYTE_ORDER == __BIG_ENDIAN
//#define __BIG_ENDIAN__
//#elif __BYTE_ORDER == __LITTLE_ENDIAN
//#define __LITTLE_ENDIAN__
//#else
//#error Unknown endianness.
//#endif
//#else
//#error Unknown endianness.
//#endif
//#endif

/* integer-valued division (with result rounding) */
#define DIV(X, Y) 		(((X) + (Y) / 2) / (Y))
#define DIVUP(X, Y) 		(((X) + (Y) - 1) / (Y))
#define MIN(X, Y) 		((X) <= (Y) ? (X) : (Y))
#define MAX(X, Y) 		((X) >= (Y) ? (X) : (Y))
#define ROUNDUP(X, Y)		(DIVUP(X, Y) * (Y))

/* concatenation macros */
#define __cat2(str1,str2)	str1##str2
#define cat2(str1,str2)		__cat2(str1,str2)
#define __cat3(str1,str2,str3)	str1##str2##str3
#define cat3(str1,str2,str3)	__cat3(str1,str2,str3)

/* sizeof for arrays */
#define sizeofarray(a)		(sizeof(a) / sizeof((a)[0]))

/* data/type/function attributes */
#if !defined(_WIN32)
#define PACKED			__attribute__((packed))
#define SECTION(x)		__attribute__((section(x)))
#define ALIGN(x)		__attribute__((aligned(x)))
#define NORETURN		__attribute__((noreturn))
//#define UNUSED			__attribute__((unused))
#define WEAK			__attribute__((weak))
#define USED			__attribute__((used))
#else
#define PACKED
#define SECTION(x)
#define ALIGN(x)
#define NORETURN
//#define UNUSED
#define USED
#endif

/* macro for making string from __LINE__ */
#define __s2(x)	#x
#define __s(x)	__s2(x)
/* macro that traces position in source file (for debug) */
#define __TRACEPOS  debug_puts_P(PSTR(__FILE__ "(" __s(__LINE__) ")\n"))
#define __ASSERT(x)	    \
	do { if (!(x)) { debug_puts("#E#: "#x); \
	__TRACEPOS; app_block(); } } while (0)

/*
    Bytes order conversion macros
*/

/* Convert a 2-byte variable stored in little-endian order to CPU format */
#define LE2CPUW(x)					\
    (((unsigned short)((unsigned char *)(x))[0]) |	\
    ((unsigned short)(((unsigned char *)(x))[1]) << 8))
#define CPU2LEW(x) LE2CPUW(x)

/* Convert a 2-byte variable stored in little-endian order to CPU format */
#ifdef __LITTLE_ENDIAN__
#define LE2CPUWX(x) (x)
#else
#define LE2CPUWX(x)			    \
    ((((unsigned short)(x) >> 8) & 0xFF) |  \
    (((unsigned short)(x) & 0xFF ) << 8))
#endif
#define CPU2LEWX(x) LE2CPUWX(x)

/* Convert a 2-byte variable stored in big-endian order to CPU format */
#define BE2CPUW(x)					\
    (((unsigned short)((unsigned char *)(x))[1]) |	\
    ((unsigned short)(((unsigned char *)(x))[0]) << 8))
#define CPU2BEW(x) BE2CPUW(x)

/* Convert a 4-byte variable stored in little-endian order to CPU format */
#define LE2CPUL(x)					\
    (((unsigned long)((unsigned char *)(x))[0]) |	\
    ((unsigned long)(((unsigned char *)(x))[1]) << 8) |	\
    ((unsigned long)(((unsigned char *)(x))[2]) << 16) |\
    ((unsigned long)(((unsigned char *)(x))[3]) << 24))
#define CPU2LEL(x) LE2CPUL(x)

/* Convert a 4-byte variable stored in big-endian order to CPU format */
#define BE2CPUL(x)					\
    (((unsigned long)((unsigned char *)(x))[3]) |	\
    ((unsigned long)(((unsigned char *)(x))[2]) << 8) |	\
    ((unsigned long)(((unsigned char *)(x))[1]) << 16) |\
    ((unsigned long)(((unsigned char *)(x))[0]) << 24))
#define CPU2BEL(x) BE2CPUL(x)

/* Convert a short integer to little-endian format and store it in RAM */
#define CPU2LEW_UNALIGNED(sv,a)				\
    ({							\
	((unsigned char*)(a))[0] = (sv) & 0xff;		\
	((unsigned char*)(a))[1] = ((sv) >>  8) & 0xff;	\
    })

/* Convert a short integer to big-endian format and store it in RAM */
#define CPU2BEW_UNALIGNED(sv,a)				\
    ({							\
	((unsigned char*)(a))[0] = ((sv) >>  8) & 0xff;	\
	((unsigned char*)(a))[1] = (sv) & 0xff;		\
    })

/* Convert a long integer to little-endian format and store it in RAM */
#define CPU2LEL_UNALIGNED(lv, a)					\
    ({									\
	((unsigned char*)(a))[0] = (unsigned long)(lv) & 0xff;		\
	((unsigned char*)(a))[1] = ((unsigned long)(lv) >> 8) & 0xff;	\
	((unsigned char*)(a))[2] = ((unsigned long)(lv) >> 16) & 0xff;	\
	((unsigned char*)(a))[3] = ((unsigned long)(lv) >> 24) & 0xff;	\
    })

/* Convert a long integer to big-endian format and store it in RAM */
#define CPU2BEL_UNALIGNED(bv, a)			\
    ({							\
	((unsigned char*)(a))[3] = (unsigned long)(bv) & 0xff;		\
	((unsigned char*)(a))[2] = ((unsigned long)(bv) >> 8) & 0xff;	\
	((unsigned char*)(a))[1] = ((unsigned long)(bv) >> 16) & 0xff;	\
	((unsigned char*)(a))[0] = ((unsigned long)(bv) >> 24) & 0xff;	\
    })


#endif /* SRC_INC_DEFS_H_ */
