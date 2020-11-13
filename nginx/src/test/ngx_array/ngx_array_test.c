#include <ngx_config.h>
#include <ngx_core.h>


#include <ngx_array.h>
#include <ngx_log.h>



/******************************************************************************************************************************/
volatile ngx_cycle_t  *ngx_cycle;
ngx_uint_t             ngx_dump_config;
ngx_pid_t              ngx_pid;

char *ngx_syslog_process_conf(ngx_conf_t *cf, ngx_syslog_peer_t *peer){return NULL;}
void ngx_syslog_writer(ngx_log_t *log, ngx_uint_t level, u_char *buf, size_t len){return;}
ngx_int_t ngx_get_full_name(ngx_pool_t *pool, ngx_str_t *prefix, ngx_str_t *name){return 0;}
/******************************************************************************************************************************/

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
    ngx_uint_t     i, ret;
    ngx_pool_t   *pool;
    ngx_array_t   array;
    INTER_FUNC   *func;


    pool = ngx_create_pool(1024 * 1024, NULL);
    if (pool == NULL) {
        return NGX_ERROR;
    }


    ret = ngx_array_init(&array, pool, ARRAY_SIZE, sizeof(INTER_FUNC));
    if (ret != NGX_OK) {
        ngx_destroy_pool(pool);
        return NGX_ERROR;
    }


    for (i = 0; i < ARRAY_SIZE; i++) {
        func = ngx_array_push(&array);
        *func = functbl[i];
    }

    func = array.elts;
    for (i = 0; i < array.nelts; i++) {
        func[i]();
    }

    ngx_array_destroy(&array);
    ngx_destroy_pool(pool);

    return 0;
}

