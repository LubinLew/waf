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
hs_create_database(db_mgt_t* mdb, hs_mgt_t** pmgt);


int 
hs_destroy_database(hs_mgt_t* mgt);


signature_info_t* 
hs_scan_database(hs_mgt_t* mgt, unsigned char* data, size_t length);


int
hs_set_scan_level(hs_mgt_t* mgt, risk_level_t level);

/*-----------------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __HS_HEADER_H__ */

