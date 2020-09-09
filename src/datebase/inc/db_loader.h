#ifndef __DB_LOADER_H__
#define __DB_LOADER_H__

#include <engine.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------*/
typedef struct _db_mgt {
    int               version;
    int               count;
    signature_info_t* bucket;
    char*              mem_pos;
    char              memory[0];
} db_mgt_t;


int database_open(const char* db_path, db_mgt_t** pmgt);


void database_close(db_mgt_t* mgt);

/*-------------------------------------------------------------------*/
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __DB_LOADER_H__ */

