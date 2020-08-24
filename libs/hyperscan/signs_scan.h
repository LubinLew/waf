#ifndef __SIGNS_SCAN_H__
#define __SIGNS_SCAN_H__

#include <db_common.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------*/
int waf_hs_create(const char* path);

int waf_hs_scan(const char* target, size_t length, context_t* ctx);

void waf_hs_free(void);

/*-------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif /* __SIGNS_SCAN_H__ */

