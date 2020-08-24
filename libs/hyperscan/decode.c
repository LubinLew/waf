#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

#include <decode.h>


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
	DECODE_URI | DECODE_HTML,
	/* HTTP_FIELD_ARGS */
	DECODE_URI | DECODE_HTML,
	/* HTTP_FIELD_COOKIE */
	DECODE_URI | DECODE_HTML,
	/* HTTP_FILED_REFERER */
	DECODE_URI | DECODE_HTML,
	/* HTTP_FIELD_USER_AGENT */
	DECODE_URI | DECODE_HTML,
	/* HTTP_FIELD_CONTENT_LENGTH */
	DECODE_URI | DECODE_HTML
};



static int http_uri_decode()
{}

static int http_html_decode()
{}

static int http_base64_decode()
{}

static int http_js_decode()
{}


int http_field_decode(http_fields_t id, const char* data)
{
	int decode_map = g_decode_map[id];

	if (decode_map|DECODE_URI) {
		http_uri_decode();
	}

	if (decode_map|DECODE_URI) {
		http_html_decode();
	}


	return 0;
}



