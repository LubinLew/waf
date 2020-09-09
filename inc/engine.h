#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/*-----------------------------------------------------------------------------------*/

typedef enum _http_field {
	HTTP_FIELD_URL = 0,
	HTTP_FIELD_QUERY_ARG_KEY,
	HTTP_FIELD_QUERY_ARG_VAL,
	HTTP_FIELD_POST_ARG_KEY,
	HTTP_FIELD_POST_ARG_VAL,
	HTTP_FIELD_COOKIE_KEY,
	HTTP_FIELD_COOKIE_VAL,
	HTTP_FIELD_HOST,
	HTTP_FILED_REFERER,
	HTTP_FIELD_USER_AGENT,
	HTTP_FIELD_CONTENT_VAL,
	HTTP_FIELD_CONTENT_LENGTH
} http_field_t;


typedef enum _risk_level {
	RISK_LVL_SUPER = 0,
	RISK_LVL_HIGH,
	RISK_LVL_MEDIUM,
	RISK_LVL_LOW
} risk_level_t;


typedef struct _signature_info {
	uint32_t id;
	uint8_t* name;
	uint8_t* pattern;
	uint8_t* flags;
	uint8_t  category_id;
	uint8_t* category_str;
	uint8_t  sub_category_id;
	uint8_t  sub_category_str;
	uint8_t* cve_id_str;
	uint8_t* description_str;
	risk_level_t risk_level;
} signature_info_t;

typedef struct _engine_mgt engine_mgt_t;

/* load signatures */
engine_mgt_t* 
waf_engine_init(void);


/* (re)load signatures */
int 
waf_engine_set_database(engine_mgt_t* mgt, const char* path);


int 
waf_engine_set_level(engine_mgt_t* mgt, risk_level_t level);


/* do your own whitelist match */
typedef int (*WHITELIST_CB)(uin32_t id);

int 
waf_engine_set_whitelist_cb(engine_mgt_t* mgt, WHITELIST_CB cb);




/* scanning */
signature_info_t* 
waf_engine_scan(engine_mgt_t* mgt, http_field_t field, uint8_t* data, size_t len);


/* cleanup */
int 
waf_engine_exit(engine_mgt_t* mgt);

/*-----------------------------------------------------------------------------------*/
#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif  /* __ENGINE_H__ */

