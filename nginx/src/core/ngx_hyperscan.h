
/*
 * Copyright (C) LubinLew
 */


#ifndef _NGX_HYPERSCAN_H_INCLUDED_
#define _NGX_HYPERSCAN_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>

#include <hs.h>


#define NGX_HS_DEFAULT_SLOT (5)


typedef enum {
    NGX_HS_TYPE_REGEX = 0,  /* reguarl expression */
    NGX_HS_TYPE_LIT,        /* Pure Literals */
} ngx_hs_type_e;

typedef enum {
    NGX_HS_MODE_BLOCK    = HS_MODE_BLOCK,
    NGX_HS_MODE_STREAM   = HS_MODE_STREAM,
    NGX_HS_MODE_VECTORED = HS_MODE_VECTORED
} ngx_hs_mode_e;


typedef ngx_int_t (*ngx_database_proc)(const u_char *data, size_t len);
typedef ngx_int_t (*ngx_hs_callback)(ngx_int_t id, void *userdata);


typedef struct {
    ngx_hs_mode_e  mode;
    ngx_hs_type_e  type;
   
    hs_database_t *database;
    hs_scratch_t  *scratch;

    ngx_hs_callback handler;
} ngx_hyperscan_t;



ngx_hyperscan_t *ngx_hyperscan_create(ngx_hs_mode_e mode, ngx_hs_type_e type);
ngx_int_t ngx_hyperscan_compile(ngx_hyperscan_t *hs, const u_char *path, ngx_database_proc handler);
ngx_int_t ngx_hyperscan_scan(ngx_hyperscan_t *hs, ngx_str_t *str);
ngx_int_t ngx_hyperscan_register(ngx_hyperscan_t *hs, ngx_hs_callback cb, void *userdata);
ngx_int_t ngx_hyperscan_free(ngx_hyperscan_t *hs);
ngx_int_t ngx_hyperscan_reload(ngx_hyperscan_t *hs);
ngx_int_t ngx_hyperscan_destroy(ngx_hyperscan_t *hs);


#endif /* _NGX_HYPERSCAN_H_INCLUDED_ */
