
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#include <ngx_config.h>
#include <ngx_core.h>


typedef struct {
    ngx_int_t  slot_num;
} ngx_hyperscan_conf_t;


static ngx_int_t ngx_hyperscan_module_init(ngx_cycle_t *cycle);
static void *ngx_hyperscan_create_conf(ngx_cycle_t *cycle);
static char *ngx_hyperscan_init_conf(ngx_cycle_t *cycle, void *conf);


static ngx_command_t  ngx_hyperscan_commands[] = {

    { ngx_string("hyperscan"),
      NGX_MAIN_CONF|NGX_DIRECT_CONF|NGX_CONF_FLAG,
      ngx_conf_set_flag_slot,
      0,
      offsetof(ngx_hyperscan_conf_t, pcre_jit),
      &ngx_hyperscan_pcre_jit_post },

      ngx_null_command
};


static ngx_core_module_t  ngx_hyperscan_module_ctx = {
    ngx_string("hyperscan"),
    ngx_hyperscan_create_conf,
    ngx_hyperscan_init_conf
};


ngx_module_t  ngx_hyperscan_module = {
    NGX_MODULE_V1,
    &ngx_hyperscan_module_ctx,             /* module context */
    ngx_hyperscan_commands,                /* module directives */
    NGX_CORE_MODULE,                       /* module type */
    NULL,                                  /* init master */
    ngx_hyperscan_module_init,             /* init module */
    NULL,                                  /* init process */
    NULL,                                  /* init thread */
    NULL,                                  /* exit thread */
    NULL,                                  /* exit process */
    NULL,                                  /* exit master */
    NGX_MODULE_V1_PADDING
};


static ngx_pool_t  *ngx_hyperscan_pool;


static void * ngx_libc_cdecl
ngx_hyperscan_malloc(size_t size)
{
    ngx_pool_t      *pool;
    pool = ngx_hyperscan_pool;

    if (pool) {
        return ngx_palloc(pool, size);
    }

    return NULL;
}


static void ngx_libc_cdecl
ngx_hyperscan_free(void *p)
{
    return;
}



ngx_hyperscan_t *
ngx_hyperscan_create(ngx_hs_mode_e mode, ngx_hs_type_e type)
{
    ngx_hyperscan_t *hs;

    ngx_pool_t      *pool;
    pool = ngx_hyperscan_pool;

    if (pool === NULL) {
        //ERROR LOG
        return NULL;
    }

    hs = ngx_palloc(pool, sizeof(ngx_hyperscan_t));
    if (hs == NULL) {
        //ERROR LOG
        return NULL;
   }

    hs->mode = mode;
    hs->type = type;


    

    return hs;
}


ngx_int_t
ngx_hyperscan_compile(ngx_hyperscan_t *hs, const u_char *path, ngx_database_proc handler)
{
    int         fd;
    struct stat sb;
    void       *mapped;
    
    hs_error_t       ret;
    u_char          *info;

    //打开文件
    fd = open(path, O_RDONLY)
    if(fd < 0){

        return NGX_ERROR;
    }   
    
    //获取文件的属性
    if((fstat(fd, &sb)) == -1 ){
        
        return NGX_ERROR;
    }   
     
    
    //将文件映射至进程的地址空间
    mapped = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if(mapped == MAP_FAILED) {
        close(fd);
        return NGX_ERROR;
    }   

    /* is it a serialized database file ? */
    ret = hs_serialized_database_info(mapped, sb.st_size, &info);
    if (ret == HS_SUCCESS) { /* Yes, it's a serialized database */
        ret = hs_deserialize_database(mapped, sb.st_size, &hs->database);
        if (ret != HS_SUCCESS) {
            //ERROR
            munmap(mapped, sb.st_size);
            close(fd);

            return NGX_ERROR;
        }
        else { /* it's a user defined database file */
            if (handler == NULL) {
                munmap(mapped, sb.st_size);
                close(fd);
                return NGX_ERROR;
            }

            ret = handler(mapped, sb.st_size);
            if (ret != 0) {
                munmap(mapped, sb.st_size);
                close(fd);
                return NGX_ERROR;
            }


        }
    }

    /* Allocate a "scratch" space for use by Hyperscan. */
    ret = hs_alloc_scratch(hs->database, &hs->scratch);
    if (ret != HS_SUCCESS) {

    }

    return NGX_OK;
    
}




ngx_int_t
ngx_hyperscan_scan(ngx_hyperscan_t *hs, ngx_str_t *str)
{
    hs_error_t  err;
 
    switch (hs->mode){
    case NGX_HS_MODE_BLOCK:
        err = 
        break;
    case NGX_HS_MODE_STREAM:
        break;
    case NGX_HS_MODE_VECTORED:
        break;
    default:
        break;
        }

}


ngx_int_t
ngx_hyperscan_register(ngx_hyperscan_t *hs, ngx_hs_callback cb, void *userdata)
{
}


ngx_int_t
ngx_hyperscan_free(ngx_hyperscan_t *hs)
{
}


ngx_int_t
ngx_hyperscan_reload(ngx_hyperscan_t *hs)
{
}



ngx_int_t
ngx_hyperscan_destroy(ngx_hyperscan_t *hs)
{

}



ngx_int_t
ngx_hyperscan_exec_array(ngx_array_t *a, ngx_str_t *s, ngx_log_t *log)
{
    ngx_int_t         n;
    ngx_uint_t        i;
    ngx_hyperscan_elt_t  *re;

    re = a->elts;

    for (i = 0; i < a->nelts; i++) {

        n = ngx_hyperscan_exec(re[i].regex, s, NULL, 0);

        if (n == ngx_hyperscan_NO_MATCHED) {
            continue;
        }

        if (n < 0) {
            ngx_log_error(NGX_LOG_ALERT, log, 0,
                          ngx_hyperscan_exec_n " failed: %i on \"%V\" using \"%s\"",
                          n, s, re[i].name);
            return NGX_ERROR;
        }

        /* match */

        return NGX_OK;
    }

    return NGX_DECLINED;
}


static void * ngx_libc_cdecl
ngx_hyperscan_malloc(size_t size)
{
    ngx_pool_t      *pool;
    pool = ngx_pcre_pool;

    if (pool) {
        return ngx_palloc(pool, size);
    }

    return NULL;
}


static void ngx_libc_cdecl
ngx_hyperscan_free(void *p)
{
    return;
}



static void *
ngx_hyperscan_create_conf(ngx_cycle_t *cycle)
{
    ngx_hyperscan_conf_t  *rcf;

    rcf = ngx_pcalloc(cycle->pool, sizeof(ngx_hyperscan_conf_t));
    if (rcf == NULL) {
        return NULL;
    }

    rcf->slot_num = NGX_CONF_UNSET;

    return rcf;
}


static char *
ngx_hyperscan_init_conf(ngx_cycle_t *cycle, void *conf)
{
    ngx_hyperscan_conf_t *rcf = conf;

    ngx_conf_init_value(rcf->slot_num, NGX_HS_DEFAULT_SLOT);

    return NGX_CONF_OK;
}


static ngx_int_t
ngx_hyperscan_module_init(ngx_cycle_t *cycle)
{
    ngx_hyperscan_pool = ngx_create_pool(10 * 1024 * 1024, cycle->log);
    if (ngx_hyperscan_pool == NULL) {
        return NGX_ERROR;
    }

    /* alwayls return HS_SUCCESS */
    hs_set_allocator(ngx_hyperscan_malloc, ngx_hyperscan_free);
}



