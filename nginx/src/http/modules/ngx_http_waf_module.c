#include <ngx_config.h>
#include <ngx_core.h>


static ngx_http_output_header_filter_pt ngx_http_next_header_filter;
static ngx_http_output_body_filter_pt ngx_http_next_body_filter;

/* ngx_http_module_t */
#if 0
static ngx_int_t ngx_http_waf_preconfiguration(ngx_conf_t *cf);
static void* ngx_http_waf_create_main_conf(ngx_conf_t* cf);
static char* ngx_http_waf_init_main_conf(ngx_conf_t* cf, void* conf);
static void* ngx_http_waf_create_srv_conf(ngx_conf_t* cf);
static char* ngx_http_waf_merge_srv_conf(ngx_conf_t* cf, void* parent, void* child);
#endif
static ngx_int_t ngx_http_waf_module_init(ngx_conf_t *cf);

static void* ngx_http_waf_create_loc_conf(ngx_conf_t* cf);
static char* ngx_http_waf_merge_loc_conf(ngx_conf_t* cf, void* parent, void* child);

/* ngx_command_t */
char *ngx_http_waf_conf_set_flag_slot(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);



typedef struct {
	ngx_flag_t is_enable;    
} ngx_http_waf_main_conf_t;

typedef struct {
	ngx_flag_t is_enable;    
} ngx_http_waf_srv_conf_t;

typedef struct {
	ngx_flag_t is_enable;    
} ngx_http_waf_loc_conf_t;



static ngx_http_module_t ngx_http_waf_module_ctx = {
        NULL,                          /* preconfiguration */
        ngx_http_waf_module_init,      /* postconfiguration */

        NULL,                          /* create main configuration */
        NULL,                          /* init main configuration */

        NULL,                          /* create server configuration */
        NULL,                          /* merge server configuration */

        ngx_http_waf_create_loc_conf,  /* create location configuration */
        ngx_http_waf_merge_loc_conf,   /* merge location configuration */
};


static ngx_command_t ngx_http_waf_module_commands[] = {
    { ngx_string("waf"), 
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_FLAG, /* on|off */
      ngx_http_waf_conf_set_flag_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_waf_loc_conf_t, is_enable),
      NULL },

	ngx_null_command
};


ngx_module_t ngx_http_waf_module = {
        NGX_MODULE_V1,
        &ngx_http_waf_module_ctx,      /* module context */
        ngx_http_waf_module_commands,  /* module directives */
        NGX_HTTP_MODULE,               /* module type */
        NULL,                          /* init master */
        NULL,                          /* init module */
        NULL,                          /* init process */
        NULL,                          /* init thread */
        NULL,                          /* exit thread */
        NULL,                          /* exit process */
        NULL,                          /* exit master */
        NGX_MODULE_V1_PADDING
};


char *
ngx_http_waf_conf_set_flag_slot(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
	ngx_log_error(NGX_LOG_EMERG, cf->log, 0, 
			 "[set_flag_slot]cf %s conf %p", ((ngx_str_t*)cf->args->elts)[1].data, conf);

	return ngx_conf_set_flag_slot(cf, cmd, conf);
}

#if 0
static ngx_int_t 
ngx_http_waf_preconfiguration(ngx_conf_t *cf)
{
	ngx_log_error(NGX_LOG_EMERG, cf->log, 0, 
			 "[preconfiguration]cf %p", cf);

	return NGX_OK;
}

static void* 
ngx_http_waf_create_main_conf(ngx_conf_t* cf)
{
	ngx_http_waf_main_conf_t* mycf;

	mycf = (ngx_http_waf_main_conf_t*)ngx_palloc(cf->pool, sizeof(ngx_http_waf_main_conf_t));
	if (NULL == mycf) {
		return NULL;
	}

	/* must do */
	mycf->is_enable = NGX_CONF_UNSET;
	
	ngx_log_error(NGX_LOG_EMERG, cf->log, 0, 
			 "[create_main_conf]cf %p conf %p", cf, mycf);

	return mycf;
}

static char* 
ngx_http_waf_init_main_conf(ngx_conf_t* cf, void* conf)
{
	ngx_log_error(NGX_LOG_EMERG, cf->log, 0, 
			 "[init_main_conf]cf %p conf %p", cf, conf);

    return NGX_CONF_OK;
}

static void* 
ngx_http_waf_create_srv_conf(ngx_conf_t* cf)
{
	ngx_http_waf_srv_conf_t* mycf;

	mycf = (ngx_http_waf_srv_conf_t*)ngx_palloc(cf->pool, sizeof(ngx_http_waf_srv_conf_t));
	if (NULL == mycf) {
		return NULL;
	}

	/* must do */
	mycf->is_enable = NGX_CONF_UNSET;

	ngx_log_error(NGX_LOG_EMERG, cf->log, 0, 
			 "[create_srv_conf]cf %p conf %p", cf, mycf);
	
	return mycf;
}

static char* 
ngx_http_waf_merge_srv_conf(ngx_conf_t* cf, void* parent, void* child)
{
	ngx_log_error(NGX_LOG_EMERG, cf->log, 0, 
			 "[merge_srv_conf]parent %p child %p", parent, child);

    return NGX_CONF_OK;
}
#endif

static void*
ngx_http_waf_create_loc_conf(ngx_conf_t* cf)
{
	ngx_http_waf_loc_conf_t* mycf;

	mycf = (ngx_http_waf_loc_conf_t*)ngx_palloc(cf->pool, sizeof(ngx_http_waf_loc_conf_t));
	if (NULL == mycf) {
		return NULL;
	}

	/* must do */
	mycf->is_enable = NGX_CONF_UNSET;

	ngx_log_error(NGX_LOG_EMERG, cf->log, 0, 
			 "[create_loc_conf]cf %p conf %p",cf, mycf);

	return mycf;
}


static char*
ngx_http_waf_merge_loc_conf(ngx_conf_t* cf, void* parent, void* child)
{
    ngx_http_waf_loc_conf_t* prev = parent;
    ngx_http_waf_loc_conf_t* conf = child;

	
	ngx_log_error(NGX_LOG_EMERG, cf->log, 0, 
			 "[merge_loc_conf]parent %p child %p", parent, child);

    ngx_conf_merge_value(conf->is_enable, prev->is_enable, 1);
	
    return NGX_CONF_OK;
}


ngx_inline static acv_waf_ctx_t *
ngx_http_waf_create_ctx(ngx_http_request_t *r)
{
    acv_waf_ctx_t *ctx;

    /* alloc memory for waf-ctx */
    ctx = ngx_pcalloc(r->pool, sizeof(acv_waf_ctx_t));
    if (ctx == NULL) {
	    ngx_log_error(NGX_LOG_EMERG, r->connection->log, 0, "OUT OF MEMORY");
        return NULL;
    }
        
    /* connect waf-ctx with the the request */
    ngx_http_set_ctx(r, ctx, ngx_http_waf_module);

    return ctx;
}


static ngx_int_t
ngx_http_waf_check_request_header_handler(ngx_http_request_t *r)
{
    acv_waf_ctx_t* ctx;
	ngx_http_waf_loc_conf_t* cf;

	/* get conf */
	cf = ngx_http_get_module_loc_conf(r, ngx_http_waf_module);
	if (!cf->is_enable) {/* waf is disalbe */
		return NGX_DECLINED;
	}

	/* create ctx for request */
    ctx = ngx_http_waf_create_ctx(r);
	if (NULL == ctx) {
		return NGX_DECLINED;
	}

	/* check filter-policy here */
	if (acv_waf_http_filter_policy_match(r, ctx) != NGX_OK) {
		return NGX_DECLINED; /* not match the filter-policy */
	}
	
	
    return acv_waf_http_check_request_header(r, ctx);
}


void 
ngx_http_read_client_body_finish_cb(ngx_http_request_t *r)
{
    r->main->count--;
	acv_waf_ctx_t* ctx;

	/* ctx must exist here */
    ctx = ngx_http_get_module_ctx(r, ngx_http_waf_module);
	ctx->read_req_body_done = 1;
	ngx_log_error(NGX_LOG_EMERG, r->connection->log, 0, 
			 "ngx_http_read_client_body_finish_cb");

	/* continue to proc other phases */
    ngx_http_core_run_phases(r);
}


static ngx_int_t
ngx_http_waf_read_request_body_handler(ngx_http_request_t *r)
{
    ngx_int_t rc;
    acv_waf_ctx_t *ctx;
	ngx_http_waf_loc_conf_t* cf;

	/* get conf */
	cf = ngx_http_get_module_loc_conf(r, ngx_http_waf_module);
	if (!cf->is_enable) {/* waf is disalbe */
		return NGX_DECLINED;
	}

    /* just post/put method has req-body */
    if (!(r->method & (NGX_HTTP_POST | NGX_HTTP_PUT))) {
        return NGX_DECLINED;
    }
    
    /* ctx=null means no waf rules for the request */
    ctx = ngx_http_get_module_ctx(r, ngx_http_waf_module);
    if (NULL == ctx) {
        return NGX_DECLINED;
    }

	/* this request is bypassed */
	if (ctx->bypass) {
		r->request_body_no_buffering = 1;
        return NGX_DECLINED;
	}

	if (ctx->read_req_body_done) {
		return NGX_OK;
	}

    /* start to read the client body */
	rc = ngx_http_read_client_request_body(r, ngx_http_read_client_body_finish_cb);
	if (rc >= NGX_HTTP_SPECIAL_RESPONSE) {
		return rc;
	}
	else if (rc == NGX_AGAIN) {    
		return NGX_DONE;
	}

    return NGX_OK;
}


static ngx_int_t
ngx_http_waf_access_log_handler(ngx_http_request_t *r)
{
	ngx_http_waf_loc_conf_t* cf;

	/* get conf */
	cf = ngx_http_get_module_loc_conf(r, ngx_http_waf_module);
	if (!cf->is_enable) {/* waf is disalbe */
		return NGX_DECLINED;
	}
	
    return NGX_OK;
}

static ngx_int_t
ngx_http_waf_filter_header_filter(ngx_http_request_t* r)
{
	ngx_int_t rc;
	acv_waf_ctx_t *ctx;	
	ngx_http_waf_loc_conf_t* cf;

	/* get conf */
	cf = ngx_http_get_module_loc_conf(r, ngx_http_waf_module);
	if (!cf->is_enable) {/* waf is disalbe */
		return ngx_http_next_header_filter(r);
	}

    ctx = ngx_http_get_module_ctx(r, ngx_http_waf_module);
	if (NULL == ctx) {
		return ngx_http_next_header_filter(r);
	}
	
	/* this request is bypassed */
	if (ctx->bypass) {
		return ngx_http_next_header_filter(r);
	}

	rc = acv_waf_http_check_response_header(r, ctx);
	if (rc != NGX_OK) {
		return rc;
	}

	return ngx_http_next_header_filter(r);
}


static ngx_int_t
ngx_http_waf_filter_body_filter(ngx_http_request_t* r, ngx_chain_t* in)
{
	ngx_int_t rc;
	acv_waf_ctx_t *ctx;	
	ngx_http_waf_loc_conf_t* cf;

	/* get conf */
	cf = ngx_http_get_module_loc_conf(r, ngx_http_waf_module);
	if (!cf->is_enable) {/* waf is disalbe */
		return ngx_http_next_body_filter(r, in);
	}

    ctx = ngx_http_get_module_ctx(r, ngx_http_waf_module);
	if (NULL == ctx) {
		return ngx_http_next_body_filter(r, in);
	}
	
	/* this request is bypassed */
	if (ctx->bypass) {
		return ngx_http_next_body_filter(r, in);
	}

	rc = acv_waf_http_check_response_body(r, ctx);
	if (rc != NGX_OK) {
		return rc;
	}

	return ngx_http_next_body_filter(r, in);
}


static ngx_int_t 
ngx_http_waf_filter_init(ngx_conf_t* cf)
{
	ngx_http_next_header_filter = ngx_http_top_header_filter;
	ngx_http_top_header_filter = ngx_http_waf_filter_header_filter;

	ngx_http_next_body_filter = ngx_http_top_body_filter;
	ngx_http_top_body_filter = ngx_http_waf_filter_body_filter;

	return NGX_OK;
}


static ngx_int_t
ngx_http_waf_module_init(ngx_conf_t *cf)
{
    ngx_http_handler_pt        *h;
    ngx_http_core_main_conf_t  *cmcf;

    cmcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_core_module);

    /* register req-header check handler */
    h = ngx_array_push(&cmcf->phases[NGX_HTTP_POST_READ_PHASE].handlers);
    if (h == NULL) {
		ngx_log_error(NGX_LOG_EMERG, cf->log, 0, 
			     "register req-header check-handler failed");
        return NGX_ERROR;
    }
    *h = ngx_http_waf_check_request_header_handler;
	ngx_log_error(NGX_LOG_INFO, cf->log, 0,
				  "register req-header check-handler success");

    /* register req-body check handler */
    h = ngx_array_push(&cmcf->phases[NGX_HTTP_PREACCESS_PHASE].handlers);
    if (h == NULL) {
		ngx_log_error(NGX_LOG_EMERG, cf->log, 0, 
			      "register req-body check-handler failed");
        return NGX_ERROR;
    }
    *h = ngx_http_waf_read_request_body_handler;
	ngx_log_error(NGX_LOG_INFO, cf->log, 0,
				  "register req-body check-handler success");

    /* register access-log handler */
    h = ngx_array_push(&cmcf->phases[NGX_HTTP_LOG_PHASE].handlers);
    if (h == NULL) {
		ngx_log_error(NGX_LOG_EMERG, cf->log, 0, "register access-log-handler failed");
        return NGX_ERROR;
    }
    *h = ngx_http_waf_access_log_handler;
	ngx_log_error(NGX_LOG_INFO, cf->log, 0,
				  "register access-log-handler success");

	/* register response-filter handler */
	return ngx_http_waf_filter_init(cf);
}


