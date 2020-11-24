#include <ngx_config.h>
#include <ngx_core.h>


#include <ngx_list.h>
#include <ngx_log.h>



/******************************************************************************************************************************/
volatile ngx_cycle_t  *ngx_cycle;
ngx_uint_t             ngx_dump_config;
ngx_pid_t              ngx_pid;

char *ngx_syslog_process_conf(ngx_conf_t *cf, ngx_syslog_peer_t *peer){return NULL;}
void ngx_syslog_writer(ngx_log_t *log, ngx_uint_t level, u_char *buf, size_t len){return;}
ngx_int_t ngx_get_full_name(ngx_pool_t *pool, ngx_str_t *prefix, ngx_str_t *name){return 0;}
/******************************************************************************************************************************/



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
    unsigned int     i;
    ngx_pool_t      *pool;
    ngx_list_t      *list;
    ngx_list_part_t *part;
    INTER_FUNC      *func;


    pool = ngx_create_pool(1024 * 1024, NULL);
    if (pool == NULL) {
        return NGX_ERROR;
    }

    /* 创建单向链表 */
    list = ngx_list_create(pool, 2, sizeof(INTER_FUNC));
    if (list == NULL) {
        ngx_destroy_pool(pool);
        return NGX_ERROR;
    }

    /* 单向链表赋值 */
    for (i = 0; i < sizeof(functbl)/sizeof(INTER_FUNC); i++) {
        func = ngx_list_push(list);
        *func = functbl[i];
        //printf("[IN]list[%u] *%p = %p\n", i, func, functbl[i]);
    }

    /* 单向链表遍历 */
    part = &list->part;
    while(part) {
        /* 遍历一个节点 */
        func = part->elts;
        for (i = 0; i < part->nelts; i++) {
            //printf("[OUT]list[%u] *%p = %p\n", i, func + i, func[i]);
            func[i]();
        }

        /* 指向下一个节点 */
        part = part->next;
    }
    
    ngx_destroy_pool(pool);

    return 0;
}

