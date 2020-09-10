/* 
 * hyperscan
 * Copyright (c) LubinLew
 *
*/
#ifndef __HS_HEADER_H__
#define __HS_HEADER_H__

#include <db_loader.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/*-----------------------------------------------------------------------------------*/

typedef struct _hs_mgt hs_mgt_t;


int
hs_wrapper_create(db_mgt_t* mdb, hs_mgt_t** pmgt);


int 
hs_wrapper_destroy(hs_mgt_t* mgt);


signature_info_t* 
hs_wrapper_scan(hs_mgt_t* mgt, unsigned char* data, size_t length);


int
hs_wrapper_level(hs_mgt_t* mgt, risk_level_t level);


int
hs_wrapper_whitelist(hs_mgt_t* mgt, WHITELIST_CB cb);


/*-----------------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __HS_HEADER_H__ */

