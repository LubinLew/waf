#include <engine.h>
#include <tf_header.h>


typedef enum {
	DECODE_URI    = 0x01,
	DECODE_HTML   = 0x02,
	DECODE_JS     = 0x04,
	DECODE_CSS    = 0x08,
	DECODE_BASE64 = 0x10,
} decode_flags_t;

const static int g_decode_map[] = {
	/* HTTP_FIELD_URL */
	DECODE_URI,
	/* HTTP_FIELD_HOST */
	DECODE_URI | DECODE_HTML | DECODE_JS | DECODE_CSS,
	/* HTTP_FIELD_ARGS */
	DECODE_URI | DECODE_HTML | DECODE_JS | DECODE_CSS,
	/* HTTP_FIELD_COOKIE */
	DECODE_URI | DECODE_HTML | DECODE_JS | DECODE_CSS,
	/* HTTP_FILED_REFERER */
	DECODE_URI | DECODE_HTML | DECODE_JS | DECODE_CSS,
	/* HTTP_FIELD_USER_AGENT */
	DECODE_URI | DECODE_HTML | DECODE_JS | DECODE_CSS,
	/* HTTP_FIELD_CONTENT_LENGTH */
	DECODE_URI | DECODE_HTML | DECODE_JS | DECODE_CSS,
};



/* load signatures */
int  
waf_engine_init(db_type_t type, void* arg)
{

}


/* reload signatures */
int  
waf_engine_reload(db_type_t type, void* arg)
{

}




/* scanning */
int  
waf_engine_scan(http_field_t field,
			uint8_t data, size_t len,
			match_event_handler handler, void* context)
{

}


/* cleanup */
int  
waf_engine_exit(void)
{

}

