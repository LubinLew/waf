/* 
 * Internal Debug Header
 * Copyright (c) LubinLew
 *
*/
#ifndef __TF_DEBUG_H__
#define __TF_DEBUG_H__


#define __unused__  __attribute__((unused))

#ifdef __DEBUG
    typedef struct _test_util {
        char* target;
        char* match;
    }test_util_t;

    static char *_str_output(uint8_t *_start, uint8_t *_end) __unused__;
    static char *_cmp_result(void* s1, void* s2) __unused__;

    /* Debug Output Wrapper */
    char *_str_output(uint8_t *_start, uint8_t *_end) {
        static int index = 0;
        static char buf[5][1024];
        char *store = buf[(index++) % 5];
        size_t len = _end - _start;
        memcpy(store, (char *)_start, len);
        store[len] = '\0';
        return store;
    }
    
    char* _cmp_result(void* s1, void* s2) {
        if (!strcmp((char*)s1, (char*)s2)) {
            return "\033[42;0mOK\033[0m";
        }
        return "\033[32;0mNG\033[0m";
    }

    #define _DBG(fmt, ...)    printf(">>[%s:%3d]"fmt"\n", __FUNCTION__, __LINE__, __VA_ARGS__)
    #define _CORDBG(fmt, ...) printf(">>[%s:%3d]\033[7m"fmt"\033[0m\n", __FUNCTION__, __LINE__, __VA_ARGS__)
#else /* __DEBUG */
    #define _DBG(fmt, ...)
    #define _CORDBG(fmt, ...) 
#endif /* __DEBUG */

#endif /* __TF_DEBUG_H__ */

