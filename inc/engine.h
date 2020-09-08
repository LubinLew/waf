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


typedef enum _db_type {
	DB_FMT_XML,
	DB_FMT_JSON,
	DB_FMT_MEM
} db_type_t;

/* load signatures */
int  
waf_engine_init(db_type_t type, void* arg);

/* reload signatures */
int  
waf_engine_reload(db_type_t type, void* arg);



/* hyperscan match event callback function type */
typedef int (*match_event_handler)(unsigned int id,
            unsigned long long from, unsigned long long to,
            unsigned int flags, void *context);

/* scanning */
int  
waf_engine_scan(http_field_t field,       \
			uint8_t data, size_t len,     \
			match_event_handler handler, void* context);


/* cleanup */
int  
waf_engine_exit(void);

/*-----------------------------------------------------------------------------------*/
#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif  /* __ENGINE_H__ */

