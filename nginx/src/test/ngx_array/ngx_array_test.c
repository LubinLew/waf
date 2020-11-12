#include <ngx_array.h>

#include <ngx_config.h>

#include <ngx_log.h>


#define ARRAY_SIZE (10)

typedef void (*INTER_FUNC)(void);
static void _internal_handler_0(void){printf("%s\n", __FUNCTION__);}
static void _internal_handler_1(void){printf("%s\n", __FUNCTION__);}
static void _internal_handler_2(void){printf("%s\n", __FUNCTION__);}
static void _internal_handler_3(void){printf("%s\n", __FUNCTION__);}
static void _internal_handler_4(void){printf("%s\n", __FUNCTION__);}
static void _internal_handler_5(void){printf("%s\n", __FUNCTION__);}
static void _internal_handler_6(void){printf("%s\n", __FUNCTION__);}
static void _internal_handler_7(void){printf("%s\n", __FUNCTION__);}
static void _internal_handler_8(void){printf("%s\n", __FUNCTION__);}
static void _internal_handler_9(void){printf("%s\n", __FUNCTION__);}

static INTER_FUNC functbl[] = {
    _internal_handler_0,
    _internal_handler_1,
    _internal_handler_2,
    _internal_handler_3,
    _internal_handler_4,
    _internal_handler_5,
    _internal_handler_6,   
    _internal_handler_7,
    _internal_handler_8,
    _internal_handler_9
};

int ngx_cdecl
main(int argc, char *const *argv)
{
    ngx_int_t     i, ret;
    ngx_log_t    *log;
    ngx_pool_t   *pool;
    ngx_array_t  *array;
    INTER_FUNC   *func;


    pool = ngx_create_pool(1024 * 1024, log);
    if (pool == NULL) {
        return NGX_ERROR;
    }


    array = ngx_array_create(pool, ARRAY_SIZE, sizeof(INTER_FUNC));
    if (array == NULL) {
        ngx_destroy_pool(pool);
        return NGX_ERROR;
    }


    ret = ngx_array_init(array, pool, ARRAY_SIZE, sizeof(INTER_FUNC));
    if (ret != NGX_OK) {
        ngx_array_destroy(array);
        ngx_destroy_pool(pool);
        return ret;
    }

    for (i = 0; i < ARRAY_SIZE; i++) {
        func = ngx_array_push(array);
        *func = functbl[i];
    }

    return 0;
}

