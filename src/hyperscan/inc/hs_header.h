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
hs_load_database(db_mgt_t* db, hs_mgt_t** pmgt);

int 
hs_free_database(hs_mgt_t* pmgt)


/*-----------------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __HS_HEADER_H__ */

