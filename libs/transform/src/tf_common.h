/* 
 * Internal Header
 * Copyright (c) LubinLew
 *
*/
#ifndef __TF_COMMON_H__
#define __TF_COMMON_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


/* provide the compiler with branch prediction information */
#define likely(x)   __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
#define __unused__  __attribute__((unused))

/* function return */
#define TS_TRUE   (1)
#define TS_FALSE  (0)

/* decode to space */
#define _SP (uint8_t)(0x20)
/* decode failed */
#define _NG (uint8_t)(0xFF)


/* fast short-string compare */
#define _2cmp(_d1, _d2) *((uint16_t*)(_d1)) == *((uint16_t*)(_d2))
#define _4cmp(_d1, _d2) *((uint32_t*)(_d1)) == *((uint32_t*)(_d2))

/* internal string copy, copy range [_start, _end) */
#define _copy(_start, _end, _dst) while (_start < _end) {*(_dst++) = *(_start++);}


#ifndef __EXCLUDE_EXTERN_TBL
	extern uint8_t g_hex_charset[];
	extern uint8_t g_dec_charset[];
	extern uint8_t g_url_charset[];
	extern uint8_t g_ascii_charset[];
	extern uint8_t g_base64_charset[];
	extern uint8_t g_base64url_charset[];
#endif /* __EXCLUDE_EXTERN_TBL */

#define _chr(_ch) g_url_charset[_ch]
#define _hex(_ch) g_hex_charset[_ch]
#define _num(_ch) g_dec_charset[_ch]


/* decode Percent-Encoding data */
#define _HEX2VAL(_val1, _val2) ((uint8_t)((uint8_t)((_val1 << 4) + (_val2))))
#define _DEC2VAL(_val1, _val2) ((uint8_t)((uint8_t)((_val1 * 10) + (_val2))))
#define _HEXCHR2VAL(_val1, _val2) _HEX2VAL(_hex(_val1), _hex(_val2))

/*------------------------------------ DEBUG ---------------------------------------*/
#ifdef __DEBUG
/* Debug Output Wrapper */
static char *_str_output(uint8_t *_start, uint8_t *_end) __unused__;
static char *_str_output(uint8_t *_start, uint8_t *_end)
{
	static int index = 0;
	static char buf[5][1024];
	char *store = buf[(index++) % 5];
	size_t len = _end - _start;
	memcpy(store, (char *)_start, len);
	store[len] = '\0';
	return store;
}
#define _DBG(fmt, ...) fprintf(stderr, ">>[%s:%3d]"fmt"\n", __FUNCTION__, __LINE__, __VA_ARGS__)
#else /* __DEBUG */
	#define _DBG(fmt, ...)
#endif /* __DEBUG */


#endif /* __TF_COMMON_H__ */

