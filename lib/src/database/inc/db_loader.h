#ifndef __DB_LOADER_H__
#define __DB_LOADER_H__

#include <engine.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------*/
typedef struct _db_mgt {
    uint32_t          version;
    uint32_t          count;
    signature_info_t* bucket;
    uint8_t*          mem_pos;
    uint8_t           memory[0];
} db_mgt_t;


int 
signature_database_open(const char* db_path, db_mgt_t** pmgt);


int
signature_database_close(db_mgt_t* mgt);

/*-------------------------------------------------------------------*/
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __DB_LOADER_H__ */

