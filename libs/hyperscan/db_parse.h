#ifndef __DB_PARSE_H__
#define __DB_PARSE_H__

#include <db_common.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------*/

int mgt_open_db(const char* path, mgt_t** pmgt) ;

 void mgt_close_db(mgt_t* mgt);

/*-------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif /* __DB_PARSE_H__ */

