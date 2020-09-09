#include <engine.h>
#include <tf_header.h>
#include <db_loader.h>
#include <hs_header.h>

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


typedef struct _hs_mgt {
	risk_level_t risk_level;
	db_mgt_t*  db;
	hs_mgt_t*  hs;
	WHITELIST_CB wcb;
} engine_mgt_t;




static engine_mgt_t* g_engine_mgt;

/* load signatures */
int  
waf_engine_init(db_type_t type, void* arg)
{
	g_engine_mgt = calloc(sizeof(engine_mgt_t), 1);
	if (!g_engine_mgt) {
		perror("calloc failed, ");
		return -1;
	}

	g_engine_mgt->callback = NULL;
}

/* if error occurred, we can still use the old database */
int  
waf_engine_set_database(uint8_t* path)
{
	int ret;
	db_mgt_t*  db;
	hs_mgt_t*  hs;

	ret = database_open(path, &db);
	if (ret != 0) {
		return ret;
	}

	ret = hs_load_database(db, &hs);
	if (ret != 0) {
		return ret;
	}

	/* free old database */
	if (g_engine_mgt->hs) { /* reload */
		hs_free_database(g_engine_mgt->hs);
		g_engine_mgt->hs = NULL;
		database_close(g_engine_mgt->db);
		g_engine_mgt->db = NULL;
	}

	/* set new database */
	g_engine_mgt->hs = hs;
	g_engine_mgt->db = db;

	return 0;
}



int 
waf_engine_set_level(risk_level_t level)
{
	if (g_engine_mgt) {
		g_engine_mgt->risk_level = level;
		return 0;
	}

	return -1;
}



int 
waf_engine_set_whitelist_cb(WHITELIST_CB cb)
{
	if (g_engine_mgt) {
		g_engine_mgt->wcb = cb;
		return 0;
	}

	return -1;
}





/* scanning */
signature_info_t*   
waf_engine_scan(http_field_t field, uint8_t* data, size_t len)
{
	int map = g_decode_map[field];

	if (map & DECODE_URI) {
		data = tf_url_decode(data, &len);
	}

	if (map & DECODE_HTML) {
		data = tf_html_entity_decode(data, &len);
	}

	if (map & DECODE_JS) {
		data = tf_js_decode(data, &len);
	}

	if (map & DECODE_CSS) {
		data = tf_css_decode(data, &len);
	}

}


/* cleanup */
int  
waf_engine_exit(void)
{
	if (g_engine_mgt) {
		free(g_engine_mgt);
	}

	g_engine_mgt = NULL;

	return 0;
}


